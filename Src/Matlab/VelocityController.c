/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VelocityController.c
 *
 * Code generated for Simulink model 'VelocityController'.
 *
 * Model version                  : 1.27
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Fri Jul 12 15:09:39 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "VelocityController.h"
#include <math.h>
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
void VelocityController_step(VelocityController_RT_MODEL *const rtM, real_T rtU_targetvel, real_T rtU_v,
                             real_T *rtY_u)
{
    VelocityController_DW *rtDW = rtM->dwork;
    real_T rtb_DeadZone;
    real_T rtb_DeadZone_0;
    real_T rtb_FilterCoefficient;
    real_T rtb_IntegralGain;
    real_T rtb_y;
    int8_T rtb_DeadZone_1;
    int8_T rtb_IntegralGain_0;

    /* Sum: '<S1>/Add' incorporates:
     *  Inport: '<Root>/feed'
     *  Inport: '<Root>/ref'
     */
    rtb_IntegralGain = rtU_targetvel - rtU_v;

    /* Gain: '<S40>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S32>/Filter'
     *  Gain: '<S31>/Derivative Gain'
     *  Sum: '<S32>/SumD'
     */
    rtb_FilterCoefficient = (1.45672350385708 * rtb_IntegralGain -
                             rtDW->Filter_DSTATE) *
                            98.7705129393937;

    /* Sum: '<S46>/Sum' incorporates:
     *  DiscreteIntegrator: '<S37>/Integrator'
     *  Gain: '<S42>/Proportional Gain'
     */
    rtb_DeadZone = (992.697353800287 * rtb_IntegralGain + rtDW->Integrator_DSTATE) + rtb_FilterCoefficient;

    /* MATLAB Function: '<S1>/friction compensation' incorporates:
     *  Inport: '<Root>/ref'
     */
    if (fabs(rtU_targetvel) > 0.005) {
        if (rtU_targetvel > 0.0) {
            rtb_y = 154.0;
        } else {
            rtb_y = -154.0;
        }
    } else {
        rtb_y = tanh(rtU_targetvel / 0.005) * 154.0 / 0.76159415595576485;
    }

    /* End of MATLAB Function: '<S1>/friction compensation' */

    /* Saturate: '<S44>/Saturation' incorporates:
     *  DeadZone: '<S30>/DeadZone'
     */
    if (rtb_DeadZone > 1000.0) {
        rtb_DeadZone_0 = 1000.0;
        rtb_DeadZone -= 1000.0;
    } else {
        if (rtb_DeadZone < -1000.0) {
            rtb_DeadZone_0 = -1000.0;
        } else {
            rtb_DeadZone_0 = rtb_DeadZone;
        }

        if (rtb_DeadZone >= -1000.0) {
            rtb_DeadZone = 0.0;
        } else {
            rtb_DeadZone -= -1000.0;
        }
    }

    /* End of Saturate: '<S44>/Saturation' */

    /* Outport: '<Root>/u' incorporates:
     *  Gain: '<S1>/Gain'
     *  Inport: '<Root>/ref'
     *  Sum: '<S1>/Add1'
     */
    *rtY_u = (0.99 * rtU_targetvel + rtb_DeadZone_0) + rtb_y;

    /* Gain: '<S34>/Integral Gain' */
    rtb_IntegralGain *= 9306.57767463189;

    /* Switch: '<S28>/Switch1' incorporates:
     *  Constant: '<S28>/Constant'
     *  Constant: '<S28>/Constant2'
     *  Constant: '<S28>/Constant5'
     *  RelationalOperator: '<S28>/fix for DT propagation issue'
     */
    if (rtb_DeadZone > 0.0) {
        rtb_DeadZone_1 = 1;
    } else {
        rtb_DeadZone_1 = -1;
    }

    /* End of Switch: '<S28>/Switch1' */

    /* Switch: '<S28>/Switch2' incorporates:
     *  Constant: '<S28>/Constant3'
     *  Constant: '<S28>/Constant4'
     *  Constant: '<S28>/Constant5'
     *  RelationalOperator: '<S28>/fix for DT propagation issue1'
     */
    if (rtb_IntegralGain > 0.0) {
        rtb_IntegralGain_0 = 1;
    } else {
        rtb_IntegralGain_0 = -1;
    }

    /* End of Switch: '<S28>/Switch2' */

    /* Switch: '<S28>/Switch' incorporates:
     *  Constant: '<S28>/Constant1'
     *  Constant: '<S28>/Constant5'
     *  Logic: '<S28>/AND3'
     *  RelationalOperator: '<S28>/Equal1'
     *  RelationalOperator: '<S28>/Relational Operator'
     */
    if ((rtb_DeadZone != 0.0) && (rtb_DeadZone_1 == rtb_IntegralGain_0)) {
        rtb_IntegralGain = 0.0;
    }

    /* End of Switch: '<S28>/Switch' */

    /* Update for DiscreteIntegrator: '<S37>/Integrator' */
    rtDW->Integrator_DSTATE += 0.00025 * rtb_IntegralGain;

    /* Update for DiscreteIntegrator: '<S32>/Filter' */
    rtDW->Filter_DSTATE += 0.00025 * rtb_FilterCoefficient;
}

/* Model initialize function */
void VelocityController_initialize(VelocityController_RT_MODEL *const rtM)
{
    /* (no initialization code required) */
    UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
