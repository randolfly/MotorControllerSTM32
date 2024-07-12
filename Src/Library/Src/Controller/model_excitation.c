#include "Controller/model_excitation.h"

double excitation_signal           = 0;
double excitation_signal_magnitude = 250;
double excitation_signal_gain      = 1;

void init_model_excitation(void)
{
    Excitation_initialize();
    Excitation_rtU.magnitude = excitation_signal_magnitude;
    Excitation_rtU.gain      = excitation_signal_gain;
}

uint8_t step_model_excitation(void)
{
    static boolean_T OverrunFlag = false;
    Excitation_rtU.magnitude     = excitation_signal_magnitude;
    Excitation_rtU.gain          = excitation_signal_gain;
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
        // clear prev index, for next excitation
        Excitation_rtDW.FromWorkspace_IWORK.PrevIndex = -1;
        Excitation_rtY.output                         = 0;
        excitation_signal                             = 0;
        return 1;
    } else {
        return 0;
    }

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}