#include "Util/byte_operator.h"

double uint8_array_to_double(uint8_t *src_byte_array)
{
    double result = 0.0f;
    memcpy(&result, src_byte_array, DATALOG_DATA_TYPE_SIZE);
    result = (double)result;
    return result;
}

void double_to_uint8_array(double src_double, uint8_t *dst)
{
    union {
        double src_double;
        uint8_t dst_byte_array[DATALOG_DATA_TYPE_SIZE];
    } tmp_union;
    tmp_union.src_double = src_double;
    memcpy(dst, tmp_union.dst_byte_array, DATALOG_DATA_TYPE_SIZE);
}

void double_array_to_uint8_array(double *src_double_array, uint8_t *dst, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) {
        double_to_uint8_array(src_double_array[i], dst + i * DATALOG_DATA_TYPE_SIZE);
    }
}

void uint8_array_to_double_array(uint8_t *src_byte_array, double *dst, uint16_t byte_len)
{
    for (uint16_t i = 0; i < byte_len / DATALOG_DATA_TYPE_SIZE; i++) {
        dst[i] = uint8_array_to_double(src_byte_array + i * DATALOG_DATA_TYPE_SIZE);
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
