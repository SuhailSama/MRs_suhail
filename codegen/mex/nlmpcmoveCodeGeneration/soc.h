/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * soc.h
 *
 * Code generation for function 'soc'
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
boolean_T soc(const real_T Hessian[2601], const emxArray_real_T *grad,
              e_struct_T *TrialState, i_struct_T *memspace,
              j_struct_T *WorkingSet, f_struct_T *QRManager,
              g_struct_T *CholManager, h_struct_T *QPObjective,
              const d_struct_T *qpoptions);

/* End of code generation (soc.h) */
