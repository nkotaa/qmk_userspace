#ifndef ALIAS_H
#define ALIAS_H

#include QMK_KEYBOARD_H

#include "custom_keycodes.h"

// left-hand mod-taps
#define HOME_T LGUI_T(KC_T)
#define HOME_S LCTL_T(KC_S)
#define HOME_R LALT_T(KC_R)
// right-hand mod-taps
#define HOME_N RGUI_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I RALT_T(KC_I)

#define OSM_SFT OSM(MOD_LSFT)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)

#define BASE TO(_BASE)
#define EXT TG(_EXTEND)
#define ASCI OSL(_ASCII)
#define HOME_LF LT(0, KC_LEFT)
#define SYM_BSP LT(_ASCII, KC_BSPC)

enum layers {
    _BASE,
    _EXTEND,
    _ASCII
};

#define PAR_DIR PARENT_DIRECTORY
#define BR_COMP BRACKET_COMPLETE
#define HOM_DIR HOME_DIRECTORY
#define SM_EXT SMART_EXTEND

#endif /* ALIAS_H */
