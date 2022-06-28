/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fmincon.h
 *
 * Code generation for function 'fmincon'
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
void fmincon(const k_struct_T *fun_workspace_runtimedata,
             const real_T c_fun_workspace_userdata_Curren[3],
             const real_T fun_workspace_userdata_LastMV[2],
             const emxArray_real_T *c_fun_workspace_userdata_Refere,
             const emxArray_real_T *fun_workspace_userdata_MVTarget,
             const real_T fun_workspace_userdata_MVIndex[2],
             const real_T x0[51], const emxArray_real_T *Aineq,
             const emxArray_real_T *bineq, const real_T lb[51],
             const real_T ub[51],
             const k_struct_T *nonlcon_workspace_runtimedata,
             const l_struct_T *nonlcon_workspace_userdata, real_T x[51],
             real_T *fval, real_T *exitflag, c_struct_T *output);

/* End of code generation (fmincon.h) */
