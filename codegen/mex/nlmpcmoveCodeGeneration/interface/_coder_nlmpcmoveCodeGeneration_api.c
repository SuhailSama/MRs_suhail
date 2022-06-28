/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_nlmpcmoveCodeGeneration_api.c
 *
 * Code generation for function '_coder_nlmpcmoveCodeGeneration_api'
 *
 */

/* Include files */
#include "_coder_nlmpcmoveCodeGeneration_api.h"
#include "nlmpcmoveCodeGeneration.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_mexutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static const mxArray *b_emlrt_marshallOut(const real_T u[2]);

static real_T (*c_emlrt_marshallIn(const mxArray *x,
                                   const char_T *identifier))[3];

static const mxArray *c_emlrt_marshallOut(const struct1_T u);

static real_T (*d_emlrt_marshallIn(const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3];

static const mxArray *d_emlrt_marshallOut(const emxArray_real_T *u);

static real_T (*e_emlrt_marshallIn(const mxArray *lastMV,
                                   const char_T *identifier))[2];

static const mxArray *e_emlrt_marshallOut(const emxArray_real_T *u);

static real_T (*f_emlrt_marshallIn(const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[2];

static const mxArray *f_emlrt_marshallOut(const struct2_T *u);

static void g_emlrt_marshallIn(const mxArray *onlinedata,
                               const char_T *identifier, struct1_T *y);

static const mxArray *g_emlrt_marshallOut(const real_T u[33]);

static void h_emlrt_marshallIn(const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               struct1_T *y);

static void i_emlrt_marshallIn(const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y);

static void j_emlrt_marshallIn(const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y);

static real_T (*l_emlrt_marshallIn(const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3];

static real_T (*m_emlrt_marshallIn(const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[2];

static void n_emlrt_marshallIn(const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret);

static void o_emlrt_marshallIn(const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret);

/* Function Definitions */
static const mxArray *b_emlrt_marshallOut(const real_T u[2])
{
  static const int32_T i = 0;
  static const int32_T i1 = 2;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

static real_T (*c_emlrt_marshallIn(const mxArray *x,
                                   const char_T *identifier))[3]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[3];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(emlrtAlias(x), &thisId);
  emlrtDestroyArray(&x);
  return y;
}

static const mxArray *c_emlrt_marshallOut(const struct1_T u)
{
  static const char_T *sv[5] = {"ref", "MVTarget", "X0", "MV0", "Slack0"};
  const mxArray *b_y;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 5, (const char_T **)&sv[0]));
  emlrtSetFieldR2017b(y, 0, (const char_T *)"ref", d_emlrt_marshallOut(u.ref),
                      0);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"MVTarget",
                      e_emlrt_marshallOut(u.MVTarget), 1);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"X0", d_emlrt_marshallOut(u.X0), 2);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"MV0", e_emlrt_marshallOut(u.MV0),
                      3);
  b_y = NULL;
  m = emlrtCreateDoubleScalar(u.Slack0);
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Slack0", b_y, 4);
  return y;
}

static real_T (*d_emlrt_marshallIn(const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[3]
{
  real_T(*y)[3];
  y = l_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *d_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *m;
  const mxArray *y;
  const real_T *u_data;
  real_T *pData;
  int32_T b_iv[2];
  int32_T b_i;
  int32_T i;
  u_data = u->data;
  y = NULL;
  b_iv[0] = u->size[0];
  b_iv[1] = 3;
  m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < u->size[0]; b_i++) {
    pData[i] = u_data[b_i];
    i++;
  }
  for (b_i = 0; b_i < u->size[0]; b_i++) {
    pData[i] = u_data[b_i + u->size[0]];
    i++;
  }
  for (b_i = 0; b_i < u->size[0]; b_i++) {
    pData[i] = u_data[b_i + u->size[0] * 2];
    i++;
  }
  emlrtAssign(&y, m);
  return y;
}

static real_T (*e_emlrt_marshallIn(const mxArray *lastMV,
                                   const char_T *identifier))[2]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[2];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(emlrtAlias(lastMV), &thisId);
  emlrtDestroyArray(&lastMV);
  return y;
}

static const mxArray *e_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *m;
  const mxArray *y;
  const real_T *u_data;
  real_T *pData;
  int32_T b_iv[2];
  int32_T b_i;
  int32_T i;
  u_data = u->data;
  y = NULL;
  b_iv[0] = u->size[0];
  b_iv[1] = 2;
  m = emlrtCreateNumericArray(2, &b_iv[0], mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < u->size[0]; b_i++) {
    pData[i] = u_data[b_i];
    i++;
  }
  for (b_i = 0; b_i < u->size[0]; b_i++) {
    pData[i] = u_data[b_i + u->size[0]];
    i++;
  }
  emlrtAssign(&y, m);
  return y;
}

