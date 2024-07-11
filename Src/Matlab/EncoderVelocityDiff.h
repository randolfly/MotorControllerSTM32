/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: EncoderVelocityDiff.h
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

#ifndef RTW_HEADER_EncoderVelocityDiff_h_
#define RTW_HEADER_EncoderVelocityDiff_h_
#ifndef EncoderVelocityDiff_COMMON_INCLUDES_
#define EncoderVelocityDiff_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif /* EncoderVelocityDiff_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Forward declaration for rtModel */
typedef struct Encoder_tag_RTM Encoder_RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
    real_T DiscreteTransferFcn_states; /* '<S1>/Discrete Transfer Fcn' */
} Encoder_DW;

/* Real-time Model Data Structure */
struct Encoder_tag_RTM {
    Encoder_DW *dwork;
};

/* Model entry point functions */
extern void EncoderVelocityDiff_initialize(Encoder_RT_MODEL *const rtM);
extern void EncoderVelocityDiff_step(Encoder_RT_MODEL *const rtM, real_T rtU_position,
                                     real_T *rtY_velocity);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'EncoderVelocityDiff'
 * '<S1>'   : 'EncoderVelocityDiff/Continous Diff'
 */
#endif /* RTW_HEADER_EncoderVelocityDiff_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
