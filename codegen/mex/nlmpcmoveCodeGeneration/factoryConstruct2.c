/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * factoryConstruct2.c
 *
 * Code generation for function 'factoryConstruct2'
 *
 */

/* Include files */
#include "factoryConstruct2.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void c_factoryConstruct(const k_struct_T *objfun_workspace_runtimedata,
                        const real_T c_objfun_workspace_userdata_Cur[3],
                        const real_T c_objfun_workspace_userdata_Las[2],
                        const emxArray_real_T *c_objfun_workspace_userdata_Ref,
                        const emxArray_real_T *c_objfun_workspace_userdata_MVT,
                        const real_T c_objfun_workspace_userdata_MVI[2],
                        const k_struct_T *nonlin_workspace_runtimedata,
                        const l_struct_T *nonlin_workspace_userdata,
                        int32_T mCineq, const real_T lb[51],
                        const real_T ub[51], o_struct_T *obj)
{
  const real_T *d_objfun_workspace_userdata_MVT;
  const real_T *d_objfun_workspace_userdata_Ref;
  int32_T i;
  int32_T idx;
  boolean_T b;
  d_objfun_workspace_userdata_MVT = c_objfun_workspace_userdata_MVT->data;
  d_objfun_workspace_userdata_Ref = c_objfun_workspace_userdata_Ref->data;
  emxCopyStruct_struct_T(&obj->objfun.workspace.runtimedata,
                         objfun_workspace_runtimedata);
  obj->objfun.workspace.userdata.Ts = 0.1;
  obj->objfun.workspace.userdata.CurrentStates[0] =
      c_objfun_workspace_userdata_Cur[0];
  obj->objfun.workspace.userdata.CurrentStates[1] =
      c_objfun_workspace_userdata_Cur[1];
  obj->objfun.workspace.userdata.CurrentStates[2] =
      c_objfun_workspace_userdata_Cur[2];
  obj->objfun.workspace.userdata.LastMV[0] = c_objfun_workspace_userdata_Las[0];
  obj->objfun.workspace.userdata.LastMV[1] = c_objfun_workspace_userdata_Las[1];
  i = obj->objfun.workspace.userdata.References->size[0] *
      obj->objfun.workspace.userdata.References->size[1];
  obj->objfun.workspace.userdata.References->size[0] =
      c_objfun_workspace_userdata_Ref->size[0];
  obj->objfun.workspace.userdata.References->size[1] =
      c_objfun_workspace_userdata_Ref->size[1];
  emxEnsureCapacity_real_T(obj->objfun.workspace.userdata.References, i);
  idx = c_objfun_workspace_userdata_Ref->size[0] *
        c_objfun_workspace_userdata_Ref->size[1];
  for (i = 0; i < idx; i++) {
    obj->objfun.workspace.userdata.References->data[i] =
        d_objfun_workspace_userdata_Ref[i];
  }
  i = obj->objfun.workspace.userdata.MVTarget->size[0] *
      obj->objfun.workspace.userdata.MVTarget->size[1];
  obj->objfun.workspace.userdata.MVTarget->size[0] =
      c_objfun_workspace_userdata_MVT->size[0];
  obj->objfun.workspace.userdata.MVTarget->size[1] =
      c_objfun_workspace_userdata_MVT->size[1];
  emxEnsureCapacity_real_T(obj->objfun.workspace.userdata.MVTarget, i);
  idx = c_objfun_workspace_userdata_MVT->size[0] *
        c_objfun_workspace_userdata_MVT->size[1];
  for (i = 0; i < idx; i++) {
    obj->objfun.workspace.userdata.MVTarget->data[i] =
        d_objfun_workspace_userdata_MVT[i];
  }
  obj->objfun.workspace.userdata.PredictionHorizon = 10.0;
  obj->objfun.workspace.userdata.NumOfStates = 3.0;
  obj->objfun.workspace.userdata.NumOfOutputs = 3.0;
  obj->objfun.workspace.userdata.NumOfInputs = 2.0;
  obj->objfun.workspace.userdata.MVIndex[0] =
      c_objfun_workspace_userdata_MVI[0];
  obj->objfun.workspace.userdata.MVIndex[1] =
      c_objfun_workspace_userdata_MVI[1];
  emxCopyStruct_struct_T(&obj->nonlin.workspace.runtimedata,
                         nonlin_workspace_runtimedata);
  emxCopyStruct_struct_T1(&obj->nonlin.workspace.userdata,
                          nonlin_workspace_userdata);
  obj->f_1 = 0.0;
  i = obj->cIneq_1->size[0];
  obj->cIneq_1->size[0] = mCineq;
  emxEnsureCapacity_real_T(obj->cIneq_1, i);
  obj->f_2 = 0.0;
  i = obj->cIneq_2->size[0];
  obj->cIneq_2->size[0] = mCineq;
  emxEnsureCapacity_real_T(obj->cIneq_2, i);
  obj->nVar = 51;
  obj->mIneq = mCineq;
  obj->mEq = 32;
  obj->numEvals = 0;
  obj->SpecifyObjectiveGradient = true;
  obj->SpecifyConstraintGradient = true;
  obj->isEmptyNonlcon = (mCineq + 32 == 0);
  obj->FiniteDifferenceType = 0;
  b = false;
  idx = 0;
  while ((!b) && (idx + 1 <= 51)) {
    obj->hasLB[idx] =
        ((!muDoubleScalarIsInf(lb[idx])) && (!muDoubleScalarIsNaN(lb[idx])));
    obj->hasUB[idx] =
        ((!muDoubleScalarIsInf(ub[idx])) && (!muDoubleScalarIsNaN(ub[idx])));
    if (obj->hasLB[idx] || obj->hasUB[idx]) {
      b = true;
    }
    idx++;
  }
  while (idx + 1 <= 51) {
    obj->hasLB[idx] =
        ((!muDoubleScalarIsInf(lb[idx])) && (!muDoubleScalarIsNaN(lb[idx])));
    obj->hasUB[idx] =
        ((!muDoubleScalarIsInf(ub[idx])) && (!muDoubleScalarIsNaN(ub[idx])));
    idx++;
  }
  obj->hasBounds = b;
}

/* End of code generation (factoryConstruct2.c) */
