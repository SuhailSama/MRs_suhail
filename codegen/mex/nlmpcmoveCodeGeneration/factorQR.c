/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * factorQR.c
 *
 * Code generation for function 'factorQR'
 *
 */

/* Include files */
#include "factorQR.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "xgeqrf.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void factorQR(f_struct_T *obj, const emxArray_real_T *A, int32_T mrows,
              int32_T ncols, int32_T ldA)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  const real_T *A_data;
  int32_T idx;
  boolean_T guard1 = false;
  A_data = A->data;
  guard1 = false;
  if ((A->size[0] != 0) && (mrows * ncols > 0)) {
    for (idx = 0; idx < ncols; idx++) {
      if (mrows >= 1) {
        n_t = (ptrdiff_t)mrows;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &A_data[ldA * idx], &incx_t, &obj->QR->data[obj->ldq * idx],
              &incy_t);
      }
    }
    guard1 = true;
  } else if (mrows * ncols == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }
  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt->data[idx] = idx + 1;
    }
    obj->minRowCol = muIntScalarMin_sint32(mrows, ncols);
    xgeqrf(obj->QR, mrows, ncols, obj->tau);
  }
}

/* End of code generation (factorQR.c) */
