/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * partialColLDL3_.c
 *
 * Code generation for function 'partialColLDL3_'
 *
 */

/* Include files */
#include "partialColLDL3_.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void partialColLDL3_(g_struct_T *obj, int32_T LD_offset, int32_T NColsRemain,
                     real_T REG_PRIMAL)
{
  real_T y;
  int32_T LD_diagOffset;
  int32_T LDimSizeP1;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T ia;
  int32_T idx;
  int32_T ix;
  int32_T iy0;
  int32_T j;
  int32_T k;
  int32_T lda;
  int32_T m;
  int32_T subBlockSize;
  int32_T subRows;
  int32_T y_tmp;
  LDimSizeP1 = obj->ldm + 1;
  i = NColsRemain - 1;
  for (k = 0; k < 48; k++) {
    subRows = (NColsRemain - k) - 1;
    LD_diagOffset = (LD_offset + LDimSizeP1 * k) - 1;
    for (idx = 0; idx <= subRows; idx++) {
      obj->workspace_ = obj->FMat->data[LD_diagOffset + idx];
    }
    for (idx = 0; idx <= i; idx++) {
      obj->workspace2_ = obj->workspace_;
    }
    lda = obj->ldm;
    y = obj->workspace2_;
    if ((NColsRemain != 0) && (k != 0)) {
      ix = LD_offset + k;
      i1 = obj->ldm * (k - 1) + 1;
      for (idx = 1; lda < 0 ? idx >= i1 : idx <= i1; idx += lda) {
        i2 = (idx + NColsRemain) - 1;
        for (ia = idx; ia <= i2; ia++) {
          y += obj->workspace_ * -obj->FMat->data[ix - 1];
        }
        ix += obj->ldm;
      }
    }
    obj->workspace2_ = y;
    for (idx = 0; idx <= i; idx++) {
      obj->workspace_ = y;
    }
    for (idx = 0; idx <= subRows; idx++) {
      obj->FMat->data[LD_diagOffset + idx] = obj->workspace_;
    }
    if (muDoubleScalarAbs(obj->FMat->data[LD_diagOffset]) <= obj->regTol_) {
      obj->FMat->data[LD_diagOffset] += REG_PRIMAL;
    }
    for (idx = 0; idx < subRows; idx++) {
      i1 = (LD_diagOffset + idx) + 1;
      obj->FMat->data[i1] /= obj->FMat->data[LD_diagOffset];
    }
  }
  for (j = 48; j <= i; j += 48) {
    y_tmp = NColsRemain - j;
    subBlockSize = muIntScalarMin_sint32(48, y_tmp);
    i1 = j + subBlockSize;
    i2 = i1 - 1;
    for (k = j; k <= i2; k++) {
      m = i1 - k;
      iy0 = (LD_offset + LDimSizeP1 * k) - 1;
      for (idx = 0; idx < 48; idx++) {
        obj->workspace2_ =
            obj->FMat->data[((LD_offset + k) + idx * obj->ldm) - 1];
      }
      ix = k + 1;
      lda = obj->ldm;
      if (m != 0) {
        i3 = (k + obj->ldm * 47) + 1;
        for (idx = ix; lda < 0 ? idx >= i3 : idx <= i3; idx += lda) {
          subRows = (idx + m) - 1;
          for (ia = idx; ia <= subRows; ia++) {
            LD_diagOffset = (iy0 + ia) - idx;
            obj->FMat->data[LD_diagOffset] +=
                obj->workspace_ * -obj->workspace2_;
          }
        }
      }
    }
    if (i1 < NColsRemain) {
      m = y_tmp - subBlockSize;
      ia = ((LD_offset + subBlockSize) + LDimSizeP1 * j) - 1;
      i1 = subBlockSize - 1;
      for (idx = 0; idx < 48; idx++) {
        ix = (LD_offset + j) + idx * obj->ldm;
        for (subRows = 0; subRows <= i1; subRows++) {
          obj->workspace2_ = obj->FMat->data[(ix + subRows) - 1];
        }
      }
      LD_diagOffset = obj->ldm;
      idx = obj->ldm;
      if ((m != 0) && (subBlockSize != 0)) {
        ix = ia + obj->ldm * (subBlockSize - 1);
        subRows = 0;
        for (y_tmp = ia; idx < 0 ? y_tmp >= ix : y_tmp <= ix; y_tmp += idx) {
          subRows++;
          i1 = subRows + LD_diagOffset * 47;
          for (iy0 = subRows; LD_diagOffset < 0 ? iy0 >= i1 : iy0 <= i1;
               iy0 += LD_diagOffset) {
            i2 = y_tmp + 1;
            i3 = y_tmp + m;
            for (lda = i2; lda <= i3; lda++) {
              obj->FMat->data[lda - 1] += -obj->workspace2_ * obj->workspace_;
            }
          }
        }
      }
    }
  }
}

/* End of code generation (partialColLDL3_.c) */
