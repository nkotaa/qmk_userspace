#include "smart_layers.h"

//bool has_ext_post_elapsed = false;
enum SmartSwitchMode smart_switch_mode = MODE_OFF;
uint16_t last_post_switch_key;

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

bool is_same_cluster(uint16_t current_keycode, uint16_t previous_keycode) {
    if (current_keycode == SM_EXT) {
        return true;
    }

    switch (previous_keycode) {
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
            current_keycode == previous_keycode;
    case KC_ENT ... KC_BSPC:
    case KC_DEL:
    default:
        return current_keycode == previous_keycode;
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

void smart_layer_postlapse(uint16_t keycode, keyrecord_t *record) {
    if (smart_switch_mode != MODE_POST) {
        return;
    }
    // evaluate if postlapse needs to be evaluated on both key press and release
    if (!record->event.pressed) {
        return;
    }

    if (get_mods()) {
        return;
    }

    //bool has_esc_to_base = has_ext_post_elapsed ||
    //    (get_last_mods() && !get_mods());
    if (!is_same_cluster(keycode, last_post_switch_key)) {
        layer_off(_EXTEND);
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
        if (!record->event.pressed) {
            smart_switch_mode = MODE_POST;
            last_post_switch_key = keycode;
        }
        return true;
    case KC_RGHT ... KC_UP:
    case KC_ENT ... KC_TAB:
    case KC_DEL:
        if (!record->event.pressed) {
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

void smart_layer_prelapse(uint16_t current_keycode, uint16_t last_keycode, keyrecord_t *record) {
    //if (HAS_EXT_TIMED_OUT()) {
    //    return true;
    //}

    if (!record->event.pressed || get_mods()) {
        return;
    }
    if (smart_switch_mode == MODE_OFF || smart_switch_mode == MODE_POST) {
        return;
    }
    bool has_ext_elapsed = (smart_switch_mode == MODE_PRE) ?
        !is_same_cluster(current_keycode, last_keycode) : is_same_cluster(current_keycode, last_keycode);
    if (has_ext_elapsed) {
        layer_off(_EXTEND);
    }
    //else {
    //    has_ext_post_elapsed = will_ext_elapse(current_keycode, last_keycode, record);
    //}
}
