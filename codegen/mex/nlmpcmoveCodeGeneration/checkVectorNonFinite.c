/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkVectorNonFinite.c
 *
 * Code generation for function 'checkVectorNonFinite'
 *
 */

/* Include files */
#include "checkVectorNonFinite.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
int32_T b_checkVectorNonFinite(int32_T N, const real_T vec[32], int32_T iv0)
{
  real_T allFinite_tmp;
  int32_T idx_current;
  int32_T idx_end;
  int32_T status;
  boolean_T allFinite;
  status = 1;
  allFinite = true;
  idx_current = iv0;
  idx_end = (iv0 + N) - 1;
  while (allFinite && (idx_current <= idx_end)) {
    allFinite_tmp = vec[idx_current - 1];
    allFinite = ((!muDoubleScalarIsInf(allFinite_tmp)) &&
                 (!muDoubleScalarIsNaN(allFinite_tmp)));
    idx_current++;
  }
  if (!allFinite) {
    idx_current -= 2;
    if (muDoubleScalarIsNaN(vec[idx_current])) {
      status = -3;
    } else if (vec[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }
  return status;
}

int32_T checkVectorNonFinite(int32_T N, const emxArray_real_T *vec, int32_T iv0)
{
  const real_T *vec_data;
  real_T allFinite_tmp;
  int32_T idx_current;
  int32_T idx_end;
  int32_T status;
  boolean_T allFinite;
  vec_data = vec->data;
  status = 1;
  allFinite = true;
  idx_current = iv0;
  idx_end = (iv0 + N) - 1;
  while (allFinite && (idx_current <= idx_end)) {
    allFinite_tmp = vec_data[idx_current - 1];
    allFinite = ((!muDoubleScalarIsInf(allFinite_tmp)) &&
                 (!muDoubleScalarIsNaN(allFinite_tmp)));
    idx_current++;
  }
  if (!allFinite) {
    idx_current -= 2;
    if (muDoubleScalarIsNaN(vec_data[idx_current])) {
      status = -3;
    } else if (vec_data[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }
  return status;
}

/* End of code generation (checkVectorNonFinite.c) */
