#include "Controller/model_excitation.h"

void init_model_excitation(void)
{
    Excitation_initialize();
}

void set_model_params(real_T magnitude, real_T gain)
{
    rtU.gain      = gain;
    rtU.magnitude = magnitude;
}

void get_model_output(real_T *output)
{
    *output = rtY.output;
}

uint8_t step_model_excitation(void)
{
    static boolean_T OverrunFlag = false;

    /* Disable interrupts here */

    /* Check for overrun */
    if (OverrunFlag) {
        rtmSetErrorStatus(rtM, "Overrun");
        return;
    }

    OverrunFlag = true;

    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */

    /* Step the model */
    Excitation_step();

    /* Get model outputs here */

    /* Indicate task complete */
    OverrunFlag = false;

    // if some error handler is needed, extend this function
    if (rtY.output == 0) {
        return 1;
    } else {
        return 0;
    }

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}