/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkStoppingAndUpdateFval.c
 *
 * Code generation for function 'checkStoppingAndUpdateFval'
 *
 */

/* Include files */
#include "checkStoppingAndUpdateFval.h"
#include "computeFval_ReuseHx.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void checkStoppingAndUpdateFval(
    int32_T *activeSetChangeID, const emxArray_real_T *f, e_struct_T *solution,
    i_struct_T *memspace, const h_struct_T *objective, j_struct_T *workingset,
    f_struct_T *qrmanager, real_T options_ConstraintTolerance,
    real_T options_ObjectiveLimit, boolean_T options_IterDisplayQP,
    int32_T runTimeOptions_MaxIterations,
    real_T c_runTimeOptions_ConstrRelTolFa, boolean_T updateFval)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  real_T tempMaxConstr;
  int32_T idx;
  int32_T nVar;
  boolean_T nonDegenerateWset;
  solution->iterations++;
  nVar = objective->nvar;
  if ((solution->iterations >= runTimeOptions_MaxIterations) &&
      ((solution->state != 1) || (objective->objtype == 5))) {
    solution->state = 0;
  }
  if (solution->iterations - solution->iterations / 50 * 50 == 0) {
    solution->maxConstr = maxConstraintViolation(workingset, solution->xstar);
    tempMaxConstr = solution->maxConstr;
    if (objective->objtype == 5) {
      tempMaxConstr =
          solution->maxConstr - solution->xstar->data[objective->nvar - 1];
    }
    if (tempMaxConstr >
        options_ConstraintTolerance * c_runTimeOptions_ConstrRelTolFa) {
      if (objective->nvar >= 1) {
        n_t = (ptrdiff_t)objective->nvar;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &solution->xstar->data[0], &incx_t,
              &solution->searchDir->data[0], &incy_t);
      }
      nonDegenerateWset =
          feasibleX0ForWorkingSet(memspace->workspace_double,
                                  solution->searchDir, workingset, qrmanager);
      if ((!nonDegenerateWset) && (solution->state != 0)) {
        solution->state = -2;
      }
      *activeSetChangeID = 0;
      tempMaxConstr = maxConstraintViolation(workingset, solution->searchDir);
      if (tempMaxConstr < solution->maxConstr) {
        for (idx = 0; idx < nVar; idx++) {
          solution->xstar->data[idx] = solution->searchDir->data[idx];
        }
        solution->maxConstr = tempMaxConstr;
      }
    }
  }
  if (updateFval &&
      ((options_ObjectiveLimit > rtMinusInf) || options_IterDisplayQP)) {
    solution->fstar = computeFval_ReuseHx(objective, memspace->workspace_double,
                                          f, solution->xstar);
    if ((options_ObjectiveLimit > rtMinusInf) &&
        (solution->fstar < options_ObjectiveLimit) &&
        ((solution->state != 0) || (objective->objtype != 5))) {
      solution->state = 2;
    }
  }
}

/* End of code generation (checkStoppingAndUpdateFval.c) */
