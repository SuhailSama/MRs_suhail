/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * factoryConstruct2.h
 *
 * Code generation for function 'factoryConstruct2'
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
void c_factoryConstruct(const k_struct_T *objfun_workspace_runtimedata,
                        const real_T c_objfun_workspace_userdata_Cur[3],
                        const real_T c_objfun_workspace_userdata_Las[2],
                        const emxArray_real_T *c_objfun_workspace_userdata_Ref,
                        const emxArray_real_T *c_objfun_workspace_userdata_MVT,
                        const real_T c_objfun_workspace_userdata_MVI[2],
                        const k_struct_T *nonlin_workspace_runtimedata,
                        const l_struct_T *nonlin_workspace_userdata,
                        int32_T mCineq, const real_T lb[51],
                        const real_T ub[51], o_struct_T *obj);

/* End of code generation (factoryConstruct2.h) */
