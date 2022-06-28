/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgeqp3.c
 *
 * Code generation for function 'xgeqp3'
 *
 */

/* Include files */
#include "xgeqp3.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void xgeqp3(emxArray_real_T *A, int32_T m, int32_T n, emxArray_int32_T *jpvt,
            emxArray_real_T *tau)
{
  ptrdiff_t info_t;
  ptrdiff_t *jpvt_t_data;
  emxArray_ptrdiff_t *jpvt_t;
  real_T *A_data;
  real_T *tau_data;
  int32_T i;
  int32_T ma;
  int32_T minmana;
  int32_T na;
  int32_T *jpvt_data;
  jpvt_data = jpvt->data;
  A_data = A->data;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  ma = A->size[0];
  na = A->size[1];
  minmana = muIntScalarMin_sint32(ma, na);
  i = tau->size[0];
  tau->size[0] = minmana;
  emxEnsureCapacity_real_T(tau, i);
  tau_data = tau->data;
  emxInit_ptrdiff_t(&jpvt_t);
  if ((A->size[0] == 0) || (A->size[1] == 0) || (m < 1) || (n < 1)) {
    i = tau->size[0];
    tau->size[0] = minmana;
    emxEnsureCapacity_real_T(tau, i);
    tau_data = tau->data;
    for (i = 0; i < minmana; i++) {
      tau_data[i] = 0.0;
    }
    for (ma = 0; ma < n; ma++) {
      jpvt_data[ma] = ma + 1;
    }
  } else {
    i = jpvt_t->size[0];
    jpvt_t->size[0] = jpvt->size[0];
    emxEnsureCapacity_ptrdiff_t(jpvt_t, i);
    jpvt_t_data = jpvt_t->data;
    na = jpvt->size[0];
    for (i = 0; i < na; i++) {
      jpvt_t_data[i] = (ptrdiff_t)jpvt_data[i];
    }
    info_t =
        LAPACKE_dgeqp3(102, (ptrdiff_t)m, (ptrdiff_t)n, &A_data[0],
                       (ptrdiff_t)A->size[0], &jpvt_t_data[0], &tau_data[0]);
    if ((int32_T)info_t != 0) {
      for (na = 0; na < n; na++) {
        for (i = 0; i < m; i++) {
          A_data[na * ma + i] = rtNaN;
        }
      }
      na = muIntScalarMin_sint32(m, n) - 1;
      for (ma = 0; ma <= na; ma++) {
        tau_data[ma] = rtNaN;
      }
      i = na + 2;
      for (ma = i; ma <= minmana; ma++) {
        tau_data[ma - 1] = 0.0;
      }
      for (ma = 0; ma < n; ma++) {
        jpvt_data[ma] = ma + 1;
      }
    } else {
      for (ma = 0; ma < n; ma++) {
        jpvt_data[ma] = (int32_T)jpvt_t_data[ma];
      }
    }
  }
  emxFree_ptrdiff_t(&jpvt_t);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (xgeqp3.c) */
