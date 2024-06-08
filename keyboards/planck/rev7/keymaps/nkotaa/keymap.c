#include QMK_KEYBOARD_H

#include "alias.h"
#include "smart_layers.h"
#include "custom_keycodes.h"
#include "combos.h"
#include "key_overrides.h"

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_planck_grid(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    XXXXXXX, XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
    KC_A,    HOME_R,  HOME_S,  HOME_T,  KC_G,    XXXXXXX, XXXXXXX, KC_M,    HOME_N,  HOME_E,  HOME_I,  KC_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    XXXXXXX, XXXXXXX, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
    XXXXXXX, XXXXXXX, OSM_SFT, SM_EXT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  ASCI,    XXXXXXX, XXXXXXX 
    ),

[_EXTEND] = LAYOUT_planck_grid(
    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    _______, _______, KC_9,    KC_0,    KC_1,    KC_2,    KC_3,
    OSM_SFT, OSM_ALT, OSM_CTL, OSM_GUI, XXXXXXX, _______, _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_UNDO, KC_PSTE, KC_COPY, KC_ESC,  XXXXXXX, _______, _______, KC_PGDN, KC_ENT,  KC_BSPC, KC_TAB,  KC_DEL,
    _______, _______, BASE,    KC_TRNS, _______, _______, _______, _______, KC_TRNS, KC_TRNS, _______, _______
    ),

[_ASCII] = LAYOUT_planck_grid(
    KC_RBRC, KC_LCBR, KC_RCBR, KC_AMPR, KC_HASH, _______, _______, KC_TILD, KC_PERC, KC_LBRC, KC_ASTR, KC_BSLS,
    KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  XXXXXXX, _______, _______, XXXXXXX, KC_LPRN, KC_COLN, KC_UNDS, KC_QUES,
    KC_RPRN, KC_LABK, KC_RABK, KC_PIPE, XXXXXXX, _______, _______, XXXXXXX, RETURN,  SCOPE,   HOM_DIR, KC_AT,
    _______, _______, PAR_DIR, KC_SCLN, _______, _______, _______, _______, BASE,    BR_COMP, QK_BOOT, _______
    )
};
/* clang-format on */

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SM_EXT) {
        pre_process_sm_ext_kc(keycode, record);
        return false;
    }
    if (IS_SMART_LAYER_ON()) {
        smart_layer_elapse_preroutine(keycode, get_last_keycode(), record);
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_SMART_LAYER_ON()) {
        process_record_smart_layer_kc(keycode, record);
    }
    process_record_custom_kc(keycode, record);
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_SMART_LAYER_ON()) {
        smart_layer_postlapse(keycode, get_mods(), record);
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case OSM_SFT:
        return 300;
    default:
        return TAPPING_TERM;
    }
}
