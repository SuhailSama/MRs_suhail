/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * soc.c
 *
 * Code generation for function 'soc'
 *
 */

/* Include files */
#include "soc.h"
#include "addAeqConstr.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
boolean_T soc(const real_T Hessian[2601], const emxArray_real_T *grad,
              e_struct_T *TrialState, i_struct_T *memspace,
              j_struct_T *WorkingSet, f_struct_T *QRManager,
              g_struct_T *CholManager, h_struct_T *QPObjective,
              const d_struct_T *qpoptions)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t lda_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  d_struct_T b_qpoptions;
  real_T beta1;
  real_T oldDirIdx;
  int32_T i;
  int32_T idx;
  int32_T idxIneqOffset;
  int32_T idx_Aineq;
  int32_T idx_lower;
  int32_T idx_upper;
  int32_T mConstrMax;
  int32_T mIneq;
  int32_T mLB;
  int32_T nVar;
  int32_T nWIneq_old;
  int32_T nWLower_old;
  int32_T nWUpper_old;
  char_T TRANSA;
  boolean_T success;
  nWIneq_old = WorkingSet->nWConstr[2];
  nWLower_old = WorkingSet->nWConstr[3];
  nWUpper_old = WorkingSet->nWConstr[4];
  nVar = WorkingSet->nVar;
  mConstrMax = WorkingSet->mConstrMax;
  for (idx_lower = 0; idx_lower < nVar; idx_lower++) {
    TrialState->xstarsqp[idx_lower] = TrialState->xstarsqp_old[idx_lower];
    TrialState->socDirection->data[idx_lower] =
        TrialState->xstar->data[idx_lower];
  }
  if (WorkingSet->mConstrMax >= 1) {
    n_t = (ptrdiff_t)WorkingSet->mConstrMax;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &TrialState->lambda->data[0], &incx_t,
          &TrialState->lambdaStopTest->data[0], &incy_t);
  }
  idx_Aineq = WorkingSet->sizes[1] - 1;
  mIneq = WorkingSet->sizes[2];
  idxIneqOffset = WorkingSet->isActiveIdx[2];
  if (WorkingSet->sizes[1] > 0) {
    for (idx = 0; idx <= idx_Aineq; idx++) {
      WorkingSet->beq[idx] = -TrialState->cEq[idx];
    }
    if ((WorkingSet->nVar >= 1) && (WorkingSet->sizes[1] >= 1)) {
      oldDirIdx = 1.0;
      beta1 = 1.0;
      TRANSA = 'T';
      m_t = (ptrdiff_t)WorkingSet->nVar;
      n_t = (ptrdiff_t)WorkingSet->sizes[1];
      lda_t = (ptrdiff_t)WorkingSet->ldA;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dgemv(&TRANSA, &m_t, &n_t, &oldDirIdx, &WorkingSet->Aeq->data[0], &lda_t,
            &TrialState->searchDir->data[0], &incx_t, &beta1,
            &WorkingSet->beq[0], &incy_t);
    }
    for (idx_lower = 0; idx_lower <= idx_Aineq; idx_lower++) {
      WorkingSet->bwset->data[WorkingSet->sizes[0] + idx_lower] =
          WorkingSet->beq[idx_lower];
    }
  }
  if (WorkingSet->sizes[2] > 0) {
    for (idx = 0; idx < mIneq; idx++) {
      WorkingSet->bineq->data[idx] = -TrialState->cIneq->data[idx];
    }
    if ((WorkingSet->nVar >= 1) && (WorkingSet->sizes[2] >= 1)) {
      oldDirIdx = 1.0;
      beta1 = 1.0;
      TRANSA = 'T';
      m_t = (ptrdiff_t)WorkingSet->nVar;
      n_t = (ptrdiff_t)WorkingSet->sizes[2];
      lda_t = (ptrdiff_t)WorkingSet->ldA;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dgemv(&TRANSA, &m_t, &n_t, &oldDirIdx, &WorkingSet->Aineq->data[0],
            &lda_t, &TrialState->searchDir->data[0], &incx_t, &beta1,
            &WorkingSet->bineq->data[0], &incy_t);
    }
    idx_Aineq = 1;
    idx_lower = WorkingSet->sizes[2] + 1;
    idx_upper = (WorkingSet->sizes[2] + WorkingSet->sizes[3]) + 1;
    i = WorkingSet->nActiveConstr;
    for (idx = idxIneqOffset; idx <= i; idx++) {
      mLB = WorkingSet->Wlocalidx->data[idx - 1];
      switch (WorkingSet->Wid->data[idx - 1]) {
      case 3:
        mIneq = idx_Aineq;
        idx_Aineq++;
        WorkingSet->bwset->data[idx - 1] = WorkingSet->bineq->data[mLB - 1];
        break;
      case 4:
        mIneq = idx_lower;
        idx_lower++;
        break;
      default:
        mIneq = idx_upper;
        idx_upper++;
        break;
      }
      TrialState->workingset_old->data[mIneq - 1] = mLB;
    }
  }
  for (idx_lower = 0; idx_lower < nVar; idx_lower++) {
    TrialState->xstar->data[idx_lower] = TrialState->xstarsqp[idx_lower];
  }
  b_qpoptions = *qpoptions;
  driver(Hessian, grad, TrialState, memspace, WorkingSet, QRManager,
         CholManager, QPObjective, qpoptions, &b_qpoptions);
  while ((WorkingSet->mEqRemoved > 0) &&
         (WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1] >=
          TrialState->iNonEq0)) {
    addAeqConstr(WorkingSet,
                 WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1]);
    WorkingSet->mEqRemoved--;
  }
  for (idx = 0; idx < nVar; idx++) {
    oldDirIdx = TrialState->socDirection->data[idx];
    TrialState->socDirection->data[idx] =
        TrialState->xstar->data[idx] - TrialState->socDirection->data[idx];
    TrialState->xstar->data[idx] = oldDirIdx;
  }
  if (nVar < 1) {
    oldDirIdx = 0.0;
    beta1 = 0.0;
  } else {
    n_t = (ptrdiff_t)nVar;
    incx_t = (ptrdiff_t)1;
    oldDirIdx = dnrm2(&n_t, &TrialState->socDirection->data[0], &incx_t);
    n_t = (ptrdiff_t)nVar;
    incx_t = (ptrdiff_t)1;
    beta1 = dnrm2(&n_t, &TrialState->xstar->data[0], &incx_t);
  }
  success = (oldDirIdx <= 2.0 * beta1);
  i = WorkingSet->sizes[1] - 1;
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  if (WorkingSet->sizes[1] > 0) {
    for (idx = 0; idx <= i; idx++) {
      WorkingSet->beq[idx] = -TrialState->cEq[idx];
    }
    for (idx_lower = 0; idx_lower <= i; idx_lower++) {
      WorkingSet->bwset->data[WorkingSet->sizes[0] + idx_lower] =
          WorkingSet->beq[idx_lower];
    }
  }
  if (WorkingSet->sizes[2] > 0) {
    for (idx = 0; idx < mIneq; idx++) {
      WorkingSet->bineq->data[idx] = -TrialState->cIneq->data[idx];
    }
    if (!success) {
      idx_Aineq = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
      idx_lower = WorkingSet->nActiveConstr;
      for (idx_upper = idx_Aineq; idx_upper <= idx_lower; idx_upper++) {
        WorkingSet->isActiveConstr
            ->data[(WorkingSet->isActiveIdx
                        [WorkingSet->Wid->data[idx_upper - 1] - 1] +
                    WorkingSet->Wlocalidx->data[idx_upper - 1]) -
                   2] = false;
      }
      WorkingSet->nWConstr[2] = 0;
      WorkingSet->nWConstr[3] = 0;
      WorkingSet->nWConstr[4] = 0;
      WorkingSet->nActiveConstr =
          WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1];
      for (idx = 0; idx < nWIneq_old; idx++) {
        idx_Aineq = TrialState->workingset_old->data[idx];
        WorkingSet->nWConstr[2]++;
        WorkingSet->isActiveConstr
            ->data[(WorkingSet->isActiveIdx[2] + idx_Aineq) - 2] = true;
        WorkingSet->nActiveConstr++;
        WorkingSet->Wid->data[WorkingSet->nActiveConstr - 1] = 3;
        WorkingSet->Wlocalidx->data[WorkingSet->nActiveConstr - 1] = idx_Aineq;
        idx_lower = WorkingSet->ldA * (idx_Aineq - 1);
        idx_upper = WorkingSet->ldA * (WorkingSet->nActiveConstr - 1);
        i = WorkingSet->nVar - 1;
        for (nVar = 0; nVar <= i; nVar++) {
          WorkingSet->ATwset->data[idx_upper + nVar] =
              WorkingSet->Aineq->data[idx_lower + nVar];
        }
        WorkingSet->bwset->data[WorkingSet->nActiveConstr - 1] =
            WorkingSet->bineq->data[idx_Aineq - 1];
      }
      for (idx = 0; idx < nWLower_old; idx++) {
        addBoundToActiveSetMatrix_(
            WorkingSet, 4, TrialState->workingset_old->data[idx + mIneq]);
      }
      for (idx = 0; idx < nWUpper_old; idx++) {
        addBoundToActiveSetMatrix_(
            WorkingSet, 5,
            TrialState->workingset_old->data[(idx + mIneq) + mLB]);
      }
    }
  }
  if (!success) {
    if (mConstrMax >= 1) {
      n_t = (ptrdiff_t)mConstrMax;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dcopy(&n_t, &TrialState->lambdaStopTest->data[0], &incx_t,
            &TrialState->lambda->data[0], &incy_t);
    }
  } else {
    sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr,
                 WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid,
                 WorkingSet->Wlocalidx, memspace->workspace_double);
  }
  return success;
}

/* End of code generation (soc.c) */
