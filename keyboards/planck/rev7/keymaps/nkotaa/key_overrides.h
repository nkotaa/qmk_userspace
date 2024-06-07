#include QMK_KEYBOARD_H

const key_override_t grave_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_GRV);
const key_override_t circumflex_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_CIRC);
const key_override_t dollar_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_DLR);
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
    &grave_key_override,
    &circumflex_key_override,
    &dollar_key_override,
    &delete_key_override,
    NULL
};
