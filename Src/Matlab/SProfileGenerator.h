/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SProfileGenerator.h
 *
 * Code generated for Simulink model 'SProfileGenerator'.
 *
 * Model version                  : 1.26
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Wed Jul 17 14:41:52 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SProfileGenerator_h_
#define RTW_HEADER_SProfileGenerator_h_
#ifndef SProfileGenerator_COMMON_INCLUDES_
#define SProfileGenerator_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif /* SProfileGenerator_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm) ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val) ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct SProfileGenerator_tag_RTM SProfileGenerator_RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
    real_T param[16];                       /* '<S1>/SProfileFSM' */
    real_T T;                               /* '<S1>/SProfileFSM' */
    real_T sigma;                           /* '<S1>/SProfileFSM' */
    real_T current_pos;                     /* '<S1>/SProfileFSM' */
    real_T start_t;                         /* '<S1>/SProfileFSM' */
    uint8_T is_active_c3_SProfileGenerator; /* '<S1>/SProfileFSM' */
    uint8_T is_c3_SProfileGenerator;        /* '<S1>/SProfileFSM' */
} SProfileGenerator_DW;

/* Real-time Model Data Structure */
struct SProfileGenerator_tag_RTM {
    const char_T *volatile errorStatus;
    SProfileGenerator_DW *dwork;

    /*
     * Timing:
     * The following substructure contains information regarding
     * the timing information for the model.
     */
    struct {
        uint32_T clockTick0;
    } Timing;
};

/* Model entry point functions */
extern void SProfileGenerator_initialize(SProfileGenerator_RT_MODEL *const rtM);
extern void SProfileGenerator_step(SProfileGenerator_RT_MODEL *const rtM, real_T rtU_startpos,
                                   real_T rtU_end_pos, real_T rtU_start_vel, real_T rtU_end_vel, real_T rtU_max_vel, real_T rtU_max_acc, real_T rtU_max_jerk, real_T rtU_execute,
                                   real_T *rtY_pos);

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
 * hilite_system('SProfilePlan_code/SProfileGenerator')    - opens subsystem SProfilePlan_code/SProfileGenerator
 * hilite_system('SProfilePlan_code/SProfileGenerator/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SProfilePlan_code'
 * '<S1>'   : 'SProfilePlan_code/SProfileGenerator'
 * '<S2>'   : 'SProfilePlan_code/SProfileGenerator/SProfileFSM'
 */
#endif /* RTW_HEADER_SProfileGenerator_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
