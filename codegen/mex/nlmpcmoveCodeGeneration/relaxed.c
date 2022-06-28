/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * relaxed.c
 *
 * Code generation for function 'relaxed'
 *
 */

/* Include files */
#include "relaxed.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "sortLambdaQP.h"
#include "xgemv.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void relaxed(const real_T Hessian[2601], const emxArray_real_T *grad,
             e_struct_T *TrialState, struct_T *MeritFunction,
             i_struct_T *memspace, j_struct_T *WorkingSet,
             f_struct_T *QRManager, g_struct_T *CholManager,
             h_struct_T *QPObjective, d_struct_T *qpoptions)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  d_struct_T b_qpoptions;
  const real_T *grad_data;
  real_T beta;
  real_T qpfvalLinearExcess;
  real_T qpfvalQuadExcess;
  real_T rho;
  int32_T b_mEq;
  int32_T b_mIneq;
  int32_T idx;
  int32_T idx_negative;
  int32_T idx_positive;
  int32_T mEq;
  int32_T mFiniteLB;
  int32_T mIneq;
  int32_T nActiveLBArtificial;
  int32_T nVarMax;
  int32_T nVarOrig;
  int32_T tf_tmp;
  boolean_T b_tf;
  boolean_T tf;
  grad_data = grad->data;
  nVarOrig = WorkingSet->nVar;
  nVarMax = WorkingSet->nVarMax;
  mIneq = WorkingSet->sizes[2];
  mEq = WorkingSet->sizes[1];
  beta = 0.0;
  for (idx = 0; idx < nVarOrig; idx++) {
    beta += Hessian[idx + 51 * idx];
  }
  beta /= (real_T)WorkingSet->nVar;
  if (TrialState->sqpIterations <= 1) {
    if (QPObjective->nvar < 1) {
      idx_positive = 0;
    } else {
      n_t = (ptrdiff_t)QPObjective->nvar;
      incx_t = (ptrdiff_t)1;
      n_t = idamax(&n_t, &grad_data[0], &incx_t);
      idx_positive = (int32_T)n_t;
    }
    rho = 100.0 * muDoubleScalarMax(
                      1.0, muDoubleScalarAbs(grad_data[idx_positive - 1]));
  } else {
    if (WorkingSet->mConstr < 1) {
      idx_positive = 0;
    } else {
      n_t = (ptrdiff_t)WorkingSet->mConstr;
      incx_t = (ptrdiff_t)1;
      n_t = idamax(&n_t, &TrialState->lambdasqp->data[0], &incx_t);
      idx_positive = (int32_T)n_t;
    }
    rho = muDoubleScalarAbs(TrialState->lambdasqp->data[idx_positive - 1]);
  }
  QPObjective->nvar = WorkingSet->nVar;
  QPObjective->beta = beta;
  QPObjective->rho = rho;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 4;
  setProblemType(WorkingSet, 2);
  b_mIneq = WorkingSet->sizes[2] - 1;
  b_mEq = WorkingSet->sizes[1] - 1;
  mFiniteLB = (WorkingSet->sizes[3] - (WorkingSet->sizes[1] << 1)) -
              WorkingSet->sizes[2];
  if (WorkingSet->sizes[2] >= 1) {
    n_t = (ptrdiff_t)WorkingSet->sizes[2];
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &WorkingSet->bineq->data[0], &incx_t,
          &memspace->workspace_double->data[0], &incy_t);
  }
  c_xgemv(nVarOrig, WorkingSet->sizes[2], WorkingSet->Aineq, WorkingSet->ldA,
          TrialState->xstar, memspace->workspace_double);
  for (idx = 0; idx <= b_mIneq; idx++) {
    TrialState->xstar->data[nVarOrig + idx] =
        (real_T)(memspace->workspace_double->data[idx] > 0.0) *
        memspace->workspace_double->data[idx];
  }
  for (idx_negative = 0; idx_negative <= b_mEq; idx_negative++) {
    memspace->workspace_double->data[idx_negative] =
        WorkingSet->beq[idx_negative];
  }
  c_xgemv(nVarOrig, WorkingSet->sizes[1], WorkingSet->Aeq, WorkingSet->ldA,
          TrialState->xstar, memspace->workspace_double);
  for (idx = 0; idx <= b_mEq; idx++) {
    idx_positive = (b_mIneq + idx) + 1;
    idx_negative = ((b_mIneq + b_mEq) + idx) + 2;
    if (memspace->workspace_double->data[idx] <= 0.0) {
      TrialState->xstar->data[nVarOrig + idx_positive] = 0.0;
      TrialState->xstar->data[nVarOrig + idx_negative] =
          -memspace->workspace_double->data[idx];
      addBoundToActiveSetMatrix_(WorkingSet, 4, (mFiniteLB + idx_positive) + 1);
      if (memspace->workspace_double->data[idx] >= -1.0E-6) {
        addBoundToActiveSetMatrix_(WorkingSet, 4,
                                   (mFiniteLB + idx_negative) + 1);
      }
    } else {
      TrialState->xstar->data[nVarOrig + idx_positive] =
          memspace->workspace_double->data[idx];
      TrialState->xstar->data[nVarOrig + idx_negative] = 0.0;
      addBoundToActiveSetMatrix_(WorkingSet, 4, (mFiniteLB + idx_negative) + 1);
      if (memspace->workspace_double->data[idx] <= 1.0E-6) {
        addBoundToActiveSetMatrix_(WorkingSet, 4,
                                   (mFiniteLB + idx_positive) + 1);
      }
    }
  }
  idx_positive = qpoptions->MaxIterations;
  qpoptions->MaxIterations =
      (qpoptions->MaxIterations + WorkingSet->nVar) - nVarOrig;
  b_qpoptions = *qpoptions;
  driver(Hessian, grad, TrialState, memspace, WorkingSet, QRManager,
         CholManager, QPObjective, qpoptions, &b_qpoptions);
  qpoptions->MaxIterations = idx_positive;
  b_mIneq = WorkingSet->sizes[2];
  b_mEq = WorkingSet->sizes[1];
  idx_positive = WorkingSet->sizes[1] << 1;
  idx_negative = idx_positive + WorkingSet->sizes[2];
  mFiniteLB = WorkingSet->sizes[3] - 1;
  nActiveLBArtificial = 0;
  for (idx = 0; idx < b_mEq; idx++) {
    tf_tmp = WorkingSet->isActiveIdx[3] + mFiniteLB;
    tf = WorkingSet->isActiveConstr->data[(tf_tmp - (b_mEq << 1)) + idx];
    b_tf = WorkingSet->isActiveConstr->data[(tf_tmp - b_mEq) + idx];
    memspace->workspace_int->data[idx] = tf;
    memspace->workspace_int->data[idx + b_mEq] = b_tf;
    nActiveLBArtificial = (nActiveLBArtificial + tf) + b_tf;
  }
  for (idx = 0; idx < b_mIneq; idx++) {
    tf = WorkingSet->isActiveConstr
             ->data[((WorkingSet->isActiveIdx[3] + mFiniteLB) - idx_negative) +
                    idx];
    memspace->workspace_int->data[idx + idx_positive] = tf;
    nActiveLBArtificial += tf;
  }
  if (TrialState->state != -6) {
    idx_positive = (WorkingSet->nVarMax - nVarOrig) - 1;
    if (idx_positive < 1) {
      qpfvalLinearExcess = 0.0;
      qpfvalQuadExcess = 0.0;
    } else {
      n_t = (ptrdiff_t)idx_positive;
      incx_t = (ptrdiff_t)1;
      qpfvalLinearExcess =
          dasum(&n_t, &TrialState->xstar->data[nVarOrig], &incx_t);
      n_t = (ptrdiff_t)idx_positive;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      qpfvalQuadExcess = ddot(&n_t, &TrialState->xstar->data[nVarOrig], &incx_t,
                              &TrialState->xstar->data[nVarOrig], &incy_t);
    }
    qpfvalLinearExcess = (TrialState->fstar - rho * qpfvalLinearExcess) -
                         beta / 2.0 * qpfvalQuadExcess;
    idx_positive = (nVarMax - nVarOrig) - 1;
    qpfvalQuadExcess = MeritFunction->penaltyParam;
    beta = 0.0;
    if (mEq >= 1) {
      for (idx_negative = 0; idx_negative < mEq; idx_negative++) {
        beta += muDoubleScalarAbs(TrialState->cEq[idx_negative]);
      }
    }
    rho = 0.0;
    for (idx = 0; idx < mIneq; idx++) {
      if (TrialState->cIneq->data[idx] > 0.0) {
        rho += TrialState->cIneq->data[idx];
      }
    }
    rho += beta;
    beta = MeritFunction->linearizedConstrViol;
    if (idx_positive < 1) {
      MeritFunction->linearizedConstrViol = 0.0;
    } else {
      n_t = (ptrdiff_t)idx_positive;
      incx_t = (ptrdiff_t)1;
      MeritFunction->linearizedConstrViol =
          dasum(&n_t, &TrialState->xstar->data[nVarOrig], &incx_t);
    }
    beta = (rho + beta) - MeritFunction->linearizedConstrViol;
    if ((beta > 2.2204460492503131E-16) && (qpfvalLinearExcess > 0.0)) {
      if (TrialState->sqpFval == 0.0) {
        qpfvalQuadExcess = 1.0;
      } else {
        qpfvalQuadExcess = 1.5;
      }
      qpfvalQuadExcess = qpfvalQuadExcess * qpfvalLinearExcess / beta;
    }
    if (qpfvalQuadExcess < MeritFunction->penaltyParam) {
      MeritFunction->phi = TrialState->sqpFval + qpfvalQuadExcess * rho;
      if ((MeritFunction->initFval +
           qpfvalQuadExcess * (MeritFunction->initConstrViolationEq +
                               MeritFunction->initConstrViolationIneq)) -
              MeritFunction->phi >
          (real_T)MeritFunction->nPenaltyDecreases * MeritFunction->threshold) {
        MeritFunction->nPenaltyDecreases++;
        if ((MeritFunction->nPenaltyDecreases << 1) >
            TrialState->sqpIterations) {
          MeritFunction->threshold *= 10.0;
        }
        MeritFunction->penaltyParam =
            muDoubleScalarMax(qpfvalQuadExcess, 1.0E-10);
      } else {
        MeritFunction->phi =
            TrialState->sqpFval + MeritFunction->penaltyParam * rho;
      }
    } else {
      MeritFunction->penaltyParam =
          muDoubleScalarMax(qpfvalQuadExcess, 1.0E-10);
      MeritFunction->phi =
          TrialState->sqpFval + MeritFunction->penaltyParam * rho;
    }
    MeritFunction->phiPrimePlus = muDoubleScalarMin(
        qpfvalLinearExcess - MeritFunction->penaltyParam * rho, 0.0);
    idx_positive = WorkingSet->isActiveIdx[1] - 2;
    for (idx = 0; idx < mEq; idx++) {
      if ((memspace->workspace_int->data[idx] != 0) &&
          (memspace->workspace_int->data[idx + mEq] != 0)) {
        tf = true;
      } else {
        tf = false;
      }
      mFiniteLB = (idx_positive + idx) + 1;
      TrialState->lambda->data[mFiniteLB] *= (real_T)tf;
    }
    idx_positive = WorkingSet->isActiveIdx[2];
    idx_negative = WorkingSet->nActiveConstr;
    for (idx = idx_positive; idx <= idx_negative; idx++) {
      if (WorkingSet->Wid->data[idx - 1] == 3) {
        TrialState->lambda->data[idx - 1] *=
            (real_T)memspace->workspace_int
                ->data[(WorkingSet->Wlocalidx->data[idx - 1] + (mEq << 1)) - 1];
      }
    }
  }
  idx_positive = WorkingSet->sizes[0];
  mEq = WorkingSet->sizes[1];
  mFiniteLB = (WorkingSet->sizes[3] - (WorkingSet->sizes[1] << 1)) -
              WorkingSet->sizes[2];
  idx = WorkingSet->nActiveConstr;
  while ((idx > idx_positive + mEq) && (nActiveLBArtificial > 0)) {
    if ((WorkingSet->Wid->data[idx - 1] == 4) &&
        (WorkingSet->Wlocalidx->data[idx - 1] > mFiniteLB)) {
      idx_negative = WorkingSet->nActiveConstr - 1;
      beta = TrialState->lambda->data[idx_negative];
      TrialState->lambda->data[idx_negative] = 0.0;
      TrialState->lambda->data[idx - 1] = beta;
      removeConstr(WorkingSet, idx);
      nActiveLBArtificial--;
    }
    idx--;
  }
  QPObjective->nvar = nVarOrig;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 3;
  setProblemType(WorkingSet, 3);
  sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr, WorkingSet->sizes,
               WorkingSet->isActiveIdx, WorkingSet->Wid, WorkingSet->Wlocalidx,
               memspace->workspace_double);
}

/* End of code generation (relaxed.c) */
