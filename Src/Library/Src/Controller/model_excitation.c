#include "Controller/model_excitation.h"

float excitation_signal;

void set_model_excitation_params(real_T magnitude, real_T gain)
{
    Excitation_rtU.gain      = gain;
    Excitation_rtU.magnitude = magnitude;
}

void init_model_excitation(void)
{
    Excitation_initialize();
    set_model_excitation_params(200, 1);
}

uint8_t step_model_excitation(void)
{
    static boolean_T OverrunFlag = false;

    /* Disable interrupts here */

    /* Check for overrun */
    if (OverrunFlag) {
        rtmSetErrorStatus(Excitation_rtM, "Overrun");
        return 2;
    }

    OverrunFlag = true;

    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */

    /* Step the model */
    Excitation_step();
    excitation_signal = Excitation_rtY.output;
    /* Get model outputs here */

    /* Indicate task complete */
    OverrunFlag = false;

    // if some error handler is needed, extend this function
    if (Excitation_rtY.output == 0) {
        return 1;
    } else {
        return 0;
    }

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}