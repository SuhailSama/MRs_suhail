/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * all.c
 *
 * Code generation for function 'all'
 *
 */

/* Include files */
#include "all.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void all(const boolean_T x[30], boolean_T y[3])
{
  int32_T ix;
  boolean_T exitg1;
  y[0] = true;
  y[1] = true;
  y[2] = true;
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix <= 10)) {
    if (!x[ix - 1]) {
      y[0] = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }
  ix = 11;
  exitg1 = false;
  while ((!exitg1) && (ix <= 20)) {
    if (!x[ix - 1]) {
      y[1] = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }
  ix = 21;
  exitg1 = false;
  while ((!exitg1) && (ix <= 30)) {
    if (!x[ix - 1]) {
      y[2] = false;
      exitg1 = true;
    } else {
      ix++;
    }
  }
}

/* End of code generation (all.c) */
