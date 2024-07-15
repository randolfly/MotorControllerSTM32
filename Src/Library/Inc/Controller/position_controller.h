#ifndef __POSITION_CONTROLLER_H__
#define __POSITION_CONTROLLER_H__

#include <stdlib.h>
#include "PositionController.h"

#include "Util/type_def_protocol.h"

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    PositionController_RT_MODEL *model;
    PositionController_DW *state;
} position_controller_t;

/**
 * @brief init the model
 * @param  position_controller: position_controller_t instance
 */
void init_position_controller(position_controller_t *position_controller);

/**
 * @brief deinit the model
 * @param  position_controller: position_controller_t instance
 */
void deinit_position_controller(position_controller_t *position_controller);

/**
 * @brief execution 1 step of position controller
 * @param  position_controller: position_controller_t instance
 * @param  pos_ref: position reference
 * @param  pos_feed: position feedback
 * @param  vel_command: velocity command calculation result(pointer)[internally constrained its magnitude <= 3.0 rad/s]
 */
void step_position_controller(position_controller_t *position_controller,
                              real_T pos_ref, real_T pos_feed, real_T *vel_command);
#ifdef _cplusplus
}
#endif
#endif // !__POSITION_CONTROLLER_H__