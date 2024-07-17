#include "Controller/s_profile_generator.h"

void init_s_profile_generator(s_profile_generator_t *s_profile_generator)
{
    s_profile_generator->model        = (SProfileGenerator_RT_MODEL *)malloc(sizeof(SProfileGenerator_RT_MODEL));
    s_profile_generator->state        = (SProfileGenerator_DW *)malloc(sizeof(SProfileGenerator_DW));
    s_profile_generator->param        = (s_profile_generator_param_t *)malloc(sizeof(s_profile_generator_param_t));
    s_profile_generator->model->dwork = s_profile_generator->state;
    SProfileGenerator_initialize(s_profile_generator->model);
    s_profile_generator->param->start_vel = 0;
    s_profile_generator->param->end_vel   = 0;
    s_profile_generator->param->execute   = 1;
    s_profile_generator->param->max_acc   = 1;
    s_profile_generator->param->max_jerk  = 1;
    s_profile_generator->param->max_vel   = 2;
    s_profile_generator->param->start_pos = 0;
    s_profile_generator->param->end_pos   = 0;
    s_profile_generator->param->pos       = 0;
}

void deinit_s_profile_generator(s_profile_generator_t *s_profile_generator)
{
    free(s_profile_generator->state);
    free(s_profile_generator->model);
    free(s_profile_generator->param);
}

void step_s_profile_generator(s_profile_generator_t *s_profile_generator)
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
    SProfileGenerator_step(s_profile_generator->model,
                           s_profile_generator->param->start_pos,
                           s_profile_generator->param->end_pos,
                           s_profile_generator->param->start_vel,
                           s_profile_generator->param->end_vel,
                           s_profile_generator->param->max_vel,
                           s_profile_generator->param->max_vel,
                           s_profile_generator->param->max_jerk,
                           s_profile_generator->param->execute,
                           &(s_profile_generator->param->pos));

    /* Get model outputs here */

    /* Indicate task complete */
    OverrunFlag = false;

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}
