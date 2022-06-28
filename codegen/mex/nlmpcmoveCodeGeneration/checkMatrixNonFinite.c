/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkMatrixNonFinite.c
 *
 * Code generation for function 'checkMatrixNonFinite'
 *
 */

/* Include files */
#include "checkMatrixNonFinite.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include <string.h>

/* Function Definitions */
int32_T checkMatrixNonFinite(int32_T mrows, int32_T ncols,
                             const emxArray_real_T *mat, int32_T col0,
                             int32_T ldm)
{
  const real_T *mat_data;
  int32_T col;
  int32_T col_end;
  int32_T idx_mat;
  int32_T row;
  int32_T status;
  boolean_T allFinite;
  mat_data = mat->data;
  status = 1;
  allFinite = true;
  row = -1;
  col = col0;
  col_end = (col0 + ncols) - 1;
  while (allFinite && (col <= col_end)) {
    row = -1;
    while (allFinite && (row + 2 <= mrows)) {
      idx_mat = (row + ldm * (col - 1)) + 1;
      allFinite = ((!muDoubleScalarIsInf(mat_data[idx_mat])) &&
                   (!muDoubleScalarIsNaN(mat_data[idx_mat])));
      row++;
    }
    col++;
  }
  if (!allFinite) {
    idx_mat = row + ldm * (col - 2);
    if (muDoubleScalarIsNaN(mat_data[idx_mat])) {
      status = -3;
    } else if (mat_data[idx_mat] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  }
  return status;
}

/* End of code generation (checkMatrixNonFinite.c) */
