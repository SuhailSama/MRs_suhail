/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * nlmpcmoveCodeGeneration_mexutil.c
 *
 * Code generation for function 'nlmpcmoveCodeGeneration_mexutil'
 *
 */

/* Include files */
#include "nlmpcmoveCodeGeneration_mexutil.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
real_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = k_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

const mxArray *b_feval(const mxArray *m1, const mxArray *m2, const mxArray *m3,
                       const mxArray *m4, const mxArray *m5, const mxArray *m6,
                       const mxArray *m7, emlrtMCInfo *location)
{
  const mxArray *pArrays[7];
  const mxArray *m;
  pArrays[0] = m1;
  pArrays[1] = m2;
  pArrays[2] = m3;
  pArrays[3] = m4;
  pArrays[4] = m5;
  pArrays[5] = m6;
  pArrays[6] = m7;
  return emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 1, &m, 7, &pArrays[0],
                               (const char_T *)"feval", true, location);
}

real_T emlrt_marshallIn(const mxArray *a__output_of_feval_,
                        const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(emlrtAlias(a__output_of_feval_), &thisId);
  emlrtDestroyArray(&a__output_of_feval_);
  return y;
}

const mxArray *feval(const mxArray *m1, const mxArray *m2, const mxArray *m3,
                     emlrtMCInfo *location)
{
  const mxArray *pArrays[3];
  const mxArray *m;
  pArrays[0] = m1;
  pArrays[1] = m2;
  pArrays[2] = m3;
  return emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 1, &m, 3, &pArrays[0],
                               (const char_T *)"feval", true, location);
}

real_T k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src,
                          (const char_T *)"double", false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/* End of code generation (nlmpcmoveCodeGeneration_mexutil.c) */
