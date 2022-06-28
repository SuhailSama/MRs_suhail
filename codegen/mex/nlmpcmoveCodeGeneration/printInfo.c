/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * printInfo.c
 *
 * Code generation for function 'printInfo'
 *
 */

/* Include files */
#include "printInfo.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_mexutil.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static const mxArray *c_feval(const mxArray *m1, const mxArray *m2,
                              const mxArray *m3, const mxArray *m4,
                              emlrtMCInfo *location);

static const mxArray *emlrt_marshallOut(const char_T u[7]);

static void workingSetAction(int32_T activeConstrChangedType,
                             int32_T localActiveConstrIdx,
                             int32_T activeSetChangeID,
                             const emxArray_int32_T *workingset_indexLB,
                             const emxArray_int32_T *workingset_indexUB);

/* Function Definitions */
static const mxArray *c_feval(const mxArray *m1, const mxArray *m2,
                              const mxArray *m3, const mxArray *m4,
                              emlrtMCInfo *location)
{
  const mxArray *pArrays[4];
  const mxArray *m;
  pArrays[0] = m1;
  pArrays[1] = m2;
  pArrays[2] = m3;
  pArrays[3] = m4;
  return emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 1, &m, 4, &pArrays[0],
                               (const char_T *)"feval", true, location);
}

