/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VelocityController.h
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

#ifndef RTW_HEADER_VelocityController_h_
#define RTW_HEADER_VelocityController_h_
#ifndef VelocityController_COMMON_INCLUDES_
#define VelocityController_COMMON_INCLUDES_
#include "rtwtypes.h"
// #include "rtw_continuous.h"
// #include "rtw_solver.h"
#endif /* VelocityController_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm) ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val) ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct VelocityController_tag_RTM VelocityController_RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
    real_T Integrator_DSTATE; /* '<S37>/Integrator' */
    real_T Filter_DSTATE;     /* '<S32>/Filter' */
} VelocityController_DW;

/* Real-time Model Data Structure */
struct VelocityController_tag_RTM {
    const char_T *volatile errorStatus;
    VelocityController_DW *dwork;
};

/* Model entry point functions */
extern void VelocityController_initialize(VelocityController_RT_MODEL *const rtM);
extern void VelocityController_step(VelocityController_RT_MODEL *const rtM, real_T rtU_ref, real_T rtU_v, real_T *rtY_u);

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
 * hilite_system('VelocityLoop/VelocityController')    - opens subsystem VelocityLoop/VelocityController
 * hilite_system('VelocityLoop/VelocityController/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VelocityLoop'
 * '<S1>'   : 'VelocityLoop/VelocityController'
 * '<S2>'   : 'VelocityLoop/VelocityController/PID Controller'
 * '<S3>'   : 'VelocityLoop/VelocityController/friction compensation'
 * '<S4>'   : 'VelocityLoop/VelocityController/PID Controller/Anti-windup'
 * '<S5>'   : 'VelocityLoop/VelocityController/PID Controller/D Gain'
 * '<S6>'   : 'VelocityLoop/VelocityController/PID Controller/Filter'
 * '<S7>'   : 'VelocityLoop/VelocityController/PID Controller/Filter ICs'
 * '<S8>'   : 'VelocityLoop/VelocityController/PID Controller/I Gain'
 * '<S9>'   : 'VelocityLoop/VelocityController/PID Controller/Ideal P Gain'
 * '<S10>'  : 'VelocityLoop/VelocityController/PID Controller/Ideal P Gain Fdbk'
 * '<S11>'  : 'VelocityLoop/VelocityController/PID Controller/Integrator'
 * '<S12>'  : 'VelocityLoop/VelocityController/PID Controller/Integrator ICs'
 * '<S13>'  : 'VelocityLoop/VelocityController/PID Controller/N Copy'
 * '<S14>'  : 'VelocityLoop/VelocityController/PID Controller/N Gain'
 * '<S15>'  : 'VelocityLoop/VelocityController/PID Controller/P Copy'
 * '<S16>'  : 'VelocityLoop/VelocityController/PID Controller/Parallel P Gain'
 * '<S17>'  : 'VelocityLoop/VelocityController/PID Controller/Reset Signal'
 * '<S18>'  : 'VelocityLoop/VelocityController/PID Controller/Saturation'
 * '<S19>'  : 'VelocityLoop/VelocityController/PID Controller/Saturation Fdbk'
 * '<S20>'  : 'VelocityLoop/VelocityController/PID Controller/Sum'
 * '<S21>'  : 'VelocityLoop/VelocityController/PID Controller/Sum Fdbk'
 * '<S22>'  : 'VelocityLoop/VelocityController/PID Controller/Tracking Mode'
 * '<S23>'  : 'VelocityLoop/VelocityController/PID Controller/Tracking Mode Sum'
 * '<S24>'  : 'VelocityLoop/VelocityController/PID Controller/Tsamp - Integral'
 * '<S25>'  : 'VelocityLoop/VelocityController/PID Controller/Tsamp - Ngain'
 * '<S26>'  : 'VelocityLoop/VelocityController/PID Controller/postSat Signal'
 * '<S27>'  : 'VelocityLoop/VelocityController/PID Controller/preSat Signal'
 * '<S28>'  : 'VelocityLoop/VelocityController/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S29>'  : 'VelocityLoop/VelocityController/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S30>'  : 'VelocityLoop/VelocityController/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S31>'  : 'VelocityLoop/VelocityController/PID Controller/D Gain/Internal Parameters'
 * '<S32>'  : 'VelocityLoop/VelocityController/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S33>'  : 'VelocityLoop/VelocityController/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'VelocityLoop/VelocityController/PID Controller/I Gain/Internal Parameters'
 * '<S35>'  : 'VelocityLoop/VelocityController/PID Controller/Ideal P Gain/Passthrough'
 * '<S36>'  : 'VelocityLoop/VelocityController/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'VelocityLoop/VelocityController/PID Controller/Integrator/Discrete'
 * '<S38>'  : 'VelocityLoop/VelocityController/PID Controller/Integrator ICs/Internal IC'
 * '<S39>'  : 'VelocityLoop/VelocityController/PID Controller/N Copy/Disabled'
 * '<S40>'  : 'VelocityLoop/VelocityController/PID Controller/N Gain/Internal Parameters'
 * '<S41>'  : 'VelocityLoop/VelocityController/PID Controller/P Copy/Disabled'
 * '<S42>'  : 'VelocityLoop/VelocityController/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S43>'  : 'VelocityLoop/VelocityController/PID Controller/Reset Signal/Disabled'
 * '<S44>'  : 'VelocityLoop/VelocityController/PID Controller/Saturation/Enabled'
 * '<S45>'  : 'VelocityLoop/VelocityController/PID Controller/Saturation Fdbk/Disabled'
 * '<S46>'  : 'VelocityLoop/VelocityController/PID Controller/Sum/Sum_PID'
 * '<S47>'  : 'VelocityLoop/VelocityController/PID Controller/Sum Fdbk/Disabled'
 * '<S48>'  : 'VelocityLoop/VelocityController/PID Controller/Tracking Mode/Disabled'
 * '<S49>'  : 'VelocityLoop/VelocityController/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'VelocityLoop/VelocityController/PID Controller/Tsamp - Integral/Passthrough'
 * '<S51>'  : 'VelocityLoop/VelocityController/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'VelocityLoop/VelocityController/PID Controller/postSat Signal/Forward_Path'
 * '<S53>'  : 'VelocityLoop/VelocityController/PID Controller/preSat Signal/Forward_Path'
 */
#endif /* RTW_HEADER_VelocityController_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
