/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkVectorNonFinite.h
 *
 * Code generation for function 'checkVectorNonFinite'
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
int32_T b_checkVectorNonFinite(int32_T N, const real_T vec[32], int32_T iv0);

int32_T checkVectorNonFinite(int32_T N, const emxArray_real_T *vec,
                             int32_T iv0);

/* End of code generation (checkVectorNonFinite.h) */
