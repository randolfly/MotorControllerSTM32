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

#include "type_def_protocol.h"

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

#endif // !__BYTE_OPERATOR_H__
