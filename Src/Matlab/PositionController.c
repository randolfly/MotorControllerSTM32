/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PositionController.c
 *
 * Code generated for Simulink model 'PositionController'.
 *
 * Model version                  : 1.59
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Jul 16 15:47:40 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "PositionController.h"
#include "rtwtypes.h"

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
void PositionController_step(PositionController_RT_MODEL *const rtM, real_T rtU_targetpos, real_T rtU_p, real_T *rtY_vel_u)
{
    PositionController_DW *rtDW = rtM->dwork;
    real_T rtb_DeadZone;
    real_T rtb_FilterCoefficient;
    real_T rtb_IntegralGain;
    int8_T rtb_DeadZone_0;
    int8_T rtb_IntegralGain_0;

    /* Sum: '<S1>/Add' incorporates:
     *  Inport: '<Root>/feed_pos'
     *  Inport: '<Root>/target pos'
     */
    rtb_IntegralGain = rtU_targetpos - rtU_p;

    /* Gain: '<S39>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S31>/Filter'
     *  Gain: '<S30>/Derivative Gain'
     *  Sum: '<S31>/SumD'
     */
    rtb_FilterCoefficient = (0.381884424337911 * rtb_IntegralGain -
                             rtDW->Filter_DSTATE) *
                            1796.5853498224708;

    /* Sum: '<S45>/Sum' incorporates:
     *  DiscreteIntegrator: '<S36>/Integrator'
     *  Gain: '<S41>/Proportional Gain'
     */
    rtb_DeadZone = (36.642474191183 * rtb_IntegralGain + rtDW->Integrator_DSTATE) + rtb_FilterCoefficient;

    /* Saturate: '<S43>/Saturation' incorporates:
     *  DeadZone: '<S29>/DeadZone'
     */
    if (rtb_DeadZone > 2.0) {
        /* Outport: '<Root>/vel_u' */
        *rtY_vel_u = 2.0;
        rtb_DeadZone -= 2.0;
    } else {
        if (rtb_DeadZone < -2.0) {
            /* Outport: '<Root>/vel_u' */
            *rtY_vel_u = -2.0;
        } else {
            /* Outport: '<Root>/vel_u' */
            *rtY_vel_u = rtb_DeadZone;
        }

        if (rtb_DeadZone >= -2.0) {
            rtb_DeadZone = 0.0;
        } else {
            rtb_DeadZone -= -2.0;
        }
    }

    /* End of Saturate: '<S43>/Saturation' */

    /* Gain: '<S33>/Integral Gain' */
    rtb_IntegralGain *= 260.6538729316;

    /* Switch: '<S27>/Switch1' incorporates:
     *  Constant: '<S27>/Constant'
     *  Constant: '<S27>/Constant2'
     *  Constant: '<S27>/Constant5'
     *  RelationalOperator: '<S27>/fix for DT propagation issue'
     */
    if (rtb_DeadZone > 0.0) {
        rtb_DeadZone_0 = 1;
    } else {
        rtb_DeadZone_0 = -1;
    }

    /* End of Switch: '<S27>/Switch1' */

    /* Switch: '<S27>/Switch2' incorporates:
     *  Constant: '<S27>/Constant3'
     *  Constant: '<S27>/Constant4'
     *  Constant: '<S27>/Constant5'
     *  RelationalOperator: '<S27>/fix for DT propagation issue1'
     */
    if (rtb_IntegralGain > 0.0) {
        rtb_IntegralGain_0 = 1;
    } else {
        rtb_IntegralGain_0 = -1;
    }

    /* End of Switch: '<S27>/Switch2' */

    /* Switch: '<S27>/Switch' incorporates:
     *  Constant: '<S27>/Constant1'
     *  Constant: '<S27>/Constant5'
     *  Logic: '<S27>/AND3'
     *  RelationalOperator: '<S27>/Equal1'
     *  RelationalOperator: '<S27>/Relational Operator'
     */
    if ((rtb_DeadZone != 0.0) && (rtb_DeadZone_0 == rtb_IntegralGain_0)) {
        rtb_IntegralGain = 0.0;
    }

    /* End of Switch: '<S27>/Switch' */

    /* Update for DiscreteIntegrator: '<S36>/Integrator' */
    rtDW->Integrator_DSTATE += 0.0005 * rtb_IntegralGain;

    /* Update for DiscreteIntegrator: '<S31>/Filter' */
    rtDW->Filter_DSTATE += 0.0005 * rtb_FilterCoefficient;
}

/* Model initialize function */
void PositionController_initialize(PositionController_RT_MODEL *const rtM)
{
    /* (no initialization code required) */
    UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
