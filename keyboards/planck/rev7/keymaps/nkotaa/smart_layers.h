#ifndef SMART_LAYERS_H
#define SMART_LAYERS_H

#include <assert.h>

#include QMK_KEYBOARD_H

#include "alias.h"

#define IS_SMART_LAYER_ON() (get_highest_layer(layer_state) == _EXTEND)
#define EXTEND_LAYER_LAZY_TIMEOUT 60000
#define HAS_EXT_TIMED_OUT() (IS_SMART_LAYER_ON() && (last_matrix_activity_elapsed() > EXTEND_LAYER_LAZY_TIMEOUT))

enum SmartSwitchMode {
    MODE_OFF,
    MODE_PRE,
    MODE_POST,
    MODE_INVERSE
};

void smart_layer_elapse_preroutine(uint16_t, uint16_t, keyrecord_t*);
void smart_layer_postlapse(uint16_t, bool, bool, keyrecord_t*);
bool process_record_smart_layer_kc(uint16_t, keyrecord_t*);
void pre_process_sm_ext_kc(uint16_t, keyrecord_t*);

#endif /* SMART_LAYERS_H */
