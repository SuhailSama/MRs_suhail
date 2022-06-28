/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fmincon.c
 *
 * Code generation for function 'fmincon'
 *
 */

/* Include files */
#include "fmincon.h"
#include "driver1.h"
#include "evalObjAndConstrAndDerivatives.h"
#include "factoryConstruct.h"
#include "factoryConstruct1.h"
#include "factoryConstruct2.h"
#include "initActiveSet.h"
#include "nlmpcmoveCodeGeneration.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "updateWorkingSetForNewQP.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void fmincon(const k_struct_T *fun_workspace_runtimedata,
             const real_T c_fun_workspace_userdata_Curren[3],
             const real_T fun_workspace_userdata_LastMV[2],
             const emxArray_real_T *c_fun_workspace_userdata_Refere,
             const emxArray_real_T *fun_workspace_userdata_MVTarget,
             const real_T fun_workspace_userdata_MVIndex[2],
             const real_T x0[51], const emxArray_real_T *Aineq,
             const emxArray_real_T *bineq, const real_T lb[51],
             const real_T ub[51],
             const k_struct_T *nonlcon_workspace_runtimedata,
             const l_struct_T *nonlcon_workspace_userdata, real_T x[51],
             real_T *fval, real_T *exitflag, c_struct_T *output)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t lda_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  e_struct_T TrialState;
  emxArray_real_T *varargout_1;
  emxArray_real_T *varargout_3;
  f_struct_T QRManager;
  g_struct_T CholManager;
  h_struct_T QPObjective;
  i_struct_T memspace;
  j_struct_T WorkingSet;
  n_struct_T FcnEvaluator;
  o_struct_T FiniteDifferences;
  p_struct_T expl_temp;
  struct_T MeritFunction;
  real_T unusedExpr[2601];
  real_T varargout_4[1632];
  const real_T *Aineq_data;
  const real_T *b_fun_workspace_userdata_MVTarg;
  const real_T *bineq_data;
  const real_T *d_fun_workspace_userdata_Refere;
  real_T absxk;
  real_T alpha1;
  real_T scale;
  real_T t;
  int32_T i;
  int32_T loop_ub;
  int32_T mConstrMax;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mLinIneq;
  int32_T mNonlinIneq;
  int32_T mUB;
  int32_T nVarMax;
  char_T TRANSA;
  boolean_T guard1 = false;
  bineq_data = bineq->data;
  Aineq_data = Aineq->data;
  b_fun_workspace_userdata_MVTarg = fun_workspace_userdata_MVTarget->data;
  d_fun_workspace_userdata_Refere = c_fun_workspace_userdata_Refere->data;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInitStruct_struct_T(&TrialState);
  emxInit_real_T(&varargout_3, 2);
  emxInit_real_T(&varargout_1, 2);
  c_nlmpcmoveCodeGeneration_anonF(nonlcon_workspace_runtimedata->x,
                                  nonlcon_workspace_runtimedata->OutputMin,
                                  nonlcon_workspace_runtimedata->OutputMax, x0,
                                  varargout_1, TrialState.cEq, varargout_3,
                                  varargout_4);
  mNonlinIneq = varargout_1->size[0] * varargout_1->size[1];
  mIneq = bineq->size[0] + mNonlinIneq;
  mConstrMax = (mIneq + mIneq) + 199;
  nVarMax = mIneq + 116;
  nVarMax = muIntScalarMax_sint32(nVarMax, mConstrMax);
  factoryConstruct(mIneq + 116, mConstrMax, mIneq, mNonlinIneq, &TrialState);
  emxFree_real_T(&varargout_1);
  emxFree_real_T(&varargout_3);
  memcpy(&TrialState.xstarsqp[0], &x0[0], 51U * sizeof(real_T));
  emxInitStruct_struct_T1(&FcnEvaluator);
  FcnEvaluator.mCineq = mNonlinIneq;
  emxCopyStruct_struct_T(&FcnEvaluator.objfun.workspace.runtimedata,
                         fun_workspace_runtimedata);
  FcnEvaluator.objfun.workspace.userdata.Ts = 0.1;
  FcnEvaluator.objfun.workspace.userdata.CurrentStates[0] =
      c_fun_workspace_userdata_Curren[0];
  FcnEvaluator.objfun.workspace.userdata.CurrentStates[1] =
      c_fun_workspace_userdata_Curren[1];
  FcnEvaluator.objfun.workspace.userdata.CurrentStates[2] =
      c_fun_workspace_userdata_Curren[2];
  FcnEvaluator.objfun.workspace.userdata.LastMV[0] =
      fun_workspace_userdata_LastMV[0];
  FcnEvaluator.objfun.workspace.userdata.LastMV[1] =
      fun_workspace_userdata_LastMV[1];
  i = FcnEvaluator.objfun.workspace.userdata.References->size[0] *
      FcnEvaluator.objfun.workspace.userdata.References->size[1];
  FcnEvaluator.objfun.workspace.userdata.References->size[0] =
      c_fun_workspace_userdata_Refere->size[0];
  FcnEvaluator.objfun.workspace.userdata.References->size[1] =
      c_fun_workspace_userdata_Refere->size[1];
  emxEnsureCapacity_real_T(FcnEvaluator.objfun.workspace.userdata.References,
                           i);
  loop_ub = c_fun_workspace_userdata_Refere->size[0] *
            c_fun_workspace_userdata_Refere->size[1];
  for (i = 0; i < loop_ub; i++) {
    FcnEvaluator.objfun.workspace.userdata.References->data[i] =
        d_fun_workspace_userdata_Refere[i];
  }
  i = FcnEvaluator.objfun.workspace.userdata.MVTarget->size[0] *
      FcnEvaluator.objfun.workspace.userdata.MVTarget->size[1];
  FcnEvaluator.objfun.workspace.userdata.MVTarget->size[0] =
      fun_workspace_userdata_MVTarget->size[0];
  FcnEvaluator.objfun.workspace.userdata.MVTarget->size[1] =
      fun_workspace_userdata_MVTarget->size[1];
  emxEnsureCapacity_real_T(FcnEvaluator.objfun.workspace.userdata.MVTarget, i);
  loop_ub = fun_workspace_userdata_MVTarget->size[0] *
            fun_workspace_userdata_MVTarget->size[1];
  for (i = 0; i < loop_ub; i++) {
    FcnEvaluator.objfun.workspace.userdata.MVTarget->data[i] =
        b_fun_workspace_userdata_MVTarg[i];
  }
  emxInitStruct_struct_T5(&FiniteDifferences);
  emxInitStruct_struct_T6(&QRManager);
  FcnEvaluator.objfun.workspace.userdata.PredictionHorizon = 10.0;
  FcnEvaluator.objfun.workspace.userdata.NumOfStates = 3.0;
  FcnEvaluator.objfun.workspace.userdata.NumOfOutputs = 3.0;
  FcnEvaluator.objfun.workspace.userdata.NumOfInputs = 2.0;
  FcnEvaluator.objfun.workspace.userdata.MVIndex[0] =
      fun_workspace_userdata_MVIndex[0];
  FcnEvaluator.objfun.workspace.userdata.MVIndex[1] =
      fun_workspace_userdata_MVIndex[1];
  emxCopyStruct_struct_T(&FcnEvaluator.nonlcon.workspace.runtimedata,
                         nonlcon_workspace_runtimedata);
  emxCopyStruct_struct_T1(&FcnEvaluator.nonlcon.workspace.userdata,
                          nonlcon_workspace_userdata);
  FcnEvaluator.nVar = 51;
  FcnEvaluator.mCeq = 32;
  FcnEvaluator.NonFiniteSupport = true;
  FcnEvaluator.SpecifyObjectiveGradient = true;
  FcnEvaluator.SpecifyConstraintGradient = true;
  FcnEvaluator.ScaleProblem = false;
  c_factoryConstruct(
      fun_workspace_runtimedata, c_fun_workspace_userdata_Curren,
      fun_workspace_userdata_LastMV, c_fun_workspace_userdata_Refere,
      fun_workspace_userdata_MVTarget, fun_workspace_userdata_MVIndex,
      nonlcon_workspace_runtimedata, nonlcon_workspace_userdata, mNonlinIneq,
      lb, ub, &FiniteDifferences);
  QRManager.ldq = nVarMax;
  i = QRManager.QR->size[0] * QRManager.QR->size[1];
  QRManager.QR->size[0] = nVarMax;
  QRManager.QR->size[1] = nVarMax;
  emxEnsureCapacity_real_T(QRManager.QR, i);
  i = QRManager.Q->size[0] * QRManager.Q->size[1];
  QRManager.Q->size[0] = nVarMax;
  QRManager.Q->size[1] = nVarMax;
  emxEnsureCapacity_real_T(QRManager.Q, i);
  loop_ub = nVarMax * nVarMax;
  for (i = 0; i < loop_ub; i++) {
    QRManager.Q->data[i] = 0.0;
  }
  i = QRManager.jpvt->size[0];
  QRManager.jpvt->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(QRManager.jpvt, i);
  for (i = 0; i < nVarMax; i++) {
    QRManager.jpvt->data[i] = 0;
  }
  emxInitStruct_struct_T7(&CholManager);
  emxInitStruct_struct_T8(&QPObjective);
  emxInitStruct_struct_T9(&memspace);
  emxInitStruct_struct_T11(&expl_temp);
  QRManager.mrows = 0;
  QRManager.ncols = 0;
  i = QRManager.tau->size[0];
  QRManager.tau->size[0] = muIntScalarMin_sint32(nVarMax, nVarMax);
  emxEnsureCapacity_real_T(QRManager.tau, i);
  QRManager.minRowCol = 0;
  QRManager.usedPivoting = false;
  i = CholManager.FMat->size[0] * CholManager.FMat->size[1];
  CholManager.FMat->size[0] = nVarMax;
  CholManager.FMat->size[1] = nVarMax;
  emxEnsureCapacity_real_T(CholManager.FMat, i);
  CholManager.ldm = nVarMax;
  CholManager.ndims = 0;
  CholManager.info = 0;
  CholManager.scaleFactor = 0.0;
  CholManager.ConvexCheck = true;
  CholManager.regTol_ = rtInf;
  CholManager.workspace_ = rtInf;
  CholManager.workspace2_ = rtInf;
  i = QPObjective.grad->size[0];
  QPObjective.grad->size[0] = mIneq + 116;
  emxEnsureCapacity_real_T(QPObjective.grad, i);
  i = QPObjective.Hx->size[0];
  QPObjective.Hx->size[0] = mIneq + 115;
  emxEnsureCapacity_real_T(QPObjective.Hx, i);
  QPObjective.maxVar = mIneq + 116;
  QPObjective.beta = 0.0;
  QPObjective.rho = 0.0;
  QPObjective.prev_objtype = 3;
  QPObjective.prev_nvar = 0;
  QPObjective.prev_hasLinear = false;
  QPObjective.gammaScalar = 0.0;
  QPObjective.hasLinear = true;
  QPObjective.nvar = 51;
  QPObjective.objtype = 3;
  i = memspace.workspace_double->size[0] * memspace.workspace_double->size[1];
  memspace.workspace_double->size[0] = nVarMax;
  if (2 < mIneq + 116) {
    memspace.workspace_double->size[1] = mIneq + 116;
  } else {
    memspace.workspace_double->size[1] = 2;
  }
  emxEnsureCapacity_real_T(memspace.workspace_double, i);
  i = memspace.workspace_int->size[0];
  memspace.workspace_int->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(memspace.workspace_int, i);
  i = memspace.workspace_sort->size[0];
  memspace.workspace_sort->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(memspace.workspace_sort, i);
  i = expl_temp.lineq_constraint->size[0];
  expl_temp.lineq_constraint->size[0] = bineq->size[0];
  emxEnsureCapacity_real_T(expl_temp.lineq_constraint, i);
  loop_ub = bineq->size[0];
  for (i = 0; i < loop_ub; i++) {
    expl_temp.lineq_constraint->data[i] = 1.0;
  }
  i = expl_temp.cineq_constraint->size[0];
  expl_temp.cineq_constraint->size[0] = mNonlinIneq;
  emxEnsureCapacity_real_T(expl_temp.cineq_constraint, i);
  for (i = 0; i < mNonlinIneq; i++) {
    expl_temp.cineq_constraint->data[i] = 1.0;
  }
  for (nVarMax = 0; nVarMax < 32; nVarMax++) {
    expl_temp.ceq_constraint[nVarMax] = 1.0;
  }
  emxInitStruct_struct_T10(&WorkingSet);
  b_factoryConstruct(mIneq, mIneq + 116, mConstrMax, &WorkingSet);
  mLB = 0;
  mUB = 0;
  mFixed = 0;
  for (nVarMax = 0; nVarMax < 51; nVarMax++) {
    alpha1 = lb[nVarMax];
    guard1 = false;
    if ((!muDoubleScalarIsInf(alpha1)) && (!muDoubleScalarIsNaN(alpha1))) {
      if (muDoubleScalarAbs(alpha1 - ub[nVarMax]) < 1.0E-6) {
        mFixed++;
        WorkingSet.indexFixed->data[mFixed - 1] = nVarMax + 1;
      } else {
        mLB++;
        WorkingSet.indexLB->data[mLB - 1] = nVarMax + 1;
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      alpha1 = ub[nVarMax];
      if ((!muDoubleScalarIsInf(alpha1)) && (!muDoubleScalarIsNaN(alpha1))) {
        mUB++;
        WorkingSet.indexUB->data[mUB - 1] = nVarMax + 1;
      }
    }
  }
  mLinIneq = bineq->size[0];
  loop_ub = mIneq + mLB;
  nVarMax = ((loop_ub + mUB) + mFixed) + 32;
  WorkingSet.mConstr = nVarMax;
  WorkingSet.mConstrOrig = nVarMax;
  WorkingSet.mConstrMax = mConstrMax;
  WorkingSet.sizes[0] = mFixed;
  WorkingSet.sizes[1] = 32;
  WorkingSet.sizes[2] = mIneq;
  WorkingSet.sizes[3] = mLB;
  WorkingSet.sizes[4] = mUB;
  WorkingSet.sizesPhaseOne[0] = mFixed;
  WorkingSet.sizesPhaseOne[1] = 32;
  WorkingSet.sizesPhaseOne[2] = mIneq;
  WorkingSet.sizesPhaseOne[3] = mLB + 1;
  WorkingSet.sizesPhaseOne[4] = mUB;
  WorkingSet.sizesRegularized[0] = mFixed;
  WorkingSet.sizesRegularized[1] = 32;
  WorkingSet.sizesRegularized[2] = mIneq;
  WorkingSet.sizesRegularized[3] = loop_ub + 64;
  WorkingSet.sizesRegularized[4] = mUB;
  WorkingSet.sizesRegPhaseOne[0] = mFixed;
  WorkingSet.sizesRegPhaseOne[1] = 32;
  WorkingSet.sizesRegPhaseOne[2] = mIneq;
  WorkingSet.sizesRegPhaseOne[3] = loop_ub + 65;
  WorkingSet.sizesRegPhaseOne[4] = mUB;
  WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
  WorkingSet.isActiveIdxRegPhaseOne[1] = mFixed;
  WorkingSet.isActiveIdxRegPhaseOne[2] = 32;
  WorkingSet.isActiveIdxRegPhaseOne[3] = mIneq;
  WorkingSet.isActiveIdxRegPhaseOne[4] = mLB;
  WorkingSet.isActiveIdxRegPhaseOne[5] = mUB;
  for (nVarMax = 0; nVarMax < 5; nVarMax++) {
    WorkingSet.sizesNormal[nVarMax] = WorkingSet.sizes[nVarMax];
    WorkingSet.isActiveIdxRegPhaseOne[nVarMax + 1] +=
        WorkingSet.isActiveIdxRegPhaseOne[nVarMax];
  }
  for (i = 0; i < 6; i++) {
    nVarMax = WorkingSet.isActiveIdxRegPhaseOne[i];
    WorkingSet.isActiveIdx[i] = nVarMax;
    WorkingSet.isActiveIdxNormal[i] = nVarMax;
  }
  WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
  WorkingSet.isActiveIdxRegPhaseOne[1] = mFixed;
  WorkingSet.isActiveIdxRegPhaseOne[2] = 32;
  WorkingSet.isActiveIdxRegPhaseOne[3] = mIneq;
  WorkingSet.isActiveIdxRegPhaseOne[4] = mLB + 1;
  WorkingSet.isActiveIdxRegPhaseOne[5] = mUB;
  for (nVarMax = 0; nVarMax < 5; nVarMax++) {
    WorkingSet.isActiveIdxRegPhaseOne[nVarMax + 1] +=
        WorkingSet.isActiveIdxRegPhaseOne[nVarMax];
  }
  for (i = 0; i < 6; i++) {
    WorkingSet.isActiveIdxPhaseOne[i] = WorkingSet.isActiveIdxRegPhaseOne[i];
  }
  WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
  WorkingSet.isActiveIdxRegPhaseOne[1] = mFixed;
  WorkingSet.isActiveIdxRegPhaseOne[2] = 32;
  WorkingSet.isActiveIdxRegPhaseOne[3] = mIneq;
  WorkingSet.isActiveIdxRegPhaseOne[4] = loop_ub + 64;
  WorkingSet.isActiveIdxRegPhaseOne[5] = mUB;
  for (nVarMax = 0; nVarMax < 5; nVarMax++) {
    WorkingSet.isActiveIdxRegPhaseOne[nVarMax + 1] +=
        WorkingSet.isActiveIdxRegPhaseOne[nVarMax];
  }
  for (i = 0; i < 6; i++) {
    WorkingSet.isActiveIdxRegularized[i] = WorkingSet.isActiveIdxRegPhaseOne[i];
  }
  WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
  WorkingSet.isActiveIdxRegPhaseOne[1] = mFixed;
  WorkingSet.isActiveIdxRegPhaseOne[2] = 32;
  WorkingSet.isActiveIdxRegPhaseOne[3] = mIneq;
  WorkingSet.isActiveIdxRegPhaseOne[4] = loop_ub + 65;
  WorkingSet.isActiveIdxRegPhaseOne[5] = mUB;
  for (nVarMax = 0; nVarMax < 5; nVarMax++) {
    WorkingSet.isActiveIdxRegPhaseOne[nVarMax + 1] +=
        WorkingSet.isActiveIdxRegPhaseOne[nVarMax];
  }
  if (mIneq > 0) {
    for (nVarMax = 0; nVarMax < mLinIneq; nVarMax++) {
      i = WorkingSet.nVar;
      for (loop_ub = 0; loop_ub < i; loop_ub++) {
        WorkingSet.Aineq->data[loop_ub + WorkingSet.ldA * nVarMax] =
            Aineq_data[nVarMax + mLinIneq * loop_ub];
      }
    }
  }
  for (nVarMax = 0; nVarMax < mLB; nVarMax++) {
    TrialState.xstarsqp[WorkingSet.indexLB->data[nVarMax] - 1] =
        muDoubleScalarMax(
            TrialState.xstarsqp[WorkingSet.indexLB->data[nVarMax] - 1],
            lb[WorkingSet.indexLB->data[nVarMax] - 1]);
  }
  for (nVarMax = 0; nVarMax < mUB; nVarMax++) {
    TrialState.xstarsqp[WorkingSet.indexUB->data[nVarMax] - 1] =
        muDoubleScalarMin(
            TrialState.xstarsqp[WorkingSet.indexUB->data[nVarMax] - 1],
            ub[WorkingSet.indexUB->data[nVarMax] - 1]);
  }
  for (nVarMax = 0; nVarMax < mFixed; nVarMax++) {
    TrialState.xstarsqp[WorkingSet.indexFixed->data[nVarMax] - 1] =
        ub[WorkingSet.indexFixed->data[nVarMax] - 1];
  }
  expl_temp.objective = 1.0;
  evalObjAndConstrAndDerivatives(
      fun_workspace_runtimedata->x, fun_workspace_runtimedata->lastMV,
      fun_workspace_runtimedata->ref, fun_workspace_runtimedata->OutputWeights,
      fun_workspace_runtimedata->MVWeights,
      fun_workspace_runtimedata->MVRateWeights,
      fun_workspace_runtimedata->ECRWeight,
      fun_workspace_runtimedata->MVScaledTarget,
      nonlcon_workspace_runtimedata->x,
      nonlcon_workspace_runtimedata->OutputMin,
      nonlcon_workspace_runtimedata->OutputMax, 51, mNonlinIneq, 32, false,
      TrialState.xstarsqp, TrialState.grad, TrialState.cIneq,
      TrialState.iNonIneq0, TrialState.cEq, TrialState.iNonEq0,
      WorkingSet.Aineq, TrialState.iNonIneq0, WorkingSet.ldA, WorkingSet.Aeq,
      TrialState.iNonEq0, WorkingSet.ldA, &expl_temp, &alpha1, &nVarMax);
  TrialState.sqpFval = alpha1;
  TrialState.FunctionEvaluations = FiniteDifferences.numEvals + 1;
  if (bineq->size[0] > 0) {
    n_t = (ptrdiff_t)bineq->size[0];
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dcopy(&n_t, &bineq_data[0], &incx_t, &TrialState.cIneq->data[0], &incy_t);
    alpha1 = 1.0;
    scale = -1.0;
    TRANSA = 'T';
    m_t = (ptrdiff_t)51;
    n_t = (ptrdiff_t)bineq->size[0];
    lda_t = (ptrdiff_t)WorkingSet.ldA;
    incx_t = (ptrdiff_t)1;
    incy_t = (ptrdiff_t)1;
    dgemv(&TRANSA, &m_t, &n_t, &alpha1, &WorkingSet.Aineq->data[0], &lda_t,
          &TrialState.xstarsqp[0], &incx_t, &scale, &TrialState.cIneq->data[0],
          &incy_t);
  }
  updateWorkingSetForNewQP(x0, &WorkingSet, mIneq, TrialState.mNonlinIneq,
                           TrialState.cIneq, TrialState.mNonlinEq,
                           TrialState.cEq, mLB, lb, mUB, ub, mFixed);
  initActiveSet(&WorkingSet);
  MeritFunction.initFval = TrialState.sqpFval;
  MeritFunction.penaltyParam = 1.0;
  MeritFunction.threshold = 0.0001;
  MeritFunction.nPenaltyDecreases = 0;
  MeritFunction.linearizedConstrViol = 0.0;
  alpha1 = 0.0;
  for (nVarMax = 0; nVarMax < 32; nVarMax++) {
    alpha1 += muDoubleScalarAbs(TrialState.cEq[nVarMax]);
  }
  MeritFunction.initConstrViolationEq = alpha1;
  alpha1 = 0.0;
  for (nVarMax = 0; nVarMax < mIneq; nVarMax++) {
    if (TrialState.cIneq->data[nVarMax] > 0.0) {
      alpha1 += TrialState.cIneq->data[nVarMax];
    }
  }
  MeritFunction.initConstrViolationIneq = alpha1;
  MeritFunction.phi = 0.0;
  MeritFunction.phiPrimePlus = 0.0;
  MeritFunction.phiFullStep = 0.0;
  MeritFunction.feasRelativeFactor = 0.0;
  MeritFunction.nlpPrimalFeasError = 0.0;
  MeritFunction.nlpDualFeasError = 0.0;
  MeritFunction.nlpComplError = 0.0;
  MeritFunction.firstOrderOpt = 0.0;
  MeritFunction.hasObjective = true;
  b_driver(bineq, lb, ub, &TrialState, &MeritFunction, &FcnEvaluator,
           &FiniteDifferences, &memspace, &WorkingSet, &QRManager, &CholManager,
           &QPObjective, expl_temp.lineq_constraint, expl_temp.cineq_constraint,
           expl_temp.ceq_constraint, unusedExpr);
  emxFreeStruct_struct_T11(&expl_temp);
  emxFreeStruct_struct_T10(&WorkingSet);
  emxFreeStruct_struct_T9(&memspace);
  emxFreeStruct_struct_T8(&QPObjective);
  emxFreeStruct_struct_T7(&CholManager);
  emxFreeStruct_struct_T6(&QRManager);
  emxFreeStruct_struct_T5(&FiniteDifferences);
  emxFreeStruct_struct_T4(&FcnEvaluator);
  *fval = TrialState.sqpFval;
  *exitflag = TrialState.sqpExitFlag;
  output->iterations = TrialState.sqpIterations;
  output->funcCount = TrialState.FunctionEvaluations;
  output->algorithm[0] = 's';
  output->algorithm[1] = 'q';
  output->algorithm[2] = 'p';
  output->constrviolation = MeritFunction.nlpPrimalFeasError;
  alpha1 = 0.0;
  scale = 3.3121686421112381E-170;
  for (nVarMax = 0; nVarMax < 51; nVarMax++) {
    x[nVarMax] = TrialState.xstarsqp[nVarMax];
    absxk = muDoubleScalarAbs(TrialState.delta_x->data[nVarMax]);
    if (absxk > scale) {
      t = scale / absxk;
      alpha1 = alpha1 * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      alpha1 += t * t;
    }
  }
  output->stepsize = scale * muDoubleScalarSqrt(alpha1);
  output->lssteplength = TrialState.steplength;
  output->firstorderopt = MeritFunction.firstOrderOpt;
  emxFreeStruct_struct_T(&TrialState);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (fmincon.c) */
