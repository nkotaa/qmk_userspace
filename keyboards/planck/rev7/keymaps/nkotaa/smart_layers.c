#include "smart_layers.h"

static enum SmartSwitchMode smart_switch_mode = MODE_OFF;
static bool has_ext_post_elapsed = false;

bool is_same_cluster(uint16_t current_keycode, uint16_t last_keycode) {
    switch (last_keycode) {
    case KC_RGHT ... KC_LEFT:
        return current_keycode == KC_BSPC || current_keycode == KC_DEL ||
            (current_keycode >= KC_RGHT && current_keycode <= KC_UP);
    case KC_DOWN ... KC_UP:
        return (current_keycode >= KC_RGHT && current_keycode <= KC_UP);
    case KC_1 ... KC_0:
        return (current_keycode >= KC_1 && current_keycode <= KC_0) ||
            current_keycode == KC_BSPC;
    case KC_TAB:
        return current_keycode == last_keycode;
    case KC_ENT ... KC_BSPC:
    case KC_DEL:
    default:
        return current_keycode == last_keycode;
    }
}

bool is_escape_sequence(uint16_t current_keycode, uint16_t last_keycode) {
    switch (last_keycode) {
    case KC_DOWN ... KC_UP:
    case KC_TAB:
        return current_keycode == KC_ENT;
    case KC_1 ... KC_0:
        return current_keycode == KC_UP || current_keycode == KC_DOWN;
    default:
        return false;
    }
}

void pre_process_sm_ext_kc(uint16_t keycode, keyrecord_t *record) {
    assert(keycode == SM_EXT);
    if (!record->event.pressed) {
        return;
    }
    if (!IS_SMART_LAYER_ON()) {
        layer_on(_EXTEND);
    } else {
        smart_switch_mode = MODE_INVERSE;
    }
}

void smart_layer_elapse_preroutine(uint16_t current_keycode, uint16_t last_keycode, keyrecord_t *record) {
    //if (HAS_EXT_TIMED_OUT()) {
    //    return true;
    //}

    if (!record->event.pressed || smart_switch_mode == MODE_OFF) {
        return;
    }
    bool has_ext_elapsed = false;
    bool is_from_same_cluster = is_same_cluster(current_keycode, last_keycode);
    switch (smart_switch_mode) {
    case MODE_OFF:
        return;
    case MODE_POST:
        return;
    case MODE_INVERSE:
        has_ext_elapsed = is_from_same_cluster;
        break;
    case MODE_PRE:
        if (is_from_same_cluster) {
            return;
        }
        if (is_escape_sequence(current_keycode, last_keycode)) {
            smart_switch_mode = MODE_POST;
            has_ext_post_elapsed = true;
            return;
        }
        has_ext_elapsed = true;
        break;
    }
    if (has_ext_elapsed) {
        layer_off(_EXTEND);
        smart_switch_mode = MODE_OFF;
    }
}

// pay attention to whether to process these keys on press (event.pressed)
// or release (!event.pressed)
bool process_record_smart_layer_kc(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case OSM_SFT:
    case OSM_ALT:
    case OSM_GUI:
    case OSM_CTL:
        if (record->event.pressed) {
            smart_switch_mode = MODE_POST;
        }
        return true;
    case KC_1 ... KC_0:
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

// needs to be evaluated and executed on both key press and release to avoid lag
void smart_layer_postlapse(uint16_t keycode, bool has_mods, bool has_last_mods, keyrecord_t *record) {
    if (smart_switch_mode != MODE_POST) {
        return;
    }
    if (has_ext_post_elapsed && !has_mods) {
        layer_off(_EXTEND);
        smart_switch_mode = MODE_OFF;
        has_ext_post_elapsed = false;
        return;
    }
    bool is_keycode_osm = keycode == OSM_SFT || keycode == OSM_ALT ||
        keycode == OSM_GUI || keycode == OSM_CTL;
    has_ext_post_elapsed = has_ext_post_elapsed || (has_last_mods && !is_keycode_osm);
}
