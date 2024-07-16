/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PositionController.h
 *
 * Code generated for Simulink model 'PositionController'.
 *
 * Model version                  : 1.53
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Jul 16 14:37:23 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PositionController_h_
#define RTW_HEADER_PositionController_h_
#ifndef PositionController_COMMON_INCLUDES_
#define PositionController_COMMON_INCLUDES_
#include "rtwtypes.h"
// #include "rtw_continuous.h"
// #include "rtw_solver.h"
#endif /* PositionController_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm) ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val) ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct PositionController_tag_RTM PositionController_RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
    real_T Filter_states[60]; /* '<S1>/Filter' */
    real_T Integrator_DSTATE; /* '<S36>/Integrator' */
    real_T Filter_DSTATE;     /* '<S31>/Filter' */
} PositionController_DW;

/* Constant parameters (default storage) */
typedef struct {
    /* Expression: [-0.000745028638623983783 -0.000577474298723682205 -0.000751502332388434189 -0.000913450818789973869 -0.00103956263695267415 -0.00110063533352465167 -0.00106262372687730266 -0.000887654848896703348 -0.000535445851242314654 3.4913017385062827e-05 0.000862876847342860642 0.00198415901238353917 0.00342835429867265886 0.0052166045566638319 0.00735944837296535585 0.00985499677566344275 0.0126875682712835544 0.0158268985973420359 0.0192280141426906179 0.0228318243485051489 0.0265664494262882918 0.0303492577346870275 0.0340895447629842932 0.0376917456185542343 0.0410590378852357801 0.0440971641302333739 0.0467182851770751445 0.0488446679381579207 0.0504120158277508584 0.0513722655164936814 0.05169570023985956 0.0513722655164936814 0.0504120158277508584 0.0488446679381579207 0.0467182851770751445 0.0440971641302333739 0.0410590378852357801 0.0376917456185542343 0.0340895447629842932 0.0303492577346870275 0.0265664494262882918 0.0228318243485051489 0.0192280141426906179 0.0158268985973420359 0.0126875682712835544 0.00985499677566344275 0.00735944837296535585 0.0052166045566638319 0.00342835429867265886 0.00198415901238353917 0.000862876847342860642 3.4913017385062827e-05 -0.000535445851242314654 -0.000887654848896703348 -0.00106262372687730266 -0.00110063533352465167 -0.00103956263695267415 -0.000913450818789973869 -0.000751502332388434189 -0.000577474298723682205 -0.000745028638623983783]
     * Referenced by: '<S1>/Filter'
     */
    real_T Filter_Coefficients[61];
} PositionController_ConstP;

/* Real-time Model Data Structure */
struct PositionController_tag_RTM {
    const char_T *volatile errorStatus;
    PositionController_DW *dwork;
};

/* Constant parameters (default storage) */
extern const PositionController_ConstP PositionController_rtConstP;

/* Model entry point functions */
extern void PositionController_initialize(PositionController_RT_MODEL *const rtM);
extern void PositionController_step(PositionController_RT_MODEL *const rtM, real_T rtU_targetpos,
                                    real_T rtU_p, real_T *rtY_vel_u);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('PositionLoop_code_202407156/PositionController')    - opens subsystem PositionLoop_code_202407156/PositionController
 * hilite_system('PositionLoop_code_202407156/PositionController/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PositionLoop_code_202407156'
 * '<S1>'   : 'PositionLoop_code_202407156/PositionController'
 * '<S2>'   : 'PositionLoop_code_202407156/PositionController/Position PID'
 * '<S3>'   : 'PositionLoop_code_202407156/PositionController/Position PID/Anti-windup'
 * '<S4>'   : 'PositionLoop_code_202407156/PositionController/Position PID/D Gain'
 * '<S5>'   : 'PositionLoop_code_202407156/PositionController/Position PID/Filter'
 * '<S6>'   : 'PositionLoop_code_202407156/PositionController/Position PID/Filter ICs'
 * '<S7>'   : 'PositionLoop_code_202407156/PositionController/Position PID/I Gain'
 * '<S8>'   : 'PositionLoop_code_202407156/PositionController/Position PID/Ideal P Gain'
 * '<S9>'   : 'PositionLoop_code_202407156/PositionController/Position PID/Ideal P Gain Fdbk'
 * '<S10>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Integrator'
 * '<S11>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Integrator ICs'
 * '<S12>'  : 'PositionLoop_code_202407156/PositionController/Position PID/N Copy'
 * '<S13>'  : 'PositionLoop_code_202407156/PositionController/Position PID/N Gain'
 * '<S14>'  : 'PositionLoop_code_202407156/PositionController/Position PID/P Copy'
 * '<S15>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Parallel P Gain'
 * '<S16>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Reset Signal'
 * '<S17>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Saturation'
 * '<S18>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Saturation Fdbk'
 * '<S19>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Sum'
 * '<S20>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Sum Fdbk'
 * '<S21>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tracking Mode'
 * '<S22>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tracking Mode Sum'
 * '<S23>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tsamp - Integral'
 * '<S24>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tsamp - Ngain'
 * '<S25>'  : 'PositionLoop_code_202407156/PositionController/Position PID/postSat Signal'
 * '<S26>'  : 'PositionLoop_code_202407156/PositionController/Position PID/preSat Signal'
 * '<S27>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Anti-windup/Disc. Clamping Parallel'
 * '<S28>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S29>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S30>'  : 'PositionLoop_code_202407156/PositionController/Position PID/D Gain/Internal Parameters'
 * '<S31>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Filter/Disc. Forward Euler Filter'
 * '<S32>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Filter ICs/Internal IC - Filter'
 * '<S33>'  : 'PositionLoop_code_202407156/PositionController/Position PID/I Gain/Internal Parameters'
 * '<S34>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Ideal P Gain/Passthrough'
 * '<S35>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Ideal P Gain Fdbk/Disabled'
 * '<S36>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Integrator/Discrete'
 * '<S37>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Integrator ICs/Internal IC'
 * '<S38>'  : 'PositionLoop_code_202407156/PositionController/Position PID/N Copy/Disabled'
 * '<S39>'  : 'PositionLoop_code_202407156/PositionController/Position PID/N Gain/Internal Parameters'
 * '<S40>'  : 'PositionLoop_code_202407156/PositionController/Position PID/P Copy/Disabled'
 * '<S41>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Parallel P Gain/Internal Parameters'
 * '<S42>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Reset Signal/Disabled'
 * '<S43>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Saturation/Enabled'
 * '<S44>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Saturation Fdbk/Disabled'
 * '<S45>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Sum/Sum_PID'
 * '<S46>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Sum Fdbk/Disabled'
 * '<S47>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tracking Mode/Disabled'
 * '<S48>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tracking Mode Sum/Passthrough'
 * '<S49>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tsamp - Integral/Passthrough'
 * '<S50>'  : 'PositionLoop_code_202407156/PositionController/Position PID/Tsamp - Ngain/Passthrough'
 * '<S51>'  : 'PositionLoop_code_202407156/PositionController/Position PID/postSat Signal/Forward_Path'
 * '<S52>'  : 'PositionLoop_code_202407156/PositionController/Position PID/preSat Signal/Forward_Path'
 */
#endif /* RTW_HEADER_PositionController_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
