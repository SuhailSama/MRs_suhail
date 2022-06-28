/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * driver.c
 *
 * Code generation for function 'driver'
 *
 */

/* Include files */
#include "driver.h"
#include "PresolveWorkingSet.h"
#include "computeFval.h"
#include "iterate.h"
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "blas.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void driver(const real_T H[2601], const emxArray_real_T *f,
            e_struct_T *solution, i_struct_T *memspace, j_struct_T *workingset,
            f_struct_T *qrmanager, g_struct_T *cholmanager,
            h_struct_T *objective, const d_struct_T *options,
            d_struct_T *runTimeOptions)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  real_T maxConstr_new;
  int32_T PROBTYPE_ORIG;
  int32_T i;
  int32_T i1;
  int32_T idxStartIneq;
  int32_T idx_global;
  int32_T mEqFixed;
  int32_T nVar_tmp_tmp;
  boolean_T exitg1;
  boolean_T guard1 = false;
  solution->iterations = 0;
  runTimeOptions->RemainFeasible = (options->PricingTolerance <= 0.0);
  nVar_tmp_tmp = workingset->nVar;
  guard1 = false;
  if (workingset->probType == 3) {
    i = workingset->sizes[0];
    for (mEqFixed = 0; mEqFixed < i; mEqFixed++) {
      solution->xstar->data[workingset->indexFixed->data[mEqFixed] - 1] =
          workingset->ub->data[workingset->indexFixed->data[mEqFixed] - 1];
    }
    i = workingset->sizes[3];
    for (mEqFixed = 0; mEqFixed < i; mEqFixed++) {
      if (workingset->isActiveConstr
              ->data[(workingset->isActiveIdx[3] + mEqFixed) - 1]) {
        solution->xstar->data[workingset->indexLB->data[mEqFixed] - 1] =
            -workingset->lb->data[workingset->indexLB->data[mEqFixed] - 1];
      }
    }
    i = workingset->sizes[4];
    for (mEqFixed = 0; mEqFixed < i; mEqFixed++) {
      if (workingset->isActiveConstr
              ->data[(workingset->isActiveIdx[4] + mEqFixed) - 1]) {
        solution->xstar->data[workingset->indexUB->data[mEqFixed] - 1] =
            workingset->ub->data[workingset->indexUB->data[mEqFixed] - 1];
      }
    }
    PresolveWorkingSet(solution, memspace, workingset, qrmanager, options);
    if (solution->state >= 0) {
      guard1 = true;
    }
  } else {
    solution->state = 82;
    guard1 = true;
  }
  if (guard1) {
    solution->iterations = 0;
    solution->maxConstr = maxConstraintViolation(workingset, solution->xstar);
    maxConstr_new =
        options->ConstraintTolerance * runTimeOptions->ConstrRelTolFactor;
    if (solution->maxConstr > maxConstr_new) {
      PROBTYPE_ORIG = workingset->probType;
      i = workingset->nVar;
      i1 = workingset->nVar;
      solution->xstar->data[workingset->nVar] = solution->maxConstr + 1.0;
      if (workingset->probType == 3) {
        idxStartIneq = 1;
      } else {
        idxStartIneq = 4;
      }
      setProblemType(workingset, idxStartIneq);
      idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
      mEqFixed = workingset->nActiveConstr;
      for (idx_global = idxStartIneq; idx_global <= mEqFixed; idx_global++) {
        workingset->isActiveConstr
            ->data[(workingset->isActiveIdx
                        [workingset->Wid->data[idx_global - 1] - 1] +
                    workingset->Wlocalidx->data[idx_global - 1]) -
                   2] = false;
      }
      workingset->nWConstr[2] = 0;
      workingset->nWConstr[3] = 0;
      workingset->nWConstr[4] = 0;
      workingset->nActiveConstr =
          workingset->nWConstr[0] + workingset->nWConstr[1];
      objective->prev_objtype = objective->objtype;
      objective->prev_nvar = objective->nvar;
      objective->prev_hasLinear = objective->hasLinear;
      objective->objtype = 5;
      objective->nvar = i1 + 1;
      objective->gammaScalar = 1.0;
      objective->hasLinear = true;
      solution->fstar = computeFval(objective, memspace->workspace_double, H, f,
                                    solution->xstar);
      solution->state = 5;
      iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
              objective, options->SolverName, 1.4901161193847657E-10,
              options->ConstraintTolerance, maxConstr_new,
              options->PricingTolerance, options->IterDisplayQP,
              runTimeOptions);
      if (workingset->isActiveConstr
              ->data[(workingset->isActiveIdx[3] + workingset->sizes[3]) - 2]) {
        mEqFixed = workingset->sizes[0] + workingset->sizes[1];
        exitg1 = false;
        while ((!exitg1) && (mEqFixed + 1 <= workingset->nActiveConstr)) {
          if ((workingset->Wid->data[mEqFixed] == 4) &&
              (workingset->Wlocalidx->data[mEqFixed] == workingset->sizes[3])) {
            removeConstr(workingset, mEqFixed + 1);
            exitg1 = true;
          } else {
            mEqFixed++;
          }
        }
      }
      idxStartIneq = workingset->nActiveConstr;
      mEqFixed = workingset->sizes[0] + workingset->sizes[1];
      while ((idxStartIneq > mEqFixed) && (idxStartIneq > i)) {
        removeConstr(workingset, idxStartIneq);
        idxStartIneq--;
      }
      solution->maxConstr = solution->xstar->data[i1];
      setProblemType(workingset, PROBTYPE_ORIG);
      objective->objtype = objective->prev_objtype;
      objective->nvar = objective->prev_nvar;
      objective->hasLinear = objective->prev_hasLinear;
      if (solution->state != 0) {
        solution->maxConstr =
            maxConstraintViolation(workingset, solution->xstar);
        if (solution->maxConstr > maxConstr_new) {
          idxStartIneq = workingset->mConstrMax;
          for (mEqFixed = 0; mEqFixed < idxStartIneq; mEqFixed++) {
            solution->lambda->data[mEqFixed] = 0.0;
          }
          solution->fstar = computeFval(objective, memspace->workspace_double,
                                        H, f, solution->xstar);
          solution->state = -2;
        } else {
          if (solution->maxConstr > 0.0) {
            if (nVar_tmp_tmp >= 1) {
              n_t = (ptrdiff_t)nVar_tmp_tmp;
              incx_t = (ptrdiff_t)1;
              incy_t = (ptrdiff_t)1;
              dcopy(&n_t, &solution->xstar->data[0], &incx_t,
                    &solution->searchDir->data[0], &incy_t);
            }
            PresolveWorkingSet(solution, memspace, workingset, qrmanager,
                               options);
            maxConstr_new = maxConstraintViolation(workingset, solution->xstar);
            if (maxConstr_new >= solution->maxConstr) {
              solution->maxConstr = maxConstr_new;
              if (nVar_tmp_tmp >= 1) {
                n_t = (ptrdiff_t)nVar_tmp_tmp;
                incx_t = (ptrdiff_t)1;
                incy_t = (ptrdiff_t)1;
                dcopy(&n_t, &solution->searchDir->data[0], &incx_t,
                      &solution->xstar->data[0], &incy_t);
              }
            }
          }
          iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
                  objective, options->SolverName, options->StepTolerance,
                  options->ConstraintTolerance, options->ObjectiveLimit,
                  options->PricingTolerance, options->IterDisplayQP,
                  runTimeOptions);
        }
      }
    } else {
      iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
              objective, options->SolverName, options->StepTolerance,
              options->ConstraintTolerance, options->ObjectiveLimit,
              options->PricingTolerance, options->IterDisplayQP,
              runTimeOptions);
    }
  }
}

/* End of code generation (driver.c) */
