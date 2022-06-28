/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * step.h
 *
 * Code generation for function 'step'
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
boolean_T step(int32_T *STEP_TYPE, real_T Hessian[2601], const real_T lb[51],
               const real_T ub[51], e_struct_T *TrialState,
               struct_T *MeritFunction, i_struct_T *memspace,
               j_struct_T *WorkingSet, f_struct_T *QRManager,
               g_struct_T *CholManager, h_struct_T *QPObjective,
               d_struct_T *qpoptions);

/* End of code generation (step.h) */
