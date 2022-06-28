/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fullColLDL2_.c
 *
 * Code generation for function 'fullColLDL2_'
 *
 */

/* Include files */
#include "fullColLDL2_.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void fullColLDL2_(g_struct_T *obj, int32_T LD_offset, int32_T NColsRemain,
                  real_T REG_PRIMAL)
{
  real_T alpha1;
  real_T temp;
  real_T y;
  int32_T LD_diagOffset;
  int32_T LDimSizeP1;
  int32_T i;
  int32_T i1;
  int32_T ijA;
  int32_T j;
  int32_T jA;
  int32_T k;
  int32_T subMatrixDim;
  LDimSizeP1 = obj->ldm;
  for (k = 0; k < NColsRemain; k++) {
    LD_diagOffset = (LD_offset + (LDimSizeP1 + 1) * k) - 1;
    if (muDoubleScalarAbs(obj->FMat->data[LD_diagOffset]) <= obj->regTol_) {
      obj->FMat->data[LD_diagOffset] += REG_PRIMAL;
    }
    alpha1 = -1.0 / obj->FMat->data[LD_diagOffset];
    subMatrixDim = (NColsRemain - k) - 2;
    for (jA = 0; jA <= subMatrixDim; jA++) {
      obj->workspace_ = obj->FMat->data[(LD_diagOffset + jA) + 1];
    }
    y = obj->workspace_;
    if (!(alpha1 == 0.0)) {
      jA = LD_diagOffset + LDimSizeP1;
      for (j = 0; j <= subMatrixDim; j++) {
        if (y != 0.0) {
          temp = y * alpha1;
          i = jA + 2;
          i1 = subMatrixDim + jA;
          for (ijA = i; ijA <= i1 + 2; ijA++) {
            obj->FMat->data[ijA - 1] += obj->workspace_ * temp;
          }
        }
        jA += obj->ldm;
      }
    }
    for (jA = 0; jA <= subMatrixDim; jA++) {
      i = (LD_diagOffset + jA) + 1;
      obj->FMat->data[i] /= obj->FMat->data[LD_diagOffset];
    }
  }
  jA = (LD_offset + (obj->ldm + 1) * (NColsRemain - 1)) - 1;
  if (muDoubleScalarAbs(obj->FMat->data[jA]) <= obj->regTol_) {
    obj->FMat->data[jA] += REG_PRIMAL;
  }
}

/* End of code generation (fullColLDL2_.c) */
