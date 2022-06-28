/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * maxConstraintViolation.c
 *
 * Code generation for function 'maxConstraintViolation'
 *
 */

/* Include files */
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
real_T maxConstraintViolation(j_struct_T *obj, const emxArray_real_T *x)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  const real_T *x_data;
  real_T v;
  int32_T idx;
  int32_T mEq;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mUB;
  int32_T offsetEq2;
  x_data = x->data;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  if (obj->probType == 2) {
    v = 0.0;
    mIneq = obj->sizes[2];
    mEq = obj->sizes[1] - 1;
    if (obj->Aineq->size[0] != 0) {
      if (obj->sizes[2] >= 1) {
        n_t = (ptrdiff_t)obj->sizes[2];
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &obj->bineq->data[0], &incx_t,
              &obj->maxConstrWorkspace->data[0], &incy_t);
      }
      c_xgemv(obj->nVarOrig, obj->sizes[2], obj->Aineq, obj->ldA, x,
              obj->maxConstrWorkspace);
      for (idx = 0; idx < mIneq; idx++) {
        obj->maxConstrWorkspace->data[idx] -= x_data[obj->nVarOrig + idx];
        v = muDoubleScalarMax(v, obj->maxConstrWorkspace->data[idx]);
      }
    }
    if (obj->Aeq->size[0] != 0) {
      for (mIneq = 0; mIneq <= mEq; mIneq++) {
        obj->maxConstrWorkspace->data[mIneq] = obj->beq[mIneq];
      }
      c_xgemv(obj->nVarOrig, obj->sizes[1], obj->Aeq, obj->ldA, x,
              obj->maxConstrWorkspace);
      mIneq = obj->nVarOrig + obj->sizes[2];
      offsetEq2 = mIneq + obj->sizes[1];
      for (idx = 0; idx <= mEq; idx++) {
        obj->maxConstrWorkspace->data[idx] =
            (obj->maxConstrWorkspace->data[idx] - x_data[mIneq + idx]) +
            x_data[offsetEq2 + idx];
        v = muDoubleScalarMax(
            v, muDoubleScalarAbs(obj->maxConstrWorkspace->data[idx]));
      }
    }
  } else {
    v = 0.0;
    mIneq = obj->sizes[2];
    mEq = obj->sizes[1] - 1;
    if (obj->Aineq->size[0] != 0) {
      if (obj->sizes[2] >= 1) {
        n_t = (ptrdiff_t)obj->sizes[2];
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &obj->bineq->data[0], &incx_t,
              &obj->maxConstrWorkspace->data[0], &incy_t);
      }
      c_xgemv(obj->nVar, obj->sizes[2], obj->Aineq, obj->ldA, x,
              obj->maxConstrWorkspace);
      for (idx = 0; idx < mIneq; idx++) {
        v = muDoubleScalarMax(v, obj->maxConstrWorkspace->data[idx]);
      }
    }
    if (obj->Aeq->size[0] != 0) {
      for (mIneq = 0; mIneq <= mEq; mIneq++) {
        obj->maxConstrWorkspace->data[mIneq] = obj->beq[mIneq];
      }
      c_xgemv(obj->nVar, obj->sizes[1], obj->Aeq, obj->ldA, x,
              obj->maxConstrWorkspace);
      for (idx = 0; idx <= mEq; idx++) {
        v = muDoubleScalarMax(
            v, muDoubleScalarAbs(obj->maxConstrWorkspace->data[idx]));
      }
    }
  }
  if (obj->sizes[3] > 0) {
    for (idx = 0; idx < mLB; idx++) {
      mIneq = obj->indexLB->data[idx] - 1;
      v = muDoubleScalarMax(v, -x_data[mIneq] - obj->lb->data[mIneq]);
    }
  }
  if (obj->sizes[4] > 0) {
    for (idx = 0; idx < mUB; idx++) {
      mIneq = obj->indexUB->data[idx] - 1;
      v = muDoubleScalarMax(v, x_data[mIneq] - obj->ub->data[mIneq]);
    }
  }
  if (obj->sizes[0] > 0) {
    for (idx = 0; idx < mFixed; idx++) {
      v = muDoubleScalarMax(
          v, muDoubleScalarAbs(x_data[obj->indexFixed->data[idx] - 1] -
                               obj->ub->data[obj->indexFixed->data[idx] - 1]));
    }
  }
  return v;
}

/* End of code generation (maxConstraintViolation.c) */
