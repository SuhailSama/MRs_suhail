/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * modifyOverheadPhaseOne_.c
 *
 * Code generation for function 'modifyOverheadPhaseOne_'
 *
 */

/* Include files */
#include "modifyOverheadPhaseOne_.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void modifyOverheadPhaseOne_(j_struct_T *obj)
{
  int32_T i;
  int32_T idx;
  int32_T idxEq;
  i = obj->sizes[0];
  for (idx = 0; idx < i; idx++) {
    obj->ATwset->data[(obj->nVar + obj->ldA * idx) - 1] = 0.0;
  }
  i = obj->sizes[1];
  for (idx = 0; idx < i; idx++) {
    idxEq = (obj->nVar + obj->ldA * idx) - 1;
    obj->Aeq->data[idxEq] = 0.0;
    obj->ATwset->data[idxEq + obj->ldA * (obj->isActiveIdx[1] - 1)] = 0.0;
  }
  i = obj->sizes[2];
  for (idx = 0; idx < i; idx++) {
    obj->Aineq->data[(obj->nVar + obj->ldA * idx) - 1] = -1.0;
  }
  obj->indexLB->data[obj->sizes[3] - 1] = obj->nVar;
  obj->lb->data[obj->nVar - 1] = obj->SLACK0;
  idxEq = obj->isActiveIdx[2];
  i = obj->nActiveConstr;
  for (idx = idxEq; idx <= i; idx++) {
    obj->ATwset->data[(obj->nVar + obj->ldA * (idx - 1)) - 1] = -1.0;
  }
  if (obj->nWConstr[4] > 0) {
    i = obj->sizesNormal[4];
    for (idx = 0; idx <= i; idx++) {
      obj->isActiveConstr->data[(obj->isActiveIdx[4] + idx) - 1] = false;
    }
  }
  obj->isActiveConstr->data[obj->isActiveIdx[4] - 2] = false;
}

/* End of code generation (modifyOverheadPhaseOne_.c) */
