/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeGrad_StoreHx.c
 *
 * Code generation for function 'computeGrad_StoreHx'
 *
 */

/* Include files */
#include "computeGrad_StoreHx.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void computeGrad_StoreHx(h_struct_T *obj, const real_T H[2601],
                         const emxArray_real_T *f, const emxArray_real_T *x)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  const real_T *f_data;
  const real_T *x_data;
  real_T a;
  int32_T i;
  int32_T iy;
  int32_T k;
  int32_T maxRegVar;
  x_data = x->data;
  f_data = f->data;
  switch (obj->objtype) {
  case 5:
    i = obj->nvar;
    for (iy = 0; iy <= i - 2; iy++) {
      obj->grad->data[iy] = 0.0;
    }
    obj->grad->data[obj->nvar - 1] = obj->gammaScalar;
    break;
  case 3:
    e_xgemv(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
    i = obj->nvar;
    for (iy = 0; iy < i; iy++) {
      obj->grad->data[iy] = obj->Hx->data[iy];
    }
    if (obj->hasLinear && (obj->nvar >= 1)) {
      a = 1.0;
      n_t = (ptrdiff_t)obj->nvar;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      daxpy(&n_t, &a, &f_data[0], &incx_t, &obj->grad->data[0], &incy_t);
    }
    break;
  case 4:
    maxRegVar = obj->maxVar - 1;
    e_xgemv(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
    i = obj->nvar + 1;
    for (iy = i; iy <= maxRegVar; iy++) {
      obj->Hx->data[iy - 1] = obj->beta * x_data[iy - 1];
    }
    for (iy = 0; iy < maxRegVar; iy++) {
      obj->grad->data[iy] = obj->Hx->data[iy];
    }
    if (obj->hasLinear && (obj->nvar >= 1)) {
      a = 1.0;
      n_t = (ptrdiff_t)obj->nvar;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      daxpy(&n_t, &a, &f_data[0], &incx_t, &obj->grad->data[0], &incy_t);
    }
    maxRegVar = (obj->maxVar - obj->nvar) - 1;
    if (maxRegVar >= 1) {
      iy = obj->nvar;
      i = maxRegVar - 1;
      for (k = 0; k <= i; k++) {
        maxRegVar = iy + k;
        obj->grad->data[maxRegVar] += obj->rho;
      }
    }
    break;
  }
}

/* End of code generation (computeGrad_StoreHx.c) */
