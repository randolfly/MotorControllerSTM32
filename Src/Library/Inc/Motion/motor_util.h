/**
 * @file motor_util.h
 * @brief provide motor utils functions
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-06-26
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __MOTOR_UTIL_H__
#define __MOTOR_UTIL_H__

#include "type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief convert torque ratio() to actual dac output
 * @param torque_permillage: torque permillage: 1000->4096, -1000->0
 * @return uint32_t: dac target value, [0, 4096] (2^12)
 */
uint32_t torque_permillage_to_dac(float torque_permillage);

#ifdef _cplusplus
}
#endif

#endif // !__MOTOR_UTIL_H__
