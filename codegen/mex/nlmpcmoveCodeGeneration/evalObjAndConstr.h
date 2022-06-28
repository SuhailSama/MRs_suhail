/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * evalObjAndConstr.h
 *
 * Code generation for function 'evalObjAndConstr'
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
void evalObjAndConstr(const real_T c_obj_objfun_workspace_runtimed[3],
                      const real_T d_obj_objfun_workspace_runtimed[2],
                      const emxArray_real_T *e_obj_objfun_workspace_runtimed,
                      const real_T f_obj_objfun_workspace_runtimed[30],
                      const real_T g_obj_objfun_workspace_runtimed[20],
                      const real_T h_obj_objfun_workspace_runtimed[20],
                      real_T i_obj_objfun_workspace_runtimed,
                      const emxArray_real_T *j_obj_objfun_workspace_runtimed,
                      const real_T c_obj_nonlcon_workspace_runtime[3],
                      const real_T d_obj_nonlcon_workspace_runtime[30],
                      const real_T e_obj_nonlcon_workspace_runtime[30],
                      int32_T obj_mCineq, int32_T obj_mCeq,
                      boolean_T obj_ScaleProblem, const real_T x[51],
                      emxArray_real_T *Cineq_workspace, int32_T ineq0,
                      real_T Ceq_workspace[32], int32_T eq0,
                      const emxArray_real_T *scales_cineq_constraint,
                      const real_T scales_ceq_constraint[32], real_T *fval,
                      int32_T *status);

/* End of code generation (evalObjAndConstr.h) */
