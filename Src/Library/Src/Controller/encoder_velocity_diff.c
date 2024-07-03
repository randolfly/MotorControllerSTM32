#include "Controller/encoder_velocity_diff.h"

void init_encoder_velocity_diff(encoder_velocity_diff_t *velocity_diff)
{
    velocity_diff->model        = (RT_MODEL *)malloc(sizeof(RT_MODEL));
    velocity_diff->state        = (DW *)malloc(sizeof(DW));
    velocity_diff->model->dwork = (velocity_diff->state);
    EncoderVelocityDiff_initialize(velocity_diff->model);
}

void deinit_encoder_velocity_diff(encoder_velocity_diff_t *velocity_diff)
{
    free(velocity_diff->state);
    free(velocity_diff->model);
}

void step_encoder_velocity_diff(encoder_velocity_diff_t *velocity_diff,
                                real_T input_position,
                                real_T *output_velocity)
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
    EncoderVelocityDiff_step(velocity_diff->model,
                             input_position,
                             output_velocity);

    /* Get model outputs here */

    /* Indicate task complete */
    OverrunFlag = false;

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}