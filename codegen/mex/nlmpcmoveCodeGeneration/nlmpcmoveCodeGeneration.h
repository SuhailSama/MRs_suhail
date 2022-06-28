/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * nlmpcmoveCodeGeneration.h
 *
 * Code generation for function 'nlmpcmoveCodeGeneration'
 *
 */

#pragma once

/* Include files */
#include "nlmpcmoveCodeGeneration_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void c_nlmpcmoveCodeGeneration_anonF(
    const real_T runtimedata_x[3], const real_T runtimedata_OutputMin[30],
    const real_T runtimedata_OutputMax[30], const real_T z[51],
    emxArray_real_T *varargout_1, real_T varargout_2[32],
    emxArray_real_T *varargout_3, real_T varargout_4[1632]);

void nlmpcmoveCodeGeneration(const real_T x[3], const real_T lastMV[2],
                             struct1_T *onlinedata, real_T mv[2],
                             struct2_T *info);

/* End of code generation (nlmpcmoveCodeGeneration.h) */
