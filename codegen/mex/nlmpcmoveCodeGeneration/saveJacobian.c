/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * saveJacobian.c
 *
 * Code generation for function 'saveJacobian'
 *
 */

/* Include files */
#include "saveJacobian.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void saveJacobian(e_struct_T *obj, int32_T nVar, int32_T mIneq,
                  const emxArray_real_T *JacCineqTrans, int32_T ineqCol0,
                  int32_T mEq, const emxArray_real_T *JacCeqTrans,
                  int32_T eqCol0, int32_T ldJ)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  const real_T *JacCeqTrans_data;
  const real_T *JacCineqTrans_data;
  int32_T i;
  int32_T iCol;
  int32_T idx_col;
  JacCeqTrans_data = JacCeqTrans->data;
  JacCineqTrans_data = JacCineqTrans->data;
  iCol = ldJ * (ineqCol0 - 1);
  i = mIneq - ineqCol0;
  for (idx_col = 0; idx_col <= i; idx_col++) {
    if (nVar >= 1) {
      n_t = (ptrdiff_t)nVar;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dcopy(&n_t, &JacCineqTrans_data[iCol + idx_col * ldJ], &incx_t,
            &obj->JacCineqTrans_old->data[idx_col * ldJ], &incy_t);
    }
  }
  iCol = ldJ * (eqCol0 - 1);
  i = mEq - eqCol0;
  for (idx_col = 0; idx_col <= i; idx_col++) {
    if (nVar >= 1) {
      n_t = (ptrdiff_t)nVar;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dcopy(&n_t, &JacCeqTrans_data[iCol + idx_col * ldJ], &incx_t,
            &obj->JacCeqTrans_old->data[idx_col * ldJ], &incy_t);
    }
  }
}

/* End of code generation (saveJacobian.c) */
