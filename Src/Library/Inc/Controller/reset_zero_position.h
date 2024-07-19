#ifndef __RESET_ZERO_POSITION_H__
#define __RESET_ZERO_POSITION_H__

#include <math.h>
#include "Util/type_def_protocol.h"
#include "Motion/motor.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RESET_ZERO_HOLDON,
    RESET_ZERO_MOVEMENT,
    RESET_ZERO_FETCH_ZERO,
} reset_zero_position_state_t;

typedef struct {
    uint8_t execute;          // execute the reset zero position
    uint8_t reach_ideal_zero; // reach the ideal zero position(z signal)
} reset_zero_position_event_t;

typedef struct
{
    double ideal_zero_position; // Z signal position
    double target_velocity;     // velocity to move to the zero position
} reset_zero_position_param_t;

typedef struct {
    reset_zero_position_state_t state;
    reset_zero_position_event_t event;
    reset_zero_position_param_t param;
} reset_zero_position_machine_t;

/**
 * @brief init the reset zero position machine with HOLDON state
 * @param  reset_zero_position_machine: reset zero position machine
 */
void init_reset_zero_position_machine(reset_zero_position_machine_t *reset_zero_position_machine);

/**
 * @brief update the reset zero position machine
 * @param  reset_zero_position_machine: reset zero position machine
 * @param  motor: motor
 */
void update_reset_zero_position_machine(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor);

/* ============= STATE ACTIONS ============= */

void holdon_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor);

void movement_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor);

void fetch_zero_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor);

/* ============= STATE TRANSLATION ACTIONS ============= */

void holdon_to_movement_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor);

void movement_to_fetch_zero_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor);

void fetch_zero_to_holdon_action(reset_zero_position_machine_t *reset_zero_position_machine, motor_t *motor);

#ifdef _cplusplus
}
#endif
#endif // !__RESET_ZERO_POSITION_H__