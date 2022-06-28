/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_deltax.c
 *
 * Code generation for function 'compute_deltax'
 *
 */

/* Include files */
#include "compute_deltax.h"
#include "factor.h"
#include "fullColLDL2_.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "partialColLDL3_.h"
#include "rt_nonfinite.h"
#include "solve.h"
#include "solve1.h"
#include "xgemm.h"
#include "xgemv.h"
#include "blas.h"
#include "lapacke.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void compute_deltax(const real_T H[2601], e_struct_T *solution,
                    i_struct_T *memspace, const f_struct_T *qrmanager,
                    g_struct_T *cholmanager, const h_struct_T *objective,
                    boolean_T alwaysPositiveDef)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t lda_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  real_T SCALED_REG_PRIMAL;
  real_T beta1;
  int32_T exitg2;
  int32_T idx;
  int32_T k;
  int32_T ldw;
  int32_T mNull_tmp;
  int32_T nVar;
  int32_T nVars;
  int32_T nullStartIdx_tmp;
  char_T TRANSA;
  char_T TRANSA1;
  char_T UPLO1;
  boolean_T exitg1;
  nVar = qrmanager->mrows - 1;
  mNull_tmp = qrmanager->mrows - qrmanager->ncols;
  if (mNull_tmp <= 0) {
    for (idx = 0; idx <= nVar; idx++) {
      solution->searchDir->data[idx] = 0.0;
    }
  } else {
    for (idx = 0; idx <= nVar; idx++) {
      solution->searchDir->data[idx] = -objective->grad->data[idx];
    }
    if (qrmanager->ncols <= 0) {
      switch (objective->objtype) {
      case 5:
        break;
      case 3:
        if (alwaysPositiveDef) {
          cholmanager->ndims = qrmanager->mrows;
          for (idx = 0; idx <= nVar; idx++) {
            nVars = (nVar + 1) * idx;
            ldw = cholmanager->ldm * idx;
            for (k = 0; k <= nVar; k++) {
              cholmanager->FMat->data[ldw + k] = H[nVars + k];
            }
          }
          n_t = LAPACKE_dpotrf_work(102, 'U', (ptrdiff_t)qrmanager->mrows,
                                    &cholmanager->FMat->data[0],
                                    (ptrdiff_t)cholmanager->ldm);
          if ((int32_T)n_t < 0) {
            nVar = cholmanager->FMat->size[0];
            nVars = cholmanager->FMat->size[1];
            k = cholmanager->FMat->size[0] * cholmanager->FMat->size[1];
            cholmanager->FMat->size[0] = nVar;
            cholmanager->FMat->size[1] = nVars;
            emxEnsureCapacity_real_T(cholmanager->FMat, k);
            nVar *= nVars;
            for (k = 0; k < nVar; k++) {
              cholmanager->FMat->data[k] = rtNaN;
            }
          }
          cholmanager->info = (int32_T)n_t;
        } else {
          factor(cholmanager, H, qrmanager->mrows, qrmanager->mrows);
        }
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else if (alwaysPositiveDef) {
          solve(cholmanager, solution->searchDir);
        } else {
          b_solve(cholmanager, solution->searchDir);
        }
        break;
      case 4:
        if (alwaysPositiveDef) {
          nVar = objective->nvar;
          cholmanager->ndims = objective->nvar;
          for (idx = 0; idx < nVar; idx++) {
            nVars = nVar * idx;
            ldw = cholmanager->ldm * idx;
            for (k = 0; k < nVar; k++) {
              cholmanager->FMat->data[ldw + k] = H[nVars + k];
            }
          }
          n_t = LAPACKE_dpotrf_work(102, 'U', (ptrdiff_t)objective->nvar,
                                    &cholmanager->FMat->data[0],
                                    (ptrdiff_t)cholmanager->ldm);
          if ((int32_T)n_t < 0) {
            nVar = cholmanager->FMat->size[0];
            nVars = cholmanager->FMat->size[1];
            k = cholmanager->FMat->size[0] * cholmanager->FMat->size[1];
            cholmanager->FMat->size[0] = nVar;
            cholmanager->FMat->size[1] = nVars;
            emxEnsureCapacity_real_T(cholmanager->FMat, k);
            nVar *= nVars;
            for (k = 0; k < nVar; k++) {
              cholmanager->FMat->data[k] = rtNaN;
            }
          }
          cholmanager->info = (int32_T)n_t;
          if (cholmanager->info != 0) {
            solution->state = -6;
          } else {
            solve(cholmanager, solution->searchDir);
            nVar = qrmanager->mrows - objective->nvar;
            SCALED_REG_PRIMAL = 1.0 / objective->beta;
            if (nVar >= 1) {
              n_t = (ptrdiff_t)nVar;
              incx_t = (ptrdiff_t)1;
              dscal(&n_t, &SCALED_REG_PRIMAL,
                    &solution->searchDir->data[objective->nvar], &incx_t);
            }
          }
        }
        break;
      }
    } else {
      nullStartIdx_tmp = qrmanager->ldq * qrmanager->ncols + 1;
      if (objective->objtype == 5) {
        for (idx = 0; idx < mNull_tmp; idx++) {
          memspace->workspace_double->data[idx] =
              -qrmanager->Q
                   ->data[nVar + qrmanager->ldq * (qrmanager->ncols + idx)];
        }
        f_xgemv(qrmanager->mrows, mNull_tmp, qrmanager->Q, nullStartIdx_tmp,
                qrmanager->ldq, memspace->workspace_double,
                solution->searchDir);
      } else {
        if (objective->objtype == 3) {
          ldw = memspace->workspace_double->size[0];
          xgemm(qrmanager->mrows, mNull_tmp, qrmanager->mrows, H,
                qrmanager->mrows, qrmanager->Q, nullStartIdx_tmp,
                qrmanager->ldq, memspace->workspace_double,
                memspace->workspace_double->size[0]);
          b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q,
                  nullStartIdx_tmp, qrmanager->ldq, memspace->workspace_double,
                  ldw, cholmanager->FMat, cholmanager->ldm);
        } else if (alwaysPositiveDef) {
          nVars = qrmanager->mrows;
          ldw = memspace->workspace_double->size[0];
          xgemm(objective->nvar, mNull_tmp, objective->nvar, H, objective->nvar,
                qrmanager->Q, nullStartIdx_tmp, qrmanager->ldq,
                memspace->workspace_double,
                memspace->workspace_double->size[0]);
          for (nVar = 0; nVar < mNull_tmp; nVar++) {
            k = objective->nvar + 1;
            for (idx = k; idx <= nVars; idx++) {
              memspace->workspace_double
                  ->data[(idx + memspace->workspace_double->size[0] * nVar) -
                         1] =
                  objective->beta *
                  qrmanager->Q->data[(idx + qrmanager->Q->size[0] *
                                                (nVar + qrmanager->ncols)) -
                                     1];
            }
          }
          b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q,
                  nullStartIdx_tmp, qrmanager->ldq, memspace->workspace_double,
                  ldw, cholmanager->FMat, cholmanager->ldm);
        }
        if (alwaysPositiveDef) {
          cholmanager->ndims = mNull_tmp;
          n_t = LAPACKE_dpotrf_work(102, 'U', (ptrdiff_t)mNull_tmp,
                                    &cholmanager->FMat->data[0],
                                    (ptrdiff_t)cholmanager->ldm);
          if ((int32_T)n_t < 0) {
            nVar = cholmanager->FMat->size[0];
            nVars = cholmanager->FMat->size[1];
            k = cholmanager->FMat->size[0] * cholmanager->FMat->size[1];
            cholmanager->FMat->size[0] = nVar;
            cholmanager->FMat->size[1] = nVars;
            emxEnsureCapacity_real_T(cholmanager->FMat, k);
            nVar *= nVars;
            for (k = 0; k < nVar; k++) {
              cholmanager->FMat->data[k] = rtNaN;
            }
          }
          cholmanager->info = (int32_T)n_t;
        } else {
          SCALED_REG_PRIMAL = 1.4901161193847656E-8 * cholmanager->scaleFactor *
                              (real_T)mNull_tmp;
          nVars = cholmanager->ldm + 1;
          cholmanager->ndims = mNull_tmp;
          n_t = (ptrdiff_t)mNull_tmp;
          incx_t = (ptrdiff_t)(cholmanager->ldm + 1);
          n_t = idamax(&n_t, &cholmanager->FMat->data[0], &incx_t);
          cholmanager->regTol_ = muDoubleScalarMax(
              muDoubleScalarAbs(
                  cholmanager->FMat
                      ->data[((int32_T)n_t +
                              cholmanager->ldm * ((int32_T)n_t - 1)) -
                             1]) *
                  2.2204460492503131E-16,
              muDoubleScalarAbs(SCALED_REG_PRIMAL));
          if ((cholmanager->FMat->size[0] * cholmanager->FMat->size[1] >
               16384) &&
              (mNull_tmp > 128)) {
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < mNull_tmp)) {
              nVar = nVars * k + 1;
              ldw = mNull_tmp - k;
              if (k + 48 <= mNull_tmp) {
                partialColLDL3_(cholmanager, nVar, ldw, SCALED_REG_PRIMAL);
                k += 48;
              } else {
                fullColLDL2_(cholmanager, nVar, ldw, SCALED_REG_PRIMAL);
                exitg1 = true;
              }
            }
          } else {
            fullColLDL2_(cholmanager, 1, mNull_tmp, SCALED_REG_PRIMAL);
          }
          if (cholmanager->ConvexCheck) {
            idx = 0;
            do {
              exitg2 = 0;
              if (idx <= mNull_tmp - 1) {
                if (cholmanager->FMat->data[idx + cholmanager->ldm * idx] <=
                    0.0) {
                  cholmanager->info = -idx - 1;
                  exitg2 = 1;
                } else {
                  idx++;
                }
              } else {
                cholmanager->ConvexCheck = false;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }
        }
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          if (qrmanager->mrows >= 1) {
            SCALED_REG_PRIMAL = -1.0;
            beta1 = 0.0;
            TRANSA = 'T';
            m_t = (ptrdiff_t)qrmanager->mrows;
            n_t = (ptrdiff_t)mNull_tmp;
            lda_t = (ptrdiff_t)qrmanager->ldq;
            incx_t = (ptrdiff_t)1;
            incy_t = (ptrdiff_t)1;
            dgemv(&TRANSA, &m_t, &n_t, &SCALED_REG_PRIMAL,
                  &qrmanager->Q->data[nullStartIdx_tmp - 1], &lda_t,
                  &objective->grad->data[0], &incx_t, &beta1,
                  &memspace->workspace_double->data[0], &incy_t);
          }
          if (alwaysPositiveDef) {
            if (cholmanager->ndims >= 1) {
              TRANSA = 'N';
              TRANSA1 = 'T';
              UPLO1 = 'U';
              n_t = (ptrdiff_t)cholmanager->ndims;
              lda_t = (ptrdiff_t)cholmanager->ldm;
              incx_t = (ptrdiff_t)1;
              dtrsv(&UPLO1, &TRANSA1, &TRANSA, &n_t,
                    &cholmanager->FMat->data[0], &lda_t,
                    &memspace->workspace_double->data[0], &incx_t);
            }
            if (cholmanager->ndims >= 1) {
              TRANSA = 'N';
              TRANSA1 = 'N';
              UPLO1 = 'U';
              n_t = (ptrdiff_t)cholmanager->ndims;
              lda_t = (ptrdiff_t)cholmanager->ldm;
              incx_t = (ptrdiff_t)1;
              dtrsv(&UPLO1, &TRANSA1, &TRANSA, &n_t,
                    &cholmanager->FMat->data[0], &lda_t,
                    &memspace->workspace_double->data[0], &incx_t);
            }
          } else {
            if (cholmanager->ndims >= 1) {
              TRANSA = 'U';
              TRANSA1 = 'N';
              UPLO1 = 'L';
              n_t = (ptrdiff_t)cholmanager->ndims;
              lda_t = (ptrdiff_t)cholmanager->ldm;
              incx_t = (ptrdiff_t)1;
              dtrsv(&UPLO1, &TRANSA1, &TRANSA, &n_t,
                    &cholmanager->FMat->data[0], &lda_t,
                    &memspace->workspace_double->data[0], &incx_t);
            }
            k = cholmanager->ndims;
            for (idx = 0; idx < k; idx++) {
              memspace->workspace_double->data[idx] /=
                  cholmanager->FMat->data[idx + cholmanager->ldm * idx];
            }
            if (cholmanager->ndims >= 1) {
              TRANSA = 'U';
              TRANSA1 = 'T';
              UPLO1 = 'L';
              n_t = (ptrdiff_t)cholmanager->ndims;
              lda_t = (ptrdiff_t)cholmanager->ldm;
              incx_t = (ptrdiff_t)1;
              dtrsv(&UPLO1, &TRANSA1, &TRANSA, &n_t,
                    &cholmanager->FMat->data[0], &lda_t,
                    &memspace->workspace_double->data[0], &incx_t);
            }
          }
          f_xgemv(qrmanager->mrows, mNull_tmp, qrmanager->Q, nullStartIdx_tmp,
                  qrmanager->ldq, memspace->workspace_double,
                  solution->searchDir);
        }
      }
    }
  }
}

/* End of code generation (compute_deltax.c) */
