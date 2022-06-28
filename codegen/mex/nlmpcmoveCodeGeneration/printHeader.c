/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * printHeader.c
 *
 * Code generation for function 'printHeader'
 *
 */

/* Include files */
#include "printHeader.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_mexutil.h"
#include "rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

/* Function Definitions */
void printHeader(void)
{
  static const int32_T b_iv[2] = {1, 7};
  static const int32_T iv1[2] = {1, 119};
  static const int32_T iv2[2] = {1, 7};
  static const int32_T iv3[2] = {1, 133};
  static const int32_T iv4[2] = {1, 7};
  static const int32_T iv5[2] = {1, 2};
  static const char_T c_u[133] = {
      ' ', 'I', 't', 'e', 'r', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', 'F', 'v', 'a',  'l', ' ', ' ', ' ', ' ', ' ', ' ', 'O',
      'p', 't', 'i', 'm', 'a', 'l',  'i', 't', 'y', ' ', ' ', ' ', ' ', ' ',
      'F', 'e', 'a', 's', 'i', 'b',  'i', 'l', 'i', 't', 'y', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', 'a', 'l', 'p', 'h', 'a', ' ',
      ' ', ' ', ' ', 'N', 'o', 'r',  'm', ' ', 'o', 'f', ' ', 's', 't', 'e',
      'p', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', 'A', 'c',
      't', 'i', 'o', 'n', ' ', ' ',  ' ', ' ', ' ', 'C', 'o', 'n', 's', 't',
      'r', 'a', 'i', 'n', 't', 's',  ' ', ' ', ' ', ' ', 'S', 't', 'e', 'p',
      ' ', 'T', 'y', 'p', 'e', '\\', 'n'};
  static const char_T b_u[119] = {
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', 'F', 'i',
      'r', 's', 't', '-', 'o', 'r',  'd', 'e', 'r', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A',
      'c', 't', 'i', 'v', 'e', '\\', 'n'};
  static const char_T u[7] = {'f', 'p', 'r', 'i', 'n', 't', 'f'};
  static const char_T d_u[2] = {'\\', 'n'};
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateCharArray(2, &b_iv[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&y, m);
  b_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&b_y, m);
  c_y = NULL;
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 119, m, &b_u[0]);
  emlrtAssign(&c_y, m);
  emlrt_marshallIn(feval(y, b_y, c_y, &emlrtMCI), "<output of feval>");
  d_y = NULL;
  m = emlrtCreateCharArray(2, &iv2[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&d_y, m);
  e_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&e_y, m);
  f_y = NULL;
  m = emlrtCreateCharArray(2, &iv3[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 133, m, &c_u[0]);
  emlrtAssign(&f_y, m);
  emlrt_marshallIn(feval(d_y, e_y, f_y, &emlrtMCI), "<output of feval>");
  g_y = NULL;
  m = emlrtCreateCharArray(2, &iv4[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&g_y, m);
  h_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&h_y, m);
  i_y = NULL;
  m = emlrtCreateCharArray(2, &iv5[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 2, m, &d_u[0]);
  emlrtAssign(&i_y, m);
  emlrt_marshallIn(feval(g_y, h_y, i_y, &emlrtMCI), "<output of feval>");
}

/* End of code generation (printHeader.c) */
