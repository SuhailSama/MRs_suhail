/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * factor.c
 *
 * Code generation for function 'factor'
 *
 */

/* Include files */
#include "factor.h"
#include "fullColLDL2_.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "partialColLDL3_.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void factor(g_struct_T *obj, const real_T A[2601], int32_T ndims, int32_T ldA)
{
  ptrdiff_t incx_t;
  ptrdiff_t n_t;
  real_T SCALED_REG_PRIMAL;
  int32_T A_maxDiag_idx;
  int32_T LDimSizeP1;
  int32_T exitg2;
  int32_T idx;
  int32_T k;
  int32_T order;
  boolean_T exitg1;
  SCALED_REG_PRIMAL = 1.4901161193847656E-8 * obj->scaleFactor * (real_T)ndims;
  LDimSizeP1 = obj->ldm + 1;
  obj->ndims = ndims;
  for (idx = 0; idx < ndims; idx++) {
    A_maxDiag_idx = ldA * idx;
    order = obj->ldm * idx;
    for (k = 0; k < ndims; k++) {
      obj->FMat->data[order + k] = A[A_maxDiag_idx + k];
    }
  }
  if (ndims < 1) {
    A_maxDiag_idx = -1;
  } else {
    n_t = (ptrdiff_t)ndims;
    incx_t = (ptrdiff_t)(obj->ldm + 1);
    n_t = idamax(&n_t, &obj->FMat->data[0], &incx_t);
    A_maxDiag_idx = (int32_T)n_t - 1;
  }
  obj->regTol_ = muDoubleScalarMax(
      muDoubleScalarAbs(
          obj->FMat->data[A_maxDiag_idx + obj->ldm * A_maxDiag_idx]) *
          2.2204460492503131E-16,
      muDoubleScalarAbs(SCALED_REG_PRIMAL));
  if ((obj->FMat->size[0] * obj->FMat->size[1] > 16384) && (ndims > 128)) {
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < ndims)) {
      A_maxDiag_idx = LDimSizeP1 * k + 1;
      order = ndims - k;
      if (k + 48 <= ndims) {
        partialColLDL3_(obj, A_maxDiag_idx, order, SCALED_REG_PRIMAL);
        k += 48;
      } else {
        fullColLDL2_(obj, A_maxDiag_idx, order, SCALED_REG_PRIMAL);
        exitg1 = true;
      }
    }
  } else {
    fullColLDL2_(obj, 1, ndims, SCALED_REG_PRIMAL);
  }
  if (obj->ConvexCheck) {
    idx = 0;
    do {
      exitg2 = 0;
      if (idx <= ndims - 1) {
        if (obj->FMat->data[idx + obj->ldm * idx] <= 0.0) {
          obj->info = -idx - 1;
          exitg2 = 1;
        } else {
          idx++;
        }
      } else {
        obj->ConvexCheck = false;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
}

/* End of code generation (factor.c) */
