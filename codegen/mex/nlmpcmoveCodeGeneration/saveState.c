/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * saveState.c
 *
 * Code generation for function 'saveState'
 *
 */

/* Include files */
#include "saveState.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void saveState(e_struct_T *obj)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  int32_T k;
  obj->sqpFval_old = obj->sqpFval;
  for (k = 0; k < 51; k++) {
    obj->xstarsqp_old[k] = obj->xstarsqp[k];
    obj->grad_old->data[k] = obj->grad->data[k];
  }
  if (obj->mIneq >= 1) {
    n_t = (ptrdiff_t)obj->mIneq;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &obj->cIneq->data[0], &incx_t, &obj->cIneq_old->data[0],
          &incy_t);
  }
  k = obj->mEq;
  if (0 <= k - 1) {
    memcpy(&obj->cEq_old[0], &obj->cEq[0], k * sizeof(real_T));
  }
}

/* End of code generation (saveState.c) */
