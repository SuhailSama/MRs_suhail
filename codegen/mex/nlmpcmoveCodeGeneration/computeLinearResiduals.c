/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeLinearResiduals.c
 *
 * Code generation for function 'computeLinearResiduals'
 *
 */

/* Include files */
#include "computeLinearResiduals.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void computeLinearResiduals(const real_T x[51], int32_T nVar,
                            emxArray_real_T *workspaceIneq, int32_T mLinIneq,
                            const emxArray_real_T *AineqT,
                            const emxArray_real_T *bineq, int32_T ldAi,
                            real_T workspaceEq[32], int32_T mLinEq,
                            const emxArray_real_T *AeqT, int32_T ldAe)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t lda_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  const real_T *AeqT_data;
  const real_T *AineqT_data;
  const real_T *bineq_data;
  real_T alpha1;
  real_T beta1;
  real_T *workspaceIneq_data;
  char_T TRANSA;
  AeqT_data = AeqT->data;
  bineq_data = bineq->data;
  AineqT_data = AineqT->data;
  workspaceIneq_data = workspaceIneq->data;
  if (mLinIneq > 0) {
    n_t = (ptrdiff_t)mLinIneq;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &bineq_data[0], &incx_t, &workspaceIneq_data[0], &incy_t);
    if (nVar >= 1) {
      alpha1 = 1.0;
      beta1 = -1.0;
      TRANSA = 'T';
      m_t = (ptrdiff_t)nVar;
      n_t = (ptrdiff_t)mLinIneq;
      lda_t = (ptrdiff_t)ldAi;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dgemv(&TRANSA, &m_t, &n_t, &alpha1, &AineqT_data[0], &lda_t, &x[0],
            &incx_t, &beta1, &workspaceIneq_data[0], &incy_t);
    }
  }
  if ((mLinEq > 0) && (nVar >= 1)) {
    alpha1 = 1.0;
    beta1 = -1.0;
    TRANSA = 'T';
    m_t = (ptrdiff_t)nVar;
    n_t = (ptrdiff_t)mLinEq;
    lda_t = (ptrdiff_t)ldAe;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dgemv(&TRANSA, &m_t, &n_t, &alpha1, &AeqT_data[0], &lda_t, &x[0], &incx_t,
          &beta1, &workspaceEq[0], &incy_t);
  }
}

/* End of code generation (computeLinearResiduals.c) */
