/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * nlmpcmoveCodeGeneration.c
 *
 * Code generation for function 'nlmpcmoveCodeGeneration'
 *
 */

/* Include files */
#include "nlmpcmoveCodeGeneration.h"
#include "fmincon.h"
#include "mtimes.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "znlmpc_confun.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void c_nlmpcmoveCodeGeneration_anonF(
    const real_T runtimedata_x[3], const real_T runtimedata_OutputMin[30],
    const real_T runtimedata_OutputMax[30], const real_T z[51],
    emxArray_real_T *varargout_1, real_T varargout_2[32],
    emxArray_real_T *varargout_3, real_T varargout_4[1632])
{
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  emxArray_real_T *Jc;
  emxArray_real_T *c;
  real_T Jx[900];
  real_T Jmv[600];
  real_T y[600];
  real_T b_Jx[60];
  real_T Ju[40];
  real_T b_y[40];
  real_T X[33];
  real_T b_X[33];
  real_T b_z[30];
  real_T U[22];
  real_T Umv[22];
  real_T a[20];
  real_T val[6];
  real_T alpha1;
  real_T beta1;
  real_T cequ_idx_0;
  real_T cequ_idx_1;
  real_T d;
  real_T d1;
  real_T fk_idx_1_tmp;
  real_T *Jc_data;
  real_T *c_data;
  real_T *varargout_1_data;
  int32_T b_i;
  int32_T i;
  int32_T input_sizes_idx_0;
  int32_T k;
  int32_T sizes_idx_1;
  char_T TRANSA1;
  char_T TRANSB1;
  int8_T ic[3];
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  memset(&X[0], 0, 33U * sizeof(real_T));
  memset(&Umv[0], 0, 22U * sizeof(real_T));
  for (i = 0; i < 20; i++) {
    d = 0.0;
    for (k = 0; k < 20; k++) {
      d += (real_T)iv[i + 20 * k] * z[k + 30];
    }
    a[i] = d;
  }
  for (i = 0; i < 2; i++) {
    for (k = 0; k < 10; k++) {
      Umv[k + 11 * i] = a[i + (k << 1)];
    }
  }
  memcpy(&b_z[0], &z[0], 30U * sizeof(real_T));
  for (i = 0; i < 3; i++) {
    for (k = 0; k < 10; k++) {
      X[(k + 11 * i) + 1] = b_z[i + 3 * k];
    }
    X[11 * i] = runtimedata_x[i];
  }
  for (b_i = 0; b_i < 2; b_i++) {
    Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
    memcpy(&U[b_i * 11], &Umv[b_i * 11], 11U * sizeof(real_T));
  }
  memset(&Jx[0], 0, 900U * sizeof(real_T));
  memset(&Jmv[0], 0, 600U * sizeof(real_T));
  memset(&b_z[0], 0, 30U * sizeof(real_T));
  ic[0] = 1;
  ic[1] = 2;
  ic[2] = 3;
  for (i = 0; i < 11; i++) {
    sizes_idx_1 = i << 1;
    Umv[sizes_idx_1] = U[i];
    Umv[sizes_idx_1 + 1] = U[i + 11];
  }
  for (i = 0; i < 11; i++) {
    b_X[3 * i] = X[i];
    b_X[3 * i + 1] = X[i + 11];
    b_X[3 * i + 2] = X[i + 22];
  }
  for (b_i = 0; b_i < 10; b_i++) {
    /*  State equations for parking:  */
    /*  state variables x, y and yaw angle theta. */
    /*  control variables v and steering angle delta. */
    /*  Copyright 2019 The MathWorks, Inc. */
    /*  */
    /*  Parameters */
    /*  Variables */
    /*  State equations */
    i = b_i << 1;
    d = Umv[i];
    d1 = Umv[i + 1];
    beta1 = 0.1 * d * muDoubleScalarCos(d1);
    fk_idx_1_tmp = 0.1 * d * muDoubleScalarSin(d1);
    /*  State equations for parking:  */
    /*  state variables x, y and yaw angle theta. */
    /*  control variables v and steering angle delta. */
    /*  Copyright 2019 The MathWorks, Inc. */
    /*  */
    /*  Parameters */
    /*  Variables */
    /*  Linearize the state equations at the current condition */
    /*  input , output */
    for (i = 0; i < 6; i++) {
      val[i] = 0.0;
    }
    /*  input , control */
    /*  A(1,3) = -v*sin(theta); %d(dxdt(1))dx(3) */
    cequ_idx_0 = muDoubleScalarCos(d);
    val[0] = 2.8 * cequ_idx_0;
    /* d(dxdt(1))du(1) */
    /*  A(2,3) = v*cos(theta); %d(dxdt(2))dx(3) */
    alpha1 = muDoubleScalarSin(d);
    val[1] = 2.8 * alpha1;
    /* d(dxdt(2))du(1) */
    val[3] = -2.8 * d1 * alpha1;
    /* d(dxdt(1))du(2) */
    val[4] = 2.8 * d1 * cequ_idx_0;
    /* d(dxdt(2))du(2) */
    /*  State equations for parking:  */
    /*  state variables x, y and yaw angle theta. */
    /*  control variables v and steering angle delta. */
    /*  Copyright 2019 The MathWorks, Inc. */
    /*  */
    /*  Parameters */
    /*  Variables */
    /*  State equations */
    sizes_idx_1 = 3 * (b_i + 1);
    b_z[ic[0] - 1] = (b_X[3 * b_i] + 0.05 * (beta1 + beta1)) - b_X[sizes_idx_1];
    b_z[ic[1] - 1] = (b_X[3 * b_i + 1] + 0.05 * (fk_idx_1_tmp + fk_idx_1_tmp)) -
                     b_X[sizes_idx_1 + 1];
    b_z[ic[2] - 1] = (b_X[3 * b_i + 2] + 0.1) - b_X[sizes_idx_1 + 2];
    if (b_i + 1 > 1) {
      input_sizes_idx_0 = 90 * (b_i - 1);
      for (k = 0; k < 3; k++) {
        Jx[((ic[0] + 30 * k) + input_sizes_idx_0) - 1] = 0.0;
        Jx[((ic[1] + 30 * k) + input_sizes_idx_0) - 1] = 0.0;
        Jx[((ic[2] + 30 * k) + input_sizes_idx_0) - 1] = 0.0;
        sizes_idx_1 = ((ic[k] + 30 * k) + input_sizes_idx_0) - 1;
        Jx[sizes_idx_1]++;
      }
    }
    for (k = 0; k < 3; k++) {
      Jx[((ic[0] + 30 * k) + 90 * b_i) - 1] = 0.0;
      Jx[((ic[1] + 30 * k) + 90 * b_i) - 1] = 0.0;
      Jx[((ic[2] + 30 * k) + 90 * b_i) - 1] = 0.0;
      input_sizes_idx_0 = ((ic[k] + 30 * k) + 90 * b_i) - 1;
      Jx[input_sizes_idx_0]--;
    }
    for (i = 0; i < 6; i++) {
      d = val[i];
      d = 0.05 * (d + d);
      val[i] = d;
    }
    for (k = 0; k < 2; k++) {
      Jmv[((ic[0] + 30 * k) + 60 * b_i) - 1] = val[3 * k];
      Jmv[((ic[1] + 30 * k) + 60 * b_i) - 1] = val[3 * k + 1];
      Jmv[((ic[2] + 30 * k) + 60 * b_i) - 1] = val[3 * k + 2];
    }
    ic[0] = (int8_T)(ic[0] + 3);
    ic[1] = (int8_T)(ic[1] + 3);
    ic[2] = (int8_T)(ic[2] + 3);
  }
  emxInit_real_T(&c, 2);
  emxInit_real_T(&Jc, 2);
  TRANSB1 = 'N';
  TRANSA1 = 'N';
  alpha1 = 1.0;
  beta1 = 0.0;
  m_t = (ptrdiff_t)30;
  n_t = (ptrdiff_t)20;
  k_t = (ptrdiff_t)20;
  lda_t = (ptrdiff_t)30;
  ldb_t = (ptrdiff_t)20;
  ldc_t = (ptrdiff_t)30;
  dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &Jmv[0], &lda_t, &dv[0],
        &ldb_t, &beta1, &y[0], &ldc_t);
  outputBounds(runtimedata_OutputMin, runtimedata_OutputMax, X, z[50], c, Jc);
  Jc_data = Jc->data;
  c_data = c->data;
  /*  Terminal constraints for parking. */
  /*  Copyright 2019 The MathWorks, Inc. */
  cequ_idx_0 = U[10];
  cequ_idx_1 = U[21];
  memset(&Ju[0], 0, 40U * sizeof(real_T));
  for (k = 0; k < 33; k++) {
    d = muDoubleScalarAbs(X[k]);
    b_X[k] = d;
    if (d < 1.0) {
      b_X[k] = 1.0;
    }
  }
  d = U[10];
  d1 = U[21];
  for (b_i = 0; b_i < 10; b_i++) {
    for (sizes_idx_1 = 0; sizes_idx_1 < 3; sizes_idx_1++) {
      alpha1 = 1.0E-6 * b_X[sizes_idx_1];
      /*  Terminal constraints for parking. */
      /*  Copyright 2019 The MathWorks, Inc. */
      input_sizes_idx_0 = (sizes_idx_1 << 1) + 6 * b_i;
      b_Jx[input_sizes_idx_0] = (d - d) / alpha1;
      b_Jx[input_sizes_idx_0 + 1] = (d1 - d1) / alpha1;
    }
  }
  for (k = 0; k < 22; k++) {
    d = muDoubleScalarAbs(U[k]);
    Umv[k] = d;
    if (d < 1.0) {
      Umv[k] = 1.0;
    }
  }
  d = Umv[0];
  d1 = Umv[1];
  for (b_i = 0; b_i < 9; b_i++) {
    alpha1 = 1.0E-6 * d;
    /*  Terminal constraints for parking. */
    /*  Copyright 2019 The MathWorks, Inc. */
    sizes_idx_1 = b_i << 2;
    beta1 = U[10] - cequ_idx_0;
    Ju[sizes_idx_1] = beta1 / alpha1;
    fk_idx_1_tmp = U[21] - cequ_idx_1;
    Ju[sizes_idx_1 + 1] = fk_idx_1_tmp / alpha1;
    U[b_i] = (U[b_i] + alpha1) - alpha1;
    alpha1 = 1.0E-6 * d1;
    /*  Terminal constraints for parking. */
    /*  Copyright 2019 The MathWorks, Inc. */
    Ju[sizes_idx_1 + 2] = beta1 / alpha1;
    Ju[sizes_idx_1 + 3] = fk_idx_1_tmp / alpha1;
    U[b_i + 11] = (U[b_i + 11] + alpha1) - alpha1;
  }
  alpha1 = 1.0E-6 * Umv[0];
  U[10] += alpha1;
  /*  Terminal constraints for parking. */
  /*  Copyright 2019 The MathWorks, Inc. */
  Ju[36] = (U[10] - cequ_idx_0) / alpha1;
  Ju[37] = (U[21] - cequ_idx_1) / alpha1;
  U[10] -= alpha1;
  alpha1 = 1.0E-6 * Umv[1];
  U[21] += alpha1;
  /*  Terminal constraints for parking. */
  /*  Copyright 2019 The MathWorks, Inc. */
  Ju[38] = (U[10] - cequ_idx_0) / alpha1;
  Ju[39] = (U[21] - cequ_idx_1) / alpha1;
  TRANSB1 = 'N';
  TRANSA1 = 'N';
  alpha1 = 1.0;
  beta1 = 0.0;
  m_t = (ptrdiff_t)2;
  n_t = (ptrdiff_t)20;
  k_t = (ptrdiff_t)20;
  lda_t = (ptrdiff_t)2;
  ldb_t = (ptrdiff_t)20;
  ldc_t = (ptrdiff_t)2;
  dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, &Ju[0], &lda_t, &dv[0],
        &ldb_t, &beta1, &b_y[0], &ldc_t);
  if ((c->size[0] != 0) && (c->size[1] != 0)) {
    sizes_idx_1 = c->size[1];
  } else {
    sizes_idx_1 = 0;
  }
  if ((sizes_idx_1 == 0) || ((c->size[0] != 0) && (c->size[1] != 0))) {
    input_sizes_idx_0 = c->size[0];
  } else {
    input_sizes_idx_0 = 0;
  }
  i = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = input_sizes_idx_0;
  varargout_1->size[1] = sizes_idx_1;
  emxEnsureCapacity_real_T(varargout_1, i);
  varargout_1_data = varargout_1->data;
  for (i = 0; i < sizes_idx_1; i++) {
    for (k = 0; k < input_sizes_idx_0; k++) {
      varargout_1_data[k + varargout_1->size[0] * i] =
          c_data[k + input_sizes_idx_0 * i];
    }
  }
  emxFree_real_T(&c);
  memcpy(&varargout_2[0], &b_z[0], 30U * sizeof(real_T));
  varargout_2[30] = cequ_idx_0;
  varargout_2[31] = cequ_idx_1;
  if ((Jc->size[0] != 0) && (Jc->size[1] != 0)) {
    sizes_idx_1 = Jc->size[0];
  } else {
    sizes_idx_1 = 0;
  }
  if ((sizes_idx_1 == 0) || ((Jc->size[0] != 0) && (Jc->size[1] != 0))) {
    input_sizes_idx_0 = Jc->size[1];
  } else {
    input_sizes_idx_0 = 0;
  }
  i = varargout_3->size[0] * varargout_3->size[1];
  varargout_3->size[0] = sizes_idx_1;
  varargout_3->size[1] = input_sizes_idx_0;
  emxEnsureCapacity_real_T(varargout_3, i);
  c_data = varargout_3->data;
  for (i = 0; i < input_sizes_idx_0; i++) {
    for (k = 0; k < sizes_idx_1; k++) {
      c_data[k + varargout_3->size[0] * i] = Jc_data[k + sizes_idx_1 * i];
    }
  }
  emxFree_real_T(&Jc);
  for (i = 0; i < 30; i++) {
    for (k = 0; k < 30; k++) {
      varargout_4[k + 51 * i] = Jx[i + 30 * k];
    }
    for (k = 0; k < 20; k++) {
      varargout_4[(k + 51 * i) + 30] = y[i + 30 * k];
    }
    varargout_4[51 * i + 50] = 0.0;
  }
  for (i = 0; i < 2; i++) {
    for (k = 0; k < 30; k++) {
      varargout_4[k + 51 * (i + 30)] = b_Jx[i + (k << 1)];
    }
    for (k = 0; k < 20; k++) {
      varargout_4[(k + 51 * (i + 30)) + 30] = b_y[i + (k << 1)];
    }
    varargout_4[51 * (i + 30) + 50] = 0.0;
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

void nlmpcmoveCodeGeneration(const real_T x[3], const real_T lastMV[2],
                             struct1_T *onlinedata, real_T mv[2],
                             struct2_T *info)
{
  static const real_T varargin_14[20] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
                                         0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 0.2,
                                         0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
  static const real_T varargin_26[20] = {0.0,
                                         0.0,
                                         0.0,
                                         0.0,
                                         0.0,
                                         0.0,
                                         0.0,
                                         0.0,
                                         0.0,
                                         0.0,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862,
                                         -6.2831853071795862};
  static const real_T varargin_28[20] = {1.0,
                                         1.0,
                                         1.0,
                                         1.0,
                                         1.0,
                                         1.0,
                                         1.0,
                                         1.0,
                                         1.0,
                                         1.0,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862,
                                         6.2831853071795862};
  static const int8_T varargin_10[30] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                         3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
  static const int8_T b_iv[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10};
  c_struct_T Out;
  emxArray_int8_T *ii;
  emxArray_real_T b_Auf;
  emxArray_real_T *Auf;
  emxArray_real_T *B;
  emxArray_real_T *b_initX;
  emxArray_real_T *initMV;
  emxArray_real_T *initX;
  emxArray_real_T *ref;
  emxArray_real_T *y;
  k_struct_T CostFcn_workspace_runtimedata;
  l_struct_T expl_temp;
  real_T Bu[80];
  real_T b_dv[51];
  real_T c_initX[51];
  real_T dv1[51];
  real_T z[51];
  real_T b_x[30];
  real_T Umv[22];
  real_T b_lastMV[20];
  real_T Bu_idx_1;
  real_T ic_idx_0;
  real_T ic_idx_1;
  real_T *initMV_data;
  real_T *initX_data;
  real_T *ref_data;
  real_T *y_data;
  int32_T b_ii[2];
  int32_T Au_tmp;
  int32_T b_i;
  int32_T i;
  int32_T idx;
  int32_T loop_ub;
  int32_T unnamed_idx_0;
  int8_T Au[1600];
  int8_T input_sizes_idx_1;
  int8_T *ii_data;
  boolean_T icf[80];
  boolean_T exitg1;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_real_T(&ref, 2);
  ref_data = ref->data;
  if (onlinedata->ref->size[0] == 0) {
    i = ref->size[0] * ref->size[1];
    ref->size[0] = 10;
    ref->size[1] = 3;
    emxEnsureCapacity_real_T(ref, i);
    ref_data = ref->data;
    for (i = 0; i < 30; i++) {
      ref_data[i] = 0.0;
    }
  } else if (onlinedata->ref->size[0] == 0) {
    ref->size[0] = 0;
    ref->size[1] = 0;
  } else if (onlinedata->ref->size[0] < 10) {
    unnamed_idx_0 = 10 - onlinedata->ref->size[0];
    i = ref->size[0] * ref->size[1];
    ref->size[0] = onlinedata->ref->size[0] + unnamed_idx_0;
    ref->size[1] = 3;
    emxEnsureCapacity_real_T(ref, i);
    ref_data = ref->data;
    loop_ub = onlinedata->ref->size[0];
    for (i = 0; i < 3; i++) {
      for (b_i = 0; b_i < loop_ub; b_i++) {
        ref_data[b_i + ref->size[0] * i] =
            onlinedata->ref->data[b_i + onlinedata->ref->size[0] * i];
      }
    }
    for (i = 0; i < 3; i++) {
      for (b_i = 0; b_i < unnamed_idx_0; b_i++) {
        ref_data[(b_i + onlinedata->ref->size[0]) + ref->size[0] * i] =
            onlinedata->ref->data[(onlinedata->ref->size[0] +
                                   onlinedata->ref->size[0] * i) -
                                  1];
      }
    }
  } else {
    i = ref->size[0] * ref->size[1];
    ref->size[0] = onlinedata->ref->size[0];
    ref->size[1] = 3;
    emxEnsureCapacity_real_T(ref, i);
    ref_data = ref->data;
    loop_ub = onlinedata->ref->size[0] * 3;
    for (i = 0; i < loop_ub; i++) {
      ref_data[i] = onlinedata->ref->data[i];
    }
  }
  emxInitStruct_struct_T4(&expl_temp);
  if (onlinedata->MVTarget->size[0] == 0) {
    i = expl_temp.MVTarget->size[0] * expl_temp.MVTarget->size[1];
    expl_temp.MVTarget->size[0] = 10;
    expl_temp.MVTarget->size[1] = 2;
    emxEnsureCapacity_real_T(expl_temp.MVTarget, i);
    for (i = 0; i < 20; i++) {
      expl_temp.MVTarget->data[i] = 0.0;
    }
  } else if (onlinedata->MVTarget->size[0] == 0) {
    expl_temp.MVTarget->size[0] = 0;
    expl_temp.MVTarget->size[1] = 0;
  } else if (onlinedata->MVTarget->size[0] < 10) {
    unnamed_idx_0 = 10 - onlinedata->MVTarget->size[0];
    i = expl_temp.MVTarget->size[0] * expl_temp.MVTarget->size[1];
    expl_temp.MVTarget->size[0] = onlinedata->MVTarget->size[0] + unnamed_idx_0;
    expl_temp.MVTarget->size[1] = 2;
    emxEnsureCapacity_real_T(expl_temp.MVTarget, i);
    loop_ub = onlinedata->MVTarget->size[0];
    for (i = 0; i < 2; i++) {
      for (b_i = 0; b_i < loop_ub; b_i++) {
        expl_temp.MVTarget->data[b_i + expl_temp.MVTarget->size[0] * i] =
            onlinedata->MVTarget->data[b_i + onlinedata->MVTarget->size[0] * i];
      }
    }
    for (i = 0; i < 2; i++) {
      for (b_i = 0; b_i < unnamed_idx_0; b_i++) {
        expl_temp.MVTarget->data[(b_i + onlinedata->MVTarget->size[0]) +
                                 expl_temp.MVTarget->size[0] * i] =
            onlinedata->MVTarget->data[(onlinedata->MVTarget->size[0] +
                                        onlinedata->MVTarget->size[0] * i) -
                                       1];
      }
    }
  } else {
    i = expl_temp.MVTarget->size[0] * expl_temp.MVTarget->size[1];
    expl_temp.MVTarget->size[0] = onlinedata->MVTarget->size[0];
    expl_temp.MVTarget->size[1] = 2;
    emxEnsureCapacity_real_T(expl_temp.MVTarget, i);
    loop_ub = onlinedata->MVTarget->size[0] * 2;
    for (i = 0; i < loop_ub; i++) {
      expl_temp.MVTarget->data[i] = onlinedata->MVTarget->data[i];
    }
  }
  emxInit_real_T(&initX, 2);
  initX_data = initX->data;
  if (onlinedata->X0->size[0] != 0) {
    if (onlinedata->X0->size[0] == 0) {
      initX->size[0] = 0;
      initX->size[1] = 0;
    } else if (onlinedata->X0->size[0] < 10) {
      unnamed_idx_0 = 10 - onlinedata->X0->size[0];
      i = initX->size[0] * initX->size[1];
      initX->size[0] = onlinedata->X0->size[0] + unnamed_idx_0;
      initX->size[1] = 3;
      emxEnsureCapacity_real_T(initX, i);
      initX_data = initX->data;
      loop_ub = onlinedata->X0->size[0];
      for (i = 0; i < 3; i++) {
        for (b_i = 0; b_i < loop_ub; b_i++) {
          initX_data[b_i + initX->size[0] * i] =
              onlinedata->X0->data[b_i + onlinedata->X0->size[0] * i];
        }
      }
      for (i = 0; i < 3; i++) {
        for (b_i = 0; b_i < unnamed_idx_0; b_i++) {
          initX_data[(b_i + onlinedata->X0->size[0]) + initX->size[0] * i] =
              onlinedata->X0->data[(onlinedata->X0->size[0] +
                                    onlinedata->X0->size[0] * i) -
                                   1];
        }
      }
    } else {
      i = initX->size[0] * initX->size[1];
      initX->size[0] = onlinedata->X0->size[0];
      initX->size[1] = 3;
      emxEnsureCapacity_real_T(initX, i);
      initX_data = initX->data;
      loop_ub = onlinedata->X0->size[0] * 3;
      for (i = 0; i < loop_ub; i++) {
        initX_data[i] = onlinedata->X0->data[i];
      }
    }
  } else {
    for (i = 0; i < 3; i++) {
      b_x[10 * i] = x[i];
      for (b_i = 0; b_i < 9; b_i++) {
        b_x[(b_i + 10 * i) + 1] = x[i];
      }
    }
    i = initX->size[0] * initX->size[1];
    initX->size[0] = 10;
    initX->size[1] = 3;
    emxEnsureCapacity_real_T(initX, i);
    initX_data = initX->data;
    for (i = 0; i < 30; i++) {
      initX_data[i] = b_x[i];
    }
  }
  emxInit_real_T(&initMV, 2);
  initMV_data = initMV->data;
  if (onlinedata->MV0->size[0] != 0) {
    if (onlinedata->MV0->size[0] == 0) {
      initMV->size[0] = 0;
      initMV->size[1] = 0;
    } else if (onlinedata->MV0->size[0] < 10) {
      unnamed_idx_0 = 10 - onlinedata->MV0->size[0];
      i = initMV->size[0] * initMV->size[1];
      initMV->size[0] = onlinedata->MV0->size[0] + unnamed_idx_0;
      initMV->size[1] = 2;
      emxEnsureCapacity_real_T(initMV, i);
      initMV_data = initMV->data;
      loop_ub = onlinedata->MV0->size[0];
      for (i = 0; i < 2; i++) {
        for (b_i = 0; b_i < loop_ub; b_i++) {
          initMV_data[b_i + initMV->size[0] * i] =
              onlinedata->MV0->data[b_i + onlinedata->MV0->size[0] * i];
        }
      }
      for (i = 0; i < 2; i++) {
        for (b_i = 0; b_i < unnamed_idx_0; b_i++) {
          initMV_data[(b_i + onlinedata->MV0->size[0]) + initMV->size[0] * i] =
              onlinedata->MV0->data[(onlinedata->MV0->size[0] +
                                     onlinedata->MV0->size[0] * i) -
                                    1];
        }
      }
    } else {
      i = initMV->size[0] * initMV->size[1];
      initMV->size[0] = onlinedata->MV0->size[0];
      initMV->size[1] = 2;
      emxEnsureCapacity_real_T(initMV, i);
      initMV_data = initMV->data;
      loop_ub = onlinedata->MV0->size[0] * 2;
      for (i = 0; i < loop_ub; i++) {
        initMV_data[i] = onlinedata->MV0->data[i];
      }
    }
  } else {
    for (i = 0; i < 2; i++) {
      b_lastMV[10 * i] = lastMV[i];
      for (b_i = 0; b_i < 9; b_i++) {
        b_lastMV[(b_i + 10 * i) + 1] = lastMV[i];
      }
    }
    i = initMV->size[0] * initMV->size[1];
    initMV->size[0] = 10;
    initMV->size[1] = 2;
    emxEnsureCapacity_real_T(initMV, i);
    initMV_data = initMV->data;
    for (i = 0; i < 20; i++) {
      initMV_data[i] = b_lastMV[i];
    }
  }
  i = expl_temp.References->size[0] * expl_temp.References->size[1];
  expl_temp.References->size[0] = ref->size[0];
  expl_temp.References->size[1] = ref->size[1];
  emxEnsureCapacity_real_T(expl_temp.References, i);
  loop_ub = ref->size[0] * ref->size[1];
  for (i = 0; i < loop_ub; i++) {
    expl_temp.References->data[i] = ref_data[i];
  }
  emxInitStruct_struct_T3(&CostFcn_workspace_runtimedata);
  expl_temp.MVIndex[0] = 1.0;
  expl_temp.MVIndex[1] = 2.0;
  CostFcn_workspace_runtimedata.x[0] = x[0];
  CostFcn_workspace_runtimedata.x[1] = x[1];
  CostFcn_workspace_runtimedata.x[2] = x[2];
  CostFcn_workspace_runtimedata.lastMV[0] = lastMV[0];
  CostFcn_workspace_runtimedata.lastMV[1] = lastMV[1];
  i = CostFcn_workspace_runtimedata.ref->size[0] *
      CostFcn_workspace_runtimedata.ref->size[1];
  CostFcn_workspace_runtimedata.ref->size[0] = ref->size[0];
  CostFcn_workspace_runtimedata.ref->size[1] = ref->size[1];
  emxEnsureCapacity_real_T(CostFcn_workspace_runtimedata.ref, i);
  loop_ub = ref->size[0] * ref->size[1];
  for (i = 0; i < loop_ub; i++) {
    CostFcn_workspace_runtimedata.ref->data[i] = ref_data[i];
  }
  for (i = 0; i < 30; i++) {
    CostFcn_workspace_runtimedata.OutputWeights[i] = varargin_10[i];
  }
  for (i = 0; i < 20; i++) {
    CostFcn_workspace_runtimedata.MVWeights[i] = 0.0;
    CostFcn_workspace_runtimedata.MVRateWeights[i] = varargin_14[i];
  }
  CostFcn_workspace_runtimedata.ECRWeight = 100000.0;
  for (i = 0; i < 30; i++) {
    CostFcn_workspace_runtimedata.OutputMin[i] = rtMinusInf;
    CostFcn_workspace_runtimedata.OutputMax[i] = rtInf;
    CostFcn_workspace_runtimedata.StateMin[i] = rtMinusInf;
    CostFcn_workspace_runtimedata.StateMax[i] = rtInf;
  }
  for (i = 0; i < 20; i++) {
    CostFcn_workspace_runtimedata.MVMin[i] = varargin_26[i];
    CostFcn_workspace_runtimedata.MVMax[i] = varargin_28[i];
    CostFcn_workspace_runtimedata.MVRateMin[i] = rtMinusInf;
    CostFcn_workspace_runtimedata.MVRateMax[i] = rtInf;
  }
  i = CostFcn_workspace_runtimedata.MVScaledTarget->size[0] *
      CostFcn_workspace_runtimedata.MVScaledTarget->size[1];
  CostFcn_workspace_runtimedata.MVScaledTarget->size[0] =
      expl_temp.MVTarget->size[0];
  CostFcn_workspace_runtimedata.MVScaledTarget->size[1] =
      expl_temp.MVTarget->size[1];
  emxEnsureCapacity_real_T(CostFcn_workspace_runtimedata.MVScaledTarget, i);
  loop_ub = expl_temp.MVTarget->size[0] * expl_temp.MVTarget->size[1];
  for (i = 0; i < loop_ub; i++) {
    CostFcn_workspace_runtimedata.MVScaledTarget->data[i] =
        expl_temp.MVTarget->data[i];
  }
  memset(&Au[0], 0, 1600U * sizeof(int8_T));
  memset(&Bu[0], 0, 80U * sizeof(real_T));
  memset(&icf[0], 0, 80U * sizeof(boolean_T));
  ic_idx_0 = 1.0;
  ic_idx_1 = 2.0;
  for (b_i = 0; b_i < 10; b_i++) {
    icf[(int32_T)ic_idx_0 - 1] = false;
    icf[(int32_T)ic_idx_1 - 1] = false;
    icf[(int32_T)(ic_idx_0 + 2.0) - 1] = false;
    icf[(int32_T)(ic_idx_1 + 2.0) - 1] = false;
    icf[(int32_T)(ic_idx_0 + 4.0) - 1] = true;
    icf[(int32_T)(ic_idx_1 + 4.0) - 1] = true;
    icf[(int32_T)(ic_idx_0 + 6.0) - 1] = true;
    unnamed_idx_0 = (int32_T)ic_idx_0 + 160 * b_i;
    Au[unnamed_idx_0 - 1] = -1;
    idx = (int32_T)ic_idx_1 + 160 * b_i;
    Au[idx - 1] = 0;
    icf[(int32_T)(ic_idx_1 + 6.0) - 1] = true;
    Au[unnamed_idx_0 + 79] = 0;
    Au[idx + 79] = -1;
    unnamed_idx_0 = (int32_T)(ic_idx_0 + 2.0) + 160 * b_i;
    Au[unnamed_idx_0 - 1] = 1;
    idx = (int32_T)(ic_idx_1 + 2.0) + 160 * b_i;
    Au[idx - 1] = 0;
    Au[unnamed_idx_0 + 79] = 0;
    Au[idx + 79] = 1;
    unnamed_idx_0 = (int32_T)(ic_idx_0 + 4.0) + 160 * b_i;
    Au[unnamed_idx_0 - 1] = -1;
    idx = (int32_T)(ic_idx_1 + 4.0) + 160 * b_i;
    Au[idx - 1] = 0;
    Au[unnamed_idx_0 + 79] = 0;
    Au[idx + 79] = -1;
    unnamed_idx_0 = (int32_T)(ic_idx_0 + 6.0) + 160 * b_i;
    Au[unnamed_idx_0 - 1] = 1;
    idx = (int32_T)(ic_idx_1 + 6.0) + 160 * b_i;
    Au[idx - 1] = 0;
    Au[unnamed_idx_0 + 79] = 0;
    Au[idx + 79] = 1;
    Bu[(int32_T)ic_idx_0 - 1] = rtInf;
    Bu[(int32_T)ic_idx_1 - 1] = rtInf;
    Bu[(int32_T)(ic_idx_0 + 2.0) - 1] = rtInf;
    Bu[(int32_T)(ic_idx_1 + 2.0) - 1] = rtInf;
    Bu[(int32_T)(ic_idx_0 + 4.0) - 1] = -varargin_26[b_i];
    Bu[(int32_T)(ic_idx_1 + 4.0) - 1] = -varargin_26[b_i + 10];
    Bu[(int32_T)(ic_idx_0 + 6.0) - 1] = varargin_28[b_i];
    Bu[(int32_T)(ic_idx_1 + 6.0) - 1] = varargin_28[b_i + 10];
    if (b_i + 1 == 1) {
      Bu_idx_1 = Bu[(int32_T)ic_idx_1 - 1] - lastMV[1];
      Bu[(int32_T)ic_idx_0 - 1] -= lastMV[0];
      Bu[(int32_T)ic_idx_1 - 1] = Bu_idx_1;
      Bu_idx_1 = Bu[(int32_T)(ic_idx_1 + 2.0) - 1] + lastMV[1];
      Bu[(int32_T)(ic_idx_0 + 2.0) - 1] += lastMV[0];
      Bu[(int32_T)(ic_idx_1 + 2.0) - 1] = Bu_idx_1;
    } else {
      unnamed_idx_0 = 160 * (b_i - 1);
      idx = (int32_T)ic_idx_0 + unnamed_idx_0;
      Au[idx - 1] = 1;
      Au_tmp = (int32_T)ic_idx_1 + unnamed_idx_0;
      Au[Au_tmp - 1] = 0;
      Au[idx + 79] = 0;
      Au[Au_tmp + 79] = 1;
      idx = (int32_T)(ic_idx_0 + 2.0) + unnamed_idx_0;
      Au[idx - 1] = -1;
      unnamed_idx_0 += (int32_T)(ic_idx_1 + 2.0);
      Au[unnamed_idx_0 - 1] = 0;
      Au[idx + 79] = 0;
      Au[unnamed_idx_0 + 79] = -1;
    }
    ic_idx_0 += 8.0;
    ic_idx_1 += 8.0;
  }
  emxInit_int8_T(&ii, 1);
  idx = 0;
  i = ii->size[0];
  ii->size[0] = 80;
  emxEnsureCapacity_int8_T(ii, i);
  ii_data = ii->data;
  unnamed_idx_0 = 0;
  exitg1 = false;
  while ((!exitg1) && (unnamed_idx_0 < 80)) {
    if (icf[unnamed_idx_0]) {
      idx++;
      ii_data[idx - 1] = (int8_T)(unnamed_idx_0 + 1);
      if (idx >= 80) {
        exitg1 = true;
      } else {
        unnamed_idx_0++;
      }
    } else {
      unnamed_idx_0++;
    }
  }
  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }
  i = ii->size[0];
  if (1 > idx) {
    ii->size[0] = 0;
  } else {
    ii->size[0] = idx;
  }
  emxEnsureCapacity_int8_T(ii, i);
  ii_data = ii->data;
  emxInit_real_T(&B, 1);
  if (loop_ub > 0) {
    i = B->size[0];
    B->size[0] = loop_ub;
    emxEnsureCapacity_real_T(B, i);
    ref_data = B->data;
    for (i = 0; i < loop_ub; i++) {
      ref_data[i] = Bu[ii_data[i] - 1];
    }
    emxInit_real_T(&Auf, 3);
    i = Auf->size[0] * Auf->size[1] * Auf->size[2];
    Auf->size[0] = loop_ub;
    Auf->size[1] = 2;
    Auf->size[2] = 10;
    emxEnsureCapacity_real_T(Auf, i);
    ref_data = Auf->data;
    for (unnamed_idx_0 = 0; unnamed_idx_0 < 2; unnamed_idx_0++) {
      for (Au_tmp = 0; Au_tmp < 10; Au_tmp++) {
        for (b_i = 0; b_i < loop_ub; b_i++) {
          ref_data[(b_i + Auf->size[0] * unnamed_idx_0) +
                   Auf->size[0] * 2 * Au_tmp] =
              Au[((ii_data[b_i] + 80 * unnamed_idx_0) + 160 * Au_tmp) - 1];
        }
      }
    }
    emxInit_real_T(&y, 2);
    b_Auf = *Auf;
    b_ii[0] = loop_ub;
    b_ii[1] = 20;
    b_Auf.size = &b_ii[0];
    b_Auf.numDimensions = 2;
    mtimes(&b_Auf, y);
    y_data = y->data;
    if (y->size[0] != 0) {
      input_sizes_idx_1 = 20;
    } else {
      input_sizes_idx_1 = 0;
    }
    unnamed_idx_0 = ii->size[0];
    if (y->size[0] != 0) {
      Au_tmp = 20;
    } else {
      Au_tmp = 0;
    }
    i = ref->size[0] * ref->size[1];
    ref->size[0] = loop_ub;
    ref->size[1] = input_sizes_idx_1 + 31;
    emxEnsureCapacity_real_T(ref, i);
    ref_data = ref->data;
    emxFree_real_T(&Auf);
    for (i = 0; i < 30; i++) {
      for (b_i = 0; b_i < loop_ub; b_i++) {
        ref_data[b_i + ref->size[0] * i] = 0.0;
      }
    }
    idx = input_sizes_idx_1;
    for (i = 0; i < idx; i++) {
      for (b_i = 0; b_i < loop_ub; b_i++) {
        ref_data[b_i + ref->size[0] * (i + 30)] =
            y_data[b_i + unnamed_idx_0 * i];
      }
    }
    emxFree_real_T(&y);
    for (i = 0; i < loop_ub; i++) {
      ref_data[i + ref->size[0] * (Au_tmp + 30)] = 0.0;
    }
  } else {
    B->size[0] = 0;
    ref->size[0] = 0;
    ref->size[1] = 51;
  }
  emxFree_int8_T(&ii);
  emxInit_real_T(&b_initX, 2);
  expl_temp.NumOfInputs = 2.0;
  expl_temp.NumOfOutputs = 3.0;
  expl_temp.NumOfStates = 3.0;
  expl_temp.PredictionHorizon = 10.0;
  expl_temp.LastMV[0] = lastMV[0];
  expl_temp.LastMV[1] = lastMV[1];
  expl_temp.CurrentStates[0] = x[0];
  expl_temp.CurrentStates[1] = x[1];
  expl_temp.CurrentStates[2] = x[2];
  expl_temp.Ts = 0.1;
  i = b_initX->size[0] * b_initX->size[1];
  b_initX->size[0] = initX->size[1];
  b_initX->size[1] = initX->size[0];
  emxEnsureCapacity_real_T(b_initX, i);
  ref_data = b_initX->data;
  loop_ub = initX->size[0];
  for (i = 0; i < loop_ub; i++) {
    idx = initX->size[1];
    for (b_i = 0; b_i < idx; b_i++) {
      ref_data[b_i + b_initX->size[0] * i] =
          initX_data[i + initX->size[0] * b_i];
    }
  }
  i = initX->size[0] * initX->size[1];
  initX->size[0] = initMV->size[1];
  initX->size[1] = initMV->size[0];
  emxEnsureCapacity_real_T(initX, i);
  initX_data = initX->data;
  loop_ub = initMV->size[0];
  for (i = 0; i < loop_ub; i++) {
    idx = initMV->size[1];
    for (b_i = 0; b_i < idx; b_i++) {
      initX_data[b_i + initX->size[0] * i] =
          initMV_data[i + initMV->size[0] * b_i];
    }
  }
  emxFree_real_T(&initMV);
  for (i = 0; i < 20; i++) {
    ic_idx_0 = 0.0;
    for (b_i = 0; b_i < 20; b_i++) {
      ic_idx_0 += (real_T)iv[i + 20 * b_i] * initX_data[b_i];
    }
    b_lastMV[i] = ic_idx_0;
  }
  emxFree_real_T(&initX);
  for (i = 0; i < 30; i++) {
    c_initX[i] = ref_data[i];
  }
  emxFree_real_T(&b_initX);
  memcpy(&c_initX[30], &b_lastMV[0], 20U * sizeof(real_T));
  c_initX[50] = onlinedata->Slack0;
  for (i = 0; i < 30; i++) {
    b_dv[i] = rtMinusInf;
  }
  for (i = 0; i < 20; i++) {
    b_dv[i + 30] = rtMinusInf;
  }
  b_dv[50] = 0.0;
  for (i = 0; i < 30; i++) {
    dv1[i] = rtInf;
  }
  for (i = 0; i < 20; i++) {
    dv1[i + 30] = rtInf;
  }
  dv1[50] = rtInf;
  fmincon(&CostFcn_workspace_runtimedata, x, lastMV, expl_temp.References,
          expl_temp.MVTarget, expl_temp.MVIndex, c_initX, ref, B, b_dv, dv1,
          &CostFcn_workspace_runtimedata, &expl_temp, z, &info->Cost, &ic_idx_1,
          &Out);
  emxFreeStruct_struct_T3(&expl_temp);
  emxFree_real_T(&ref);
  emxFreeStruct_struct_T1(&CostFcn_workspace_runtimedata);
  emxFree_real_T(&B);
  if ((ic_idx_1 == 0.0) && (Out.constrviolation > 1.0E-6)) {
    ic_idx_1 = -2.0;
  }
  memset(&info->Xopt[0], 0, 33U * sizeof(real_T));
  memset(&info->MVopt[0], 0, 22U * sizeof(real_T));
  memset(&Umv[0], 0, 22U * sizeof(real_T));
  for (i = 0; i < 20; i++) {
    ic_idx_0 = 0.0;
    for (b_i = 0; b_i < 20; b_i++) {
      ic_idx_0 += (real_T)iv[i + 20 * b_i] * z[b_i + 30];
    }
    b_lastMV[i] = ic_idx_0;
  }
  for (i = 0; i < 2; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      Umv[b_i + 11 * i] = b_lastMV[i + (b_i << 1)];
    }
  }
  memcpy(&b_x[0], &z[0], 30U * sizeof(real_T));
  for (i = 0; i < 3; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      info->Xopt[(b_i + 11 * i) + 1] = b_x[i + 3 * b_i];
    }
    info->Xopt[11 * i] = x[i];
  }
  for (b_i = 0; b_i < 2; b_i++) {
    Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
    memcpy(&info->MVopt[b_i * 11], &Umv[b_i * 11], 11U * sizeof(real_T));
  }
  if (ic_idx_1 > 0.0) {
    mv[0] = info->MVopt[0];
    mv[1] = info->MVopt[11];
  } else {
    mv[0] = lastMV[0];
    mv[1] = lastMV[1];
  }
  info->ExitFlag = ic_idx_1;
  info->Iterations = Out.iterations;
  onlinedata->Slack0 = muDoubleScalarMax(0.0, z[50]);
  memcpy(&info->Yopt[0], &info->Xopt[0], 33U * sizeof(real_T));
  for (i = 0; i < 11; i++) {
    info->Topt[i] = 0.1 * (real_T)i;
  }
  info->Slack = z[50];
  i = onlinedata->X0->size[0] * onlinedata->X0->size[1];
  onlinedata->X0->size[0] = 10;
  onlinedata->X0->size[1] = 3;
  emxEnsureCapacity_real_T(onlinedata->X0, i);
  for (i = 0; i < 3; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      onlinedata->X0->data[b_i + onlinedata->X0->size[0] * i] =
          info->Xopt[b_iv[b_i] + 11 * i];
    }
  }
  i = onlinedata->MV0->size[0] * onlinedata->MV0->size[1];
  onlinedata->MV0->size[0] = 10;
  onlinedata->MV0->size[1] = 2;
  emxEnsureCapacity_real_T(onlinedata->MV0, i);
  for (i = 0; i < 2; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      onlinedata->MV0->data[b_i + onlinedata->MV0->size[0] * i] =
          info->MVopt[(b_i + 11 * i) + 1];
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (nlmpcmoveCodeGeneration.c) */
