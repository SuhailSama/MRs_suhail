/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * iterate.c
 *
 * Code generation for function 'iterate'
 *
 */

/* Include files */
#include "iterate.h"
#include "addBoundToActiveSetMatrix_.h"
#include "checkStoppingAndUpdateFval.h"
#include "computeFval_ReuseHx.h"
#include "computeGrad_StoreHx.h"
#include "computeQ_.h"
#include "compute_deltax.h"
#include "deleteColMoveEnd.h"
#include "factorQR.h"
#include "feasibleratiotest.h"
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "printHeader.h"
#include "printInfo.h"
#include "printInitialInfo.h"
#include "ratiotest.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "squareQ_appendCol.h"
#include "xgemv.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void iterate(const real_T H[2601], const emxArray_real_T *f,
             e_struct_T *solution, i_struct_T *memspace, j_struct_T *workingset,
             f_struct_T *qrmanager, g_struct_T *cholmanager,
             h_struct_T *objective, const char_T options_SolverName[7],
             real_T options_StepTolerance, real_T options_ConstraintTolerance,
             real_T options_ObjectiveLimit, real_T options_PricingTolerance,
             boolean_T options_IterDisplayQP, const d_struct_T *runTimeOptions)
{
  static const char_T b[7] = {'f', 'm', 'i', 'n', 'c', 'o', 'n'};
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t lda_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  real_T alpha;
  real_T beta1;
  real_T minLambda;
  real_T normDelta;
  real_T tolDelta;
  int32_T TYPE;
  int32_T activeConstrChangedType;
  int32_T activeSetChangeID;
  int32_T exitg1;
  int32_T globalActiveConstrIdx;
  int32_T i;
  int32_T iAineq0;
  int32_T iAw0;
  int32_T idx;
  int32_T localActiveConstrIdx;
  int32_T nVar;
  char_T DIAGA1;
  char_T TRANSA1;
  char_T UPLO1;
  boolean_T b_guard1 = false;
  boolean_T b_guard2 = false;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T newBlocking;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  TYPE = objective->objtype;
  tolDelta = 6.7434957617430445E-7;
  nVar = workingset->nVar;
  activeConstrChangedType = 1;
  localActiveConstrIdx = 0;
  globalActiveConstrIdx = 0;
  computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = computeFval_ReuseHx(objective, memspace->workspace_double,
                                        f, solution->xstar);
  if (solution->iterations < runTimeOptions->MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }
  iAineq0 = workingset->mConstrMax;
  for (iAw0 = 0; iAw0 < iAineq0; iAw0++) {
    solution->lambda->data[iAw0] = 0.0;
  }
  if ((solution->iterations == 0) && options_IterDisplayQP) {
    printHeader();
    printInitialInfo(workingset->probType, solution->fstar,
                     solution->iterations, workingset->nActiveConstr);
  }
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      newBlocking = false;
      guard1 = false;
      guard2 = false;
      if (subProblemChanged) {
        switch (activeSetChangeID) {
        case 1:
          squareQ_appendCol(qrmanager, workingset->ATwset,
                            workingset->ldA * (workingset->nActiveConstr - 1) +
                                1);
          break;
        case -1:
          deleteColMoveEnd(qrmanager, globalActiveConstrIdx);
          break;
        default:
          factorQR(qrmanager, workingset->ATwset, nVar,
                   workingset->nActiveConstr, workingset->ldA);
          computeQ_(qrmanager, qrmanager->mrows);
          break;
        }
        compute_deltax(H, solution, memspace, qrmanager, cholmanager, objective,
                       memcmp(&options_SolverName[0], &b[0], 7) == 0);
        if (solution->state != -5) {
          exitg1 = 1;
        } else {
          if (nVar < 1) {
            normDelta = 0.0;
          } else {
            n_t = (ptrdiff_t)nVar;
            incx_t = (ptrdiff_t)1;
            normDelta = dnrm2(&n_t, &solution->searchDir->data[0], &incx_t);
          }
          if ((normDelta < options_StepTolerance) ||
              (workingset->nActiveConstr >= nVar)) {
            guard2 = true;
          } else {
            updateFval = (TYPE == 5);
            if (updateFval || runTimeOptions->RemainFeasible) {
              feasibleratiotest(
                  solution->xstar, solution->searchDir,
                  memspace->workspace_double, workingset->nVar, workingset->ldA,
                  workingset->Aineq, workingset->bineq, workingset->lb,
                  workingset->ub, workingset->indexLB, workingset->indexUB,
                  workingset->sizes, workingset->isActiveIdx,
                  workingset->isActiveConstr, workingset->nWConstr, updateFval,
                  options_ConstraintTolerance, &alpha, &newBlocking,
                  &activeConstrChangedType, &localActiveConstrIdx);
            } else {
              ratiotest(solution->xstar, solution->searchDir,
                        memspace->workspace_double, workingset->nVar,
                        workingset->ldA, workingset->Aineq, workingset->bineq,
                        workingset->lb, workingset->ub, workingset->indexLB,
                        workingset->indexUB, workingset->sizes,
                        workingset->isActiveIdx, workingset->isActiveConstr,
                        workingset->nWConstr, options_ConstraintTolerance,
                        &tolDelta, &alpha, &newBlocking,
                        &activeConstrChangedType, &localActiveConstrIdx);
            }
            if (newBlocking) {
              switch (activeConstrChangedType) {
              case 3:
                workingset->nWConstr[2]++;
                workingset->isActiveConstr
                    ->data[(workingset->isActiveIdx[2] + localActiveConstrIdx) -
                           2] = true;
                workingset->nActiveConstr++;
                workingset->Wid->data[workingset->nActiveConstr - 1] = 3;
                workingset->Wlocalidx->data[workingset->nActiveConstr - 1] =
                    localActiveConstrIdx;
                iAineq0 = workingset->ldA * (localActiveConstrIdx - 1);
                iAw0 = workingset->ldA * (workingset->nActiveConstr - 1);
                i = workingset->nVar - 1;
                for (idx = 0; idx <= i; idx++) {
                  workingset->ATwset->data[iAw0 + idx] =
                      workingset->Aineq->data[iAineq0 + idx];
                }
                workingset->bwset->data[workingset->nActiveConstr - 1] =
                    workingset->bineq->data[localActiveConstrIdx - 1];
                break;
              case 4:
                addBoundToActiveSetMatrix_(workingset, 4, localActiveConstrIdx);
                break;
              default:
                addBoundToActiveSetMatrix_(workingset, 5, localActiveConstrIdx);
                break;
              }
              activeSetChangeID = 1;
            } else {
              if (objective->objtype == 5) {
                if (objective->nvar < 1) {
                  minLambda = 0.0;
                } else {
                  n_t = (ptrdiff_t)objective->nvar;
                  incx_t = (ptrdiff_t)1;
                  minLambda =
                      dnrm2(&n_t, &solution->searchDir->data[0], &incx_t);
                }
                if (minLambda >
                    100.0 * (real_T)objective->nvar * 1.4901161193847656E-8) {
                  solution->state = 3;
                } else {
                  solution->state = 4;
                }
              }
              subProblemChanged = false;
              if (workingset->nActiveConstr == 0) {
                solution->state = 1;
              }
            }
            if (nVar >= 1) {
              n_t = (ptrdiff_t)nVar;
              incx_t = (ptrdiff_t)1;
              incy_t = (ptrdiff_t)1;
              daxpy(&n_t, &alpha, &solution->searchDir->data[0], &incx_t,
                    &solution->xstar->data[0], &incy_t);
            }
            computeGrad_StoreHx(objective, H, f, solution->xstar);
            updateFval = true;
            guard1 = true;
          }
        }
      } else {
        for (iAw0 = 0; iAw0 < nVar; iAw0++) {
          solution->searchDir->data[iAw0] = 0.0;
        }
        normDelta = 0.0;
        guard2 = true;
      }
      if (guard2) {
        iAineq0 = qrmanager->ncols;
        if (qrmanager->ncols > 0) {
          b_guard1 = false;
          if (objective->objtype != 4) {
            minLambda =
                100.0 * (real_T)qrmanager->mrows * 2.2204460492503131E-16;
            if ((qrmanager->mrows > 0) && (qrmanager->ncols > 0)) {
              updateFval = true;
            } else {
              updateFval = false;
            }
            if (updateFval) {
              idx = iAineq0;
              b_guard2 = false;
              if (qrmanager->mrows < qrmanager->ncols) {
                iAw0 =
                    qrmanager->mrows + qrmanager->ldq * (qrmanager->ncols - 1);
                while ((idx > qrmanager->mrows) &&
                       (muDoubleScalarAbs(qrmanager->QR->data[iAw0 - 1]) >=
                        minLambda)) {
                  idx--;
                  iAw0 -= qrmanager->ldq;
                }
                updateFval = (idx == qrmanager->mrows);
                if (updateFval) {
                  b_guard2 = true;
                }
              } else {
                b_guard2 = true;
              }
              if (b_guard2) {
                iAw0 = idx + qrmanager->ldq * (idx - 1);
                while ((idx >= 1) &&
                       (muDoubleScalarAbs(qrmanager->QR->data[iAw0 - 1]) >=
                        minLambda)) {
                  idx--;
                  iAw0 = (iAw0 - qrmanager->ldq) - 1;
                }
                updateFval = (idx == 0);
              }
            }
            if (!updateFval) {
              solution->state = -7;
            } else {
              b_guard1 = true;
            }
          } else {
            b_guard1 = true;
          }
          if (b_guard1) {
            b_xgemv(qrmanager->mrows, qrmanager->ncols, qrmanager->Q,
                    qrmanager->ldq, objective->grad,
                    memspace->workspace_double);
            if (qrmanager->ncols >= 1) {
              DIAGA1 = 'N';
              TRANSA1 = 'N';
              UPLO1 = 'U';
              n_t = (ptrdiff_t)qrmanager->ncols;
              lda_t = (ptrdiff_t)qrmanager->ldq;
              incx_t = (ptrdiff_t)1;
              dtrsv(&UPLO1, &TRANSA1, &DIAGA1, &n_t, &qrmanager->QR->data[0],
                    &lda_t, &memspace->workspace_double->data[0], &incx_t);
            }
            for (idx = 0; idx < iAineq0; idx++) {
              solution->lambda->data[idx] =
                  -memspace->workspace_double->data[idx];
            }
          }
        }
        if ((solution->state != -7) || (workingset->nActiveConstr > nVar)) {
          iAw0 = 0;
          minLambda = options_PricingTolerance *
                      runTimeOptions->ProbRelTolFactor * (real_T)(TYPE != 5);
          i = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
          iAineq0 = workingset->nActiveConstr;
          for (idx = i; idx <= iAineq0; idx++) {
            beta1 = solution->lambda->data[idx - 1];
            if (beta1 < minLambda) {
              minLambda = beta1;
              iAw0 = idx;
            }
          }
          if (iAw0 == 0) {
            solution->state = 1;
          } else {
            activeSetChangeID = -1;
            globalActiveConstrIdx = iAw0;
            subProblemChanged = true;
            activeConstrChangedType = workingset->Wid->data[iAw0 - 1];
            localActiveConstrIdx = workingset->Wlocalidx->data[iAw0 - 1];
            removeConstr(workingset, iAw0);
            solution->lambda->data[iAw0 - 1] = 0.0;
          }
        } else {
          iAw0 = workingset->nActiveConstr;
          activeSetChangeID = 0;
          globalActiveConstrIdx = workingset->nActiveConstr;
          subProblemChanged = true;
          iAineq0 = workingset->nActiveConstr - 1;
          activeConstrChangedType = workingset->Wid->data[iAineq0];
          localActiveConstrIdx = workingset->Wlocalidx->data[iAineq0];
          removeConstr(workingset, workingset->nActiveConstr);
          solution->lambda->data[iAw0 - 1] = 0.0;
        }
        updateFval = false;
        alpha = rtNaN;
        guard1 = true;
      }
      if (guard1) {
        checkStoppingAndUpdateFval(
            &activeSetChangeID, f, solution, memspace, objective, workingset,
            qrmanager, options_ConstraintTolerance, options_ObjectiveLimit,
            options_IterDisplayQP, runTimeOptions->MaxIterations,
            runTimeOptions->ConstrRelTolFactor, updateFval);
        if (options_IterDisplayQP) {
          if (solution->iterations - solution->iterations / 50 * 50 == 0) {
            printHeader();
          } else {
            solution->maxConstr =
                maxConstraintViolation(workingset, solution->xstar);
          }
          if (workingset->nVar >= 1) {
            n_t = (ptrdiff_t)workingset->nVar;
            incx_t = (ptrdiff_t)1;
            incy_t = (ptrdiff_t)1;
            dcopy(&n_t, &objective->grad->data[0], &incx_t,
                  &memspace->workspace_double->data[0], &incy_t);
          }
          if ((workingset->nVar >= 1) && (workingset->nActiveConstr >= 1)) {
            minLambda = 1.0;
            beta1 = 1.0;
            DIAGA1 = 'N';
            m_t = (ptrdiff_t)workingset->nVar;
            n_t = (ptrdiff_t)workingset->nActiveConstr;
            lda_t = (ptrdiff_t)workingset->ldA;
            incx_t = (ptrdiff_t)1;
            incy_t = (ptrdiff_t)1;
            dgemv(&DIAGA1, &m_t, &n_t, &minLambda, &workingset->ATwset->data[0],
                  &lda_t, &solution->lambda->data[0], &incx_t, &beta1,
                  &memspace->workspace_double->data[0], &incy_t);
          }
          if (workingset->nVar < 1) {
            iAineq0 = 0;
          } else {
            n_t = (ptrdiff_t)workingset->nVar;
            incx_t = (ptrdiff_t)1;
            n_t = idamax(&n_t, &memspace->workspace_double->data[0], &incx_t);
            iAineq0 = (int32_T)n_t;
          }
          solution->firstorderopt =
              muDoubleScalarAbs(memspace->workspace_double->data[iAineq0 - 1]);
          printInfo(newBlocking, workingset->probType, alpha, normDelta,
                    activeConstrChangedType, localActiveConstrIdx,
                    activeSetChangeID, solution->fstar, solution->firstorderopt,
                    solution->maxConstr, solution->iterations,
                    workingset->indexLB, workingset->indexUB,
                    workingset->nActiveConstr);
        }
      }
    } else {
      if (!updateFval) {
        solution->fstar = computeFval_ReuseHx(
            objective, memspace->workspace_double, f, solution->xstar);
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/* End of code generation (iterate.c) */
