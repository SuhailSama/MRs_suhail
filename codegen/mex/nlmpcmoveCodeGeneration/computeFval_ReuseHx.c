/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeFval_ReuseHx.c
 *
 * Code generation for function 'computeFval_ReuseHx'
 *
 */

/* Include files */
#include "computeFval_ReuseHx.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
real_T computeFval_ReuseHx(const h_struct_T *obj, emxArray_real_T *workspace,
                           const emxArray_real_T *f, const emxArray_real_T *x)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  const real_T *f_data;
  const real_T *x_data;
  real_T d;
  real_T val;
  real_T *workspace_data;
  int32_T b_i;
  int32_T i;
  int32_T maxRegVar_tmp;
  x_data = x->data;
  f_data = f->data;
  workspace_data = workspace->data;
  val = 0.0;
  switch (obj->objtype) {
  case 5:
    val = obj->gammaScalar * x_data[obj->nvar - 1];
    break;
  case 3:
    if (obj->hasLinear) {
      i = obj->nvar;
      for (b_i = 0; b_i < i; b_i++) {
        workspace_data[b_i] = 0.5 * obj->Hx->data[b_i] + f_data[b_i];
      }
      if (obj->nvar >= 1) {
        n_t = (ptrdiff_t)obj->nvar;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        val = ddot(&n_t, &x_data[0], &incx_t, &workspace_data[0], &incy_t);
      }
    } else {
      if (obj->nvar < 1) {
        d = 0.0;
      } else {
        n_t = (ptrdiff_t)obj->nvar;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        d = ddot(&n_t, &x_data[0], &incx_t, &obj->Hx->data[0], &incy_t);
      }
      val = 0.5 * d;
    }
    break;
  case 4:
    maxRegVar_tmp = obj->maxVar - 1;
    if (obj->hasLinear) {
      i = obj->nvar;
      for (b_i = 0; b_i < i; b_i++) {
        workspace_data[b_i] = f_data[b_i];
      }
      i = obj->maxVar - obj->nvar;
      for (b_i = 0; b_i <= i - 2; b_i++) {
        workspace_data[obj->nvar + b_i] = obj->rho;
      }
      for (b_i = 0; b_i < maxRegVar_tmp; b_i++) {
        workspace_data[b_i] += 0.5 * obj->Hx->data[b_i];
      }
      if (maxRegVar_tmp >= 1) {
        n_t = (ptrdiff_t)(obj->maxVar - 1);
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        val = ddot(&n_t, &x_data[0], &incx_t, &workspace_data[0], &incy_t);
      }
    } else {
      if (maxRegVar_tmp < 1) {
        d = 0.0;
      } else {
        n_t = (ptrdiff_t)(obj->maxVar - 1);
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        d = ddot(&n_t, &x_data[0], &incx_t, &obj->Hx->data[0], &incy_t);
      }
      val = 0.5 * d;
      i = obj->nvar + 1;
      for (b_i = i; b_i <= maxRegVar_tmp; b_i++) {
        val += x_data[b_i - 1] * obj->rho;
      }
    }
    break;
  }
  return val;
}

/* End of code generation (computeFval_ReuseHx.c) */
