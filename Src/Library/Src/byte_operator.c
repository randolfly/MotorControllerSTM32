#include "byte_operator.h"

float uint8_array_to_float(uint8_t *src_byte_array)
{
    float result = 0.0f;
    memcpy(&result, src_byte_array, 4);
    result = (float)result;
    return result;
}

void float_to_uint8_array(float src_float, uint8_t *dst)
{
    union {
        float src_float;
        uint8_t dst_byte_array[4];
    } tmp_union;
    tmp_union.src_float = src_float;
    memcpy(dst, tmp_union.dst_byte_array, 4);
}
