#ifndef COMBOS_H
#define COMBOS_H

#include QMK_KEYBOARD_H

#include "custom_keycodes.h"

enum combos {
    WF_CURLY_BRACE_CLOSE,
    XC_ANGLE_BRACK_CLOSE,
    UY_PAREN_CLOSE,
    COMDOT_BRACK_CLOSE,
    TN_OSM_GUI_TO_BASE,
    TE_OSM_CTL_TO_BASE,
    TI_OSM_ALT_TO_BASE
};

// left hand combos
const uint16_t PROGMEM wf_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cd_combo[] = {KC_C, KC_D, COMBO_END};
// right hand combos
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM uy_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM hcom_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM comdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
// both hand combos, mod-tap versions for now
const uint16_t PROGMEM tn_combo[] = {LGUI_T(KC_T), RGUI_T(KC_N), COMBO_END};
const uint16_t PROGMEM te_combo[] = {LGUI_T(KC_T), RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM ti_combo[] = {LGUI_T(KC_T), RALT_T(KC_I), COMBO_END};

combo_t key_combos[] = {
    [WF_CURLY_BRACE_CLOSE] = COMBO(wf_combo, CURLY_BRACE_CLOSE),
    [XC_ANGLE_BRACK_CLOSE] = COMBO(xc_combo, ANGLE_BRACK_CLOSE),
    [UY_PAREN_CLOSE] = COMBO(uy_combo, PAREN_CLOSE),
    [COMDOT_BRACK_CLOSE] = COMBO(comdot_combo, BRACK_CLOSE),
    [TN_OSM_GUI_TO_BASE] = COMBO(tn_combo, OSM_GUI_TO_BASE),
    [TE_OSM_CTL_TO_BASE] = COMBO(te_combo, OSM_CTL_TO_BASE),
    [TI_OSM_ALT_TO_BASE] = COMBO(ti_combo, OSM_ALT_TO_BASE)
};

uint8_t combo_ref_from_layer(uint8_t);

#endif /* COMBOS_H */
