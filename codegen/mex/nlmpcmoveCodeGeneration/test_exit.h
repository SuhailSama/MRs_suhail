/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * test_exit.h
 *
 * Code generation for function 'test_exit'
 *
 */

#pragma once

/* Include files */
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void b_test_exit(b_struct_T *Flags, i_struct_T *memspace,
                 struct_T *MeritFunction,
                 const emxArray_real_T *fscales_lineq_constraint,
                 const emxArray_real_T *fscales_cineq_constraint,
                 j_struct_T *WorkingSet, e_struct_T *TrialState,
                 f_struct_T *QRManager, const real_T lb[51],
                 const real_T ub[51]);

void test_exit(i_struct_T *memspace, struct_T *MeritFunction,
               const emxArray_real_T *fscales_lineq_constraint,
               const emxArray_real_T *fscales_cineq_constraint,
               j_struct_T *WorkingSet, e_struct_T *TrialState,
               f_struct_T *QRManager, const real_T lb[51], const real_T ub[51],
               boolean_T *Flags_gradOK, boolean_T *Flags_fevalOK,
               boolean_T *Flags_done, boolean_T *Flags_stepAccepted,
               boolean_T *Flags_failedLineSearch, int32_T *Flags_stepType);

/* End of code generation (test_exit.h) */
