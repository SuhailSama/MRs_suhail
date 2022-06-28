/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * printInitialInfo.c
 *
 * Code generation for function 'printInitialInfo'
 *
 */

/* Include files */
#include "printInitialInfo.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_mexutil.h"
#include "rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

/* Function Definitions */
void printInitialInfo(int32_T PROBLEM_TYPE, real_T solution_fstar,
                      int32_T solution_iterations,
                      int32_T workingset_nActiveConstr)
{
  static const int32_T b_iv[2] = {1, 7};
  static const int32_T iv1[2] = {1, 112};
  static const int32_T iv2[2] = {1, 13};
  static const int32_T iv3[2] = {1, 7};
  static const int32_T iv4[2] = {1, 2};
  static const char_T b_u[112] = {
      '%', '5', 'i', ' ', ' ', '%', '1', '4', '.', '6', 'e', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', '%', '5', 'i', ' ', ' ', ' ', ' ', '%', 's'};
  static const char_T b_cv[13] = {'N', 'o', 'r', 'm', 'a', 'l', ' ',
                                  ' ', ' ', ' ', ' ', ' ', ' '};
  static const char_T cv1[13] = {'P', 'h', 'a', 's', 'e', ' ', 'O',
                                 'n', 'e', ' ', ' ', ' ', ' '};
  static const char_T cv2[13] = {'R', 'e', 'g', 'u', 'l', 'a', 'r',
                                 'i', 'z', 'e', 'd', ' ', ' '};
  static const char_T u[7] = {'f', 'p', 'r', 'i', 'n', 't', 'f'};
  static const char_T c_u[2] = {'\\', 'n'};
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  const mxArray *j_y;
  const mxArray *m;
  const mxArray *y;
  int32_T i;
  char_T stepType_str[13];
  switch (PROBLEM_TYPE) {
  case 1:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = cv1[i];
    }
    break;
  case 2:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = cv2[i];
    }
    break;
  case 4:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = cv[i];
    }
    break;
  default:
    for (i = 0; i < 13; i++) {
      stepType_str[i] = b_cv[i];
    }
    break;
  }
  y = NULL;
  m = emlrtCreateCharArray(2, &b_iv[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&y, m);
  b_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&b_y, m);
  c_y = NULL;
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 112, m, &b_u[0]);
  emlrtAssign(&c_y, m);
  d_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = solution_iterations;
  emlrtAssign(&d_y, m);
  e_y = NULL;
  m = emlrtCreateDoubleScalar(solution_fstar);
  emlrtAssign(&e_y, m);
  f_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = workingset_nActiveConstr;
  emlrtAssign(&f_y, m);
  g_y = NULL;
  m = emlrtCreateCharArray(2, &iv2[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 13, m, &stepType_str[0]);
  emlrtAssign(&g_y, m);
  emlrt_marshallIn(b_feval(y, b_y, c_y, d_y, e_y, f_y, g_y, &emlrtMCI),
                   "<output of feval>");
  h_y = NULL;
  m = emlrtCreateCharArray(2, &iv3[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&h_y, m);
  i_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&i_y, m);
  j_y = NULL;
  m = emlrtCreateCharArray(2, &iv4[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 2, m, &c_u[0]);
  emlrtAssign(&j_y, m);
  emlrt_marshallIn(feval(h_y, i_y, j_y, &emlrtMCI), "<output of feval>");
}

/* End of code generation (printInitialInfo.c) */
