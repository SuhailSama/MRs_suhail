/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeComplError.h
 *
 * Code generation for function 'computeComplError'
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
real_T computeComplError(const emxArray_real_T *fscales_lineq_constraint,
                         const emxArray_real_T *fscales_cineq_constraint,
                         const real_T xCurrent[51], int32_T mIneq,
                         const emxArray_real_T *cIneq,
                         const emxArray_int32_T *finiteLB, int32_T mLB,
                         const real_T lb[51], const emxArray_int32_T *finiteUB,
                         int32_T mUB, const real_T ub[51],
                         const emxArray_real_T *lambda, int32_T iL0);

/* End of code generation (computeComplError.h) */