static const mxArray *emlrt_marshallOut(const char_T u[7])
{
  static const int32_T b_iv[2] = {1, 7};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateCharArray(2, &b_iv[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static void workingSetAction(int32_T activeConstrChangedType,
                             int32_T localActiveConstrIdx,
                             int32_T activeSetChangeID,
                             const emxArray_int32_T *workingset_indexLB,
                             const emxArray_int32_T *workingset_indexUB)
{
  static const int32_T b_iv[2] = {1, 7};
  static const int32_T iv1[2] = {1, 7};
  static const int32_T iv10[2] = {1, 5};
  static const int32_T iv11[2] = {1, 7};
  static const int32_T iv12[2] = {1, 6};
  static const int32_T iv2[2] = {1, 7};
  static const int32_T iv3[2] = {1, 7};
  static const int32_T iv4[2] = {1, 7};
  static const int32_T iv5[2] = {1, 7};
  static const int32_T iv6[2] = {1, 7};
  static const int32_T iv7[2] = {1, 5};
  static const int32_T iv8[2] = {1, 5};
  static const int32_T iv9[2] = {1, 5};
  static const char_T u[7] = {'f', 'p', 'r', 'i', 'n', 't', 'f'};
  static const char_T f_u[6] = {'(', '%', '-', '5', 'i', ')'};
  static const char_T b_u[5] = {'S', 'A', 'M', 'E', ' '};
  static const char_T c_u[5] = {'A', 'I', 'N', 'E', 'Q'};
  static const char_T d_u[5] = {'L', 'O', 'W', 'E', 'R'};
  static const char_T e_u[5] = {'U', 'P', 'P', 'E', 'R'};
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  const mxArray *j_y;
  const mxArray *k_y;
  const mxArray *l_y;
  const mxArray *m;
  const mxArray *m_y;
  const mxArray *n_y;
  const mxArray *o_y;
  const mxArray *p_y;
  const mxArray *q_y;
  const mxArray *r_y;
  const mxArray *s_y;
  const mxArray *t_y;
  const mxArray *u_y;
  const mxArray *v_y;
  const mxArray *w_y;
  const mxArray *x_y;
  const mxArray *y;
  const mxArray *y_y;
  const int32_T *workingset_indexLB_data;
  const int32_T *workingset_indexUB_data;
  workingset_indexUB_data = workingset_indexUB->data;
  workingset_indexLB_data = workingset_indexLB->data;
  switch (activeSetChangeID) {
  case -1:
    b_y = NULL;
    m = emlrtCreateCharArray(2, &iv1[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
    emlrtAssign(&b_y, m);
    e_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&e_y, m);
    h_y = NULL;
    m = emlrtCreateString1('-');
    emlrtAssign(&h_y, m);
    emlrt_marshallIn(feval(b_y, e_y, h_y, &emlrtMCI), "<output of feval>");
    break;
  case 1:
    c_y = NULL;
    m = emlrtCreateCharArray(2, &iv2[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
    emlrtAssign(&c_y, m);
    f_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&f_y, m);
    i_y = NULL;
    m = emlrtCreateString1('+');
    emlrtAssign(&i_y, m);
    emlrt_marshallIn(feval(c_y, f_y, i_y, &emlrtMCI), "<output of feval>");
    break;
  default:
    y = NULL;
    m = emlrtCreateCharArray(2, &b_iv[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
    emlrtAssign(&y, m);
    d_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&d_y, m);
    g_y = NULL;
    m = emlrtCreateString1(' ');
    emlrtAssign(&g_y, m);
    emlrt_marshallIn(feval(y, d_y, g_y, &emlrtMCI), "<output of feval>");
    break;
  }
  switch (activeConstrChangedType) {
  case 3:
    k_y = NULL;
    m = emlrtCreateCharArray(2, &iv4[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
    emlrtAssign(&k_y, m);
    o_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&o_y, m);
    s_y = NULL;
    m = emlrtCreateCharArray(2, &iv8[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 5, m, &c_u[0]);
    emlrtAssign(&s_y, m);
    emlrt_marshallIn(feval(k_y, o_y, s_y, &emlrtMCI), "<output of feval>");
    break;
  case 4:
    l_y = NULL;
    m = emlrtCreateCharArray(2, &iv5[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
    emlrtAssign(&l_y, m);
    p_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&p_y, m);
    t_y = NULL;
    m = emlrtCreateCharArray(2, &iv9[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 5, m, &d_u[0]);
    emlrtAssign(&t_y, m);
    emlrt_marshallIn(feval(l_y, p_y, t_y, &emlrtMCI), "<output of feval>");
    localActiveConstrIdx = workingset_indexLB_data[localActiveConstrIdx - 1];
    break;
  case 5:
    m_y = NULL;
    m = emlrtCreateCharArray(2, &iv6[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
    emlrtAssign(&m_y, m);
    q_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&q_y, m);
    u_y = NULL;
    m = emlrtCreateCharArray(2, &iv10[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 5, m, &e_u[0]);
    emlrtAssign(&u_y, m);
    emlrt_marshallIn(feval(m_y, q_y, u_y, &emlrtMCI), "<output of feval>");
    localActiveConstrIdx = workingset_indexUB_data[localActiveConstrIdx - 1];
    break;
  default:
    j_y = NULL;
    m = emlrtCreateCharArray(2, &iv3[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
    emlrtAssign(&j_y, m);
    n_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&n_y, m);
    r_y = NULL;
    m = emlrtCreateCharArray(2, &iv7[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 5, m, &b_u[0]);
    emlrtAssign(&r_y, m);
    emlrt_marshallIn(feval(j_y, n_y, r_y, &emlrtMCI), "<output of feval>");
    localActiveConstrIdx = -1;
    break;
  }
  v_y = NULL;
  m = emlrtCreateCharArray(2, &iv11[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 7, m, &u[0]);
  emlrtAssign(&v_y, m);
  w_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&w_y, m);
  x_y = NULL;
  m = emlrtCreateCharArray(2, &iv12[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 6, m, &f_u[0]);
  emlrtAssign(&x_y, m);
  y_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = localActiveConstrIdx;
  emlrtAssign(&y_y, m);
  emlrt_marshallIn(c_feval(v_y, w_y, x_y, y_y, &emlrtMCI), "<output of feval>");
}

void printInfo(boolean_T newBlocking, int32_T PROBLEM_TYPE, real_T alpha,
               real_T stepNorm, int32_T activeConstrChangedType,
               int32_T localActiveConstrIdx, int32_T activeSetChangeID,
               real_T solution_fstar, real_T solution_firstorderopt,
               real_T solution_maxConstr, int32_T solution_iterations,
               const emxArray_int32_T *workingset_indexLB,
               const emxArray_int32_T *workingset_indexUB,
               int32_T workingset_nActiveConstr)
{
  static const int32_T b_iv[2] = {1, 27};
  static const int32_T iv1[2] = {1, 2};
  static const int32_T iv10[2] = {1, 3};
  static const int32_T iv11[2] = {1, 4};
  static const int32_T iv12[2] = {1, 6};
  static const int32_T iv13[2] = {1, 9};
  static const int32_T iv14[2] = {1, 11};
  static const int32_T iv15[2] = {1, 13};
  static const int32_T iv16[2] = {1, 2};
  static const int32_T iv2[2] = {1, 14};
  static const int32_T iv3[2] = {1, 6};
  static const int32_T iv4[2] = {1, 2};
  static const int32_T iv5[2] = {1, 6};
  static const int32_T iv6[2] = {1, 4};
  static const int32_T iv7[2] = {1, 6};
  static const int32_T iv8[2] = {1, 11};
  static const int32_T iv9[2] = {1, 6};
  static const char_T u[27] = {'%', '5', 'i', ' ', ' ', '%', '1', '4', '.',
                               '6', 'e', ' ', ' ', '%', '1', '4', '.', '6',
                               'e', ' ', ' ', '%', '1', '4', '.', '6', 'e'};
  static const char_T c_u[14] = {' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                 '-', ' ', ' ', ' ', ' ', ' ', ' '};
  static const char_T l_u[11] = {'R', 'e', 'g', 'u', 'l', 'a',
                                 'r', 'i', 'z', 'e', 'd'};
  static const char_T k_u[9] = {'P', 'h', 'a', 's', 'e', ' ', 'O', 'n', 'e'};
  static const char_T b_cv[7] = {'f', 'p', 'r', 'i', 'n', 't', 'f'};
  static const char_T d_u[6] = {'%', '1', '4', '.', '6', 'e'};
  static const char_T f_u[6] = {' ', 'S', 'A', 'M', 'E', ' '};
  static const char_T h_u[6] = {'(', '%', '-', '5', 'i', ')'};
  static const char_T j_u[6] = {'N', 'o', 'r', 'm', 'a', 'l'};
  static const char_T i_u[3] = {'%', '5', 'i'};
  static const char_T m_u[2] = {'\\', 'n'};
  const mxArray *ab_y;
  const mxArray *b_y;
  const mxArray *bb_y;
  const mxArray *c_y;
  const mxArray *cb_y;
  const mxArray *d_y;
  const mxArray *db_y;
  const mxArray *e_y;
  const mxArray *eb_y;
  const mxArray *f_y;
  const mxArray *fb_y;
  const mxArray *g_y;
  const mxArray *gb_y;
  const mxArray *h_y;
  const mxArray *hb_y;
  const mxArray *i_y;
  const mxArray *ib_y;
  const mxArray *j_y;
  const mxArray *jb_y;
  const mxArray *k_y;
  const mxArray *kb_y;
  const mxArray *l_y;
  const mxArray *lb_y;
  const mxArray *m;
  const mxArray *m_y;
  const mxArray *mb_y;
  const mxArray *n_y;
  const mxArray *nb_y;
  const mxArray *o_y;
  const mxArray *ob_y;
  const mxArray *p_y;
  const mxArray *pb_y;
  const mxArray *q_y;
  const mxArray *qb_y;
  const mxArray *r_y;
  const mxArray *s_y;
  const mxArray *t_y;
  const mxArray *u_y;
  const mxArray *v_y;
  const mxArray *w_y;
  const mxArray *x_y;
  const mxArray *y;
  const mxArray *y_y;
  int32_T i;
  char_T g_u[11];
  char_T e_u[4];
  char_T b_u[2];
  y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&y, m);
  b_y = NULL;
  m = emlrtCreateCharArray(2, &b_iv[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 27, m, &u[0]);
  emlrtAssign(&b_y, m);
  c_y = NULL;
  m = emlrtCreateDoubleScalar(solution_fstar);
  emlrtAssign(&c_y, m);
  d_y = NULL;
  m = emlrtCreateDoubleScalar(solution_firstorderopt);
  emlrtAssign(&d_y, m);
  e_y = NULL;
  m = emlrtCreateDoubleScalar(solution_maxConstr);
  emlrtAssign(&e_y, m);
  f_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = solution_iterations;
  emlrtAssign(&f_y, m);
  emlrt_marshallIn(
      b_feval(emlrt_marshallOut(b_cv), y, b_y, f_y, c_y, d_y, e_y, &emlrtMCI),
      "<output of feval>");
  g_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&g_y, m);
  b_u[0] = ' ';
  b_u[1] = ' ';
  h_y = NULL;
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 2, m, &b_u[0]);
  emlrtAssign(&h_y, m);
  emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), g_y, h_y, &emlrtMCI),
                   "<output of feval>");
  if (muDoubleScalarIsNaN(alpha)) {
    j_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&j_y, m);
    l_y = NULL;
    m = emlrtCreateCharArray(2, &iv2[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 14, m, &c_u[0]);
    emlrtAssign(&l_y, m);
    emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), j_y, l_y, &emlrtMCI),
                     "<output of feval>");
  } else {
    i_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&i_y, m);
    k_y = NULL;
    m = emlrtCreateDoubleScalar(alpha);
    emlrtAssign(&k_y, m);
    m_y = NULL;
    m = emlrtCreateCharArray(2, &iv3[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 6, m, &d_u[0]);
    emlrtAssign(&m_y, m);
    emlrt_marshallIn(c_feval(emlrt_marshallOut(b_cv), i_y, m_y, k_y, &emlrtMCI),
                     "<output of feval>");
  }
  n_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&n_y, m);
  o_y = NULL;
  m = emlrtCreateCharArray(2, &iv4[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 2, m, &b_u[0]);
  emlrtAssign(&o_y, m);
  emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), n_y, o_y, &emlrtMCI),
                   "<output of feval>");
  p_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&p_y, m);
  q_y = NULL;
  m = emlrtCreateDoubleScalar(stepNorm);
  emlrtAssign(&q_y, m);
  r_y = NULL;
  m = emlrtCreateCharArray(2, &iv5[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 6, m, &d_u[0]);
  emlrtAssign(&r_y, m);
  emlrt_marshallIn(c_feval(emlrt_marshallOut(b_cv), p_y, r_y, q_y, &emlrtMCI),
                   "<output of feval>");
  s_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&s_y, m);
  e_u[0] = ' ';
  e_u[1] = ' ';
  e_u[2] = ' ';
  e_u[3] = ' ';
  t_y = NULL;
  m = emlrtCreateCharArray(2, &iv6[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 4, m, &e_u[0]);
  emlrtAssign(&t_y, m);
  emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), s_y, t_y, &emlrtMCI),
                   "<output of feval>");
  if (newBlocking || (activeSetChangeID == -1)) {
    if (newBlocking) {
      activeSetChangeID = 1;
    }
    workingSetAction(activeConstrChangedType, localActiveConstrIdx,
                     activeSetChangeID, workingset_indexLB, workingset_indexUB);
  } else {
    u_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&u_y, m);
    v_y = NULL;
    m = emlrtCreateCharArray(2, &iv7[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 6, m, &f_u[0]);
    emlrtAssign(&v_y, m);
    emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), u_y, v_y, &emlrtMCI),
                     "<output of feval>");
    x_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&x_y, m);
    ab_y = NULL;
    m = emlrtCreateCharArray(2, &iv9[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 6, m, &h_u[0]);
    emlrtAssign(&ab_y, m);
    cb_y = NULL;
    m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)emlrtMxGetData(m) = -1;
    emlrtAssign(&cb_y, m);
    emlrt_marshallIn(
        c_feval(emlrt_marshallOut(b_cv), x_y, ab_y, cb_y, &emlrtMCI),
        "<output of feval>");
  }
  w_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&w_y, m);
  for (i = 0; i < 11; i++) {
    g_u[i] = ' ';
  }
  y_y = NULL;
  m = emlrtCreateCharArray(2, &iv8[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 11, m, &g_u[0]);
  emlrtAssign(&y_y, m);
  emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), w_y, y_y, &emlrtMCI),
                   "<output of feval>");
  bb_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&bb_y, m);
  db_y = NULL;
  m = emlrtCreateCharArray(2, &iv10[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 3, m, &i_u[0]);
  emlrtAssign(&db_y, m);
  eb_y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = workingset_nActiveConstr;
  emlrtAssign(&eb_y, m);
  emlrt_marshallIn(
      c_feval(emlrt_marshallOut(b_cv), bb_y, db_y, eb_y, &emlrtMCI),
      "<output of feval>");
  fb_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&fb_y, m);
  gb_y = NULL;
  m = emlrtCreateCharArray(2, &iv11[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 4, m, &e_u[0]);
  emlrtAssign(&gb_y, m);
  emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), fb_y, gb_y, &emlrtMCI),
                   "<output of feval>");
  switch (PROBLEM_TYPE) {
  case 1:
    ib_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&ib_y, m);
    mb_y = NULL;
    m = emlrtCreateCharArray(2, &iv13[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 9, m, &k_u[0]);
    emlrtAssign(&mb_y, m);
    emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), ib_y, mb_y, &emlrtMCI),
                     "<output of feval>");
    break;
  case 2:
    jb_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&jb_y, m);
    nb_y = NULL;
    m = emlrtCreateCharArray(2, &iv14[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 11, m, &l_u[0]);
    emlrtAssign(&nb_y, m);
    emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), jb_y, nb_y, &emlrtMCI),
                     "<output of feval>");
    break;
  case 4:
    kb_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&kb_y, m);
    ob_y = NULL;
    m = emlrtCreateCharArray(2, &iv15[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 13, m, &cv[0]);
    emlrtAssign(&ob_y, m);
    emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), kb_y, ob_y, &emlrtMCI),
                     "<output of feval>");
    break;
  default:
    hb_y = NULL;
    m = emlrtCreateDoubleScalar(1.0);
    emlrtAssign(&hb_y, m);
    lb_y = NULL;
    m = emlrtCreateCharArray(2, &iv12[0]);
    emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 6, m, &j_u[0]);
    emlrtAssign(&lb_y, m);
    emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), hb_y, lb_y, &emlrtMCI),
                     "<output of feval>");
    break;
  }
  pb_y = NULL;
  m = emlrtCreateDoubleScalar(1.0);
  emlrtAssign(&pb_y, m);
  qb_y = NULL;
  m = emlrtCreateCharArray(2, &iv16[0]);
  emlrtInitCharArrayR2013a(emlrtRootTLSGlobal, 2, m, &m_u[0]);
  emlrtAssign(&qb_y, m);
  emlrt_marshallIn(feval(emlrt_marshallOut(b_cv), pb_y, qb_y, &emlrtMCI),
                   "<output of feval>");
}

/* End of code generation (printInfo.c) */
