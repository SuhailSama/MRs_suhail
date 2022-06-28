/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * evalObjAndConstrAndDerivatives.c
 *
 * Code generation for function 'evalObjAndConstrAndDerivatives'
 *
 */

/* Include files */
#include "evalObjAndConstrAndDerivatives.h"
#include "checkMatrixNonFinite.h"
#include "checkVectorNonFinite.h"
#include "nlmpcmoveCodeGeneration.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void evalObjAndConstrAndDerivatives(
    const real_T c_obj_objfun_workspace_runtimed[3],
    const real_T d_obj_objfun_workspace_runtimed[2],
    const emxArray_real_T *e_obj_objfun_workspace_runtimed,
    const real_T f_obj_objfun_workspace_runtimed[30],
    const real_T g_obj_objfun_workspace_runtimed[20],
    const real_T h_obj_objfun_workspace_runtimed[20],
    real_T i_obj_objfun_workspace_runtimed,
    const emxArray_real_T *j_obj_objfun_workspace_runtimed,
    const real_T c_obj_nonlcon_workspace_runtime[3],
    const real_T d_obj_nonlcon_workspace_runtime[30],
    const real_T e_obj_nonlcon_workspace_runtime[30], int32_T obj_nVar,
    int32_T obj_mCineq, int32_T obj_mCeq, boolean_T obj_ScaleProblem,
    const real_T x[51], emxArray_real_T *grad_workspace,
    emxArray_real_T *Cineq_workspace, int32_T ineq0, real_T Ceq_workspace[32],
    int32_T eq0, emxArray_real_T *JacIneqTrans_workspace, int32_T iJI_col,
    int32_T ldJI, emxArray_real_T *JacEqTrans_workspace, int32_T iJE_col,
    int32_T ldJE, const p_struct_T *scales, real_T *fval, int32_T *status)
{
  static const int8_T b_iv[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  emxArray_real_T *urk;
  emxArray_real_T *varargout_1;
  emxArray_real_T *varargout_3;
  real_T varargout_4[1632];
  real_T varargout_2[51];
  real_T X[33];
  real_T b_X[33];
  real_T b_varargout_2[32];
  real_T b_x[30];
  real_T U[22];
  real_T Umv[22];
  real_T a[20];
  real_T gfU[20];
  real_T gfX[3];
  const real_T *k_obj_objfun_workspace_runtimed;
  const real_T *l_obj_objfun_workspace_runtimed;
  real_T d;
  real_T d1;
  real_T d2;
  real_T duk_idx_0;
  real_T duk_idx_1;
  real_T fs;
  real_T umvk_idx_1;
  real_T wtYerr_idx_0;
  real_T wtYerr_idx_1;
  real_T *Cineq_workspace_data;
  real_T *JacEqTrans_workspace_data;
  real_T *JacIneqTrans_workspace_data;
  real_T *grad_workspace_data;
  real_T *urk_data;
  int32_T b_i;
  int32_T i;
  int32_T idxJIWkspc;
  int32_T idx_col;
  int32_T idx_scales;
  int8_T ix[3];
  int8_T iu_idx_0;
  int8_T iu_idx_1;
  JacEqTrans_workspace_data = JacEqTrans_workspace->data;
  JacIneqTrans_workspace_data = JacIneqTrans_workspace->data;
  Cineq_workspace_data = Cineq_workspace->data;
  grad_workspace_data = grad_workspace->data;
  k_obj_objfun_workspace_runtimed = j_obj_objfun_workspace_runtimed->data;
  l_obj_objfun_workspace_runtimed = e_obj_objfun_workspace_runtimed->data;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  memset(&X[0], 0, 33U * sizeof(real_T));
  memset(&Umv[0], 0, 22U * sizeof(real_T));
  for (i = 0; i < 20; i++) {
    d = 0.0;
    for (idxJIWkspc = 0; idxJIWkspc < 20; idxJIWkspc++) {
      d += (real_T)iv[i + 20 * idxJIWkspc] * x[idxJIWkspc + 30];
    }
    a[i] = d;
  }
  for (i = 0; i < 2; i++) {
    for (idxJIWkspc = 0; idxJIWkspc < 10; idxJIWkspc++) {
      Umv[idxJIWkspc + 11 * i] = a[i + (idxJIWkspc << 1)];
    }
  }
  memcpy(&b_x[0], &x[0], 30U * sizeof(real_T));
  for (i = 0; i < 3; i++) {
    for (idxJIWkspc = 0; idxJIWkspc < 10; idxJIWkspc++) {
      X[(idxJIWkspc + 11 * i) + 1] = b_x[i + 3 * idxJIWkspc];
    }
    X[11 * i] = c_obj_objfun_workspace_runtimed[i];
  }
  for (b_i = 0; b_i < 2; b_i++) {
    Umv[11 * b_i + 10] = Umv[11 * b_i + 9];
    memcpy(&U[b_i * 11], &Umv[b_i * 11], 11U * sizeof(real_T));
  }
  memset(&b_x[0], 0, 30U * sizeof(real_T));
  memset(&gfU[0], 0, 20U * sizeof(real_T));
  fs = 0.0;
  ix[0] = 1;
  ix[1] = 2;
  ix[2] = 3;
  iu_idx_0 = 1;
  iu_idx_1 = 2;
  for (i = 0; i < 11; i++) {
    b_X[3 * i] = X[i];
    b_X[3 * i + 1] = X[i + 11];
    b_X[3 * i + 2] = X[i + 22];
    idxJIWkspc = i << 1;
    Umv[idxJIWkspc] = U[i];
    Umv[idxJIWkspc + 1] = U[i + 11];
  }
  idx_scales = e_obj_objfun_workspace_runtimed->size[1];
  emxInit_real_T(&urk, 1);
  for (b_i = 0; b_i < 10; b_i++) {
    i = urk->size[0];
    urk->size[0] = idx_scales;
    emxEnsureCapacity_real_T(urk, i);
    urk_data = urk->data;
    for (i = 0; i < idx_scales; i++) {
      urk_data[i] = l_obj_objfun_workspace_runtimed
          [b_i + e_obj_objfun_workspace_runtimed->size[0] * i];
    }
    d = f_obj_objfun_workspace_runtimed[b_i];
    i = 3 * (b_i + 1);
    d1 = d * (b_X[i] - urk_data[0]);
    umvk_idx_1 = d1 * d1;
    d1 *= d;
    wtYerr_idx_0 = d1;
    d = f_obj_objfun_workspace_runtimed[b_i + 10];
    d1 = d * (b_X[i + 1] - urk_data[1]);
    umvk_idx_1 += d1 * d1;
    d1 *= d;
    wtYerr_idx_1 = d1;
    d = f_obj_objfun_workspace_runtimed[b_i + 20];
    d1 = d * (b_X[i + 2] - urk_data[2]);
    umvk_idx_1 += d1 * d1;
    d1 *= d;
    fs += umvk_idx_1;
    for (i = 0; i < 3; i++) {
      gfX[i] = b_x[ix[i] - 1] + (((real_T)b_iv[i] * wtYerr_idx_0 +
                                  (real_T)b_iv[i + 3] * wtYerr_idx_1) +
                                 (real_T)b_iv[i + 6] * d1);
    }
    b_x[ix[0] - 1] = gfX[0];
    b_x[ix[1] - 1] = gfX[1];
    b_x[ix[2] - 1] = gfX[2];
    ix[0] = (int8_T)(ix[0] + 3);
    ix[1] = (int8_T)(ix[1] + 3);
    ix[2] = (int8_T)(ix[2] + 3);
    idxJIWkspc = b_i << 1;
    wtYerr_idx_1 = Umv[idxJIWkspc];
    umvk_idx_1 = Umv[idxJIWkspc + 1];
    if (b_i + 1 == 1) {
      duk_idx_0 = wtYerr_idx_1 - d_obj_objfun_workspace_runtimed[0];
      duk_idx_1 = umvk_idx_1 - d_obj_objfun_workspace_runtimed[1];
    } else {
      idxJIWkspc = (b_i - 1) << 1;
      duk_idx_0 = wtYerr_idx_1 - Umv[idxJIWkspc];
      duk_idx_1 = umvk_idx_1 - Umv[idxJIWkspc + 1];
    }
    idxJIWkspc = j_obj_objfun_workspace_runtimed->size[1];
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
      for (i = 0; i < idxJIWkspc; i++) {
        urk_data[i] = k_obj_objfun_workspace_runtimed
            [b_i + j_obj_objfun_workspace_runtimed->size[0] * i];
      }
    }
    d = g_obj_objfun_workspace_runtimed[b_i];
    d1 = d * (wtYerr_idx_1 - urk_data[0]);
    wtYerr_idx_1 = d1;
    wtYerr_idx_0 = d1 * d1;
    d2 = g_obj_objfun_workspace_runtimed[b_i + 10];
    d1 = d2 * (umvk_idx_1 - urk_data[1]);
    wtYerr_idx_0 += d1 * d1;
    fs += wtYerr_idx_0;
    umvk_idx_1 = gfU[iu_idx_1 - 1];
    gfU[iu_idx_0 - 1] += d * wtYerr_idx_1;
    d = h_obj_objfun_workspace_runtimed[b_i];
    wtYerr_idx_0 = d * duk_idx_0;
    wtYerr_idx_1 = wtYerr_idx_0 * wtYerr_idx_0;
    wtYerr_idx_0 *= d;
    duk_idx_0 = wtYerr_idx_0;
    gfU[iu_idx_1 - 1] = umvk_idx_1 + d2 * d1;
    d = h_obj_objfun_workspace_runtimed[b_i + 10];
    wtYerr_idx_0 = d * duk_idx_1;
    wtYerr_idx_1 += wtYerr_idx_0 * wtYerr_idx_0;
    wtYerr_idx_0 *= d;
    fs += wtYerr_idx_1;
    d = gfU[iu_idx_1 - 1];
    gfU[iu_idx_0 - 1] += duk_idx_0;
    gfU[iu_idx_1 - 1] = d + wtYerr_idx_0;
    if (b_i + 1 > 1) {
      umvk_idx_1 = gfU[(int8_T)(iu_idx_1 - 2) - 1] - wtYerr_idx_0;
      gfU[(int8_T)(iu_idx_0 - 2) - 1] -= duk_idx_0;
      gfU[(int8_T)(iu_idx_1 - 2) - 1] = umvk_idx_1;
    }
    iu_idx_0 = (int8_T)(iu_idx_0 + 2);
    iu_idx_1 = (int8_T)(iu_idx_1 + 2);
  }
  emxFree_real_T(&urk);
  *fval = fs + i_obj_objfun_workspace_runtimed * x[50] * x[50];
  for (i = 0; i < 30; i++) {
    b_x[i] *= 2.0;
  }
  for (i = 0; i < 20; i++) {
    gfU[i] *= 2.0;
  }
  for (i = 0; i < 20; i++) {
    d = 0.0;
    for (idxJIWkspc = 0; idxJIWkspc < 20; idxJIWkspc++) {
      d += (real_T)iv[i + 20 * idxJIWkspc] * gfU[idxJIWkspc];
    }
    a[i] = d;
  }
  memcpy(&varargout_2[0], &b_x[0], 30U * sizeof(real_T));
  memcpy(&varargout_2[30], &a[0], 20U * sizeof(real_T));
  varargout_2[50] = 2.0 * i_obj_objfun_workspace_runtimed * x[50];
  for (idxJIWkspc = 0; idxJIWkspc < obj_nVar; idxJIWkspc++) {
    grad_workspace_data[idxJIWkspc] = varargout_2[idxJIWkspc];
  }
  if (obj_ScaleProblem) {
    *fval *= scales->objective;
    if (obj_nVar >= 1) {
      n_t = (ptrdiff_t)obj_nVar;
      incx_t = (ptrdiff_t)1;
      dscal(&n_t, &scales->objective, &grad_workspace_data[0], &incx_t);
    }
  }
  if (muDoubleScalarIsInf(*fval) || muDoubleScalarIsNaN(*fval)) {
    if (muDoubleScalarIsNaN(*fval)) {
      *status = -3;
    } else if (*fval < 0.0) {
      *status = -1;
    } else {
      *status = -2;
    }
  } else {
    *status = checkVectorNonFinite(obj_nVar, grad_workspace, 1);
  }
  if (*status == 1) {
    emxInit_real_T(&varargout_3, 2);
    emxInit_real_T(&varargout_1, 2);
    if ((obj_mCineq > 0) && (obj_mCeq > 0)) {
      c_nlmpcmoveCodeGeneration_anonF(
          c_obj_nonlcon_workspace_runtime, d_obj_nonlcon_workspace_runtime,
          e_obj_nonlcon_workspace_runtime, x, varargout_1, b_varargout_2,
          varargout_3, varargout_4);
      grad_workspace_data = varargout_3->data;
      urk_data = varargout_1->data;
      n_t = (ptrdiff_t)obj_mCineq;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dcopy(&n_t, &urk_data[0], &incx_t, &Cineq_workspace_data[ineq0 - 1],
            &incy_t);
      for (idxJIWkspc = 0; idxJIWkspc < obj_mCeq; idxJIWkspc++) {
        Ceq_workspace[(eq0 + idxJIWkspc) - 1] = b_varargout_2[idxJIWkspc];
      }
      i = varargout_3->size[0];
      for (b_i = 0; b_i < i; b_i++) {
        idxJIWkspc = varargout_3->size[1];
        for (idx_col = 0; idx_col < idxJIWkspc; idx_col++) {
          JacIneqTrans_workspace_data[b_i + ldJI * ((iJI_col + idx_col) - 1)] =
              grad_workspace_data[b_i + varargout_3->size[0] * idx_col];
        }
      }
      for (b_i = 0; b_i < 51; b_i++) {
        for (idx_col = 0; idx_col < 32; idx_col++) {
          JacEqTrans_workspace_data[b_i + ldJE * ((iJE_col + idx_col) - 1)] =
              varargout_4[b_i + 51 * idx_col];
        }
      }
    } else if (obj_mCineq > 0) {
      c_nlmpcmoveCodeGeneration_anonF(
          c_obj_nonlcon_workspace_runtime, d_obj_nonlcon_workspace_runtime,
          e_obj_nonlcon_workspace_runtime, x, varargout_1, b_varargout_2,
          varargout_3, varargout_4);
      grad_workspace_data = varargout_3->data;
      urk_data = varargout_1->data;
      n_t = (ptrdiff_t)obj_mCineq;
      incx_t = (ptrdiff_t)1;
      incy_t = (ptrdiff_t)1;
      dcopy(&n_t, &urk_data[0], &incx_t, &Cineq_workspace_data[ineq0 - 1],
            &incy_t);
      i = varargout_3->size[0];
      for (b_i = 0; b_i < i; b_i++) {
        idxJIWkspc = varargout_3->size[1];
        for (idx_col = 0; idx_col < idxJIWkspc; idx_col++) {
          JacIneqTrans_workspace_data[b_i + ldJI * ((iJI_col + idx_col) - 1)] =
              grad_workspace_data[b_i + varargout_3->size[0] * idx_col];
        }
      }
    } else {
      c_nlmpcmoveCodeGeneration_anonF(
          c_obj_nonlcon_workspace_runtime, d_obj_nonlcon_workspace_runtime,
          e_obj_nonlcon_workspace_runtime, x, varargout_1, b_varargout_2,
          varargout_3, varargout_4);
      for (idxJIWkspc = 0; idxJIWkspc < obj_mCeq; idxJIWkspc++) {
        Ceq_workspace[(eq0 + idxJIWkspc) - 1] = b_varargout_2[idxJIWkspc];
      }
      for (b_i = 0; b_i < 51; b_i++) {
        for (idx_col = 0; idx_col < 32; idx_col++) {
          JacEqTrans_workspace_data[b_i + ldJE * ((iJE_col + idx_col) - 1)] =
              varargout_4[b_i + 51 * idx_col];
        }
      }
    }
    emxFree_real_T(&varargout_1);
    emxFree_real_T(&varargout_3);
    if (obj_ScaleProblem) {
      for (idxJIWkspc = 0; idxJIWkspc < obj_mCineq; idxJIWkspc++) {
        i = (ineq0 + idxJIWkspc) - 1;
        Cineq_workspace_data[i] *= scales->cineq_constraint->data[idxJIWkspc];
      }
      for (idxJIWkspc = 0; idxJIWkspc < obj_mCeq; idxJIWkspc++) {
        i = (eq0 + idxJIWkspc) - 1;
        Ceq_workspace[i] *= scales->ceq_constraint[idxJIWkspc];
      }
      idx_scales = 0;
      i = (iJI_col + obj_mCineq) - 1;
      for (idx_col = iJI_col; idx_col <= i; idx_col++) {
        for (b_i = 0; b_i < obj_nVar; b_i++) {
          idxJIWkspc = b_i + ldJI * (idx_col - 1);
          JacIneqTrans_workspace_data[idxJIWkspc] *=
              scales->cineq_constraint->data[idx_scales];
        }
        idx_scales++;
      }
      idx_scales = 0;
      i = (iJE_col + obj_mCeq) - 1;
      for (idx_col = iJE_col; idx_col <= i; idx_col++) {
        for (b_i = 0; b_i < obj_nVar; b_i++) {
          idxJIWkspc = b_i + ldJE * (idx_col - 1);
          JacEqTrans_workspace_data[idxJIWkspc] *=
              scales->ceq_constraint[idx_scales];
        }
        idx_scales++;
      }
    }
    *status = checkVectorNonFinite(obj_mCineq, Cineq_workspace, ineq0);
    if (*status == 1) {
      *status = b_checkVectorNonFinite(obj_mCeq, Ceq_workspace, eq0);
      if (*status == 1) {
        *status = checkMatrixNonFinite(obj_nVar, obj_mCineq,
                                       JacIneqTrans_workspace, iJI_col, ldJI);
        if (*status == 1) {
          *status = checkMatrixNonFinite(obj_nVar, obj_mCeq,
                                         JacEqTrans_workspace, iJE_col, ldJE);
        }
      }
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (evalObjAndConstrAndDerivatives.c) */
