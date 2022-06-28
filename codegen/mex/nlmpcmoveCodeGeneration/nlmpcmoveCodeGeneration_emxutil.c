/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * nlmpcmoveCodeGeneration_emxutil.c
 *
 * Code generation for function 'nlmpcmoveCodeGeneration_emxutil'
 *
 */

/* Include files */
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void c_emxFreeStruct_anonymous_funct(anonymous_function *pStruct)
{
  emxFreeStruct_struct_T2(&pStruct->workspace);
}

void c_emxInitStruct_anonymous_funct(anonymous_function *pStruct)
{
  emxInitStruct_struct_T2(&pStruct->workspace);
}

void emxCopyMatrix_real_T(real_T dst[3], const real_T src[3])
{
  int32_T i;
  for (i = 0; i < 3; i++) {
    dst[i] = src[i];
  }
}

void emxCopyMatrix_real_T1(real_T dst[2], const real_T src[2])
{
  int32_T i;
  for (i = 0; i < 2; i++) {
    dst[i] = src[i];
  }
}

void emxCopyMatrix_real_T3(real_T dst[30], const real_T src[30])
{
  memcpy(&dst[0], &src[0], 30U * sizeof(real_T));
}

void emxCopyMatrix_real_T4(real_T dst[20], const real_T src[20])
{
  memcpy(&dst[0], &src[0], 20U * sizeof(real_T));
}

void emxCopyStruct_struct_T(k_struct_T *dst, const k_struct_T *src)
{
  emxCopyMatrix_real_T(dst->x, src->x);
  emxCopyMatrix_real_T1(dst->lastMV, src->lastMV);
  emxCopy_real_T(&dst->ref, &src->ref);
  emxCopyMatrix_real_T3(dst->OutputWeights, src->OutputWeights);
  emxCopyMatrix_real_T4(dst->MVWeights, src->MVWeights);
  emxCopyMatrix_real_T4(dst->MVRateWeights, src->MVRateWeights);
  dst->ECRWeight = src->ECRWeight;
  emxCopyMatrix_real_T3(dst->OutputMin, src->OutputMin);
  emxCopyMatrix_real_T3(dst->OutputMax, src->OutputMax);
  emxCopyMatrix_real_T3(dst->StateMin, src->StateMin);
  emxCopyMatrix_real_T3(dst->StateMax, src->StateMax);
  emxCopyMatrix_real_T4(dst->MVMin, src->MVMin);
  emxCopyMatrix_real_T4(dst->MVMax, src->MVMax);
  emxCopyMatrix_real_T4(dst->MVRateMin, src->MVRateMin);
  emxCopyMatrix_real_T4(dst->MVRateMax, src->MVRateMax);
  emxCopy_real_T(&dst->MVScaledTarget, &src->MVScaledTarget);
}

void emxCopyStruct_struct_T1(l_struct_T *dst, const l_struct_T *src)
{
  dst->Ts = src->Ts;
  emxCopyMatrix_real_T(dst->CurrentStates, src->CurrentStates);
  emxCopyMatrix_real_T1(dst->LastMV, src->LastMV);
  emxCopy_real_T(&dst->References, &src->References);
  emxCopy_real_T(&dst->MVTarget, &src->MVTarget);
  dst->PredictionHorizon = src->PredictionHorizon;
  dst->NumOfStates = src->NumOfStates;
  dst->NumOfOutputs = src->NumOfOutputs;
  dst->NumOfInputs = src->NumOfInputs;
  emxCopyMatrix_real_T1(dst->MVIndex, src->MVIndex);
}

void emxCopy_real_T(emxArray_real_T **dst, emxArray_real_T *const *src)
{
  int32_T i;
  int32_T numElDst;
  int32_T numElSrc;
  numElDst = 1;
  numElSrc = 1;
  for (i = 0; i < (*dst)->numDimensions; i++) {
    numElDst *= (*dst)->size[i];
    numElSrc *= (*src)->size[i];
  }
  for (i = 0; i < (*dst)->numDimensions; i++) {
    (*dst)->size[i] = (*src)->size[i];
  }
  emxEnsureCapacity_real_T(*dst, numElDst);
  for (i = 0; i < numElSrc; i++) {
    (*dst)->data[i] = (*src)->data[i];
  }
}

