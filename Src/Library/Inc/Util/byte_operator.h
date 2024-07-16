/**
 * @file byte_operator.h
 * @brief contains byte operators, used for operating bytes
 *  provides byte<->double<->string conversion functionality
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __BYTE_OPERATOR_H__
#define __BYTE_OPERATOR_H__

#include <string.h>
#include "Util/type_def_protocol.h"
#include "Protocol/protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief transfer double to uint8_t array
 * @param  src_double: src double data
 * @param  dst: target uint8_t array, insert 4 bytes
 */
void double_to_uint8_array(double src_double, uint8_t *dst);

/**
 * @brief transfer uint8_t array to double
 * @param  src_byte_array: src byte array, insert 4 bytes
 */
double uint8_array_to_double(uint8_t *src_byte_array);

/**
 * @brief transfer double array to uint8_t array
 * @param  src_double_array: src double array
 * @param  dst: target uint8_t array
 * @param  len: length of double array
 */
void double_array_to_uint8_array(double *src_double_array, uint8_t *dst, uint16_t double_len);

/**
 * @brief transfer double array to uint8_t array
 * @param  src_byte_array: src byte array
 * @param  dst: target double array
 * @param  len: length of byte array
 */
void uint8_array_to_double_array(uint8_t *src_byte_array, double *dst, uint16_t byte_len);

/**
 * @brief transfer uint8_t array to name string list: [0x00, 0x01, 0x02] -> "kp, ki, kd". note the sep is inside in the byte array, default is ','
 * @param  src_byte_array: src byte array
 * @param  dst: target name string, the memeory will be allocated inside
 * @param  byte_len: length of byte array
 */
void uint8_array_to_name_string(uint8_t *src_byte_array, char *dst, uint16_t byte_len);

/**
 * @brief transfer name string list to uint8_t array: "kp, ki, kd" -> [0x00, 0x01, 0x02]
 * @param  src_name_string_array: src name string
 * @param  dst: target uint8_t array
 * @param  byte_len: length of string array(byte size)
 */
void name_string_to_uint8_array(char *src_name_string_array, uint8_t *dst, uint16_t string_len);

#ifdef _cplusplus
}
#endif

#endif // !__BYTE_OPERATOR_H__
