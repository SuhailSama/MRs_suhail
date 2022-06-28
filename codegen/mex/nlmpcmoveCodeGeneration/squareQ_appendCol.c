/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * squareQ_appendCol.c
 *
 * Code generation for function 'squareQ_appendCol'
 *
 */

/* Include files */
#include "squareQ_appendCol.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void squareQ_appendCol(f_struct_T *obj, const emxArray_real_T *vec, int32_T iv0)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t lda_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  const real_T *vec_data;
  real_T beta1;
  real_T c;
  real_T s;
  real_T temp;
  int32_T Qk0;
  int32_T b_temp_tmp;
  int32_T idx;
  int32_T iy;
  int32_T k;
  int32_T n;
  int32_T temp_tmp;
  char_T TRANSA;
  vec_data = vec->data;
  Qk0 = obj->ncols + 1;
  obj->minRowCol = muIntScalarMin_sint32(obj->mrows, Qk0);
  if (obj->mrows >= 1) {
    temp = 1.0;
    beta1 = 0.0;
    TRANSA = 'T';
    m_t = (ptrdiff_t)obj->mrows;
    n_t = (ptrdiff_t)obj->mrows;
    lda_t = (ptrdiff_t)obj->ldq;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dgemv(&TRANSA, &m_t, &n_t, &temp, &obj->Q->data[0], &lda_t,
          &vec_data[iv0 - 1], &incx_t, &beta1,
          &obj->QR->data[obj->ldq * obj->ncols], &incy_t);
  }
  obj->ncols++;
  obj->jpvt->data[obj->ncols - 1] = obj->ncols;
  for (idx = obj->mrows - 2; idx + 2 > obj->ncols; idx--) {
    Qk0 = idx + obj->ldq * (obj->ncols - 1);
    beta1 = obj->QR->data[Qk0];
    temp = obj->QR->data[Qk0 + 1];
    c = 0.0;
    s = 0.0;
    drotg(&beta1, &temp, &c, &s);
    obj->QR->data[Qk0] = beta1;
    obj->QR->data[Qk0 + 1] = temp;
    Qk0 = obj->ldq * idx;
    n = obj->mrows;
    if (obj->mrows >= 1) {
      iy = obj->ldq + Qk0;
      for (k = 0; k < n; k++) {
        temp_tmp = iy + k;
        b_temp_tmp = Qk0 + k;
        temp = c * obj->Q->data[b_temp_tmp] + s * obj->Q->data[temp_tmp];
        obj->Q->data[temp_tmp] =
            c * obj->Q->data[temp_tmp] - s * obj->Q->data[b_temp_tmp];
        obj->Q->data[b_temp_tmp] = temp;
      }
    }
  }
}

/* End of code generation (squareQ_appendCol.c) */
