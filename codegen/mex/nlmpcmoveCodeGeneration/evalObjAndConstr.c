/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * evalObjAndConstr.c
 *
 * Code generation for function 'evalObjAndConstr'
 *
 */

/* Include files */
#include "evalObjAndConstr.h"
#include "all.h"
#include "checkVectorNonFinite.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
void evalObjAndConstr(const real_T c_obj_objfun_workspace_runtimed[3],
                      const real_T d_obj_objfun_workspace_runtimed[2],
                      const emxArray_real_T *e_obj_objfun_workspace_runtimed,
                      const real_T f_obj_objfun_workspace_runtimed[30],
                      const real_T g_obj_objfun_workspace_runtimed[20],
                      const real_T h_obj_objfun_workspace_runtimed[20],
                      real_T i_obj_objfun_workspace_runtimed,
                      const emxArray_real_T *j_obj_objfun_workspace_runtimed,
                      const real_T c_obj_nonlcon_workspace_runtime[3],
                      const real_T d_obj_nonlcon_workspace_runtime[30],
                      const real_T e_obj_nonlcon_workspace_runtime[30],
                      int32_T obj_mCineq, int32_T obj_mCeq,
                      boolean_T obj_ScaleProblem, const real_T x[51],
                      emxArray_real_T *Cineq_workspace, int32_T ineq0,
                      real_T Ceq_workspace[32], int32_T eq0,
                      const emxArray_real_T *scales_cineq_constraint,
                      const real_T scales_ceq_constraint[32], real_T *fval,
                      int32_T *status)
{
  emxArray_int32_T *r1;
  emxArray_int8_T *r;
  emxArray_real_T *c;
  emxArray_real_T *c_c;
  emxArray_real_T *urk;
  real_T b_c[60];
  real_T X[33];
  real_T b_X[33];
  real_T ceq[32];
  real_T b_x[30];
  real_T U[22];
  real_T Umv[22];
  real_T a[20];
  const real_T *k_obj_objfun_workspace_runtimed;
  const real_T *l_obj_objfun_workspace_runtimed;
  const real_T *scales_cineq_constraint_data;
  real_T d;
  real_T duk_idx_0;
  real_T duk_idx_1;
  real_T e;
  real_T fs;
  real_T umvk;
  real_T umvk_idx_0;
  real_T umvk_idx_1;
  real_T wtYerr_idx_0;
  real_T wtYerr_idx_1;
  real_T wtYerr_idx_2;
  real_T *Cineq_workspace_data;
  real_T *c_data;
  real_T *urk_data;
  int32_T wtYerr[6];
  int32_T b_i;
  int32_T eqEnd;
  int32_T i;
  int32_T ineqEnd;
  int32_T input_sizes_idx_0;
  int32_T loop_ub;
  int32_T *r3;
  int8_T sizes_idx_1;
  int8_T *r2;
  boolean_T icf[60];
  boolean_T bv[30];
  boolean_T c_x[3];
  boolean_T exitg1;
  boolean_T guard1 = false;
  boolean_T y;
  scales_cineq_constraint_data = scales_cineq_constraint->data;
  Cineq_workspace_data = Cineq_workspace->data;
  k_obj_objfun_workspace_runtimed = j_obj_objfun_workspace_runtimed->data;
  l_obj_objfun_workspace_runtimed = e_obj_objfun_workspace_runtimed->data;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  memset(&X[0], 0, 33U * sizeof(real_T));
  memset(&Umv[0], 0, 22U * sizeof(real_T));
  for (i = 0; i < 20; i++) {
    d = 0.0;
    for (b_i = 0; b_i < 20; b_i++) {
      d += (real_T)iv[i + 20 * b_i] * x[b_i + 30];
    }
    a[i] = d;
  }
  for (i = 0; i < 2; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      Umv[b_i + 11 * i] = a[i + (b_i << 1)];
    }
  }
  memcpy(&b_x[0], &x[0], 30U * sizeof(real_T));
  for (i = 0; i < 3; i++) {
    for (b_i = 0; b_i < 10; b_i++) {
      X[(b_i + 11 * i) + 1] = b_x[i + 3 * b_i];
    }
    X[11 * i] = c_obj_objfun_workspace_runtimed[i];
  }
  for (b_i = 0; b_i < 2; b_i++) {
    Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
    memcpy(&U[b_i * 11], &Umv[b_i * 11], 11U * sizeof(real_T));
  }
  fs = 0.0;
  for (i = 0; i < 11; i++) {
    b_X[3 * i] = X[i];
    b_X[3 * i + 1] = X[i + 11];
    b_X[3 * i + 2] = X[i + 22];
    input_sizes_idx_0 = i << 1;
    Umv[input_sizes_idx_0] = U[i];
    Umv[input_sizes_idx_0 + 1] = U[i + 11];
  }
  loop_ub = e_obj_objfun_workspace_runtimed->size[1];
  emxInit_real_T(&urk, 1);
  for (b_i = 0; b_i < 10; b_i++) {
    i = urk->size[0];
    urk->size[0] = loop_ub;
    emxEnsureCapacity_real_T(urk, i);
    urk_data = urk->data;
    for (i = 0; i < loop_ub; i++) {
      urk_data[i] = l_obj_objfun_workspace_runtimed
          [b_i + e_obj_objfun_workspace_runtimed->size[0] * i];
    }
    i = 3 * (b_i + 1);
    d = f_obj_objfun_workspace_runtimed[b_i] * (b_X[i] - urk_data[0]);
    umvk_idx_0 = d * d;
    d = f_obj_objfun_workspace_runtimed[b_i + 10] * (b_X[i + 1] - urk_data[1]);
    umvk_idx_0 += d * d;
    d = f_obj_objfun_workspace_runtimed[b_i + 20] * (b_X[i + 2] - urk_data[2]);
    umvk_idx_0 += d * d;
    fs += umvk_idx_0;
    input_sizes_idx_0 = b_i << 1;
    umvk_idx_0 = Umv[input_sizes_idx_0];
    umvk_idx_1 = Umv[input_sizes_idx_0 + 1];
    if (b_i + 1 == 1) {
      duk_idx_0 = umvk_idx_0 - d_obj_objfun_workspace_runtimed[0];
      duk_idx_1 = umvk_idx_1 - d_obj_objfun_workspace_runtimed[1];
    } else {
      input_sizes_idx_0 = (b_i - 1) << 1;
      duk_idx_0 = umvk_idx_0 - Umv[input_sizes_idx_0];
      duk_idx_1 = umvk_idx_1 - Umv[input_sizes_idx_0 + 1];
    }
    input_sizes_idx_0 = j_obj_objfun_workspace_runtimed->size[1];
    if ((j_obj_objfun_workspace_runtimed->size[0] == 0) ||
        (j_obj_objfun_workspace_runtimed->size[1] == 0)) {
      i = urk->size[0];
      urk->size[0] = 2;
      emxEnsureCapacity_real_T(urk, i);
      urk_data = urk->data;
      urk_data[0] = 0.0;
      urk_data[1] = 0.0;
    } else {
      i = urk->size[0];
      urk->size[0] = j_obj_objfun_workspace_runtimed->size[1];
      emxEnsureCapacity_real_T(urk, i);
      urk_data = urk->data;
      for (i = 0; i < input_sizes_idx_0; i++) {
        urk_data[i] = k_obj_objfun_workspace_runtimed
            [b_i + j_obj_objfun_workspace_runtimed->size[0] * i];
      }
    }
    d = g_obj_objfun_workspace_runtimed[b_i] * (umvk_idx_0 - urk_data[0]);
    umvk = d * d;
    d = h_obj_objfun_workspace_runtimed[b_i] * duk_idx_0;
    umvk_idx_0 = d * d;
    d = g_obj_objfun_workspace_runtimed[b_i + 10] * (umvk_idx_1 - urk_data[1]);
    umvk += d * d;
    d = h_obj_objfun_workspace_runtimed[b_i + 10] * duk_idx_1;
    umvk_idx_0 += d * d;
    fs += umvk;
    fs += umvk_idx_0;
  }
  *fval = fs + i_obj_objfun_workspace_runtimed * x[50] * x[50];
  *status = 1;
  if (muDoubleScalarIsInf(*fval) || muDoubleScalarIsNaN(*fval)) {
    if (muDoubleScalarIsNaN(*fval)) {
      *status = -3;
    } else if (*fval < 0.0) {
      *status = -1;
    } else {
      *status = -2;
    }
  }
  if (*status == 1) {
    ineqEnd = (ineq0 + obj_mCineq) - 1;
    eqEnd = (eq0 + obj_mCeq) - 1;
    memset(&X[0], 0, 33U * sizeof(real_T));
    memset(&Umv[0], 0, 22U * sizeof(real_T));
    for (i = 0; i < 20; i++) {
      d = 0.0;
      for (b_i = 0; b_i < 20; b_i++) {
        d += (real_T)iv[i + 20 * b_i] * x[b_i + 30];
      }
      a[i] = d;
    }
    for (i = 0; i < 2; i++) {
      for (b_i = 0; b_i < 10; b_i++) {
        Umv[b_i + 11 * i] = a[i + (b_i << 1)];
      }
    }
    e = x[50];
    memcpy(&b_x[0], &x[0], 30U * sizeof(real_T));
    for (i = 0; i < 3; i++) {
      for (b_i = 0; b_i < 10; b_i++) {
        X[(b_i + 11 * i) + 1] = b_x[i + 3 * b_i];
      }
      X[11 * i] = c_obj_nonlcon_workspace_runtime[i];
    }
    for (b_i = 0; b_i < 2; b_i++) {
      Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
      memcpy(&U[b_i * 11], &Umv[b_i * 11], 11U * sizeof(real_T));
    }
    memset(&b_x[0], 0, 30U * sizeof(real_T));
    wtYerr_idx_0 = 1.0;
    wtYerr_idx_1 = 2.0;
    wtYerr_idx_2 = 3.0;
    for (i = 0; i < 11; i++) {
      input_sizes_idx_0 = i << 1;
      Umv[input_sizes_idx_0] = U[i];
      Umv[input_sizes_idx_0 + 1] = U[i + 11];
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
      umvk_idx_0 = Umv[i + 1];
      duk_idx_0 = 0.1 * d * muDoubleScalarCos(umvk_idx_0);
      umvk_idx_0 = 0.1 * d * muDoubleScalarSin(umvk_idx_0);
      /*  State equations for parking:  */
      /*  state variables x, y and yaw angle theta. */
      /*  control variables v and steering angle delta. */
      /*  Copyright 2019 The MathWorks, Inc. */
      /*  */
      /*  Parameters */
      /*  Variables */
      /*  State equations */
      input_sizes_idx_0 = 3 * (b_i + 1);
      b_x[(int32_T)wtYerr_idx_0 - 1] =
          (b_X[3 * b_i] + 0.05 * (duk_idx_0 + duk_idx_0)) -
          b_X[input_sizes_idx_0];
      b_x[(int32_T)wtYerr_idx_1 - 1] =
          (b_X[3 * b_i + 1] + 0.05 * (umvk_idx_0 + umvk_idx_0)) -
          b_X[input_sizes_idx_0 + 1];
      b_x[(int32_T)wtYerr_idx_2 - 1] =
          (b_X[3 * b_i + 2] + 0.1) - b_X[input_sizes_idx_0 + 2];
      wtYerr_idx_0 += 3.0;
      wtYerr_idx_1 += 3.0;
      wtYerr_idx_2 += 3.0;
    }
    for (i = 0; i < 30; i++) {
      bv[i] = muDoubleScalarIsInf(d_obj_nonlcon_workspace_runtime[i]);
    }
    all(bv, c_x);
    y = true;
    input_sizes_idx_0 = 0;
    exitg1 = false;
    while ((!exitg1) && (input_sizes_idx_0 <= 2)) {
      if (!c_x[input_sizes_idx_0]) {
        y = false;
        exitg1 = true;
      } else {
        input_sizes_idx_0++;
      }
    }
    emxInit_real_T(&c, 2);
    c_data = c->data;
    emxInit_int8_T(&r, 1);
    guard1 = false;
    if (y) {
      for (i = 0; i < 30; i++) {
        bv[i] = muDoubleScalarIsInf(e_obj_nonlcon_workspace_runtime[i]);
      }
      all(bv, c_x);
      y = true;
      input_sizes_idx_0 = 0;
      exitg1 = false;
      while ((!exitg1) && (input_sizes_idx_0 <= 2)) {
        if (!c_x[input_sizes_idx_0]) {
          y = false;
          exitg1 = true;
        } else {
          input_sizes_idx_0++;
        }
      }
      if (y) {
        c->size[0] = 0;
        c->size[1] = 0;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      for (b_i = 0; b_i < 60; b_i++) {
        b_c[b_i] = 0.0;
        icf[b_i] = true;
      }
      wtYerr_idx_0 = 1.0;
      wtYerr_idx_1 = 2.0;
      wtYerr_idx_2 = 3.0;
      for (b_i = 0; b_i < 10; b_i++) {
        d = d_obj_nonlcon_workspace_runtime[b_i];
        icf[(int32_T)wtYerr_idx_0 - 1] =
            ((!muDoubleScalarIsInf(d)) && (!muDoubleScalarIsNaN(d)));
        d = e_obj_nonlcon_workspace_runtime[b_i];
        umvk_idx_0 = d_obj_nonlcon_workspace_runtime[b_i + 10];
        icf[(int32_T)wtYerr_idx_1 - 1] = ((!muDoubleScalarIsInf(umvk_idx_0)) &&
                                          (!muDoubleScalarIsNaN(umvk_idx_0)));
        umvk_idx_1 = e_obj_nonlcon_workspace_runtime[b_i + 10];
        duk_idx_1 = d_obj_nonlcon_workspace_runtime[b_i + 20];
        icf[(int32_T)wtYerr_idx_2 - 1] = ((!muDoubleScalarIsInf(duk_idx_1)) &&
                                          (!muDoubleScalarIsNaN(duk_idx_1)));
        fs = e_obj_nonlcon_workspace_runtime[b_i + 20];
        icf[(int32_T)(wtYerr_idx_0 + 3.0) - 1] =
            ((!muDoubleScalarIsInf(d)) && (!muDoubleScalarIsNaN(d)));
        icf[(int32_T)(wtYerr_idx_1 + 3.0) - 1] =
            ((!muDoubleScalarIsInf(umvk_idx_1)) &&
             (!muDoubleScalarIsNaN(umvk_idx_1)));
        icf[(int32_T)(wtYerr_idx_2 + 3.0) - 1] =
            ((!muDoubleScalarIsInf(fs)) && (!muDoubleScalarIsNaN(fs)));
        y = false;
        input_sizes_idx_0 = 0;
        exitg1 = false;
        while ((!exitg1) && (input_sizes_idx_0 <= 5)) {
          wtYerr[0] = (int32_T)wtYerr_idx_0 - 1;
          wtYerr[3] = (int32_T)(wtYerr_idx_0 + 3.0) - 1;
          wtYerr[1] = (int32_T)wtYerr_idx_1 - 1;
          wtYerr[4] = (int32_T)(wtYerr_idx_1 + 3.0) - 1;
          wtYerr[2] = (int32_T)wtYerr_idx_2 - 1;
          wtYerr[5] = (int32_T)(wtYerr_idx_2 + 3.0) - 1;
          if (icf[wtYerr[input_sizes_idx_0]]) {
            y = true;
            exitg1 = true;
          } else {
            input_sizes_idx_0++;
          }
        }
        if (y) {
          duk_idx_0 = X[b_i + 1];
          b_c[(int32_T)wtYerr_idx_0 - 1] =
              (d_obj_nonlcon_workspace_runtime[b_i] - e) - duk_idx_0;
          umvk = X[b_i + 12];
          b_c[(int32_T)wtYerr_idx_1 - 1] = (umvk_idx_0 - e) - umvk;
          umvk_idx_0 = X[b_i + 23];
          b_c[(int32_T)wtYerr_idx_2 - 1] = (duk_idx_1 - e) - umvk_idx_0;
          b_c[(int32_T)(wtYerr_idx_0 + 3.0) - 1] =
              (duk_idx_0 - e_obj_nonlcon_workspace_runtime[b_i]) - e;
          b_c[(int32_T)(wtYerr_idx_1 + 3.0) - 1] = (umvk - umvk_idx_1) - e;
          b_c[(int32_T)(wtYerr_idx_2 + 3.0) - 1] = (umvk_idx_0 - fs) - e;
        }
        wtYerr_idx_0 += 6.0;
        wtYerr_idx_1 += 6.0;
        wtYerr_idx_2 += 6.0;
      }
      input_sizes_idx_0 = 0;
      for (b_i = 0; b_i < 60; b_i++) {
        if (icf[b_i]) {
          input_sizes_idx_0++;
        }
      }
      i = r->size[0];
      r->size[0] = input_sizes_idx_0;
      emxEnsureCapacity_int8_T(r, i);
      r2 = r->data;
      input_sizes_idx_0 = 0;
      for (b_i = 0; b_i < 60; b_i++) {
        if (icf[b_i]) {
          r2[input_sizes_idx_0] = (int8_T)(b_i + 1);
          input_sizes_idx_0++;
        }
      }
      i = urk->size[0];
      urk->size[0] = r->size[0];
      emxEnsureCapacity_real_T(urk, i);
      urk_data = urk->data;
      loop_ub = r->size[0];
      for (i = 0; i < loop_ub; i++) {
        urk_data[i] = b_c[r2[i] - 1];
      }
      i = c->size[0] * c->size[1];
      c->size[0] = r->size[0];
      c->size[1] = 1;
      emxEnsureCapacity_real_T(c, i);
      c_data = c->data;
      loop_ub = r->size[0];
      for (i = 0; i < loop_ub; i++) {
        c_data[i] = urk_data[i];
      }
    }
    emxFree_int8_T(&r);
    /*  Terminal constraints for parking. */
    /*  Copyright 2019 The MathWorks, Inc. */
    sizes_idx_1 = (int8_T)((c->size[0] != 0) && (c->size[1] != 0));
    if ((sizes_idx_1 == 0) || ((c->size[0] != 0) && (c->size[1] != 0))) {
      input_sizes_idx_0 = c->size[0];
    } else {
      input_sizes_idx_0 = 0;
    }
    if (ineq0 > ineqEnd) {
      i = 0;
      ineqEnd = 0;
    } else {
      i = ineq0 - 1;
    }
    emxInit_int32_T(&r1, 2);
    b_i = r1->size[0] * r1->size[1];
    r1->size[0] = 1;
    loop_ub = ineqEnd - i;
    r1->size[1] = loop_ub;
    emxEnsureCapacity_int32_T(r1, b_i);
    r3 = r1->data;
    for (b_i = 0; b_i < loop_ub; b_i++) {
      r3[b_i] = i + b_i;
    }
    emxInit_real_T(&c_c, 2);
    i = c_c->size[0] * c_c->size[1];
    c_c->size[0] = input_sizes_idx_0;
    c_c->size[1] = sizes_idx_1;
    emxEnsureCapacity_real_T(c_c, i);
    urk_data = c_c->data;
    loop_ub = sizes_idx_1;
    for (i = 0; i < loop_ub; i++) {
      for (b_i = 0; b_i < input_sizes_idx_0; b_i++) {
        urk_data[b_i] = c_data[b_i];
      }
    }
    emxFree_real_T(&c);
    loop_ub = r1->size[1];
    for (i = 0; i < loop_ub; i++) {
      Cineq_workspace_data[r3[i]] = urk_data[i];
    }
    emxFree_real_T(&c_c);
    if (eq0 > eqEnd) {
      i = 0;
      eqEnd = 0;
    } else {
      i = eq0 - 1;
    }
    b_i = r1->size[0] * r1->size[1];
    r1->size[0] = 1;
    loop_ub = eqEnd - i;
    r1->size[1] = loop_ub;
    emxEnsureCapacity_int32_T(r1, b_i);
    r3 = r1->data;
    for (b_i = 0; b_i < loop_ub; b_i++) {
      r3[b_i] = i + b_i;
    }
    memcpy(&ceq[0], &b_x[0], 30U * sizeof(real_T));
    ceq[30] = U[10];
    ceq[31] = U[21];
    loop_ub = r1->size[1];
    for (i = 0; i < loop_ub; i++) {
      Ceq_workspace[r3[i]] = ceq[i];
    }
    emxFree_int32_T(&r1);
    if (obj_ScaleProblem) {
      for (input_sizes_idx_0 = 0; input_sizes_idx_0 < obj_mCineq;
           input_sizes_idx_0++) {
        i = (ineq0 + input_sizes_idx_0) - 1;
        Cineq_workspace_data[i] *=
            scales_cineq_constraint_data[input_sizes_idx_0];
      }
      for (input_sizes_idx_0 = 0; input_sizes_idx_0 < obj_mCeq;
           input_sizes_idx_0++) {
        i = (eq0 + input_sizes_idx_0) - 1;
        Ceq_workspace[i] *= scales_ceq_constraint[input_sizes_idx_0];
      }
    }
    *status = checkVectorNonFinite(obj_mCineq, Cineq_workspace, ineq0);
    if (*status == 1) {
      *status = b_checkVectorNonFinite(obj_mCeq, Ceq_workspace, eq0);
    }
  }
  emxFree_real_T(&urk);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (evalObjAndConstr.c) */
