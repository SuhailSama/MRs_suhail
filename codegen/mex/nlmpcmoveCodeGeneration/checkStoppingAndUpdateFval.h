/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkStoppingAndUpdateFval.h
 *
 * Code generation for function 'checkStoppingAndUpdateFval'
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
void checkStoppingAndUpdateFval(
    int32_T *activeSetChangeID, const emxArray_real_T *f, e_struct_T *solution,
    i_struct_T *memspace, const h_struct_T *objective, j_struct_T *workingset,
    f_struct_T *qrmanager, real_T options_ConstraintTolerance,
    real_T options_ObjectiveLimit, boolean_T options_IterDisplayQP,
    int32_T runTimeOptions_MaxIterations,
    real_T c_runTimeOptions_ConstrRelTolFa, boolean_T updateFval);

/* End of code generation (checkStoppingAndUpdateFval.h) */
