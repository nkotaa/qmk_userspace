#ifndef CUSTOM_KEYCODES_H
#define CUSTOM_KEYCODES_H

#include QMK_KEYBOARD_H

#include "alias.h"

enum custom_keycodes {
    PAREN_CLOSE = SAFE_RANGE,
    CURLY_BRACE_CLOSE,
    ANGLE_BRACK_CLOSE,
    BRACK_CLOSE,
    SCOPE,
    HOME_DIRECTORY,
    RETURN,
    PARENT_DIRECTORY,
    BRACKET_COMPLETE,
    OSM_GUI_TO_BASE,
    OSM_CTL_TO_BASE,
    OSM_ALT_TO_BASE,
    SMART_EXTEND
};

bool remember_last_key_user(uint16_t, keyrecord_t*, uint8_t*);
bool process_record_custom_kc(uint16_t, keyrecord_t*);

#endif /* CUSTOM_KEYCODES_H */
