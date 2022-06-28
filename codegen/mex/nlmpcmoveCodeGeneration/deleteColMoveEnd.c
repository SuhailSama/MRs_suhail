/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * deleteColMoveEnd.c
 *
 * Code generation for function 'deleteColMoveEnd'
 *
 */

/* Include files */
#include "deleteColMoveEnd.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void deleteColMoveEnd(f_struct_T *obj, int32_T idx)
{
  real_T c;
  real_T d;
  real_T s;
  real_T temp;
  int32_T b_i;
  int32_T b_k;
  int32_T b_temp_tmp;
  int32_T endIdx;
  int32_T i;
  int32_T idxRotGCol;
  int32_T ix;
  int32_T k;
  int32_T n;
  int32_T temp_tmp;
  if (obj->usedPivoting) {
    i = 1;
    while ((i <= obj->ncols) && (obj->jpvt->data[i - 1] != idx)) {
      i++;
    }
    idx = i;
  }
  if (idx >= obj->ncols) {
    obj->ncols--;
  } else {
    obj->jpvt->data[idx - 1] = obj->jpvt->data[obj->ncols - 1];
    b_i = obj->minRowCol;
    for (k = 0; k < b_i; k++) {
      obj->QR->data[k + obj->ldq * (idx - 1)] =
          obj->QR->data[k + obj->ldq * (obj->ncols - 1)];
    }
    obj->ncols--;
    obj->minRowCol = muIntScalarMin_sint32(obj->mrows, obj->ncols);
    if (idx < obj->mrows) {
      i = obj->mrows - 1;
      endIdx = muIntScalarMin_sint32(i, obj->ncols);
      k = endIdx;
      idxRotGCol = obj->ldq * (idx - 1);
      while (k >= idx) {
        i = k + idxRotGCol;
        temp = obj->QR->data[i - 1];
        d = obj->QR->data[i];
        c = 0.0;
        s = 0.0;
        drotg(&temp, &d, &c, &s);
        obj->QR->data[i - 1] = temp;
        obj->QR->data[i] = d;
        obj->QR->data[k + obj->ldq * (k - 1)] = 0.0;
        i = k + obj->ldq * idx;
        n = obj->ncols - idx;
        if (n >= 1) {
          ix = i - 1;
          for (b_k = 0; b_k < n; b_k++) {
            temp = c * obj->QR->data[ix] + s * obj->QR->data[i];
            obj->QR->data[i] = c * obj->QR->data[i] - s * obj->QR->data[ix];
            obj->QR->data[ix] = temp;
            i += obj->ldq;
            ix += obj->ldq;
          }
        }
        b_i = obj->ldq * (k - 1);
        n = obj->mrows;
        if (obj->mrows >= 1) {
          ix = obj->ldq + b_i;
          for (b_k = 0; b_k < n; b_k++) {
            temp_tmp = ix + b_k;
            b_temp_tmp = b_i + b_k;
            temp = c * obj->Q->data[b_temp_tmp] + s * obj->Q->data[temp_tmp];
            obj->Q->data[temp_tmp] =
                c * obj->Q->data[temp_tmp] - s * obj->Q->data[b_temp_tmp];
            obj->Q->data[b_temp_tmp] = temp;
          }
        }
        k--;
      }
      b_i = idx + 1;
      for (k = b_i; k <= endIdx; k++) {
        i = k + obj->ldq * (k - 1);
        temp = obj->QR->data[i - 1];
        d = obj->QR->data[i];
        c = 0.0;
        s = 0.0;
        drotg(&temp, &d, &c, &s);
        obj->QR->data[i - 1] = temp;
        obj->QR->data[i] = d;
        i = k * (obj->ldq + 1);
        n = obj->ncols - k;
        if (n >= 1) {
          ix = i - 1;
          for (b_k = 0; b_k < n; b_k++) {
            temp = c * obj->QR->data[ix] + s * obj->QR->data[i];
            obj->QR->data[i] = c * obj->QR->data[i] - s * obj->QR->data[ix];
            obj->QR->data[ix] = temp;
            i += obj->ldq;
            ix += obj->ldq;
          }
        }
        i = obj->ldq * (k - 1);
        n = obj->mrows;
        if (obj->mrows >= 1) {
          ix = obj->ldq + i;
          for (b_k = 0; b_k < n; b_k++) {
            temp_tmp = ix + b_k;
            b_temp_tmp = i + b_k;
            temp = c * obj->Q->data[b_temp_tmp] + s * obj->Q->data[temp_tmp];
            obj->Q->data[temp_tmp] =
                c * obj->Q->data[temp_tmp] - s * obj->Q->data[b_temp_tmp];
            obj->Q->data[b_temp_tmp] = temp;
          }
        }
      }
    }
  }
}

/* End of code generation (deleteColMoveEnd.c) */