void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(boolean_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(boolean_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (boolean_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(int32_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(int32_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (int32_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(int8_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(int8_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (int8_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

void emxEnsureCapacity_ptrdiff_t(emxArray_ptrdiff_t *emxArray, int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(ptrdiff_t));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(ptrdiff_t) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (ptrdiff_t *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel)
{
  int32_T i;
  int32_T newNumel;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }
  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }
    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }
    newData = emlrtCallocMex((uint32_T)i, sizeof(real_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(real_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }
    emxArray->data = (real_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

void emxFreeStruct_struct1_T(struct1_T *pStruct)
{
  emxFree_real_T(&pStruct->ref);
  emxFree_real_T(&pStruct->MVTarget);
  emxFree_real_T(&pStruct->X0);
  emxFree_real_T(&pStruct->MV0);
}

void emxFreeStruct_struct_T(e_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->cIneq);
  emxFree_real_T(&pStruct->cIneq_old);
  emxFree_real_T(&pStruct->grad);
  emxFree_real_T(&pStruct->grad_old);
  emxFree_real_T(&pStruct->lambdasqp);
  emxFree_real_T(&pStruct->lambdaStopTest);
  emxFree_real_T(&pStruct->lambdaStopTestPrev);
  emxFree_real_T(&pStruct->delta_x);
  emxFree_real_T(&pStruct->socDirection);
  emxFree_int32_T(&pStruct->workingset_old);
  emxFree_real_T(&pStruct->JacCineqTrans_old);
  emxFree_real_T(&pStruct->JacCeqTrans_old);
  emxFree_real_T(&pStruct->gradLag);
  emxFree_real_T(&pStruct->delta_gradLag);
  emxFree_real_T(&pStruct->xstar);
  emxFree_real_T(&pStruct->lambda);
  emxFree_real_T(&pStruct->searchDir);
}

void emxFreeStruct_struct_T1(k_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->ref);
  emxFree_real_T(&pStruct->MVScaledTarget);
}

void emxFreeStruct_struct_T10(j_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->Aineq);
  emxFree_real_T(&pStruct->bineq);
  emxFree_real_T(&pStruct->Aeq);
  emxFree_real_T(&pStruct->lb);
  emxFree_real_T(&pStruct->ub);
  emxFree_int32_T(&pStruct->indexLB);
  emxFree_int32_T(&pStruct->indexUB);
  emxFree_int32_T(&pStruct->indexFixed);
  emxFree_real_T(&pStruct->ATwset);
  emxFree_real_T(&pStruct->bwset);
  emxFree_real_T(&pStruct->maxConstrWorkspace);
  emxFree_boolean_T(&pStruct->isActiveConstr);
  emxFree_int32_T(&pStruct->Wid);
  emxFree_int32_T(&pStruct->Wlocalidx);
}

void emxFreeStruct_struct_T11(p_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->lineq_constraint);
  emxFree_real_T(&pStruct->cineq_constraint);
}

void emxFreeStruct_struct_T2(m_struct_T *pStruct)
{
  emxFreeStruct_struct_T1(&pStruct->runtimedata);
  emxFreeStruct_struct_T3(&pStruct->userdata);
}

void emxFreeStruct_struct_T3(l_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->References);
  emxFree_real_T(&pStruct->MVTarget);
}

void emxFreeStruct_struct_T4(n_struct_T *pStruct)
{
  c_emxFreeStruct_anonymous_funct(&pStruct->objfun);
  c_emxFreeStruct_anonymous_funct(&pStruct->nonlcon);
}

void emxFreeStruct_struct_T5(o_struct_T *pStruct)
{
  c_emxFreeStruct_anonymous_funct(&pStruct->objfun);
  c_emxFreeStruct_anonymous_funct(&pStruct->nonlin);
  emxFree_real_T(&pStruct->cIneq_1);
  emxFree_real_T(&pStruct->cIneq_2);
}

void emxFreeStruct_struct_T6(f_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->QR);
  emxFree_real_T(&pStruct->Q);
  emxFree_int32_T(&pStruct->jpvt);
  emxFree_real_T(&pStruct->tau);
}

void emxFreeStruct_struct_T7(g_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->FMat);
}

void emxFreeStruct_struct_T8(h_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->grad);
  emxFree_real_T(&pStruct->Hx);
}

void emxFreeStruct_struct_T9(i_struct_T *pStruct)
{
  emxFree_real_T(&pStruct->workspace_double);
  emxFree_int32_T(&pStruct->workspace_int);
  emxFree_int32_T(&pStruct->workspace_sort);
}

void emxFree_boolean_T(emxArray_boolean_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_boolean_T *)NULL) {
    if (((*pEmxArray)->data != (boolean_T *)NULL) &&
        (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference(emlrtRootTLSGlobal, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_boolean_T *)NULL;
  }
}

void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int32_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference(emlrtRootTLSGlobal, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

void emxFree_int8_T(emxArray_int8_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int8_T *)NULL) {
    if (((*pEmxArray)->data != (int8_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference(emlrtRootTLSGlobal, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_int8_T *)NULL;
  }
}

void emxFree_ptrdiff_t(emxArray_ptrdiff_t **pEmxArray)
{
  if (*pEmxArray != (emxArray_ptrdiff_t *)NULL) {
    if (((*pEmxArray)->data != (ptrdiff_t *)NULL) &&
        (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference(emlrtRootTLSGlobal, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_ptrdiff_t *)NULL;
  }
}

void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }
    emlrtFreeMex((*pEmxArray)->size);
    emlrtRemoveHeapReference(emlrtRootTLSGlobal, (void *)pEmxArray);
    emlrtFreeEmxArray(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

void emxInitStruct_struct1_T(struct1_T *pStruct)
{
  emxInit_real_T(&pStruct->ref, 2);
  emxInit_real_T(&pStruct->MVTarget, 2);
  emxInit_real_T(&pStruct->X0, 2);
  emxInit_real_T(&pStruct->MV0, 2);
}

void emxInitStruct_struct_T(e_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->cIneq, 1);
  emxInit_real_T(&pStruct->cIneq_old, 1);
  emxInit_real_T(&pStruct->grad, 1);
  emxInit_real_T(&pStruct->grad_old, 1);
  emxInit_real_T(&pStruct->lambdasqp, 1);
  emxInit_real_T(&pStruct->lambdaStopTest, 1);
  emxInit_real_T(&pStruct->lambdaStopTestPrev, 1);
  emxInit_real_T(&pStruct->delta_x, 1);
  emxInit_real_T(&pStruct->socDirection, 1);
  emxInit_int32_T(&pStruct->workingset_old, 1);
  emxInit_real_T(&pStruct->JacCineqTrans_old, 2);
  emxInit_real_T(&pStruct->JacCeqTrans_old, 2);
  emxInit_real_T(&pStruct->gradLag, 1);
  emxInit_real_T(&pStruct->delta_gradLag, 1);
  emxInit_real_T(&pStruct->xstar, 1);
  emxInit_real_T(&pStruct->lambda, 1);
  emxInit_real_T(&pStruct->searchDir, 1);
}

void emxInitStruct_struct_T1(n_struct_T *pStruct)
{
  c_emxInitStruct_anonymous_funct(&pStruct->objfun);
  c_emxInitStruct_anonymous_funct(&pStruct->nonlcon);
}

void emxInitStruct_struct_T10(j_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->Aineq, 1);
  emxInit_real_T(&pStruct->bineq, 1);
  emxInit_real_T(&pStruct->Aeq, 1);
  emxInit_real_T(&pStruct->lb, 1);
  emxInit_real_T(&pStruct->ub, 1);
  emxInit_int32_T(&pStruct->indexLB, 1);
  emxInit_int32_T(&pStruct->indexUB, 1);
  emxInit_int32_T(&pStruct->indexFixed, 1);
  emxInit_real_T(&pStruct->ATwset, 1);
  emxInit_real_T(&pStruct->bwset, 1);
  emxInit_real_T(&pStruct->maxConstrWorkspace, 1);
  emxInit_boolean_T(&pStruct->isActiveConstr);
  emxInit_int32_T(&pStruct->Wid, 1);
  emxInit_int32_T(&pStruct->Wlocalidx, 1);
}

void emxInitStruct_struct_T11(p_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->lineq_constraint, 1);
  emxInit_real_T(&pStruct->cineq_constraint, 1);
}

void emxInitStruct_struct_T2(m_struct_T *pStruct)
{
  emxInitStruct_struct_T3(&pStruct->runtimedata);
  emxInitStruct_struct_T4(&pStruct->userdata);
}

void emxInitStruct_struct_T3(k_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->ref, 2);
  emxInit_real_T(&pStruct->MVScaledTarget, 2);
}

void emxInitStruct_struct_T4(l_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->References, 2);
  emxInit_real_T(&pStruct->MVTarget, 2);
}

void emxInitStruct_struct_T5(o_struct_T *pStruct)
{
  c_emxInitStruct_anonymous_funct(&pStruct->objfun);
  c_emxInitStruct_anonymous_funct(&pStruct->nonlin);
  emxInit_real_T(&pStruct->cIneq_1, 1);
  emxInit_real_T(&pStruct->cIneq_2, 1);
}

void emxInitStruct_struct_T6(f_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->QR, 2);
  emxInit_real_T(&pStruct->Q, 2);
  emxInit_int32_T(&pStruct->jpvt, 1);
  emxInit_real_T(&pStruct->tau, 1);
}

