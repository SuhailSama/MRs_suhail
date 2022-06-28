/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * factoryConstruct1.c
 *
 * Code generation for function 'factoryConstruct1'
 *
 */

/* Include files */
#include "factoryConstruct1.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void b_factoryConstruct(int32_T mIneqMax, int32_T nVarMax, int32_T mConstrMax,
                        j_struct_T *obj)
{
  emxArray_int8_T *b;
  int32_T b_i;
  int32_T i;
  int8_T *b_data;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_int8_T(&b, 1);
  obj->mConstr = 0;
  obj->mConstrOrig = 0;
  obj->mConstrMax = mConstrMax;
  obj->nVar = 51;
  obj->nVarOrig = 51;
  obj->nVarMax = nVarMax;
  obj->ldA = nVarMax;
  i = mIneqMax * nVarMax;
  b_i = b->size[0];
  b->size[0] = i;
  emxEnsureCapacity_int8_T(b, b_i);
  b_data = b->data;
  for (b_i = 0; b_i < i; b_i++) {
    b_data[b_i] = 1;
  }
  b_i = obj->Aineq->size[0];
  obj->Aineq->size[0] = b->size[0];
  emxEnsureCapacity_real_T(obj->Aineq, b_i);
  b_i = obj->bineq->size[0];
  obj->bineq->size[0] = mIneqMax;
  emxEnsureCapacity_real_T(obj->bineq, b_i);
  i = nVarMax << 5;
  b_i = b->size[0];
  b->size[0] = i;
  emxEnsureCapacity_int8_T(b, b_i);
  b_data = b->data;
  for (b_i = 0; b_i < i; b_i++) {
    b_data[b_i] = 1;
  }
  b_i = obj->Aeq->size[0];
  obj->Aeq->size[0] = b->size[0];
  emxEnsureCapacity_real_T(obj->Aeq, b_i);
  b_i = obj->lb->size[0];
  obj->lb->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->lb, b_i);
  b_i = obj->ub->size[0];
  obj->ub->size[0] = nVarMax;
  emxEnsureCapacity_real_T(obj->ub, b_i);
  b_i = obj->indexLB->size[0];
  obj->indexLB->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(obj->indexLB, b_i);
  b_i = obj->indexUB->size[0];
  obj->indexUB->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(obj->indexUB, b_i);
  b_i = obj->indexFixed->size[0];
  obj->indexFixed->size[0] = nVarMax;
  emxEnsureCapacity_int32_T(obj->indexFixed, b_i);
  obj->mEqRemoved = 0;
  i = nVarMax * mConstrMax;
  b_i = b->size[0];
  b->size[0] = i;
  emxEnsureCapacity_int8_T(b, b_i);
  b_data = b->data;
  for (b_i = 0; b_i < i; b_i++) {
    b_data[b_i] = 1;
  }
  b_i = obj->ATwset->size[0];
  obj->ATwset->size[0] = b->size[0];
  emxEnsureCapacity_real_T(obj->ATwset, b_i);
  b_i = obj->bwset->size[0];
  obj->bwset->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->bwset, b_i);
  obj->nActiveConstr = 0;
  b_i = obj->maxConstrWorkspace->size[0];
  obj->maxConstrWorkspace->size[0] = mConstrMax;
  emxEnsureCapacity_real_T(obj->maxConstrWorkspace, b_i);
  emxFree_int8_T(&b);
  for (i = 0; i < 5; i++) {
    obj->sizes[i] = 0;
    obj->sizesNormal[i] = 0;
    obj->sizesPhaseOne[i] = 0;
    obj->sizesRegularized[i] = 0;
    obj->sizesRegPhaseOne[i] = 0;
  }
  for (i = 0; i < 6; i++) {
    obj->isActiveIdx[i] = 0;
    obj->isActiveIdxNormal[i] = 0;
    obj->isActiveIdxPhaseOne[i] = 0;
    obj->isActiveIdxRegularized[i] = 0;
    obj->isActiveIdxRegPhaseOne[i] = 0;
  }
  b_i = obj->isActiveConstr->size[0];
  obj->isActiveConstr->size[0] = mConstrMax;
  emxEnsureCapacity_boolean_T(obj->isActiveConstr, b_i);
  b_i = obj->Wid->size[0];
  obj->Wid->size[0] = mConstrMax;
  emxEnsureCapacity_int32_T(obj->Wid, b_i);
  b_i = obj->Wlocalidx->size[0];
  obj->Wlocalidx->size[0] = mConstrMax;
  emxEnsureCapacity_int32_T(obj->Wlocalidx, b_i);
  for (i = 0; i < 5; i++) {
    obj->nWConstr[i] = 0;
  }
  obj->probType = 3;
  obj->SLACK0 = 1.0E-5;
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (factoryConstruct1.c) */
