#include "Util/byte_operator.h"

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

void float_array_to_uint8_array(float *src_float_array, uint8_t *dst, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) {
        float_to_uint8_array(src_float_array[i], dst + i * 4);
    }
}

void uint8_array_to_float_array(uint8_t *src_byte_array, float *dst, uint16_t byte_len)
{
    for (uint16_t i = 0; i < byte_len / 4; i++) {
        dst[i] = uint8_array_to_float(src_byte_array + i * 4);
    }
}

void uint8_array_to_name_string(uint8_t *src_byte_array, char *dst, uint16_t byte_len)
{
    memcpy(dst, src_byte_array, byte_len);
    src_byte_array[byte_len] = '\0';
}

void name_string_to_uint8_array(char *src_name_string_array, uint8_t *dst, uint16_t string_len)
{
    memcpy(dst, src_name_string_array, string_len);
}
