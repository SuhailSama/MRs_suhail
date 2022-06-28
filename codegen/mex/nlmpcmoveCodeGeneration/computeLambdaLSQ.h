/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeLambdaLSQ.h
 *
 * Code generation for function 'computeLambdaLSQ'
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
void computeLambdaLSQ(int32_T nVar, int32_T mConstr, f_struct_T *QRManager,
                      const emxArray_real_T *ATwset, int32_T ldA,
                      const emxArray_real_T *grad, emxArray_real_T *lambdaLSQ,
                      emxArray_real_T *workspace);

/* End of code generation (computeLambdaLSQ.h) */
