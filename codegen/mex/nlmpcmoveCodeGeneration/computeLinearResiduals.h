/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeLinearResiduals.h
 *
 * Code generation for function 'computeLinearResiduals'
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
void computeLinearResiduals(const real_T x[51], int32_T nVar,
                            emxArray_real_T *workspaceIneq, int32_T mLinIneq,
                            const emxArray_real_T *AineqT,
                            const emxArray_real_T *bineq, int32_T ldAi,
                            real_T workspaceEq[32], int32_T mLinEq,
                            const emxArray_real_T *AeqT, int32_T ldAe);

/* End of code generation (computeLinearResiduals.h) */
