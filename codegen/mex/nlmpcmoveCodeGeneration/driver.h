/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * driver.h
 *
 * Code generation for function 'driver'
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
void driver(const real_T H[2601], const emxArray_real_T *f,
            e_struct_T *solution, i_struct_T *memspace, j_struct_T *workingset,
            f_struct_T *qrmanager, g_struct_T *cholmanager,
            h_struct_T *objective, const d_struct_T *options,
            d_struct_T *runTimeOptions);

/* End of code generation (driver.h) */
