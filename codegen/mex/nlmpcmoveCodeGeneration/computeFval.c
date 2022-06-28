/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeFval.c
 *
 * Code generation for function 'computeFval'
 *
 */

/* Include files */
#include "computeFval.h"
#include "linearForm_.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
real_T computeFval(const h_struct_T *obj, emxArray_real_T *workspace,
                   const real_T H[2601], const emxArray_real_T *f,
                   const emxArray_real_T *x)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  const real_T *x_data;
  real_T val;
  real_T *workspace_data;
  int32_T i;
  int32_T i1;
  int32_T idx;
  x_data = x->data;
  val = 0.0;
  switch (obj->objtype) {
  case 5:
    val = obj->gammaScalar * x_data[obj->nvar - 1];
    break;
  case 3:
    linearForm_(obj->hasLinear, obj->nvar, workspace, H, f, x);
    workspace_data = workspace->data;
    if (obj->nvar >= 1) {
      n_t = (ptrdiff_t)obj->nvar;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      val = ddot(&n_t, &x_data[0], &incx_t, &workspace_data[0], &incy_t);
    }
    break;
  case 4:
    linearForm_(obj->hasLinear, obj->nvar, workspace, H, f, x);
    workspace_data = workspace->data;
    i = obj->nvar + 1;
    i1 = obj->maxVar - 1;
    for (idx = i; idx <= i1; idx++) {
      workspace_data[idx - 1] = 0.5 * obj->beta * x_data[idx - 1] + obj->rho;
    }
    if (i1 >= 1) {
      n_t = (ptrdiff_t)(obj->maxVar - 1);
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      val = ddot(&n_t, &x_data[0], &incx_t, &workspace_data[0], &incy_t);
    }
    break;
  }
  return val;
}

/* End of code generation (computeFval.c) */
