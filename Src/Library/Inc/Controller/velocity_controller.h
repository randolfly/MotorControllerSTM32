#ifndef __VELOCITY_CONTROLLER_H__
#define __VELOCITY_CONTROLLER_H__

#include <stdlib.h>
#include "VelocityController.h"

#include "Util/type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    VelocityController_RT_MODEL *model;
    VelocityController_DW *state;
} velocity_controller_t;

/**
 * @brief init the model
 * @param  velocity_controller: velocity_controller_t instance
 */
void init_velocity_controller(velocity_controller_t *velocity_controller);

/**
 * @brief deinit the model
 * @param  velocity_controller: velocity_controller_t instance
 */
void deinit_velocity_controller(velocity_controller_t *velocity_controller);

/**
 * @brief execution 1 step of velocity controller
 * @param  velocity_controller: velocity_controller_t instance
 * @param  vel_ref: velocity reference
 * @param  vel_feed: velocity feedback
 * @param  torque_command: torque command calculation result(pointer)
 */
void step_velocity_controller(velocity_controller_t *velocity_controller,
                              real_T vel_ref, real_T vel_feed, real_T *torque_command);
#ifdef _cplusplus
}
#endif
#endif // !__VELOCITY_CONTROLLER_H__