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

#include "Util/type_def_protocol.h"
#include "Motion/encoder.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t enable_torque_limit;
    uint8_t enable_velocity_limit;
    uint8_t enable_position_limit;

    double max_torque;
    double min_torque;
    double max_velocity;
    double min_velocity;
    double max_position;
    double min_position;
} motion_limit_t;

typedef struct
{
    motion_limit_t *motion_limit;
} motor_config_t;

typedef struct
{
    double target_torque;   /* target torque (unit: 1/1000 rated-torque), clock-wise -> + */
    double target_velocity; /* target velocity (unit: rad/s), clock-wise -> + */
    double target_position; /* target position (unit: rad), clock-wise -> + */

} motor_param_t;

typedef struct {
    /* data region */
    motor_param_t *motor_param;
    /* hardware(wire-pin, sensor) region */
    encoder_t *encoder;

    /* config region */
    motor_config_t *motor_config;
} motor_t;

/**
 * @brief check if the motor exceeds the limit
 * @param  motor: motor instance
 * @param  motion_limit: motor_limit_instance
 * @return uint8_t: 0: safe, 0b00000001: torque exceeds max, 0b00000010: velocity exceeds max, 0b00000100: position exceeds max
 * 0b10000001: torque exceeds min, 0b10000010: velocity exceeds min, 0b10000100: position exceeds min
 */
uint8_t check_motion_limit(motor_t *motor, motion_limit_t *motion_limit);

/**
 * @brief convert torque ratio() to actual dac output
 * @param torque_permillage: torque permillage: 1000->0xFF, -1000->0x00
 * @return uint32_t: dac target value, [0x00, 0xFF] (2^16)
 */
uint16_t torque_permillage_to_dac(double torque_permillage);

#ifdef _cplusplus
}
#endif

#endif // !__MOTOR_UTIL_H__
