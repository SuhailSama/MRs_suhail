/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * printInfo.h
 *
 * Code generation for function 'printInfo'
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
void printInfo(boolean_T newBlocking, int32_T PROBLEM_TYPE, real_T alpha,
               real_T stepNorm, int32_T activeConstrChangedType,
               int32_T localActiveConstrIdx, int32_T activeSetChangeID,
               real_T solution_fstar, real_T solution_firstorderopt,
               real_T solution_maxConstr, int32_T solution_iterations,
               const emxArray_int32_T *workingset_indexLB,
               const emxArray_int32_T *workingset_indexUB,
               int32_T workingset_nActiveConstr);

/* End of code generation (printInfo.h) */
