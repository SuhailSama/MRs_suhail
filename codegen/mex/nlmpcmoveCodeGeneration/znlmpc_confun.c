/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * znlmpc_confun.c
 *
 * Code generation for function 'znlmpc_confun'
 *
 */

/* Include files */
#include "znlmpc_confun.h"
#include "all.h"
#include "mtimes.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void outputBounds(const real_T runtimedata_OutputMin[30],
                  const real_T runtimedata_OutputMax[30], const real_T X[33],
                  real_T e, emxArray_real_T *c, emxArray_real_T *Jc)
{
  emxArray_int8_T *Je;
  emxArray_int8_T *Jx;
  emxArray_int8_T *r;
  emxArray_int8_T *r1;
  emxArray_int8_T *varargin_1;
  emxArray_real_T *b_c;
  emxArray_real_T *b_y;
  emxArray_real_T *r2;
  emxArray_real_T *varargin_2;
  real_T c_c[60];
  real_T b_c_tmp;
  real_T c_c_tmp;
  real_T c_tmp;
  real_T d;
  real_T d1;
  real_T d2;
  real_T d3;
  real_T *Jc_data;
  real_T *c_data;
  int32_T b_i;
  int32_T b_icf_tmp_tmp;
  int32_T c_icf_tmp_tmp;
  int32_T i;
  int32_T icf_tmp_tmp;
  int32_T k;
  int16_T b_ic[6];
  int8_T b_Jx[1800];
  int8_T b_Je[60];
  int8_T Ck[9];
  int8_T val[9];
  int8_T ic[3];
  int8_T input_sizes_idx_0;
  int8_T *Jx_data;
  int8_T *r3;
  int8_T *varargin_1_data;
  boolean_T icf[60];
  boolean_T bv[30];
  boolean_T x[3];
  boolean_T exitg1;
  boolean_T guard1 = false;
  boolean_T y;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  for (i = 0; i < 30; i++) {
    bv[i] = muDoubleScalarIsInf(runtimedata_OutputMin[i]);
  }
  all(bv, x);
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 2)) {
    if (!x[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  emxInit_int8_T(&r, 1);
  emxInit_int8_T(&r1, 1);
  emxInit_real_T(&b_y, 2);
  emxInit_int8_T(&varargin_1, 2);
  emxInit_real_T(&varargin_2, 2);
  emxInit_real_T(&b_c, 1);
  emxInit_real_T(&r2, 2);
  emxInit_int8_T(&Jx, 3);
  emxInit_int8_T(&Je, 2);
  guard1 = false;
  if (y) {
    for (i = 0; i < 30; i++) {
      bv[i] = muDoubleScalarIsInf(runtimedata_OutputMax[i]);
    }
    all(bv, x);
    y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= 2)) {
      if (!x[k]) {
        y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
    if (y) {
      c->size[0] = 0;
      c->size[1] = 0;
      Jc->size[0] = 0;
      Jc->size[1] = 0;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }
  if (guard1) {
    for (b_i = 0; b_i < 60; b_i++) {
      c_c[b_i] = 0.0;
      icf[b_i] = true;
    }
    memset(&b_Jx[0], 0, 1800U * sizeof(int8_T));
    for (b_i = 0; b_i < 60; b_i++) {
      b_Je[b_i] = 0;
    }
    ic[0] = 1;
    ic[1] = 2;
    ic[2] = 3;
    for (b_i = 0; b_i < 10; b_i++) {
      c_tmp = runtimedata_OutputMin[b_i];
      icf_tmp_tmp = ic[0] - 1;
      icf[ic[0] - 1] =
          ((!muDoubleScalarIsInf(c_tmp)) && (!muDoubleScalarIsNaN(c_tmp)));
      c_tmp = runtimedata_OutputMax[b_i];
      d = runtimedata_OutputMin[b_i + 10];
      b_icf_tmp_tmp = ic[1] - 1;
      icf[ic[1] - 1] = ((!muDoubleScalarIsInf(d)) && (!muDoubleScalarIsNaN(d)));
      d1 = runtimedata_OutputMax[b_i + 10];
      d2 = runtimedata_OutputMin[b_i + 20];
      c_icf_tmp_tmp = ic[2] - 1;
      icf[ic[2] - 1] =
          ((!muDoubleScalarIsInf(d2)) && (!muDoubleScalarIsNaN(d2)));
      d3 = runtimedata_OutputMax[b_i + 20];
      icf[(int8_T)(ic[0] + 3) - 1] =
          ((!muDoubleScalarIsInf(c_tmp)) && (!muDoubleScalarIsNaN(c_tmp)));
      icf[(int8_T)(ic[1] + 3) - 1] =
          ((!muDoubleScalarIsInf(d1)) && (!muDoubleScalarIsNaN(d1)));
      icf[(int8_T)(ic[2] + 3) - 1] =
          ((!muDoubleScalarIsInf(d3)) && (!muDoubleScalarIsNaN(d3)));
      y = false;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k <= 5)) {
        b_ic[0] = (int16_T)icf_tmp_tmp;
        b_ic[3] = (int16_T)(ic[0] + 2);
        b_ic[1] = (int16_T)b_icf_tmp_tmp;
        b_ic[4] = (int16_T)(ic[1] + 2);
        b_ic[2] = (int16_T)c_icf_tmp_tmp;
        b_ic[5] = (int16_T)(ic[2] + 2);
        if (icf[b_ic[k]]) {
          y = true;
          exitg1 = true;
        } else {
          k++;
        }
      }
      if (y) {
        for (i = 0; i < 9; i++) {
          Ck[i] = 0;
        }
        Ck[0] = 1;
        b_c_tmp = X[b_i + 1];
        c_c[ic[0] - 1] = (runtimedata_OutputMin[b_i] - e) - b_c_tmp;
        Ck[4] = 1;
        c_c_tmp = X[b_i + 12];
        c_c[ic[1] - 1] = (d - e) - c_c_tmp;
        Ck[8] = 1;
        c_tmp = X[b_i + 23];
        c_c[ic[2] - 1] = (d2 - e) - c_tmp;
        c_c[ic[0] + 2] = (b_c_tmp - runtimedata_OutputMax[b_i]) - e;
        c_c[ic[1] + 2] = (c_c_tmp - d1) - e;
        c_c[ic[2] + 2] = (c_tmp - d3) - e;
        for (i = 0; i < 9; i++) {
          val[i] = (int8_T)-Ck[i];
        }
        for (k = 0; k < 3; k++) {
          b_Jx[((ic[0] + 60 * k) + 180 * b_i) - 1] = val[3 * k];
          b_Jx[((ic[1] + 60 * k) + 180 * b_i) - 1] = val[3 * k + 1];
          b_Jx[((ic[2] + 60 * k) + 180 * b_i) - 1] = val[3 * k + 2];
        }
        for (k = 0; k < 3; k++) {
          b_Jx[((ic[0] + 60 * k) + 180 * b_i) + 2] = Ck[3 * k];
          b_Jx[((ic[1] + 60 * k) + 180 * b_i) + 2] = Ck[3 * k + 1];
          b_Jx[((ic[2] + 60 * k) + 180 * b_i) + 2] = Ck[3 * k + 2];
          b_Je[ic[k] - 1] = -1;
        }
        b_Je[(int8_T)(ic[0] + 3) - 1] = -1;
        b_Je[(int8_T)(ic[1] + 3) - 1] = -1;
        b_Je[(int8_T)(ic[2] + 3) - 1] = -1;
      }
      ic[0] = (int8_T)(ic[0] + 6);
      ic[1] = (int8_T)(ic[1] + 6);
      ic[2] = (int8_T)(ic[2] + 6);
    }
    icf_tmp_tmp = 0;
    for (b_i = 0; b_i < 60; b_i++) {
      if (icf[b_i]) {
        icf_tmp_tmp++;
      }
    }
    i = r->size[0];
    r->size[0] = icf_tmp_tmp;
    emxEnsureCapacity_int8_T(r, i);
    r3 = r->data;
    icf_tmp_tmp = 0;
    for (b_i = 0; b_i < 60; b_i++) {
      if (icf[b_i]) {
        r3[icf_tmp_tmp] = (int8_T)(b_i + 1);
        icf_tmp_tmp++;
      }
    }
    i = b_c->size[0];
    b_c->size[0] = r->size[0];
    emxEnsureCapacity_real_T(b_c, i);
    Jc_data = b_c->data;
    c_icf_tmp_tmp = r->size[0];
    for (i = 0; i < c_icf_tmp_tmp; i++) {
      Jc_data[i] = c_c[r3[i] - 1];
    }
    i = c->size[0] * c->size[1];
    c->size[0] = r->size[0];
    c->size[1] = 1;
    emxEnsureCapacity_real_T(c, i);
    c_data = c->data;
    c_icf_tmp_tmp = r->size[0];
    for (i = 0; i < c_icf_tmp_tmp; i++) {
      c_data[i] = Jc_data[i];
    }
    icf_tmp_tmp = 0;
    for (b_i = 0; b_i < 60; b_i++) {
      if (icf[b_i]) {
        icf_tmp_tmp++;
      }
    }
    i = r1->size[0];
    r1->size[0] = icf_tmp_tmp;
    emxEnsureCapacity_int8_T(r1, i);
    r3 = r1->data;
    icf_tmp_tmp = 0;
    for (b_i = 0; b_i < 60; b_i++) {
      if (icf[b_i]) {
        r3[icf_tmp_tmp] = (int8_T)(b_i + 1);
        icf_tmp_tmp++;
      }
    }
    if (r1->size[0] == 0) {
      Jc->size[0] = 0;
      Jc->size[1] = 0;
    } else {
      i = r2->size[0] * r2->size[1];
      r2->size[0] = r1->size[0];
      r2->size[1] = 20;
      emxEnsureCapacity_real_T(r2, i);
      Jc_data = r2->data;
      c_icf_tmp_tmp = r1->size[0] * 20;
      for (i = 0; i < c_icf_tmp_tmp; i++) {
        Jc_data[i] = 0.0;
      }
      mtimes(r2, b_y);
      Jc_data = b_y->data;
      i = Jx->size[0] * Jx->size[1] * Jx->size[2];
      Jx->size[0] = r1->size[0];
      Jx->size[1] = 3;
      Jx->size[2] = 10;
      emxEnsureCapacity_int8_T(Jx, i);
      Jx_data = Jx->data;
      c_icf_tmp_tmp = r1->size[0];
      for (i = 0; i < 10; i++) {
        for (k = 0; k < 3; k++) {
          for (icf_tmp_tmp = 0; icf_tmp_tmp < c_icf_tmp_tmp; icf_tmp_tmp++) {
            Jx_data[(icf_tmp_tmp + Jx->size[0] * k) + Jx->size[0] * 3 * i] =
                b_Jx[((r3[icf_tmp_tmp] + 60 * k) + 180 * i) - 1];
          }
        }
      }
      icf_tmp_tmp = r1->size[0];
      i = varargin_1->size[0] * varargin_1->size[1];
      varargin_1->size[0] = 30;
      varargin_1->size[1] = r1->size[0];
      emxEnsureCapacity_int8_T(varargin_1, i);
      varargin_1_data = varargin_1->data;
      c_icf_tmp_tmp = r1->size[0];
      for (i = 0; i < c_icf_tmp_tmp; i++) {
        for (k = 0; k < 30; k++) {
          varargin_1_data[k + 30 * i] = Jx_data[i + icf_tmp_tmp * k];
        }
      }
      i = varargin_2->size[0] * varargin_2->size[1];
      varargin_2->size[0] = 20;
      varargin_2->size[1] = b_y->size[0];
      emxEnsureCapacity_real_T(varargin_2, i);
      c_data = varargin_2->data;
      c_icf_tmp_tmp = b_y->size[0];
      for (i = 0; i < c_icf_tmp_tmp; i++) {
        for (k = 0; k < 20; k++) {
          c_data[k + 20 * i] = Jc_data[i + b_y->size[0] * k];
        }
      }
      icf_tmp_tmp = varargin_1->size[1];
      if ((varargin_1->size[1] == 0) || (varargin_2->size[1] != 0)) {
        input_sizes_idx_0 = 20;
      } else {
        input_sizes_idx_0 = 0;
      }
      b_icf_tmp_tmp = input_sizes_idx_0;
      i = Je->size[0] * Je->size[1];
      Je->size[0] = 1;
      Je->size[1] = r1->size[0];
      emxEnsureCapacity_int8_T(Je, i);
      Jx_data = Je->data;
      c_icf_tmp_tmp = r1->size[0];
      for (i = 0; i < c_icf_tmp_tmp; i++) {
        Jx_data[i] = b_Je[r3[i] - 1];
      }
      i = Jc->size[0] * Jc->size[1];
      Jc->size[0] = input_sizes_idx_0 + 31;
      Jc->size[1] = varargin_1->size[1];
      emxEnsureCapacity_real_T(Jc, i);
      Jc_data = Jc->data;
      for (i = 0; i < icf_tmp_tmp; i++) {
        for (k = 0; k < 30; k++) {
          Jc_data[k + Jc->size[0] * i] = varargin_1_data[k + 30 * i];
        }
      }
      for (i = 0; i < icf_tmp_tmp; i++) {
        for (k = 0; k < b_icf_tmp_tmp; k++) {
          Jc_data[(k + Jc->size[0] * i) + 30] =
              c_data[k + input_sizes_idx_0 * i];
        }
      }
      for (i = 0; i < icf_tmp_tmp; i++) {
        Jc_data[(input_sizes_idx_0 + Jc->size[0] * i) + 30] = Jx_data[i];
      }
    }
  }
  emxFree_int8_T(&Je);
  emxFree_int8_T(&Jx);
  emxFree_real_T(&r2);
  emxFree_real_T(&b_c);
  emxFree_real_T(&varargin_2);
  emxFree_int8_T(&varargin_1);
  emxFree_real_T(&b_y);
  emxFree_int8_T(&r1);
  emxFree_int8_T(&r);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (znlmpc_confun.c) */
