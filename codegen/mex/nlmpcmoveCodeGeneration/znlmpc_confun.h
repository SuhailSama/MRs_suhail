/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * znlmpc_confun.h
 *
 * Code generation for function 'znlmpc_confun'
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
void outputBounds(const real_T runtimedata_OutputMin[30],
                  const real_T runtimedata_OutputMax[30], const real_T X[33],
                  real_T e, emxArray_real_T *c, emxArray_real_T *Jc);

/* End of code generation (znlmpc_confun.h) */
