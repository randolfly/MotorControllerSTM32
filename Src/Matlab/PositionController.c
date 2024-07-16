/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PositionController.c
 *
 * Code generated for Simulink model 'PositionController'.
 *
 * Model version                  : 1.61
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Jul 16 16:08:31 2024
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

/* Forward declaration for local functions */
static void SystemCore_setup(dsp_simulink_MovingAverage *obj);
static void SystemCore_setup(dsp_simulink_MovingAverage *obj)
{
    real_T varargin_2;
    boolean_T flag;
    obj->isSetupComplete      = false;
    obj->isInitialized        = 1;
    obj->NumChannels          = 1;
    varargin_2                = obj->ForgettingFactor;
    obj->_pobj0.isInitialized = 0;
    obj->_pobj0.isInitialized = 0;
    flag                      = (obj->_pobj0.isInitialized == 1);
    if (flag) {
        obj->_pobj0.TunablePropsChanged = true;
    }

    obj->_pobj0.ForgettingFactor = varargin_2;
    obj->pStatistic              = &obj->_pobj0;
    obj->isSetupComplete         = true;
    obj->TunablePropsChanged     = false;
}

/* Model step function */
void PositionController_step(PositionController_RT_MODEL *const rtM, real_T rtU_targetpos, real_T rtU_p, real_T *rtY_vel_u)
{
    PositionController_DW *rtDW = rtM->dwork;
    g_dsp_internal_ExponentialMovin *obj;
    real_T lambda;
    real_T pmLocal;
    real_T pwLocal;
    real_T rtb_DeadZone;
    real_T rtb_DeadZone_0;
    real_T rtb_FilterCoefficient;
    real_T rtb_IntegralGain;
    int8_T rtb_DeadZone_1;
    int8_T rtb_IntegralGain_0;
    boolean_T flag;

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

    /* MATLABSystem: '<S1>/Moving Average' */
    if (rtDW->obj.ForgettingFactor != 0.9) {
        flag = (rtDW->obj.isInitialized == 1);
        if (flag) {
            rtDW->obj.TunablePropsChanged = true;
        }

        rtDW->obj.ForgettingFactor = 0.9;
    }

    if (rtDW->obj.TunablePropsChanged) {
        rtDW->obj.TunablePropsChanged = false;
        obj                           = rtDW->obj.pStatistic;
        flag                          = (obj->isInitialized == 1);
        if (flag) {
            obj->TunablePropsChanged = true;
        }

        rtDW->obj.pStatistic->ForgettingFactor = rtDW->obj.ForgettingFactor;
    }

    obj = rtDW->obj.pStatistic;
    if (obj->isInitialized != 1) {
        obj->isSetupComplete     = false;
        obj->isInitialized       = 1;
        obj->pwN                 = 1.0;
        obj->pmN                 = 0.0;
        obj->plambda             = obj->ForgettingFactor;
        obj->isSetupComplete     = true;
        obj->TunablePropsChanged = false;
        obj->pwN                 = 1.0;
        obj->pmN                 = 0.0;
    }

    if (obj->TunablePropsChanged) {
        obj->TunablePropsChanged = false;
        obj->plambda             = obj->ForgettingFactor;
    }

    pwLocal = obj->pwN;
    pmLocal = obj->pmN;
    lambda  = obj->plambda;

    /* Saturate: '<S43>/Saturation' */
    if (rtb_DeadZone > 2.0) {
        rtb_DeadZone_0 = 2.0;
    } else if (rtb_DeadZone < -2.0) {
        rtb_DeadZone_0 = -2.0;
    } else {
        rtb_DeadZone_0 = rtb_DeadZone;
    }

    /* End of Saturate: '<S43>/Saturation' */

    /* MATLABSystem: '<S1>/Moving Average' */
    pmLocal  = (1.0 - 1.0 / pwLocal) * pmLocal + 1.0 / pwLocal * rtb_DeadZone_0;
    obj->pwN = lambda * pwLocal + 1.0;
    obj->pmN = pmLocal;

    /* Outport: '<Root>/vel_u' incorporates:
     *  MATLABSystem: '<S1>/Moving Average'
     */
    *rtY_vel_u = pmLocal;

    /* DeadZone: '<S29>/DeadZone' */
    if (rtb_DeadZone > 2.0) {
        rtb_DeadZone -= 2.0;
    } else if (rtb_DeadZone >= -2.0) {
        rtb_DeadZone = 0.0;
    } else {
        rtb_DeadZone -= -2.0;
    }

    /* End of DeadZone: '<S29>/DeadZone' */

    /* Gain: '<S33>/Integral Gain' */
    rtb_IntegralGain *= 260.6538729316;

    /* Switch: '<S27>/Switch1' incorporates:
     *  Constant: '<S27>/Constant'
     *  Constant: '<S27>/Constant2'
     *  Constant: '<S27>/Constant5'
     *  RelationalOperator: '<S27>/fix for DT propagation issue'
     */
    if (rtb_DeadZone > 0.0) {
        rtb_DeadZone_1 = 1;
    } else {
        rtb_DeadZone_1 = -1;
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
    if ((rtb_DeadZone != 0.0) && (rtb_DeadZone_1 == rtb_IntegralGain_0)) {
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
    PositionController_DW *rtDW = rtM->dwork;

    {
        g_dsp_internal_ExponentialMovin *obj;
        boolean_T flag;

        /* Start for MATLABSystem: '<S1>/Moving Average' */
        rtDW->obj.matlabCodegenIsDeleted = true;
        rtDW->obj.isInitialized          = 0;
        rtDW->obj.NumChannels            = -1;
        rtDW->obj.matlabCodegenIsDeleted = false;
        flag                             = (rtDW->obj.isInitialized == 1);
        if (flag) {
            rtDW->obj.TunablePropsChanged = true;
        }

        rtDW->obj.ForgettingFactor = 0.9;
        SystemCore_setup(&rtDW->obj);

        /* End of Start for MATLABSystem: '<S1>/Moving Average' */

        /* InitializeConditions for MATLABSystem: '<S1>/Moving Average' */
        obj = rtDW->obj.pStatistic;
        if (obj->isInitialized == 1) {
            obj->pwN = 1.0;
            obj->pmN = 0.0;
        }

        /* End of InitializeConditions for MATLABSystem: '<S1>/Moving Average' */
    }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