static real_T (*f_emlrt_marshallIn(const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[2]
{
  real_T(*y)[2];
  y = m_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *f_emlrt_marshallOut(const struct2_T *u)
{
  static const int32_T b_iv[2] = {11, 2};
  static const int32_T i1 = 11;
  static const char_T *sv[8] = {"MVopt", "Xopt",     "Yopt",       "Topt",
                                "Slack", "ExitFlag", "Iterations", "Cost"};
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  int32_T b_i;
  int32_T c_i;
  int32_T i;
  y = NULL;
  emlrtAssign(&y, emlrtCreateStructMatrix(1, 1, 8, (const char_T **)&sv[0]));
  b_y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&b_iv[0], mxDOUBLE_CLASS,
                              mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < 2; b_i++) {
    for (c_i = 0; c_i < 11; c_i++) {
      pData[i + c_i] = u->MVopt[c_i + 11 * b_i];
    }
    i += 11;
  }
  emlrtAssign(&b_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"MVopt", b_y, 0);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Xopt",
                      g_emlrt_marshallOut(u->Xopt), 1);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Yopt",
                      g_emlrt_marshallOut(u->Yopt), 2);
  c_y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i1, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  for (b_i = 0; b_i < 11; b_i++) {
    pData[b_i] = u->Topt[b_i];
  }
  emlrtAssign(&c_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Topt", c_y, 3);
  d_y = NULL;
  m = emlrtCreateDoubleScalar(u->Slack);
  emlrtAssign(&d_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Slack", d_y, 4);
  e_y = NULL;
  m = emlrtCreateDoubleScalar(u->ExitFlag);
  emlrtAssign(&e_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"ExitFlag", e_y, 5);
  f_y = NULL;
  m = emlrtCreateDoubleScalar(u->Iterations);
  emlrtAssign(&f_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Iterations", f_y, 6);
  g_y = NULL;
  m = emlrtCreateDoubleScalar(u->Cost);
  emlrtAssign(&g_y, m);
  emlrtSetFieldR2017b(y, 0, (const char_T *)"Cost", g_y, 7);
  return y;
}

static void g_emlrt_marshallIn(const mxArray *onlinedata,
                               const char_T *identifier, struct1_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  h_emlrt_marshallIn(emlrtAlias(onlinedata), &thisId, y);
  emlrtDestroyArray(&onlinedata);
}

static const mxArray *g_emlrt_marshallOut(const real_T u[33])
{
  static const int32_T b_iv[2] = {11, 3};
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  int32_T b_i;
  int32_T c_i;
  int32_T i;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&b_iv[0], mxDOUBLE_CLASS,
                              mxREAL);
  pData = emlrtMxGetPr(m);
  i = 0;
  for (b_i = 0; b_i < 3; b_i++) {
    for (c_i = 0; c_i < 11; c_i++) {
      pData[i + c_i] = u[c_i + 11 * b_i];
    }
    i += 11;
  }
  emlrtAssign(&y, m);
  return y;
}

static void h_emlrt_marshallIn(const mxArray *u,
                               const emlrtMsgIdentifier *parentId, struct1_T *y)
{
  static const int32_T dims = 0;
  static const char_T *fieldNames[5] = {"ref", "MVTarget", "X0", "MV0",
                                        "Slack0"};
  emlrtMsgIdentifier thisId;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(emlrtRootTLSGlobal, parentId, u, 5,
                         (const char_T **)&fieldNames[0], 0U, (void *)&dims);
  thisId.fIdentifier = "ref";
  i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 0,
                                                    (const char_T *)"ref")),
                     &thisId, y->ref);
  thisId.fIdentifier = "MVTarget";
  j_emlrt_marshallIn(
      emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 1,
                                     (const char_T *)"MVTarget")),
      &thisId, y->MVTarget);
  thisId.fIdentifier = "X0";
  i_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 2,
                                                    (const char_T *)"X0")),
                     &thisId, y->X0);
  thisId.fIdentifier = "MV0";
  j_emlrt_marshallIn(emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 3,
                                                    (const char_T *)"MV0")),
                     &thisId, y->MV0);
  thisId.fIdentifier = "Slack0";
  y->Slack0 = b_emlrt_marshallIn(
      emlrtAlias(emlrtGetFieldR2017b(emlrtRootTLSGlobal, u, 0, 4,
                                     (const char_T *)"Slack0")),
      &thisId);
  emlrtDestroyArray(&u);
}

