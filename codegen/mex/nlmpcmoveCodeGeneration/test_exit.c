/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * test_exit.c
 *
 * Code generation for function 'test_exit'
 *
 */

/* Include files */
#include "test_exit.h"
#include "computeComplError.h"
#include "computeGradLag.h"
#include "computeLambdaLSQ.h"
#include "computePrimalFeasError.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "updateWorkingSetForNewQP.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void b_test_exit(b_struct_T *Flags, i_struct_T *memspace,
                 struct_T *MeritFunction,
                 const emxArray_real_T *fscales_lineq_constraint,
                 const emxArray_real_T *fscales_cineq_constraint,
                 j_struct_T *WorkingSet, e_struct_T *TrialState,
                 f_struct_T *QRManager, const real_T lb[51],
                 const real_T ub[51])
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  emxArray_real_T *gradLag;
  real_T b_TrialState[51];
  real_T c_TrialState[32];
  const real_T *gradLag_data;
  real_T d;
  real_T nlpComplErrorTmp;
  real_T optimRelativeFactor;
  real_T val;
  int32_T idx;
  int32_T mEq;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mLambda;
  int32_T mLambda_tmp_tmp;
  int32_T mUB;
  int32_T nActiveConstr;
  int32_T nVar_tmp;
  boolean_T dxTooSmall;
  boolean_T exitg1;
  boolean_T guard1 = false;
  boolean_T isFeasible;
  nVar_tmp = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  mEq = WorkingSet->sizes[1];
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  mLambda_tmp_tmp = WorkingSet->sizes[0] + WorkingSet->sizes[1];
  mLambda = ((mLambda_tmp_tmp + WorkingSet->sizes[2]) + WorkingSet->sizes[3]) +
            WorkingSet->sizes[4];
  if (mLambda >= 1) {
    n_t = (ptrdiff_t)mLambda;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &TrialState->lambdasqp->data[0], &incx_t,
          &TrialState->lambdaStopTest->data[0], &incy_t);
  }
  computeGradLag(TrialState->gradLag, WorkingSet->ldA, WorkingSet->nVar,
                 TrialState->grad, WorkingSet->sizes[2], WorkingSet->Aineq,
                 WorkingSet->sizes[1], WorkingSet->Aeq, WorkingSet->indexFixed,
                 WorkingSet->sizes[0], WorkingSet->indexLB,
                 WorkingSet->sizes[3], WorkingSet->indexUB,
                 WorkingSet->sizes[4], TrialState->lambdaStopTest);
  if (WorkingSet->nVar < 1) {
    nActiveConstr = 0;
  } else {
    n_t = (ptrdiff_t)WorkingSet->nVar;
    incx_t = (ptrdiff_t)1;
    n_t = idamax(&n_t, &TrialState->grad->data[0], &incx_t);
    nActiveConstr = (int32_T)n_t;
  }
  optimRelativeFactor = muDoubleScalarMax(
      1.0, muDoubleScalarAbs(TrialState->grad->data[nActiveConstr - 1]));
  if (muDoubleScalarIsInf(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }
  MeritFunction->nlpPrimalFeasError = computePrimalFeasError(
      TrialState->xstarsqp, WorkingSet->sizes[2] - TrialState->mNonlinIneq,
      TrialState->mNonlinIneq, TrialState->cIneq,
      WorkingSet->sizes[1] - TrialState->mNonlinEq, TrialState->mNonlinEq,
      TrialState->cEq, WorkingSet->indexLB, WorkingSet->sizes[3], lb,
      WorkingSet->indexUB, WorkingSet->sizes[4], ub);
  if (TrialState->sqpIterations == 0) {
    MeritFunction->feasRelativeFactor =
        muDoubleScalarMax(1.0, MeritFunction->nlpPrimalFeasError);
  }
  isFeasible = (MeritFunction->nlpPrimalFeasError <=
                1.0E-6 * MeritFunction->feasRelativeFactor);
  gradLag = TrialState->gradLag;
  gradLag_data = gradLag->data;
  dxTooSmall = true;
  val = 0.0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= nVar_tmp - 1)) {
    dxTooSmall = ((!muDoubleScalarIsInf(gradLag_data[idx])) &&
                  (!muDoubleScalarIsNaN(gradLag_data[idx])));
    if (!dxTooSmall) {
      exitg1 = true;
    } else {
      val = muDoubleScalarMax(val, muDoubleScalarAbs(gradLag_data[idx]));
      idx++;
    }
  }
  Flags->gradOK = dxTooSmall;
  MeritFunction->nlpDualFeasError = val;
  if (!Flags->gradOK) {
    Flags->done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = computeComplError(
        fscales_lineq_constraint, fscales_cineq_constraint,
        TrialState->xstarsqp, WorkingSet->sizes[2], TrialState->cIneq,
        WorkingSet->indexLB, WorkingSet->sizes[3], lb, WorkingSet->indexUB,
        WorkingSet->sizes[4], ub, TrialState->lambdaStopTest,
        mLambda_tmp_tmp + 1);
    MeritFunction->firstOrderOpt = muDoubleScalarMax(
        MeritFunction->nlpDualFeasError, MeritFunction->nlpComplError);
    if (TrialState->sqpIterations > 1) {
      computeGradLag(memspace->workspace_double, WorkingSet->ldA,
                     WorkingSet->nVar, TrialState->grad, WorkingSet->sizes[2],
                     WorkingSet->Aineq, WorkingSet->sizes[1], WorkingSet->Aeq,
                     WorkingSet->indexFixed, WorkingSet->sizes[0],
                     WorkingSet->indexLB, WorkingSet->sizes[3],
                     WorkingSet->indexUB, WorkingSet->sizes[4],
                     TrialState->lambdaStopTestPrev);
      gradLag = memspace->workspace_double;
      gradLag_data = gradLag->data;
      val = 0.0;
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= nVar_tmp - 1)) {
        dxTooSmall = ((!muDoubleScalarIsInf(gradLag_data[idx])) &&
                      (!muDoubleScalarIsNaN(gradLag_data[idx])));
        if (!dxTooSmall) {
          exitg1 = true;
        } else {
          val = muDoubleScalarMax(val, muDoubleScalarAbs(gradLag_data[idx]));
          idx++;
        }
      }
      nlpComplErrorTmp = computeComplError(
          fscales_lineq_constraint, fscales_cineq_constraint,
          TrialState->xstarsqp, WorkingSet->sizes[2], TrialState->cIneq,
          WorkingSet->indexLB, WorkingSet->sizes[3], lb, WorkingSet->indexUB,
          WorkingSet->sizes[4], ub, TrialState->lambdaStopTestPrev,
          (WorkingSet->sizes[0] + WorkingSet->sizes[1]) + 1);
      d = muDoubleScalarMax(val, nlpComplErrorTmp);
      if (d < muDoubleScalarMax(MeritFunction->nlpDualFeasError,
                                MeritFunction->nlpComplError)) {
        MeritFunction->nlpDualFeasError = val;
        MeritFunction->nlpComplError = nlpComplErrorTmp;
        MeritFunction->firstOrderOpt = d;
        if (mLambda >= 1) {
          n_t = (ptrdiff_t)mLambda;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dcopy(&n_t, &TrialState->lambdaStopTestPrev->data[0], &incx_t,
                &TrialState->lambdaStopTest->data[0], &incy_t);
        }
      } else if (mLambda >= 1) {
        n_t = (ptrdiff_t)mLambda;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &TrialState->lambdaStopTest->data[0], &incx_t,
              &TrialState->lambdaStopTestPrev->data[0], &incy_t);
      }
    } else if (mLambda >= 1) {
      n_t = (ptrdiff_t)mLambda;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dcopy(&n_t, &TrialState->lambdaStopTest->data[0], &incx_t,
            &TrialState->lambdaStopTestPrev->data[0], &incy_t);
    }
    if (isFeasible &&
        (MeritFunction->nlpDualFeasError <= 1.0E-6 * optimRelativeFactor) &&
        (MeritFunction->nlpComplError <= 1.0E-6 * optimRelativeFactor)) {
      Flags->done = true;
      TrialState->sqpExitFlag = 1;
    } else {
      Flags->done = false;
      if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
        Flags->done = true;
        TrialState->sqpExitFlag = -3;
      } else {
        guard1 = false;
        if (TrialState->sqpIterations > 0) {
          dxTooSmall = true;
          idx = 0;
          exitg1 = false;
          while ((!exitg1) && (idx <= nVar_tmp - 1)) {
            if (1.0E-6 *
                    muDoubleScalarMax(
                        1.0, muDoubleScalarAbs(TrialState->xstarsqp[idx])) <=
                muDoubleScalarAbs(TrialState->delta_x->data[idx])) {
              dxTooSmall = false;
              exitg1 = true;
            } else {
              idx++;
            }
          }
          if (dxTooSmall) {
            if (!isFeasible) {
              if (Flags->stepType != 2) {
                Flags->stepType = 2;
                Flags->failedLineSearch = false;
                Flags->stepAccepted = false;
                guard1 = true;
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = -2;
              }
            } else {
              nActiveConstr = WorkingSet->nActiveConstr;
              if (WorkingSet->nActiveConstr > 0) {
                if (TrialState->mNonlinEq + TrialState->mNonlinIneq > 0) {
                  memcpy(&b_TrialState[0], &TrialState->xstarsqp[0],
                         51U * sizeof(real_T));
                  memcpy(&c_TrialState[0], &TrialState->cEq[0],
                         32U * sizeof(real_T));
                  b_updateWorkingSetForNewQP(
                      b_TrialState, WorkingSet, WorkingSet->sizes[2],
                      TrialState->mNonlinIneq, TrialState->cIneq,
                      WorkingSet->sizes[1], TrialState->mNonlinEq, c_TrialState,
                      WorkingSet->sizes[3], lb, WorkingSet->sizes[4], ub,
                      WorkingSet->sizes[0]);
                }
                computeLambdaLSQ(nVar_tmp, nActiveConstr, QRManager,
                                 WorkingSet->ATwset, WorkingSet->ldA,
                                 TrialState->grad, TrialState->lambda,
                                 memspace->workspace_double);
                nActiveConstr = mFixed + 1;
                mLambda_tmp_tmp = mFixed + mEq;
                for (idx = nActiveConstr; idx <= mLambda_tmp_tmp; idx++) {
                  TrialState->lambda->data[idx - 1] =
                      -TrialState->lambda->data[idx - 1];
                }
                sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr,
                             WorkingSet->sizes, WorkingSet->isActiveIdx,
                             WorkingSet->Wid, WorkingSet->Wlocalidx,
                             memspace->workspace_double);
                computeGradLag(memspace->workspace_double, WorkingSet->ldA,
                               nVar_tmp, TrialState->grad, mIneq,
                               WorkingSet->Aineq, mEq, WorkingSet->Aeq,
                               WorkingSet->indexFixed, mFixed,
                               WorkingSet->indexLB, mLB, WorkingSet->indexUB,
                               mUB, TrialState->lambda);
                gradLag = memspace->workspace_double;
                gradLag_data = gradLag->data;
                val = 0.0;
                idx = 0;
                exitg1 = false;
                while ((!exitg1) && (idx <= nVar_tmp - 1)) {
                  dxTooSmall = ((!muDoubleScalarIsInf(gradLag_data[idx])) &&
                                (!muDoubleScalarIsNaN(gradLag_data[idx])));
                  if (!dxTooSmall) {
                    exitg1 = true;
                  } else {
                    val = muDoubleScalarMax(
                        val, muDoubleScalarAbs(gradLag_data[idx]));
                    idx++;
                  }
                }
                nlpComplErrorTmp = computeComplError(
                    fscales_lineq_constraint, fscales_cineq_constraint,
                    TrialState->xstarsqp, mIneq, TrialState->cIneq,
                    WorkingSet->indexLB, mLB, lb, WorkingSet->indexUB, mUB, ub,
                    TrialState->lambda, mFixed + 1);
                if ((val <= 1.0E-6 * optimRelativeFactor) &&
                    (nlpComplErrorTmp <= 1.0E-6 * optimRelativeFactor)) {
                  MeritFunction->nlpDualFeasError = val;
                  MeritFunction->nlpComplError = nlpComplErrorTmp;
                  MeritFunction->firstOrderOpt =
                      muDoubleScalarMax(val, nlpComplErrorTmp);
                  if (mLambda >= 1) {
                    n_t = (ptrdiff_t)mLambda;
                    incx_t = (ptrdiff_t)1;
                    incy_t = (ptrdiff_t)1;
                    dcopy(&n_t, &TrialState->lambda->data[0], &incx_t,
                          &TrialState->lambdaStopTest->data[0], &incy_t);
                  }
                  Flags->done = true;
                  TrialState->sqpExitFlag = 1;
                } else {
                  Flags->done = true;
                  TrialState->sqpExitFlag = 2;
                }
              } else {
                Flags->done = true;
                TrialState->sqpExitFlag = 2;
              }
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1) {
          if (TrialState->sqpIterations >= 400) {
            Flags->done = true;
            TrialState->sqpExitFlag = 0;
          } else if (TrialState->FunctionEvaluations >= 5100) {
            Flags->done = true;
            TrialState->sqpExitFlag = 0;
          }
        }
      }
    }
  }
}

