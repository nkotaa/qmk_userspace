#include "smart_layers.h"

static enum SmartSwitchMode smart_switch_mode = MODE_OFF;
static bool has_ext_post_elapsed = false;

void pre_process_sm_ext_kc(uint16_t keycode, keyrecord_t *record) {
    assert(keycode == SM_EXT);
    // only process smart layer actions once (on key press)
    if (!record->event.pressed) {
        return;
    }

    if (!IS_SMART_LAYER_ON()) {
        layer_on(_EXTEND);
        smart_switch_mode = MODE_OFF;
    } else {
        smart_switch_mode = MODE_INVERSE;
    }
}

//void smart_ext_off(void) {
//    has_ext_post_elapsed = false;
//    set_last_mods(0);
//    layer_off(_EXTEND);
//}

bool is_same_cluster(uint16_t current_keycode, uint16_t last_keycode) {
    if (current_keycode == SM_EXT) {
        return true;
    }

    switch (last_keycode) {
    case KC_RGHT ... KC_LEFT:
        return current_keycode == KC_BSPC || current_keycode == KC_DEL ||
            (current_keycode >= KC_RGHT && current_keycode <= KC_UP);
    case KC_DOWN ... KC_UP:
        return current_keycode == KC_ENT ||
            (current_keycode >= KC_RGHT && current_keycode <= KC_UP);
    case KC_1 ... KC_0:
        return current_keycode >= KC_1 && current_keycode <= KC_0;
    case OSM_SFT:
    case OSM_ALT:
    case OSM_GUI:
    case OSM_CTL:
        return current_keycode == OSM_SFT || current_keycode == OSM_ALT ||
            current_keycode == OSM_GUI || current_keycode == OSM_CTL;
    case KC_TAB:
        return current_keycode == KC_ENT ||
            current_keycode == last_keycode;
    case KC_ENT ... KC_BSPC:
    case KC_DEL:
    default:
        return current_keycode == last_keycode;
    }
}

//bool has_esc_to_base(uint16_t keycode, keyrecord_t *record) {
//    if (has_ext_post_elapsed) {
//        return true;
//    }
//    if (get_last_mods()) {
//        return !get_mods();
//    }
//    return false;
//}

void smart_layer_postlapse(uint16_t keycode, bool has_mods, keyrecord_t *record) {
    if (smart_switch_mode != MODE_POST) {
        return;
    }
    // postlapse is only executed on key release
    if (record->event.pressed) {
        return;
    }
    if (has_ext_post_elapsed && !has_mods) {
        layer_off(_EXTEND);
        has_ext_post_elapsed = false;
    }
}

// pay attention to whether to process these keys on press (event.pressed)
// or release (!event.pressed)
bool process_record_smart_layer_kc(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_1 ... KC_0:
    case OSM_SFT:
    case OSM_ALT:
    case OSM_GUI:
    case OSM_CTL:
        if (record->event.pressed) {
            smart_switch_mode = MODE_POST;
        }
        return true;
    case KC_RGHT ... KC_UP:
    case KC_ENT ... KC_TAB:
    case KC_DEL:
        if (!record->event.pressed && smart_switch_mode != MODE_POST) {
            smart_switch_mode = MODE_PRE;
        }
        return true;
    default:
        return false;
    }
}

//bool has_ext_elapsed(uint16_t current_keycode, uint16_t last_keycode, keyrecord_t *record) {
//    switch (smart_switch_mode) {
//    case MODE_PRE:
//        return !is_same_cluster(current_keycode, last_keycode);
//    case MODE_INVERSE:
//        return is_same_cluster(current_keycode, last_keycode);
//    case MODE_OFF:
//    case MODE_POST:
//    default:
//        return false;
//    }
//}

//bool will_ext_elapse(uint16_t current_keycode, uint16_t last_keycode, keyrecord_t *record) {
//    if (smart_switch_mode != MODE_POST) {
//        return false;
//    }
//
//    return false;
//    switch (last_keycode) {
//    case KC_1 ... KC_0:
//        return !is_same_cluster(current_keycode, last_keycode);
//    default:
//        return false;
//    }
//}

void smart_layer_elapse_preroutine(uint16_t current_keycode, uint16_t last_keycode, keyrecord_t *record) {
    //if (HAS_EXT_TIMED_OUT()) {
    //    return true;
    //}

    if (!record->event.pressed || get_mods() || smart_switch_mode == MODE_OFF) {
        return;
    }
    if (smart_switch_mode == MODE_POST) {
        has_ext_post_elapsed = has_ext_post_elapsed || !is_same_cluster(current_keycode, last_keycode);
        return;
    }
    bool has_ext_elapsed = (smart_switch_mode == MODE_PRE) ?
        !is_same_cluster(current_keycode, last_keycode) : is_same_cluster(current_keycode, last_keycode);
    if (has_ext_elapsed) {
        layer_off(_EXTEND);
    }
}
