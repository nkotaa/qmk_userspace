#include "alias.h"

uint8_t combo_ref_from_layer(uint8_t layer){
    switch (get_highest_layer(layer_state)) {
    case _EXTEND:
        return _BASE;
    default:
        return layer;
    }
}