void test_exit(i_struct_T *memspace, struct_T *MeritFunction,
               const emxArray_real_T *fscales_lineq_constraint,
               const emxArray_real_T *fscales_cineq_constraint,
               j_struct_T *WorkingSet, e_struct_T *TrialState,
               f_struct_T *QRManager, const real_T lb[51], const real_T ub[51],
               boolean_T *Flags_gradOK, boolean_T *Flags_fevalOK,
               boolean_T *Flags_done, boolean_T *Flags_stepAccepted,
               boolean_T *Flags_failedLineSearch, int32_T *Flags_stepType)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  emxArray_real_T *gradLag;
  real_T b_TrialState[51];
  real_T c_TrialState[32];
  const real_T *gradLag_data;
  real_T d;
  real_T nlpComplErrorTmp;
  real_T optimRelativeFactor;
  real_T val;
  int32_T idx;
  int32_T mEq;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mLambda;
  int32_T mLambda_tmp_tmp;
  int32_T mUB;
  int32_T nActiveConstr;
  int32_T nVar_tmp;
  boolean_T dxTooSmall;
  boolean_T exitg1;
  boolean_T guard1 = false;
  boolean_T isFeasible;
  *Flags_fevalOK = true;
  *Flags_done = false;
  *Flags_stepAccepted = false;
  *Flags_failedLineSearch = false;
  *Flags_stepType = 1;
  nVar_tmp = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  mEq = WorkingSet->sizes[1];
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  mLambda_tmp_tmp = WorkingSet->sizes[0] + WorkingSet->sizes[1];
  mLambda = ((mLambda_tmp_tmp + WorkingSet->sizes[2]) + WorkingSet->sizes[3]) +
            WorkingSet->sizes[4];
  if (mLambda >= 1) {
    n_t = (ptrdiff_t)mLambda;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &TrialState->lambdasqp->data[0], &incx_t,
          &TrialState->lambdaStopTest->data[0], &incy_t);
  }
  computeGradLag(TrialState->gradLag, WorkingSet->ldA, WorkingSet->nVar,
                 TrialState->grad, WorkingSet->sizes[2], WorkingSet->Aineq,
                 WorkingSet->sizes[1], WorkingSet->Aeq, WorkingSet->indexFixed,
                 WorkingSet->sizes[0], WorkingSet->indexLB,
                 WorkingSet->sizes[3], WorkingSet->indexUB,
                 WorkingSet->sizes[4], TrialState->lambdaStopTest);
  if (WorkingSet->nVar < 1) {
    nActiveConstr = 0;
  } else {
    n_t = (ptrdiff_t)WorkingSet->nVar;
    incx_t = (ptrdiff_t)1;
    n_t = idamax(&n_t, &TrialState->grad->data[0], &incx_t);
    nActiveConstr = (int32_T)n_t;
  }
  optimRelativeFactor = muDoubleScalarMax(
      1.0, muDoubleScalarAbs(TrialState->grad->data[nActiveConstr - 1]));
  if (muDoubleScalarIsInf(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }
  MeritFunction->nlpPrimalFeasError = computePrimalFeasError(
      TrialState->xstarsqp, WorkingSet->sizes[2] - TrialState->mNonlinIneq,
      TrialState->mNonlinIneq, TrialState->cIneq,
      WorkingSet->sizes[1] - TrialState->mNonlinEq, TrialState->mNonlinEq,
      TrialState->cEq, WorkingSet->indexLB, WorkingSet->sizes[3], lb,
      WorkingSet->indexUB, WorkingSet->sizes[4], ub);
  if (TrialState->sqpIterations == 0) {
    MeritFunction->feasRelativeFactor =
        muDoubleScalarMax(1.0, MeritFunction->nlpPrimalFeasError);
  }
  isFeasible = (MeritFunction->nlpPrimalFeasError <=
                1.0E-6 * MeritFunction->feasRelativeFactor);
  gradLag = TrialState->gradLag;
  gradLag_data = gradLag->data;
  *Flags_gradOK = true;
  val = 0.0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= nVar_tmp - 1)) {
    *Flags_gradOK = ((!muDoubleScalarIsInf(gradLag_data[idx])) &&
                     (!muDoubleScalarIsNaN(gradLag_data[idx])));
    if (!*Flags_gradOK) {
      exitg1 = true;
    } else {
      val = muDoubleScalarMax(val, muDoubleScalarAbs(gradLag_data[idx]));
      idx++;
    }
  }
  MeritFunction->nlpDualFeasError = val;
  if (!*Flags_gradOK) {
    *Flags_done = true;
    if (isFeasible) {
      TrialState->sqpExitFlag = 2;
    } else {
      TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = computeComplError(
        fscales_lineq_constraint, fscales_cineq_constraint,
        TrialState->xstarsqp, WorkingSet->sizes[2], TrialState->cIneq,
        WorkingSet->indexLB, WorkingSet->sizes[3], lb, WorkingSet->indexUB,
        WorkingSet->sizes[4], ub, TrialState->lambdaStopTest,
        mLambda_tmp_tmp + 1);
    MeritFunction->firstOrderOpt = muDoubleScalarMax(
        MeritFunction->nlpDualFeasError, MeritFunction->nlpComplError);
    if (TrialState->sqpIterations > 1) {
      computeGradLag(memspace->workspace_double, WorkingSet->ldA,
                     WorkingSet->nVar, TrialState->grad, WorkingSet->sizes[2],
                     WorkingSet->Aineq, WorkingSet->sizes[1], WorkingSet->Aeq,
                     WorkingSet->indexFixed, WorkingSet->sizes[0],
                     WorkingSet->indexLB, WorkingSet->sizes[3],
                     WorkingSet->indexUB, WorkingSet->sizes[4],
                     TrialState->lambdaStopTestPrev);
      gradLag = memspace->workspace_double;
      gradLag_data = gradLag->data;
      val = 0.0;
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= nVar_tmp - 1)) {
        dxTooSmall = ((!muDoubleScalarIsInf(gradLag_data[idx])) &&
                      (!muDoubleScalarIsNaN(gradLag_data[idx])));
        if (!dxTooSmall) {
          exitg1 = true;
        } else {
          val = muDoubleScalarMax(val, muDoubleScalarAbs(gradLag_data[idx]));
          idx++;
        }
      }
      nlpComplErrorTmp = computeComplError(
          fscales_lineq_constraint, fscales_cineq_constraint,
          TrialState->xstarsqp, WorkingSet->sizes[2], TrialState->cIneq,
          WorkingSet->indexLB, WorkingSet->sizes[3], lb, WorkingSet->indexUB,
          WorkingSet->sizes[4], ub, TrialState->lambdaStopTestPrev,
          (WorkingSet->sizes[0] + WorkingSet->sizes[1]) + 1);
      d = muDoubleScalarMax(val, nlpComplErrorTmp);
      if (d < muDoubleScalarMax(MeritFunction->nlpDualFeasError,
                                MeritFunction->nlpComplError)) {
        MeritFunction->nlpDualFeasError = val;
        MeritFunction->nlpComplError = nlpComplErrorTmp;
        MeritFunction->firstOrderOpt = d;
        if (mLambda >= 1) {
          n_t = (ptrdiff_t)mLambda;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dcopy(&n_t, &TrialState->lambdaStopTestPrev->data[0], &incx_t,
                &TrialState->lambdaStopTest->data[0], &incy_t);
        }
      } else if (mLambda >= 1) {
        n_t = (ptrdiff_t)mLambda;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &TrialState->lambdaStopTest->data[0], &incx_t,
              &TrialState->lambdaStopTestPrev->data[0], &incy_t);
      }
    } else if (mLambda >= 1) {
      n_t = (ptrdiff_t)mLambda;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dcopy(&n_t, &TrialState->lambdaStopTest->data[0], &incx_t,
            &TrialState->lambdaStopTestPrev->data[0], &incy_t);
    }
    if (isFeasible &&
        (MeritFunction->nlpDualFeasError <= 1.0E-6 * optimRelativeFactor) &&
        (MeritFunction->nlpComplError <= 1.0E-6 * optimRelativeFactor)) {
      *Flags_done = true;
      TrialState->sqpExitFlag = 1;
    } else if (isFeasible && (TrialState->sqpFval < -1.0E+20)) {
      *Flags_done = true;
      TrialState->sqpExitFlag = -3;
    } else {
      guard1 = false;
      if (TrialState->sqpIterations > 0) {
        dxTooSmall = true;
        idx = 0;
        exitg1 = false;
        while ((!exitg1) && (idx <= nVar_tmp - 1)) {
          if (1.0E-6 * muDoubleScalarMax(
                           1.0, muDoubleScalarAbs(TrialState->xstarsqp[idx])) <=
              muDoubleScalarAbs(TrialState->delta_x->data[idx])) {
            dxTooSmall = false;
            exitg1 = true;
          } else {
            idx++;
          }
        }
        if (dxTooSmall) {
          if (!isFeasible) {
            *Flags_stepType = 2;
            guard1 = true;
          } else {
            nActiveConstr = WorkingSet->nActiveConstr;
            if (WorkingSet->nActiveConstr > 0) {
              if (TrialState->mNonlinEq + TrialState->mNonlinIneq > 0) {
                memcpy(&b_TrialState[0], &TrialState->xstarsqp[0],
                       51U * sizeof(real_T));
                memcpy(&c_TrialState[0], &TrialState->cEq[0],
                       32U * sizeof(real_T));
                b_updateWorkingSetForNewQP(
                    b_TrialState, WorkingSet, WorkingSet->sizes[2],
                    TrialState->mNonlinIneq, TrialState->cIneq,
                    WorkingSet->sizes[1], TrialState->mNonlinEq, c_TrialState,
                    WorkingSet->sizes[3], lb, WorkingSet->sizes[4], ub,
                    WorkingSet->sizes[0]);
              }
              computeLambdaLSQ(nVar_tmp, nActiveConstr, QRManager,
                               WorkingSet->ATwset, WorkingSet->ldA,
                               TrialState->grad, TrialState->lambda,
                               memspace->workspace_double);
              nActiveConstr = mFixed + 1;
              mLambda_tmp_tmp = mFixed + mEq;
              for (idx = nActiveConstr; idx <= mLambda_tmp_tmp; idx++) {
                TrialState->lambda->data[idx - 1] =
                    -TrialState->lambda->data[idx - 1];
              }
              sortLambdaQP(TrialState->lambda, WorkingSet->nActiveConstr,
                           WorkingSet->sizes, WorkingSet->isActiveIdx,
                           WorkingSet->Wid, WorkingSet->Wlocalidx,
                           memspace->workspace_double);
              computeGradLag(memspace->workspace_double, WorkingSet->ldA,
                             nVar_tmp, TrialState->grad, mIneq,
                             WorkingSet->Aineq, mEq, WorkingSet->Aeq,
                             WorkingSet->indexFixed, mFixed,
                             WorkingSet->indexLB, mLB, WorkingSet->indexUB, mUB,
                             TrialState->lambda);
              gradLag = memspace->workspace_double;
              gradLag_data = gradLag->data;
              val = 0.0;
              idx = 0;
              exitg1 = false;
              while ((!exitg1) && (idx <= nVar_tmp - 1)) {
                dxTooSmall = ((!muDoubleScalarIsInf(gradLag_data[idx])) &&
                              (!muDoubleScalarIsNaN(gradLag_data[idx])));
                if (!dxTooSmall) {
                  exitg1 = true;
                } else {
                  val = muDoubleScalarMax(val,
                                          muDoubleScalarAbs(gradLag_data[idx]));
                  idx++;
                }
              }
              nlpComplErrorTmp = computeComplError(
                  fscales_lineq_constraint, fscales_cineq_constraint,
                  TrialState->xstarsqp, mIneq, TrialState->cIneq,
                  WorkingSet->indexLB, mLB, lb, WorkingSet->indexUB, mUB, ub,
                  TrialState->lambda, mFixed + 1);
              if ((val <= 1.0E-6 * optimRelativeFactor) &&
                  (nlpComplErrorTmp <= 1.0E-6 * optimRelativeFactor)) {
                MeritFunction->nlpDualFeasError = val;
                MeritFunction->nlpComplError = nlpComplErrorTmp;
                MeritFunction->firstOrderOpt =
                    muDoubleScalarMax(val, nlpComplErrorTmp);
                if (mLambda >= 1) {
                  n_t = (ptrdiff_t)mLambda;
                  incx_t = (ptrdiff_t)1;
                  incy_t = (ptrdiff_t)1;
                  dcopy(&n_t, &TrialState->lambda->data[0], &incx_t,
                        &TrialState->lambdaStopTest->data[0], &incy_t);
                }
                *Flags_done = true;
                TrialState->sqpExitFlag = 1;
              } else {
                *Flags_done = true;
                TrialState->sqpExitFlag = 2;
              }
            } else {
              *Flags_done = true;
              TrialState->sqpExitFlag = 2;
            }
          }
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        if (TrialState->sqpIterations >= 400) {
          *Flags_done = true;
          TrialState->sqpExitFlag = 0;
        } else if (TrialState->FunctionEvaluations >= 5100) {
          *Flags_done = true;
          TrialState->sqpExitFlag = 0;
        }
      }
    }
  }
}

/* End of code generation (test_exit.c) */
