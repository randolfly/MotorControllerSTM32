/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SProfileGenerator.c
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

#include "SProfileGenerator.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include <stddef.h>

/* Named constants for Chart: '<S1>/SProfileFSM' */
#define IN_GeneratePos ((uint8_T)1U)
#define IN_HoldOn      ((uint8_T)2U)
#define IN_InitParam   ((uint8_T)3U)
#define NumBitsPerChar 8U

extern real_T rt_powd_snf(real_T u0, real_T u1);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
    struct {
        uint32_T wordH;
        uint32_T wordL;
    } words;
} BigEndianIEEEDouble;

typedef struct {
    struct {
        uint32_T wordL;
        uint32_T wordH;
    } words;
} LittleEndianIEEEDouble;

typedef struct {
    union {
        real32_T wordLreal;
        uint32_T wordLuint;
    } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

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

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T inf         = 0.0;
    if (bitsPerReal == 32U) {
        inf = rtGetInfF();
    } else {
        union {
            LittleEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.bitVal.words.wordH = 0x7FF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        inf                       = tmpVal.fltVal;
    }

    return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T minf        = 0.0;
    if (bitsPerReal == 32U) {
        minf = rtGetMinusInfF();
    } else {
        union {
            LittleEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.bitVal.words.wordH = 0xFFF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        minf                      = tmpVal.fltVal;
    }

    return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T nan         = 0.0;
    if (bitsPerReal == 32U) {
        nan = rtGetNaNF();
    } else {
        union {
            LittleEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.bitVal.words.wordH = 0xFFF80000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        nan                       = tmpVal.fltVal;
    }

    return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
    IEEESingle nanF = {{0.0F}};

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
    (void)(realSize);
    rtNaN       = rtGetNaN();
    rtNaNF      = rtGetNaNF();
    rtInf       = rtGetInf();
    rtInfF      = rtGetInfF();
    rtMinusInf  = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
    return (boolean_T)((value == rtInf || value == rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
    return (boolean_T)(((value) == rtInfF || (value) == rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
    boolean_T result   = (boolean_T)0;
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    if (bitsPerReal == 32U) {
        result = rtIsNaNF((real32_T)value);
    } else {
        union {
            LittleEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.fltVal = value;
        result        = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                             ((tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                              (tmpVal.bitVal.words.wordL != 0)));
    }

    return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)((tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
    real_T tmp;
    real_T tmp_0;
    real_T y;
    if (rtIsNaN(u0) || rtIsNaN(u1)) {
        y = (rtNaN);
    } else {
        tmp   = fabs(u0);
        tmp_0 = fabs(u1);
        if (rtIsInf(u1)) {
            if (tmp == 1.0) {
                y = 1.0;
            } else if (tmp > 1.0) {
                if (u1 > 0.0) {
                    y = (rtInf);
                } else {
                    y = 0.0;
                }
            } else if (u1 > 0.0) {
                y = 0.0;
            } else {
                y = (rtInf);
            }
        } else if (tmp_0 == 0.0) {
            y = 1.0;
        } else if (tmp_0 == 1.0) {
            if (u1 > 0.0) {
                y = u0;
            } else {
                y = 1.0 / u0;
            }
        } else if (u1 == 2.0) {
            y = u0 * u0;
        } else if ((u1 == 0.5) && (u0 >= 0.0)) {
            y = sqrt(u0);
        } else if ((u0 < 0.0) && (u1 > floor(u1))) {
            y = (rtNaN);
        } else {
            y = pow(u0, u1);
        }
    }

    return y;
}

/* Model step function */
void SProfileGenerator_step(SProfileGenerator_RT_MODEL *const rtM, real_T rtU_startpos, real_T rtU_end_pos, real_T rtU_start_vel, real_T rtU_end_vel, real_T rtU_max_vel,
                            real_T rtU_max_acc, real_T rtU_max_jerk, real_T rtU_execute, real_T *rtY_pos)
{
    SProfileGenerator_DW *rtDW = rtM->dwork;
    real_T T;
    real_T Ta;
    real_T Ta_tmp;
    real_T Td;
    real_T Tj1;
    real_T Tj2;
    real_T Tv;
    real_T Tv_tmp;
    real_T a_lima;
    real_T a_limd;
    real_T a_max;
    real_T a_min;
    real_T j_max;
    real_T rtb_current_time;
    real_T sigma;
    real_T v_0;
    real_T v_1;
    real_T v_max;
    int32_T exitg1;

    /* DigitalClock: '<S1>/current_time' */
    rtb_current_time = ((rtM->Timing.clockTick0) * 0.001);

    /* Chart: '<S1>/SProfileFSM' incorporates:
     *  Inport: '<Root>/end_pos'
     *  Inport: '<Root>/end_vel'
     *  Inport: '<Root>/execute'
     *  Inport: '<Root>/max_acc'
     *  Inport: '<Root>/max_jerk'
     *  Inport: '<Root>/max_vel'
     *  Inport: '<Root>/start pos'
     *  Inport: '<Root>/start_vel'
     *  Outport: '<Root>/pos'
     */
    if (rtDW->is_active_c3_SProfileGenerator == 0U) {
        rtDW->is_active_c3_SProfileGenerator = 1U;
        rtDW->is_c3_SProfileGenerator        = IN_HoldOn;
        rtDW->T                              = 5.0;
        rtDW->current_pos                    = rtU_startpos;
    } else {
        switch (rtDW->is_c3_SProfileGenerator) {
            case IN_GeneratePos:
                rtb_current_time -= rtDW->start_t;
                if (rtb_current_time > rtDW->T) {
                    rtDW->is_c3_SProfileGenerator = IN_HoldOn;
                    rtDW->T                       = 5.0;
                    rtDW->current_pos             = rtU_startpos;
                } else {
                    if (rtb_current_time <= rtDW->T) {
                        T = (rtDW->param[0] + rtDW->param[1]) + rtDW->param[2];
                        if ((rtb_current_time >= 0.0) && (rtb_current_time < rtDW->param[3])) {
                            rtb_current_time = (rtDW->param[7] * rtb_current_time + rtDW->param
                                                                                        [5]) +
                                               rtDW->param[14] * rt_powd_snf(rtb_current_time, 3.0) / 6.0;
                        } else if ((rtb_current_time >= rtDW->param[3]) && (rtb_current_time <
                                                                            rtDW->param[0] - rtDW->param[3])) {
                            rtb_current_time = ((rtb_current_time * rtb_current_time * 3.0 - 3.0 * rtDW->param[3] * rtb_current_time) +
                                                rtDW->param[3] * rtDW->param[3]) *
                                                   (rtDW->param
                                                        [12] /
                                                    6.0) +
                                               (rtDW->param[7] * rtb_current_time + rtDW->param[5]);
                        } else if ((rtb_current_time >= rtDW->param[0] - rtDW->param[3]) &&
                                   (rtb_current_time < rtDW->param[0])) {
                            rtb_current_time = rtDW->param[0] - rtb_current_time;
                            rtb_current_time = (((rtDW->param[7] + rtDW->param[9]) *
                                                     (rtDW->param[0] / 2.0) +
                                                 rtDW->param[5]) -
                                                rtb_current_time * rtDW->param[9]) -
                                               rt_powd_snf(rtb_current_time, 3.0) / 6.0 * rtDW->param[15];
                        } else if ((rtb_current_time >= rtDW->param[0]) && (rtb_current_time <
                                                                            rtDW->param[0] + rtDW->param[1])) {
                            rtb_current_time = ((rtDW->param[7] + rtDW->param[9]) * (rtDW->param[0] / 2.0) + rtDW->param[5]) + (rtb_current_time -
                                                                                                                                rtDW->param[0]) *
                                                                                                                                   rtDW->param[9];
                        } else if ((rtb_current_time >= rtDW->param[0] + rtDW->param[1]) &&
                                   (rtb_current_time < (T - rtDW->param[2]) + rtDW->param[4])) {
                            rtb_current_time = (rtb_current_time - T) + rtDW->param[2];
                            rtb_current_time = ((rtDW->param[6] - (rtDW->param[8] + rtDW->param
                                                                                        [9]) *
                                                                      (rtDW->param[2] / 2.0)) +
                                                rtb_current_time * rtDW->param[9]) -
                                               rt_powd_snf(rtb_current_time, 3.0) / 6.0 * rtDW->param[14];
                        } else if ((rtb_current_time >= (T - rtDW->param[2]) + rtDW->param[4]) && (rtb_current_time < T - rtDW->param[4])) {
                            v_0              = (rtb_current_time - T) + rtDW->param[2];
                            rtb_current_time = (rtb_current_time - T) + rtDW->param[2];
                            rtb_current_time = ((v_0 * v_0 * 3.0 - 3.0 * rtDW->param[4] *
                                                                       rtb_current_time) +
                                                rtDW->param[4] *
                                                    rtDW->param[4]) *
                                                   (rtDW->param[13] / 6.0) +
                                               ((rtDW->param[6] - (rtDW->param[8] + rtDW->param[9]) *
                                                                      (rtDW->param[2] / 2.0)) +
                                                rtb_current_time * rtDW->param[9]);
                        } else if (rtb_current_time >= T - rtDW->param[4]) {
                            if (rtb_current_time <= T) {
                                rtb_current_time = T - rtb_current_time;
                                rtb_current_time = (rtDW->param[6] - rtb_current_time *
                                                                         rtDW->param[8]) -
                                                   rt_powd_snf(rtb_current_time,
                                                               3.0) /
                                                       6.0 * rtDW->param[14];
                            } else {
                                rtb_current_time = rtDW->param[6];
                            }
                        } else {
                            rtb_current_time = rtDW->param[6];
                        }

                        /* Outport: '<Root>/pos' */
                        *rtY_pos = rtDW->sigma * rtb_current_time;
                    } else {
                        /* Outport: '<Root>/pos' incorporates:
                         *  Inport: '<Root>/end_pos'
                         */
                        *rtY_pos = rtU_end_pos;
                    }

                    rtDW->current_pos = *rtY_pos;
                }
                break;

            case IN_HoldOn:
                sigma = rtU_end_pos - rtU_startpos;
                if ((rtU_execute == 1.0) && (fabs(sigma) > 0.0001)) {
                    rtDW->is_c3_SProfileGenerator = IN_InitParam;
                    rtDW->start_t                 = rtb_current_time;
                    rtDW->sigma                   = sigma;
                    if (!rtIsNaN(rtDW->sigma)) {
                        if (rtDW->sigma < 0.0) {
                            rtDW->sigma = -1.0;
                        } else {
                            rtDW->sigma = (rtDW->sigma > 0.0);
                        }
                    }

                    memset(&rtDW->param[0], 0, sizeof(real_T) << 4U);
                    if (!rtIsNaN(sigma)) {
                        if (sigma < 0.0) {
                            sigma = -1.0;
                        } else {
                            sigma = (sigma > 0.0);
                        }
                    }

                    rtb_current_time = sigma * rtU_startpos;
                    T                = sigma * rtU_end_pos;
                    v_0              = sigma * rtU_start_vel;
                    v_1              = sigma * rtU_end_vel;
                    Ta               = (sigma + 1.0) / 2.0;
                    sigma            = (sigma - 1.0) / 2.0;
                    v_max            = Ta * rtU_max_vel + sigma * -rtU_max_vel;
                    a_max            = Ta * rtU_max_acc + sigma * -rtU_max_acc;
                    a_min            = Ta * -rtU_max_acc + sigma * rtU_max_acc;
                    j_max            = Ta * rtU_max_jerk + sigma * -rtU_max_jerk;
                    sigma            = Ta * -rtU_max_jerk + sigma * rtU_max_jerk;
                    Td               = v_max - v_0;
                    Ta_tmp           = a_max * a_max;
                    if (Td * j_max < Ta_tmp) {
                        Tj1    = sqrt(Td / j_max);
                        Ta     = 2.0 * Tj1;
                        a_lima = j_max * Tj1;
                    } else {
                        Tj1    = a_max / j_max;
                        Ta     = Td / a_max + Tj1;
                        a_lima = a_max;
                    }

                    Td = v_max - v_1;
                    if (Td * j_max < Ta_tmp) {
                        Tj2    = sqrt(Td / j_max);
                        Td     = 2.0 * Tj2;
                        a_limd = -j_max * Tj2;
                    } else {
                        Tj2    = a_max / j_max;
                        Td     = Td / a_max + Tj2;
                        a_limd = -a_max;
                    }

                    Tv_tmp = T - rtb_current_time;
                    Tv     = (Tv_tmp / v_max - (v_0 / v_max + 1.0) * (Ta / 2.0)) - (v_1 / v_max + 1.0) * (Td / 2.0);
                    if (Tv > 0.0) {
                        rtDW->param[0]  = Ta;
                        rtDW->param[1]  = Tv;
                        rtDW->param[2]  = Td;
                        rtDW->param[3]  = Tj1;
                        rtDW->param[4]  = Tj2;
                        rtDW->param[5]  = rtb_current_time;
                        rtDW->param[6]  = T;
                        rtDW->param[7]  = v_0;
                        rtDW->param[8]  = v_1;
                        rtDW->param[9]  = v_max;
                        rtDW->param[10] = a_max;
                        rtDW->param[11] = a_min;
                        rtDW->param[12] = a_lima;
                        rtDW->param[13] = a_limd;
                        rtDW->param[14] = j_max;
                        rtDW->param[15] = sigma;
                    } else {
                        v_max  = a_max / j_max;
                        Tj1    = v_0 + v_1;
                        a_lima = Tv_tmp * 4.0;
                        Tj2    = j_max * j_max;
                        a_limd = (v_0 * v_0 + v_1 * v_1) * 2.0;
                        Td     = sqrt((a_lima - v_max * 2.0 * Tj1) * a_max + (rt_powd_snf(a_max,
                                                                                          4.0) /
                                                                              Tj2 +
                                                                          a_limd));
                        Ta_tmp /= j_max;
                        Ta = ((Ta_tmp - 2.0 * v_0) + Td) / (2.0 * a_max);
                        Td = ((Ta_tmp - 2.0 * v_1) + Td) / (2.0 * a_max);
                        if ((Ta < 0.0) || (Td < 0.0)) {
                            if (Ta < 0.0) {
                                Tj2 = (Tv_tmp * j_max - sqrt((Tv_tmp * Tv_tmp * j_max + Tj1 * Tj1 *
                                                                                            (v_1 - v_0)) *
                                                             j_max)) /
                                      (Tj1 * j_max);
                                rtDW->param[0]  = 0.0;
                                rtDW->param[1]  = 0.0;
                                rtDW->param[2]  = (T - rtb_current_time) * 2.0 / Tj1;
                                rtDW->param[3]  = 0.0;
                                rtDW->param[4]  = Tj2;
                                rtDW->param[5]  = rtb_current_time;
                                rtDW->param[6]  = T;
                                rtDW->param[7]  = v_0;
                                rtDW->param[8]  = v_1;
                                rtDW->param[9]  = rtU_start_vel;
                                rtDW->param[10] = a_max;
                                rtDW->param[11] = a_min;
                                rtDW->param[12] = 0.0;
                                rtDW->param[13] = -j_max * Tj2;
                                rtDW->param[14] = j_max;
                                rtDW->param[15] = sigma;
                            } else if (Td < 0.0) {
                                Ta  = Tv_tmp * 2.0 / Tj1;
                                Tj1 = ((T - rtb_current_time) * j_max - sqrt(Tv_tmp * Tv_tmp *
                                                                                 j_max * j_max -
                                                                             Tj1 * Tj1 * (v_1 - v_0))) /
                                      (Tj1 * j_max);
                                a_lima          = j_max * Tj1;
                                rtDW->param[0]  = Ta;
                                rtDW->param[1]  = 0.0;
                                rtDW->param[2]  = 0.0;
                                rtDW->param[3]  = Tj1;
                                rtDW->param[4]  = 0.0;
                                rtDW->param[5]  = rtb_current_time;
                                rtDW->param[6]  = T;
                                rtDW->param[7]  = v_0;
                                rtDW->param[8]  = v_1;
                                rtDW->param[9]  = (Ta - Tj1) * a_lima + v_0;
                                rtDW->param[10] = a_max;
                                rtDW->param[11] = a_min;
                                rtDW->param[12] = a_lima;
                                rtDW->param[13] = 0.0;
                                rtDW->param[14] = j_max;
                                rtDW->param[15] = sigma;
                            }
                        } else if ((Ta >= 2.0 * v_max) && (Td >= 2.0 * v_max)) {
                            rtDW->param[0]  = Ta;
                            rtDW->param[1]  = 0.0;
                            rtDW->param[2]  = Td;
                            rtDW->param[3]  = v_max;
                            rtDW->param[4]  = v_max;
                            rtDW->param[5]  = rtb_current_time;
                            rtDW->param[6]  = T;
                            rtDW->param[7]  = v_0;
                            rtDW->param[8]  = v_1;
                            rtDW->param[9]  = (Ta - v_max) * a_max + rtU_start_vel;
                            rtDW->param[10] = a_max;
                            rtDW->param[11] = a_min;
                            rtDW->param[12] = a_max;
                            rtDW->param[13] = -a_max;
                            rtDW->param[14] = j_max;
                            rtDW->param[15] = sigma;
                        } else {
                            do {
                                exitg1 = 0;
                                if ((Ta < 2.0 * v_max) || (Td < 2.0 * v_max)) {
                                    a_max *= 0.99;
                                    v_max  = a_max / j_max;
                                    Td     = sqrt((a_lima - v_max * 2.0 * Tj1) * a_max + (rt_powd_snf(a_max, 4.0) / Tj2 + a_limd));
                                    Ta_tmp = a_max * a_max / j_max;
                                    Ta     = ((Ta_tmp - 2.0 * v_0) + Td) / (2.0 * a_max);
                                    Td     = ((Ta_tmp - 2.0 * v_1) + Td) / (2.0 * a_max);
                                    if ((Ta < 0.0) || (Td < 0.0)) {
                                        if (Ta < 0.0) {
                                            Tj2 = ((T - rtb_current_time) * j_max - sqrt((Tv_tmp *
                                                                                              Tv_tmp * j_max +
                                                                                          Tj1 * Tj1 * (v_1 - v_0)) *
                                                                                         j_max)) /
                                                  ((v_1 + v_0) * j_max);
                                            rtDW->param[0]  = 0.0;
                                            rtDW->param[1]  = 0.0;
                                            rtDW->param[2]  = (T - rtb_current_time) * 2.0 / (v_0 + v_1);
                                            rtDW->param[3]  = 0.0;
                                            rtDW->param[4]  = Tj2;
                                            rtDW->param[5]  = rtb_current_time;
                                            rtDW->param[6]  = T;
                                            rtDW->param[7]  = v_0;
                                            rtDW->param[8]  = v_1;
                                            rtDW->param[9]  = rtU_start_vel;
                                            rtDW->param[10] = a_max;
                                            rtDW->param[11] = a_min;
                                            rtDW->param[12] = 0.0;
                                            rtDW->param[13] = -j_max * Tj2;
                                            rtDW->param[14] = j_max;
                                            rtDW->param[15] = sigma;
                                            exitg1          = 1;
                                        } else if (Td < 0.0) {
                                            Ta              = (T - rtb_current_time) * 2.0 / (v_0 + v_1);
                                            Tj1             = ((T - rtb_current_time) * j_max - sqrt(Tv_tmp * Tv_tmp * j_max * j_max - Tj1 * Tj1 * (v_1 - v_0))) / ((v_1 + v_0) * j_max);
                                            a_lima          = j_max * Tj1;
                                            rtDW->param[0]  = Ta;
                                            rtDW->param[1]  = 0.0;
                                            rtDW->param[2]  = 0.0;
                                            rtDW->param[3]  = Tj1;
                                            rtDW->param[4]  = 0.0;
                                            rtDW->param[5]  = rtb_current_time;
                                            rtDW->param[6]  = T;
                                            rtDW->param[7]  = v_0;
                                            rtDW->param[8]  = v_1;
                                            rtDW->param[9]  = (Ta - Tj1) * a_lima + v_0;
                                            rtDW->param[10] = a_max;
                                            rtDW->param[11] = a_min;
                                            rtDW->param[12] = a_lima;
                                            rtDW->param[13] = 0.0;
                                            rtDW->param[14] = j_max;
                                            rtDW->param[15] = sigma;
                                            exitg1          = 1;
                                        }
                                    } else if ((Ta >= 2.0 * v_max) && (Td >= 2.0 * v_max)) {
                                        rtDW->param[0]  = Ta;
                                        rtDW->param[1]  = 0.0;
                                        rtDW->param[2]  = Td;
                                        rtDW->param[3]  = v_max;
                                        rtDW->param[4]  = v_max;
                                        rtDW->param[5]  = rtb_current_time;
                                        rtDW->param[6]  = T;
                                        rtDW->param[7]  = v_0;
                                        rtDW->param[8]  = v_1;
                                        rtDW->param[9]  = (Ta - v_max) * a_max + rtU_start_vel;
                                        rtDW->param[10] = a_max;
                                        rtDW->param[11] = a_min;
                                        rtDW->param[12] = a_max;
                                        rtDW->param[13] = -a_max;
                                        rtDW->param[14] = j_max;
                                        rtDW->param[15] = sigma;
                                        exitg1          = 1;
                                    }
                                } else {
                                    exitg1 = 1;
                                }
                            } while (exitg1 == 0);
                        }
                    }

                    rtDW->T = (rtDW->param[0] + rtDW->param[1]) + rtDW->param[2];
                } else {
                    /* Outport: '<Root>/pos' */
                    *rtY_pos = rtDW->current_pos;
                }
                break;

            default:
                /* case IN_InitParam: */
                rtDW->is_c3_SProfileGenerator = IN_GeneratePos;
                break;
        }
    }

    /* End of Chart: '<S1>/SProfileFSM' */

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick0" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick0++;
}

/* Model initialize function */
void SProfileGenerator_initialize(SProfileGenerator_RT_MODEL *const rtM)
{
    /* Registration code */

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
    UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