static void i_emlrt_marshallIn(const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y)
{
  n_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void j_emlrt_marshallIn(const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_real_T *y)
{
  o_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T (*l_emlrt_marshallIn(const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[3]
{
  static const int32_T dims = 3;
  real_T(*ret)[3];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src,
                          (const char_T *)"double", false, 1U, (void *)&dims);
  ret = (real_T(*)[3])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*m_emlrt_marshallIn(const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[2]
{
  static const int32_T dims = 2;
  real_T(*ret)[2];
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src,
                          (const char_T *)"double", false, 1U, (void *)&dims);
  ret = (real_T(*)[2])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void n_emlrt_marshallIn(const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret)
{
  static const int32_T dims[2] = {10, 3};
  real_T *ret_data;
  int32_T b_iv[2];
  int32_T i;
  const boolean_T bv[2] = {true, false};
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src,
                            (const char_T *)"double", false, 2U,
                            (void *)&dims[0], &bv[0], &b_iv[0]);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_real_T(ret, i);
  ret_data = ret->data;
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, &ret_data[0], 8, false);
  emlrtDestroyArray(&src);
}

static void o_emlrt_marshallIn(const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_real_T *ret)
{
  static const int32_T dims[2] = {10, 2};
  real_T *ret_data;
  int32_T b_iv[2];
  int32_T i;
  const boolean_T bv[2] = {true, false};
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src,
                            (const char_T *)"double", false, 2U,
                            (void *)&dims[0], &bv[0], &b_iv[0]);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = b_iv[0];
  ret->size[1] = b_iv[1];
  emxEnsureCapacity_real_T(ret, i);
  ret_data = ret->data;
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, &ret_data[0], 8, false);
  emlrtDestroyArray(&src);
}

void nlmpcmoveCodeGeneration_api(const mxArray *const prhs[3], int32_T nlhs,
                                 const mxArray *plhs[3])
{
  struct1_T onlinedata;
  struct2_T info;
  real_T(*x)[3];
  real_T(*lastMV)[2];
  real_T(*mv)[2];
  mv = (real_T(*)[2])mxMalloc(sizeof(real_T[2]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInitStruct_struct1_T(&onlinedata);
  /* Marshall function inputs */
  x = c_emlrt_marshallIn(emlrtAlias(prhs[0]), "x");
  lastMV = e_emlrt_marshallIn(emlrtAlias(prhs[1]), "lastMV");
  g_emlrt_marshallIn(emlrtAliasP(prhs[2]), "onlinedata", &onlinedata);
  /* Invoke the target function */
  nlmpcmoveCodeGeneration(*x, *lastMV, &onlinedata, *mv, &info);
  /* Marshall function outputs */
  plhs[0] = b_emlrt_marshallOut(*mv);
  if (nlhs > 1) {
    plhs[1] = c_emlrt_marshallOut(onlinedata);
  }
  emxFreeStruct_struct1_T(&onlinedata);
  if (nlhs > 2) {
    plhs[2] = f_emlrt_marshallOut(&info);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (_coder_nlmpcmoveCodeGeneration_api.c) */
