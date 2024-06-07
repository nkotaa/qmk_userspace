#include "custom_keycodes.h"

bool process_record_custom_kc(uint16_t keycode, keyrecord_t *record) {
    if (!(record->event.pressed)) {
        // do nothing on release
        return false;
    }

    switch (keycode) {
    case PAREN_CLOSE:
        SEND_STRING("()" SS_TAP(X_LEFT));
        return true;
    case CURLY_BRACE_CLOSE:
        SEND_STRING("{}" SS_TAP(X_LEFT));
        return true;
    case ANGLE_BRACK_CLOSE:
        SEND_STRING("<>" SS_TAP(X_LEFT));
        return true;
    case BRACK_CLOSE:
        SEND_STRING("[]" SS_TAP(X_LEFT));
        return true;
    case SCOPE:
        SEND_STRING("::");
        return true;
    case PARENT_DIRECTORY:
        SEND_STRING("../");
        return true;
    case HOME_DIRECTORY:
        SEND_STRING("~/");
        return true;
    case RETURN:
        SEND_STRING("return");
        return true;
    case BRACKET_COMPLETE:
        SEND_STRING("INCOMPLETE;");
        return true;
    case OSM_GUI_TO_BASE:
        layer_move(_BASE);
        add_oneshot_mods(MOD_MASK_GUI);
        return true;
    case OSM_CTL_TO_BASE:
        layer_move(_BASE);
        add_oneshot_mods(MOD_MASK_CTRL);
        return true;
    case OSM_ALT_TO_BASE:
        layer_move(_BASE);
        add_oneshot_mods(MOD_MASK_ALT);
        return true;
    default:
        return false;
    }
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
    case SMART_EXTEND:
        // to explore another possibility of returning false from post_process_smart_layer
        //return false;
    default:
        return true;
    }
}