void emxInitStruct_struct_T7(g_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->FMat, 2);
}

void emxInitStruct_struct_T8(h_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->grad, 1);
  emxInit_real_T(&pStruct->Hx, 1);
}

void emxInitStruct_struct_T9(i_struct_T *pStruct)
{
  emxInit_real_T(&pStruct->workspace_double, 2);
  emxInit_int32_T(&pStruct->workspace_int, 1);
  emxInit_int32_T(&pStruct->workspace_sort, 1);
}

void emxInit_boolean_T(emxArray_boolean_T **pEmxArray)
{
  emxArray_boolean_T *emxArray;
  *pEmxArray =
      (emxArray_boolean_T *)emlrtMallocEmxArray(sizeof(emxArray_boolean_T));
  emlrtPushHeapReferenceStackEmxArray(
      emlrtRootTLSGlobal, false, (void *)pEmxArray, (void *)&emxFree_boolean_T,
      NULL, NULL, NULL);
  emxArray = *pEmxArray;
  emxArray->data = (boolean_T *)NULL;
  emxArray->numDimensions = 1;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  emxArray->size[0] = 0;
}

void emxInit_int32_T(emxArray_int32_T **pEmxArray, int32_T numDimensions)
{
  emxArray_int32_T *emxArray;
  int32_T i;
  *pEmxArray =
      (emxArray_int32_T *)emlrtMallocEmxArray(sizeof(emxArray_int32_T));
  emlrtPushHeapReferenceStackEmxArray(
      emlrtRootTLSGlobal, false, (void *)pEmxArray, (void *)&emxFree_int32_T,
      NULL, NULL, NULL);
  emxArray = *pEmxArray;
  emxArray->data = (int32_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

void emxInit_int8_T(emxArray_int8_T **pEmxArray, int32_T numDimensions)
{
  emxArray_int8_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_int8_T *)emlrtMallocEmxArray(sizeof(emxArray_int8_T));
  emlrtPushHeapReferenceStackEmxArray(
      emlrtRootTLSGlobal, false, (void *)pEmxArray, (void *)&emxFree_int8_T,
      NULL, NULL, NULL);
  emxArray = *pEmxArray;
  emxArray->data = (int8_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

void emxInit_ptrdiff_t(emxArray_ptrdiff_t **pEmxArray)
{
  emxArray_ptrdiff_t *emxArray;
  *pEmxArray =
      (emxArray_ptrdiff_t *)emlrtMallocEmxArray(sizeof(emxArray_ptrdiff_t));
  emlrtPushHeapReferenceStackEmxArray(
      emlrtRootTLSGlobal, false, (void *)pEmxArray, (void *)&emxFree_ptrdiff_t,
      NULL, NULL, NULL);
  emxArray = *pEmxArray;
  emxArray->data = (ptrdiff_t *)NULL;
  emxArray->numDimensions = 1;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  emxArray->size[0] = 0;
}

void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocEmxArray(sizeof(emxArray_real_T));
  emlrtPushHeapReferenceStackEmxArray(
      emlrtRootTLSGlobal, false, (void *)pEmxArray, (void *)&emxFree_real_T,
      NULL, NULL, NULL);
  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/* End of code generation (nlmpcmoveCodeGeneration_emxutil.c) */
