/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computePrimalFeasError.h
 *
 * Code generation for function 'computePrimalFeasError'
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
real_T computePrimalFeasError(const real_T x[51], int32_T mLinIneq,
                              int32_T mNonlinIneq, const emxArray_real_T *cIneq,
                              int32_T mLinEq, int32_T mNonlinEq,
                              const real_T cEq[32],
                              const emxArray_int32_T *finiteLB, int32_T mLB,
                              const real_T lb[51],
                              const emxArray_int32_T *finiteUB, int32_T mUB,
                              const real_T ub[51]);

/* End of code generation (computePrimalFeasError.h) */
