/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * printInitialInfo.h
 *
 * Code generation for function 'printInitialInfo'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void printInitialInfo(int32_T PROBLEM_TYPE, real_T solution_fstar,
                      int32_T solution_iterations,
                      int32_T workingset_nActiveConstr);

/* End of code generation (printInitialInfo.h) */
