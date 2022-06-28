/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeComplError.c
 *
 * Code generation for function 'computeComplError'
 *
 */

/* Include files */
#include "computeComplError.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
real_T computeComplError(const emxArray_real_T *fscales_lineq_constraint,
                         const emxArray_real_T *fscales_cineq_constraint,
                         const real_T xCurrent[51], int32_T mIneq,
                         const emxArray_real_T *cIneq,
                         const emxArray_int32_T *finiteLB, int32_T mLB,
                         const real_T lb[51], const emxArray_int32_T *finiteUB,
                         int32_T mUB, const real_T ub[51],
                         const emxArray_real_T *lambda, int32_T iL0)
{
  const real_T *cIneq_data;
  const real_T *fscales_cineq_constraint_data;
  const real_T *fscales_lineq_constraint_data;
  const real_T *lambda_data;
  real_T lbDelta;
  real_T lbLambda;
  real_T nlpComplError;
  const int32_T *finiteLB_data;
  const int32_T *finiteUB_data;
  int32_T iLineq0;
  int32_T idx;
  int32_T mLinIneq;
  int32_T mNonlinIneq;
  lambda_data = lambda->data;
  finiteUB_data = finiteUB->data;
  finiteLB_data = finiteLB->data;
  cIneq_data = cIneq->data;
  fscales_cineq_constraint_data = fscales_cineq_constraint->data;
  fscales_lineq_constraint_data = fscales_lineq_constraint->data;
  nlpComplError = 0.0;
  mLinIneq = fscales_lineq_constraint->size[0] - 1;
  mNonlinIneq = fscales_cineq_constraint->size[0];
  if ((mIneq + mLB) + mUB > 0) {
    for (idx = 0; idx <= mLinIneq; idx++) {
      lbDelta = lambda_data[(iL0 + idx) - 1];
      nlpComplError = muDoubleScalarMax(
          nlpComplError,
          muDoubleScalarMin(
              muDoubleScalarAbs(cIneq_data[idx] * lbDelta),
              muDoubleScalarMin(muDoubleScalarAbs(cIneq_data[idx]) /
                                    fscales_lineq_constraint_data[idx],
                                lbDelta * fscales_lineq_constraint_data[idx])));
    }
    iLineq0 = (iL0 + fscales_lineq_constraint->size[0]) - 2;
    for (idx = 0; idx < mNonlinIneq; idx++) {
      lbLambda = cIneq_data[(mLinIneq + idx) + 1];
      lbDelta = lambda_data[(iLineq0 + idx) + 1];
      nlpComplError = muDoubleScalarMax(
          nlpComplError,
          muDoubleScalarMin(
              muDoubleScalarAbs(lbLambda * lbDelta),
              muDoubleScalarMin(muDoubleScalarAbs(lbLambda) /
                                    fscales_cineq_constraint_data[idx],
                                lbDelta * fscales_cineq_constraint_data[idx])));
    }
    mLinIneq = (iL0 + mIneq) - 1;
    mNonlinIneq = mLinIneq + mLB;
    for (idx = 0; idx < mLB; idx++) {
      lbDelta = xCurrent[finiteLB_data[idx] - 1] - lb[finiteLB_data[idx] - 1];
      lbLambda = lambda_data[mLinIneq + idx];
      nlpComplError = muDoubleScalarMax(
          nlpComplError,
          muDoubleScalarMin(
              muDoubleScalarAbs(lbDelta * lbLambda),
              muDoubleScalarMin(muDoubleScalarAbs(lbDelta), lbLambda)));
    }
    for (idx = 0; idx < mUB; idx++) {
      lbDelta = ub[finiteUB_data[idx] - 1] - xCurrent[finiteUB_data[idx] - 1];
      lbLambda = lambda_data[mNonlinIneq + idx];
      nlpComplError = muDoubleScalarMax(
          nlpComplError,
          muDoubleScalarMin(
              muDoubleScalarAbs(lbDelta * lbLambda),
              muDoubleScalarMin(muDoubleScalarAbs(lbDelta), lbLambda)));
    }
  }
  return nlpComplError;
}

/* End of code generation (computeComplError.c) */
