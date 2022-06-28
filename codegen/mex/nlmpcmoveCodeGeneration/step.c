/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * step.c
 *
 * Code generation for function 'step'
 *
 */

/* Include files */
#include "step.h"
#include "addAeqConstr.h"
#include "driver.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "relaxed.h"
#include "rt_nonfinite.h"
#include "soc.h"
#include "sortLambdaQP.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
boolean_T step(int32_T *STEP_TYPE, real_T Hessian[2601], const real_T lb[51],
               const real_T ub[51], e_struct_T *TrialState,
               struct_T *MeritFunction, i_struct_T *memspace,
               j_struct_T *WorkingSet, f_struct_T *QRManager,
               g_struct_T *CholManager, h_struct_T *QPObjective,
               d_struct_T *qpoptions)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  d_struct_T b_qpoptions;
  emxArray_real_T *r;
  real_T constrViolationEq;
  real_T constrViolationIneq;
  real_T penaltyParamTrial;
  real_T *r1;
  int32_T exitg1;
  int32_T i;
  int32_T idx;
  int32_T idxEndIneq;
  int32_T kend;
  int32_T mUB;
  int32_T nVar;
  boolean_T checkBoundViolation;
  boolean_T guard1 = false;
  boolean_T nonlinEqRemoved;
  boolean_T stepSuccess;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  stepSuccess = true;
  checkBoundViolation = true;
  nVar = WorkingSet->nVar;
  if (*STEP_TYPE != 3) {
    for (idxEndIneq = 0; idxEndIneq < nVar; idxEndIneq++) {
      TrialState->xstar->data[idxEndIneq] = TrialState->xstarsqp[idxEndIneq];
    }
  } else if (WorkingSet->nVar >= 1) {
    n_t = (ptrdiff_t)WorkingSet->nVar;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &TrialState->xstar->data[0], &incx_t,
          &TrialState->searchDir->data[0], &incy_t);
  }
  emxInit_real_T(&r, 1);
  do {
    exitg1 = 0;
    guard1 = false;
    switch (*STEP_TYPE) {
    case 1:
      b_qpoptions = *qpoptions;
      driver(Hessian, TrialState->grad, TrialState, memspace, WorkingSet,
             QRManager, CholManager, QPObjective, qpoptions, &b_qpoptions);
      if (TrialState->state > 0) {
        i = WorkingSet->sizes[2];
        penaltyParamTrial = MeritFunction->penaltyParam;
        constrViolationEq = 0.0;
        if (WorkingSet->sizes[1] >= 1) {
          kend = WorkingSet->sizes[1];
          for (idxEndIneq = 0; idxEndIneq < kend; idxEndIneq++) {
            constrViolationEq += muDoubleScalarAbs(TrialState->cEq[idxEndIneq]);
          }
        }
        constrViolationIneq = 0.0;
        for (idx = 0; idx < i; idx++) {
          if (TrialState->cIneq->data[idx] > 0.0) {
            constrViolationIneq += TrialState->cIneq->data[idx];
          }
        }
        constrViolationIneq += constrViolationEq;
        constrViolationEq = MeritFunction->linearizedConstrViol;
        MeritFunction->linearizedConstrViol = 0.0;
        constrViolationEq += constrViolationIneq;
        if ((constrViolationEq > 2.2204460492503131E-16) &&
            (TrialState->fstar > 0.0)) {
          if (TrialState->sqpFval == 0.0) {
            penaltyParamTrial = 1.0;
          } else {
            penaltyParamTrial = 1.5;
          }
          penaltyParamTrial =
              penaltyParamTrial * TrialState->fstar / constrViolationEq;
        }
        if (penaltyParamTrial < MeritFunction->penaltyParam) {
          MeritFunction->phi =
              TrialState->sqpFval + penaltyParamTrial * constrViolationIneq;
          if ((MeritFunction->initFval +
               penaltyParamTrial * (MeritFunction->initConstrViolationEq +
                                    MeritFunction->initConstrViolationIneq)) -
                  MeritFunction->phi >
              (real_T)MeritFunction->nPenaltyDecreases *
                  MeritFunction->threshold) {
            MeritFunction->nPenaltyDecreases++;
            if ((MeritFunction->nPenaltyDecreases << 1) >
                TrialState->sqpIterations) {
              MeritFunction->threshold *= 10.0;
            }
            MeritFunction->penaltyParam =
                muDoubleScalarMax(penaltyParamTrial, 1.0E-10);
          } else {
            MeritFunction->phi =
                TrialState->sqpFval +
                MeritFunction->penaltyParam * constrViolationIneq;
          }
        } else {
          MeritFunction->penaltyParam =
              muDoubleScalarMax(penaltyParamTrial, 1.0E-10);
          MeritFunction->phi =
              TrialState->sqpFval +
              MeritFunction->penaltyParam * constrViolationIneq;
        }
        MeritFunction->phiPrimePlus =
            muDoubleScalarMin(TrialState->fstar - MeritFunction->penaltyParam *
                                                      constrViolationIneq,
                              0.0);
      }
      sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr,
                   WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid,
                   WorkingSet->Wlocalidx, memspace->workspace_double);
      nonlinEqRemoved = (WorkingSet->mEqRemoved > 0);
      while ((WorkingSet->mEqRemoved > 0) &&
             (WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1] >=
              TrialState->iNonEq0)) {
        addAeqConstr(WorkingSet,
                     WorkingSet->indexEqRemoved[WorkingSet->mEqRemoved - 1]);
        WorkingSet->mEqRemoved--;
      }
      if (nonlinEqRemoved) {
        kend = (WorkingSet->sizes[0] + TrialState->iNonEq0) - 1;
        i = TrialState->mNonlinEq;
        for (idx = 0; idx < i; idx++) {
          WorkingSet->Wlocalidx->data[kend + idx] = TrialState->iNonEq0 + idx;
        }
      }
      if ((TrialState->state <= 0) && (TrialState->state != -6)) {
        *STEP_TYPE = 2;
      } else {
        if (nVar >= 1) {
          n_t = (ptrdiff_t)nVar;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dcopy(&n_t, &TrialState->xstar->data[0], &incx_t,
                &TrialState->delta_x->data[0], &incy_t);
        }
        guard1 = true;
      }
      break;
    case 2:
      kend = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
      idxEndIneq = WorkingSet->nActiveConstr;
      for (mUB = kend; mUB <= idxEndIneq; mUB++) {
        WorkingSet->isActiveConstr->data
            [(WorkingSet->isActiveIdx[WorkingSet->Wid->data[mUB - 1] - 1] +
              WorkingSet->Wlocalidx->data[mUB - 1]) -
             2] = false;
      }
      WorkingSet->nWConstr[2] = 0;
      WorkingSet->nWConstr[3] = 0;
      WorkingSet->nWConstr[4] = 0;
      WorkingSet->nActiveConstr =
          WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1];
      i = r->size[0];
      r->size[0] = TrialState->xstar->size[0];
      emxEnsureCapacity_real_T(r, i);
      r1 = r->data;
      kend = TrialState->xstar->size[0];
      for (i = 0; i < kend; i++) {
        r1[i] = TrialState->xstar->data[i];
      }
      idxEndIneq = WorkingSet->sizes[3];
      mUB = WorkingSet->sizes[4];
      for (idx = 0; idx < idxEndIneq; idx++) {
        constrViolationEq =
            WorkingSet->lb->data[WorkingSet->indexLB->data[idx] - 1];
        if (-r1[WorkingSet->indexLB->data[idx] - 1] > constrViolationEq) {
          if (muDoubleScalarIsInf(ub[WorkingSet->indexLB->data[idx] - 1])) {
            r1[WorkingSet->indexLB->data[idx] - 1] =
                -constrViolationEq + muDoubleScalarAbs(constrViolationEq);
          } else {
            r1[WorkingSet->indexLB->data[idx] - 1] =
                (WorkingSet->ub->data[WorkingSet->indexLB->data[idx] - 1] -
                 constrViolationEq) /
                2.0;
          }
        }
      }
      for (idx = 0; idx < mUB; idx++) {
        constrViolationEq =
            WorkingSet->ub->data[WorkingSet->indexUB->data[idx] - 1];
        if (r1[WorkingSet->indexUB->data[idx] - 1] > constrViolationEq) {
          if (muDoubleScalarIsInf(lb[WorkingSet->indexUB->data[idx] - 1])) {
            r1[WorkingSet->indexUB->data[idx] - 1] =
                constrViolationEq - muDoubleScalarAbs(constrViolationEq);
          } else {
            r1[WorkingSet->indexUB->data[idx] - 1] =
                (constrViolationEq -
                 WorkingSet->lb->data[WorkingSet->indexUB->data[idx] - 1]) /
                2.0;
          }
        }
      }
      i = TrialState->xstar->size[0];
      TrialState->xstar->size[0] = r->size[0];
      emxEnsureCapacity_real_T(TrialState->xstar, i);
      kend = r->size[0];
      for (i = 0; i < kend; i++) {
        TrialState->xstar->data[i] = r1[i];
      }
      relaxed(Hessian, TrialState->grad, TrialState, MeritFunction, memspace,
              WorkingSet, QRManager, CholManager, QPObjective, qpoptions);
      if (nVar >= 1) {
        n_t = (ptrdiff_t)nVar;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &TrialState->xstar->data[0], &incx_t,
              &TrialState->delta_x->data[0], &incy_t);
      }
      guard1 = true;
      break;
    default:
      i = r->size[0];
      r->size[0] = TrialState->grad->size[0];
      emxEnsureCapacity_real_T(r, i);
      r1 = r->data;
      kend = TrialState->grad->size[0];
      for (i = 0; i < kend; i++) {
        r1[i] = TrialState->grad->data[i];
      }
      stepSuccess = soc(Hessian, r, TrialState, memspace, WorkingSet, QRManager,
                        CholManager, QPObjective, qpoptions);
      checkBoundViolation = stepSuccess;
      if (stepSuccess && (TrialState->state != -6)) {
        for (idx = 0; idx < nVar; idx++) {
          TrialState->delta_x->data[idx] = TrialState->xstar->data[idx] +
                                           TrialState->socDirection->data[idx];
        }
      }
      guard1 = true;
      break;
    }
    if (guard1) {
      if (TrialState->state != -6) {
        exitg1 = 1;
      } else {
        constrViolationEq = 0.0;
        constrViolationIneq = 1.0;
        for (idx = 0; idx < 51; idx++) {
          constrViolationEq =
              muDoubleScalarMax(constrViolationEq,
                                muDoubleScalarAbs(TrialState->grad->data[idx]));
          constrViolationIneq = muDoubleScalarMax(
              constrViolationIneq,
              muDoubleScalarAbs(TrialState->xstar->data[idx]));
        }
        constrViolationEq = muDoubleScalarMax(
            2.2204460492503131E-16, constrViolationEq / constrViolationIneq);
        for (mUB = 0; mUB < 51; mUB++) {
          kend = 51 * mUB;
          for (idxEndIneq = 0; idxEndIneq < mUB; idxEndIneq++) {
            Hessian[kend + idxEndIneq] = 0.0;
          }
          Hessian[mUB + 51 * mUB] = constrViolationEq;
          kend += mUB;
          idxEndIneq = 49 - mUB;
          if (0 <= idxEndIneq) {
            memset(&Hessian[kend + 1], 0,
                   (((idxEndIneq + kend) - kend) + 1) * sizeof(real_T));
          }
        }
      }
    }
  } while (exitg1 == 0);
  if (checkBoundViolation) {
    idxEndIneq = WorkingSet->sizes[3];
    mUB = WorkingSet->sizes[4];
    i = r->size[0];
    r->size[0] = TrialState->delta_x->size[0];
    emxEnsureCapacity_real_T(r, i);
    r1 = r->data;
    kend = TrialState->delta_x->size[0];
    for (i = 0; i < kend; i++) {
      r1[i] = TrialState->delta_x->data[i];
    }
    for (idx = 0; idx < idxEndIneq; idx++) {
      constrViolationEq = r1[WorkingSet->indexLB->data[idx] - 1];
      constrViolationIneq =
          (TrialState->xstarsqp[WorkingSet->indexLB->data[idx] - 1] +
           constrViolationEq) -
          lb[WorkingSet->indexLB->data[idx] - 1];
      if (constrViolationIneq < 0.0) {
        r1[WorkingSet->indexLB->data[idx] - 1] =
            constrViolationEq - constrViolationIneq;
        TrialState->xstar->data[WorkingSet->indexLB->data[idx] - 1] -=
            constrViolationIneq;
      }
    }
    for (idx = 0; idx < mUB; idx++) {
      constrViolationEq = r1[WorkingSet->indexUB->data[idx] - 1];
      constrViolationIneq =
          (ub[WorkingSet->indexUB->data[idx] - 1] -
           TrialState->xstarsqp[WorkingSet->indexUB->data[idx] - 1]) -
          constrViolationEq;
      if (constrViolationIneq < 0.0) {
        r1[WorkingSet->indexUB->data[idx] - 1] =
            constrViolationEq + constrViolationIneq;
        TrialState->xstar->data[WorkingSet->indexUB->data[idx] - 1] +=
            constrViolationIneq;
      }
    }
    i = TrialState->delta_x->size[0];
    TrialState->delta_x->size[0] = r->size[0];
    emxEnsureCapacity_real_T(TrialState->delta_x, i);
    kend = r->size[0];
    for (i = 0; i < kend; i++) {
      TrialState->delta_x->data[i] = r1[i];
    }
  }
  emxFree_real_T(&r);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
  return stepSuccess;
}

/* End of code generation (step.c) */
