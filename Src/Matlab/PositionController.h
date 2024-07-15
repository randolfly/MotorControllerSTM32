/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PositionController.h
 *
 * Code generated for Simulink model 'PositionController'.
 *
 * Model version                  : 1.39
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Jul 15 08:50:13 2024
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
    real_T Integrator_DSTATE; /* '<S36>/Integrator' */
    real_T Filter_DSTATE;     /* '<S31>/Filter' */
} PositionController_DW;

/* Real-time Model Data Structure */
struct PositionController_tag_RTM {
    const char_T *volatile errorStatus;
    PositionController_DW *dwork;
};

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
 * hilite_system('PositionLoop_code/PositionController')    - opens subsystem PositionLoop_code/PositionController
 * hilite_system('PositionLoop_code/PositionController/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PositionLoop_code'
 * '<S1>'   : 'PositionLoop_code/PositionController'
 * '<S2>'   : 'PositionLoop_code/PositionController/Position PID'
 * '<S3>'   : 'PositionLoop_code/PositionController/Position PID/Anti-windup'
 * '<S4>'   : 'PositionLoop_code/PositionController/Position PID/D Gain'
 * '<S5>'   : 'PositionLoop_code/PositionController/Position PID/Filter'
 * '<S6>'   : 'PositionLoop_code/PositionController/Position PID/Filter ICs'
 * '<S7>'   : 'PositionLoop_code/PositionController/Position PID/I Gain'
 * '<S8>'   : 'PositionLoop_code/PositionController/Position PID/Ideal P Gain'
 * '<S9>'   : 'PositionLoop_code/PositionController/Position PID/Ideal P Gain Fdbk'
 * '<S10>'  : 'PositionLoop_code/PositionController/Position PID/Integrator'
 * '<S11>'  : 'PositionLoop_code/PositionController/Position PID/Integrator ICs'
 * '<S12>'  : 'PositionLoop_code/PositionController/Position PID/N Copy'
 * '<S13>'  : 'PositionLoop_code/PositionController/Position PID/N Gain'
 * '<S14>'  : 'PositionLoop_code/PositionController/Position PID/P Copy'
 * '<S15>'  : 'PositionLoop_code/PositionController/Position PID/Parallel P Gain'
 * '<S16>'  : 'PositionLoop_code/PositionController/Position PID/Reset Signal'
 * '<S17>'  : 'PositionLoop_code/PositionController/Position PID/Saturation'
 * '<S18>'  : 'PositionLoop_code/PositionController/Position PID/Saturation Fdbk'
 * '<S19>'  : 'PositionLoop_code/PositionController/Position PID/Sum'
 * '<S20>'  : 'PositionLoop_code/PositionController/Position PID/Sum Fdbk'
 * '<S21>'  : 'PositionLoop_code/PositionController/Position PID/Tracking Mode'
 * '<S22>'  : 'PositionLoop_code/PositionController/Position PID/Tracking Mode Sum'
 * '<S23>'  : 'PositionLoop_code/PositionController/Position PID/Tsamp - Integral'
 * '<S24>'  : 'PositionLoop_code/PositionController/Position PID/Tsamp - Ngain'
 * '<S25>'  : 'PositionLoop_code/PositionController/Position PID/postSat Signal'
 * '<S26>'  : 'PositionLoop_code/PositionController/Position PID/preSat Signal'
 * '<S27>'  : 'PositionLoop_code/PositionController/Position PID/Anti-windup/Disc. Clamping Parallel'
 * '<S28>'  : 'PositionLoop_code/PositionController/Position PID/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S29>'  : 'PositionLoop_code/PositionController/Position PID/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S30>'  : 'PositionLoop_code/PositionController/Position PID/D Gain/Internal Parameters'
 * '<S31>'  : 'PositionLoop_code/PositionController/Position PID/Filter/Disc. Forward Euler Filter'
 * '<S32>'  : 'PositionLoop_code/PositionController/Position PID/Filter ICs/Internal IC - Filter'
 * '<S33>'  : 'PositionLoop_code/PositionController/Position PID/I Gain/Internal Parameters'
 * '<S34>'  : 'PositionLoop_code/PositionController/Position PID/Ideal P Gain/Passthrough'
 * '<S35>'  : 'PositionLoop_code/PositionController/Position PID/Ideal P Gain Fdbk/Disabled'
 * '<S36>'  : 'PositionLoop_code/PositionController/Position PID/Integrator/Discrete'
 * '<S37>'  : 'PositionLoop_code/PositionController/Position PID/Integrator ICs/Internal IC'
 * '<S38>'  : 'PositionLoop_code/PositionController/Position PID/N Copy/Disabled'
 * '<S39>'  : 'PositionLoop_code/PositionController/Position PID/N Gain/Internal Parameters'
 * '<S40>'  : 'PositionLoop_code/PositionController/Position PID/P Copy/Disabled'
 * '<S41>'  : 'PositionLoop_code/PositionController/Position PID/Parallel P Gain/Internal Parameters'
 * '<S42>'  : 'PositionLoop_code/PositionController/Position PID/Reset Signal/Disabled'
 * '<S43>'  : 'PositionLoop_code/PositionController/Position PID/Saturation/Enabled'
 * '<S44>'  : 'PositionLoop_code/PositionController/Position PID/Saturation Fdbk/Disabled'
 * '<S45>'  : 'PositionLoop_code/PositionController/Position PID/Sum/Sum_PID'
 * '<S46>'  : 'PositionLoop_code/PositionController/Position PID/Sum Fdbk/Disabled'
 * '<S47>'  : 'PositionLoop_code/PositionController/Position PID/Tracking Mode/Disabled'
 * '<S48>'  : 'PositionLoop_code/PositionController/Position PID/Tracking Mode Sum/Passthrough'
 * '<S49>'  : 'PositionLoop_code/PositionController/Position PID/Tsamp - Integral/Passthrough'
 * '<S50>'  : 'PositionLoop_code/PositionController/Position PID/Tsamp - Ngain/Passthrough'
 * '<S51>'  : 'PositionLoop_code/PositionController/Position PID/postSat Signal/Forward_Path'
 * '<S52>'  : 'PositionLoop_code/PositionController/Position PID/preSat Signal/Forward_Path'
 */
#endif /* RTW_HEADER_PositionController_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */