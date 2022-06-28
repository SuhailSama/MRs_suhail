/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkMatrixNonFinite.h
 *
 * Code generation for function 'checkMatrixNonFinite'
 *
 */

#pragma once

/* Include files */
#include "nlmpcmoveCodeGeneration_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
int32_T checkMatrixNonFinite(int32_T mrows, int32_T ncols,
                             const emxArray_real_T *mat, int32_T col0,
                             int32_T ldm);

/* End of code generation (checkMatrixNonFinite.h) */
