#include "smart_layers.h"

static enum SmartSwitchMode smart_switch_mode = MODE_OFF;

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
    case KC_ENT ... KC_TAB:
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

void smart_layer_off(void) {
    assert(smart_switch_mode != MODE_OFF);
    layer_off(_EXTEND);
    smart_switch_mode = MODE_OFF;
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

void smart_layer_elapse_preroutine(uint16_t current_keycode,
        uint16_t last_keycode, keyrecord_t *record) {
    //if (HAS_EXT_TIMED_OUT()) {
    //    return true;
    //}

    assert(current_keycode != SM_EXT);
    if (!record->event.pressed || smart_switch_mode == MODE_OFF ||
            smart_switch_mode == MODE_POST) {
        return;
    }

    bool has_ext_elapsed = false;
    if (is_escape_sequence(current_keycode, last_keycode)) {
        if (smart_switch_mode == MODE_PRE) {
            smart_switch_mode = MODE_POST;
            return;
        }
        has_ext_elapsed = smart_switch_mode == MODE_INVERSE;
    } else {
        has_ext_elapsed = (smart_switch_mode == MODE_PRE) ?
            !is_same_cluster(current_keycode, last_keycode) :
            is_same_cluster(current_keycode, last_keycode);
    }

    if (has_ext_elapsed) {
        smart_layer_off();
    }
}

// pay attention to whether to process these keys on press (event.pressed)
// or release (!event.pressed)
void process_record_smart_layer_kc(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_1 ... KC_0:
    case KC_RGHT ... KC_UP:
    case KC_ENT ... KC_TAB:
    case KC_DEL:
        if (!record->event.pressed && smart_switch_mode != MODE_POST) {
            smart_switch_mode = MODE_PRE;
        }
        return;
    case SM_EXT:
        // ignore
        return;
    default:
        if (record->event.pressed) {
            smart_switch_mode = MODE_OFF;
        }
        return;
    }
}

// evaluated only on key release but executed on both key press and
// release to minimise lag
void smart_layer_postroutine(uint16_t keycode, bool has_mods,
        bool has_last_mods, keyrecord_t *record) {
    if (keycode == SM_EXT) {
        return;
    }

    if (smart_switch_mode == MODE_POST) {
        if (!has_mods) {
            smart_layer_off();
        }
        return;
    }

    if (record->event.pressed) {
        return;
    }
    bool is_keycode_osm = keycode >= QK_ONE_SHOT_MOD &&
        keycode <= QK_ONE_SHOT_MOD_MAX;
    if (has_last_mods && !is_keycode_osm) {
        smart_switch_mode = MODE_POST;
        if (!has_mods) {
            smart_layer_off();
        }
    }
}
