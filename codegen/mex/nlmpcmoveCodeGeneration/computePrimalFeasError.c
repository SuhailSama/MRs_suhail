/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computePrimalFeasError.c
 *
 * Code generation for function 'computePrimalFeasError'
 *
 */

/* Include files */
#include "computePrimalFeasError.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
real_T computePrimalFeasError(const real_T x[51], int32_T mLinIneq,
                              int32_T mNonlinIneq, const emxArray_real_T *cIneq,
                              int32_T mLinEq, int32_T mNonlinEq,
                              const real_T cEq[32],
                              const emxArray_int32_T *finiteLB, int32_T mLB,
                              const real_T lb[51],
                              const emxArray_int32_T *finiteUB, int32_T mUB,
                              const real_T ub[51])
{
  const real_T *cIneq_data;
  real_T feasError;
  const int32_T *finiteLB_data;
  const int32_T *finiteUB_data;
  int32_T idx;
  int32_T mEq;
  int32_T mIneq;
  finiteUB_data = finiteUB->data;
  finiteLB_data = finiteLB->data;
  cIneq_data = cIneq->data;
  feasError = 0.0;
  mEq = mNonlinEq + mLinEq;
  mIneq = mNonlinIneq + mLinIneq;
  for (idx = 0; idx < mEq; idx++) {
    feasError = muDoubleScalarMax(feasError, muDoubleScalarAbs(cEq[idx]));
  }
  for (idx = 0; idx < mIneq; idx++) {
    feasError = muDoubleScalarMax(feasError, cIneq_data[idx]);
  }
  for (idx = 0; idx < mLB; idx++) {
    feasError = muDoubleScalarMax(feasError, lb[finiteLB_data[idx] - 1] -
                                                 x[finiteLB_data[idx] - 1]);
  }
  for (idx = 0; idx < mUB; idx++) {
    feasError = muDoubleScalarMax(feasError, x[finiteUB_data[idx] - 1] -
                                                 ub[finiteUB_data[idx] - 1]);
  }
  return feasError;
}

/* End of code generation (computePrimalFeasError.c) */
