#include "Controller/position_controller.h"

void init_position_controller(position_controller_t *position_controller)
{
    position_controller->model        = (PositionController_RT_MODEL *)malloc(sizeof(PositionController_RT_MODEL));
    position_controller->state        = (PositionController_DW *)malloc(sizeof(PositionController_DW));
    position_controller->model->dwork = (position_controller->state);
    PositionController_initialize(position_controller->model);
    position_controller->model->dwork->Filter_DSTATE     = 0.0;
    position_controller->model->dwork->Integrator_DSTATE = 0.0;
}

void deinit_position_controller(position_controller_t *position_controller)
{
    free(position_controller->state);
    free(position_controller->model);
}

void step_position_controller(position_controller_t *position_controller, real_T pos_ref, real_T pos_feed, real_T *vel_command)
{
    static boolean_T OverrunFlag = false;

    /* Disable interrupts here */

    /* Check for overrun */
    if (OverrunFlag) {
        return;
    }

    OverrunFlag = true;

    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */

    /* Step the model */
    PositionController_step(position_controller->model,
                            pos_ref,
                            pos_feed,
                            vel_command);

    /* Get model outputs here */

    /* Indicate task complete */
    OverrunFlag = false;

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}
