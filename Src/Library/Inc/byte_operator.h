/**
 * @file byte_operator.h
 * @brief
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
#include "type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

// max variable name size, such as hello is valid, hellohellohellohellohello is invalid
#define MaxVariableNameSize 20

/**
 * @brief transfer float to uint8_t array
 * @param  src_float: src float data
 * @param  dst: target uint8_t array
 */
void float_to_uint8_array(float src_float, uint8_t *dst);

/**
 * @brief transfer uint8_t array to float
 * @param  src_byte_array: src byte array
 */
float uint8_array_to_float(uint8_t *src_byte_array);

/**
 * @brief transfer float array to uint8_t array
 * @param  src_float_array: src float array
 * @param  dst: target uint8_t array
 * @param  len: length of float array
 */
void float_array_to_uint8_array(float *src_float_array, uint8_t *dst, uint16_t float_len);

/**
 * @brief transfer float array to uint8_t array
 * @param  src_byte_array: src byte array
 * @param  dst: target float array
 * @param  len: length of byte array
 */
void uint8_array_to_float_array(uint8_t *src_byte_array, float *dst, uint16_t byte_len);

//! just send 1d char array!!!!

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

#endif // !__BYTE_OPERATOR_H__
