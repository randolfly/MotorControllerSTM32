#ifndef __SAFETY_H__
#define __SAFETY_H__

#include "Util/type_def_protocol.h"
#include "Motion/motor.h"

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

    float max_torque;
    float min_torque;
    float max_velocity;
    float min_velocity;
    float max_position;
    float min_position;
} motion_limit_t;

/**
 * @brief check if the motor exceeds the limit
 * @param  motor: motor instance
 * @param  motion_limit: motor_limit_instance
 * @return uint8_t: 0: safe, 0b00000001: torque exceeds max, 0b00000010: velocity exceeds max, 0b00000100: position exceeds max
 * 0b10000001: torque exceeds min, 0b10000010: velocity exceeds min, 0b10000100: position exceeds min
 */
uint8_t check_motion_limit(motor_t *motor, motion_limit_t *motion_limit);

#ifdef _cplusplus
}
#endif

#endif