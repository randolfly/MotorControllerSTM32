/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: EncoderVelocityDiff.c
 *
 * Code generated for Simulink model 'EncoderVelocityDiff'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat Jun 29 21:42:01 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "EncoderVelocityDiff.h"
/*===========*
 * Constants *
 *===========*/
#define RT_PI      3.14159265358979323846
#define RT_PIF     3.1415927F
#define RT_LN_10   2.30258509299404568402
#define RT_LN_10F  2.3025851F
#define RT_LOG10E  0.43429448190325182765
#define RT_LOG10EF 0.43429449F
#define RT_E       2.7182818284590452354
#define RT_EF      2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x) /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x) (void)(x)
#endif
#endif

/* Model step function */
void EncoderVelocityDiff_step(Encoder_RT_MODEL *const rtM, real_T rtU_position, real_T *rtY_velocity)
{
    Encoder_DW *rtDW = rtM->dwork;
    real_T DiscreteTransferFcn_tmp;

    /* DiscreteTransferFcn: '<S1>/Discrete Transfer Fcn' incorporates:
     *  Inport: '<Root>/position'
     */
    DiscreteTransferFcn_tmp = rtU_position - -0.99004983374916811 *
                                                 rtDW->DiscreteTransferFcn_states;

    /* Outport: '<Root>/velocity' incorporates:
     *  DiscreteTransferFcn: '<S1>/Discrete Transfer Fcn'
     */
    *rtY_velocity = 50.0 * DiscreteTransferFcn_tmp + -50.0 *
                                                         rtDW->DiscreteTransferFcn_states;

    /* Update for DiscreteTransferFcn: '<S1>/Discrete Transfer Fcn' */
    rtDW->DiscreteTransferFcn_states = DiscreteTransferFcn_tmp;
}

/* Model initialize function */
void EncoderVelocityDiff_initialize(Encoder_RT_MODEL *const rtM)
{
    /* (no initialization code required) */
    UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
