/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeLambdaLSQ.c
 *
 * Code generation for function 'computeLambdaLSQ'
 *
 */

/* Include files */
#include "computeLambdaLSQ.h"
#include "computeQ_.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xgeqp3.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void computeLambdaLSQ(int32_T nVar, int32_T mConstr, f_struct_T *QRManager,
                      const emxArray_real_T *ATwset, int32_T ldA,
                      const emxArray_real_T *grad, emxArray_real_T *lambdaLSQ,
                      emxArray_real_T *workspace)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  const real_T *ATwset_data;
  real_T tol;
  real_T *lambdaLSQ_data;
  real_T *workspace_data;
  int32_T fullRank_R;
  int32_T iQR_diag;
  int32_T rankR;
  char_T DIAGA1;
  char_T TRANSA1;
  char_T UPLO1;
  boolean_T guard1 = false;
  lambdaLSQ_data = lambdaLSQ->data;
  ATwset_data = ATwset->data;
  for (fullRank_R = 0; fullRank_R < mConstr; fullRank_R++) {
    lambdaLSQ_data[fullRank_R] = 0.0;
  }
  guard1 = false;
  if ((ATwset->size[0] != 0) && (nVar * mConstr > 0)) {
    for (rankR = 0; rankR < mConstr; rankR++) {
      if (nVar >= 1) {
        n_t = (ptrdiff_t)nVar;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &ATwset_data[ldA * rankR], &incx_t,
              &QRManager->QR->data[QRManager->ldq * rankR], &incy_t);
      }
    }
    guard1 = true;
  } else if (nVar * mConstr == 0) {
    QRManager->mrows = nVar;
    QRManager->ncols = mConstr;
    QRManager->minRowCol = 0;
  } else {
    guard1 = true;
  }
  if (guard1) {
    QRManager->usedPivoting = true;
    QRManager->mrows = nVar;
    QRManager->ncols = mConstr;
    QRManager->minRowCol = muIntScalarMin_sint32(nVar, mConstr);
    xgeqp3(QRManager->QR, nVar, mConstr, QRManager->jpvt, QRManager->tau);
  }
  computeQ_(QRManager, QRManager->mrows);
  b_xgemv(nVar, nVar, QRManager->Q, QRManager->ldq, grad, workspace);
  workspace_data = workspace->data;
  tol = muDoubleScalarAbs(QRManager->QR->data[0]) *
        muDoubleScalarMin(1.4901161193847656E-8,
                          (real_T)muIntScalarMax_sint32(nVar, mConstr) *
                              2.2204460492503131E-16);
  fullRank_R = muIntScalarMin_sint32(nVar, mConstr);
  rankR = 0;
  iQR_diag = 0;
  while ((rankR < fullRank_R) &&
         (muDoubleScalarAbs(QRManager->QR->data[iQR_diag]) > tol)) {
    rankR++;
    iQR_diag = (iQR_diag + QRManager->ldq) + 1;
  }
  if (rankR >= 1) {
    DIAGA1 = 'N';
    TRANSA1 = 'N';
    UPLO1 = 'U';
    n_t = (ptrdiff_t)rankR;
    incy_t = (ptrdiff_t)QRManager->ldq;
    incx_t = (ptrdiff_t)1;
    dtrsv(&UPLO1, &TRANSA1, &DIAGA1, &n_t, &QRManager->QR->data[0], &incy_t,
          &workspace_data[0], &incx_t);
  }
  fullRank_R = muIntScalarMin_sint32(mConstr, fullRank_R);
  for (rankR = 0; rankR < fullRank_R; rankR++) {
    lambdaLSQ_data[QRManager->jpvt->data[rankR] - 1] = workspace_data[rankR];
  }
}

/* End of code generation (computeLambdaLSQ.c) */
