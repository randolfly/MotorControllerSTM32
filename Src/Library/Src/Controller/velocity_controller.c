#include "Controller/velocity_controller.h"

void init_velocity_controller(velocity_controller_t *velocity_controller)
{
    velocity_controller->model        = (VelocityController_RT_MODEL *)malloc(sizeof(VelocityController_RT_MODEL));
    velocity_controller->state        = (VelocityController_DW *)malloc(sizeof(VelocityController_DW));
    velocity_controller->model->dwork = (velocity_controller->state);
    VelocityController_initialize(velocity_controller->model);
    velocity_controller->model->dwork->Filter_DSTATE     = 0.0;
    velocity_controller->model->dwork->Integrator_DSTATE = 0.0;
}

void deinit_velocity_controller(velocity_controller_t *velocity_controller)
{
    free(velocity_controller->state);
    free(velocity_controller->model);
}

void step_velocity_controller(velocity_controller_t *velocity_controller,
                              real_T vel_ref, real_T vel_feed, real_T *torque_command)
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
    VelocityController_step(velocity_controller->model,
                            vel_ref,
                            vel_feed,
                            torque_command);

    /* Get model outputs here */

    /* Indicate task complete */
    OverrunFlag = false;

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}