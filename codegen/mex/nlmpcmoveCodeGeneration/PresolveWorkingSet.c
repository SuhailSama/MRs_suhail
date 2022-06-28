/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * PresolveWorkingSet.c
 *
 * Code generation for function 'PresolveWorkingSet'
 *
 */

/* Include files */
#include "PresolveWorkingSet.h"
#include "computeQ_.h"
#include "countsort.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void PresolveWorkingSet(e_struct_T *solution, i_struct_T *memspace,
                        j_struct_T *workingset, f_struct_T *qrmanager,
                        const d_struct_T *options)
{
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t n_t;
  real_T tol;
  real_T x;
  int32_T i;
  int32_T idx;
  int32_T idxDiag;
  int32_T idxStartIneq;
  int32_T mTotalWorkingEq_tmp_tmp;
  int32_T mWorkingFixed;
  int32_T nDepInd;
  int32_T nVar_tmp_tmp;
  boolean_T exitg1;
  boolean_T guard1 = false;
  boolean_T okWorkingSet;
  solution->state = 82;
  nVar_tmp_tmp = workingset->nVar;
  mWorkingFixed = workingset->nWConstr[0];
  mTotalWorkingEq_tmp_tmp = workingset->nWConstr[0] + workingset->nWConstr[1];
  nDepInd = 0;
  if (mTotalWorkingEq_tmp_tmp > 0) {
    for (idxStartIneq = 0; idxStartIneq < mTotalWorkingEq_tmp_tmp;
         idxStartIneq++) {
      for (idxDiag = 0; idxDiag < nVar_tmp_tmp; idxDiag++) {
        qrmanager->QR->data[idxStartIneq + qrmanager->ldq * idxDiag] =
            workingset->ATwset->data[idxDiag + workingset->ldA * idxStartIneq];
      }
    }
    idxStartIneq = mTotalWorkingEq_tmp_tmp - workingset->nVar;
    nDepInd = muIntScalarMax_sint32(0, idxStartIneq);
    for (idx = 0; idx < nVar_tmp_tmp; idx++) {
      qrmanager->jpvt->data[idx] = 0;
    }
    i = mTotalWorkingEq_tmp_tmp * workingset->nVar;
    if (i == 0) {
      qrmanager->mrows = mTotalWorkingEq_tmp_tmp;
      qrmanager->ncols = workingset->nVar;
      qrmanager->minRowCol = 0;
    } else {
      qrmanager->usedPivoting = true;
      qrmanager->mrows = mTotalWorkingEq_tmp_tmp;
      qrmanager->ncols = workingset->nVar;
      qrmanager->minRowCol =
          muIntScalarMin_sint32(mTotalWorkingEq_tmp_tmp, workingset->nVar);
      xgeqp3(qrmanager->QR, mTotalWorkingEq_tmp_tmp, workingset->nVar,
             qrmanager->jpvt, qrmanager->tau);
    }
    tol = 100.0 * (real_T)workingset->nVar * 2.2204460492503131E-16;
    idxStartIneq =
        muIntScalarMin_sint32(workingset->nVar, mTotalWorkingEq_tmp_tmp);
    idxDiag = idxStartIneq + qrmanager->ldq * (idxStartIneq - 1);
    while ((idxDiag > 0) &&
           (muDoubleScalarAbs(qrmanager->QR->data[idxDiag - 1]) < tol)) {
      idxDiag = (idxDiag - qrmanager->ldq) - 1;
      nDepInd++;
    }
    if (nDepInd > 0) {
      computeQ_(qrmanager, qrmanager->mrows);
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= nDepInd - 1)) {
        n_t = (ptrdiff_t)mTotalWorkingEq_tmp_tmp;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        x = ddot(&n_t,
                 &qrmanager->Q->data[qrmanager->ldq *
                                     ((mTotalWorkingEq_tmp_tmp - idx) - 1)],
                 &incx_t, &workingset->bwset->data[0], &incy_t);
        if (muDoubleScalarAbs(x) >= tol) {
          nDepInd = -1;
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }
    if (nDepInd > 0) {
      for (idxDiag = 0; idxDiag < mTotalWorkingEq_tmp_tmp; idxDiag++) {
        if (nVar_tmp_tmp >= 1) {
          n_t = (ptrdiff_t)nVar_tmp_tmp;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dcopy(&n_t, &workingset->ATwset->data[workingset->ldA * idxDiag],
                &incx_t, &qrmanager->QR->data[qrmanager->ldq * idxDiag],
                &incy_t);
        }
      }
      for (idx = 0; idx < mWorkingFixed; idx++) {
        qrmanager->jpvt->data[idx] = 1;
      }
      mWorkingFixed = workingset->nWConstr[0] + 1;
      for (idx = mWorkingFixed; idx <= mTotalWorkingEq_tmp_tmp; idx++) {
        qrmanager->jpvt->data[idx - 1] = 0;
      }
      if (i == 0) {
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = mTotalWorkingEq_tmp_tmp;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = mTotalWorkingEq_tmp_tmp;
        qrmanager->minRowCol = idxStartIneq;
        xgeqp3(qrmanager->QR, workingset->nVar, mTotalWorkingEq_tmp_tmp,
               qrmanager->jpvt, qrmanager->tau);
      }
      for (idx = 0; idx < nDepInd; idx++) {
        memspace->workspace_int->data[idx] =
            qrmanager->jpvt->data[(mTotalWorkingEq_tmp_tmp - nDepInd) + idx];
      }
      countsort(memspace->workspace_int, nDepInd, memspace->workspace_sort, 1,
                mTotalWorkingEq_tmp_tmp);
      for (idx = nDepInd; idx >= 1; idx--) {
        i = workingset->nWConstr[0] + workingset->nWConstr[1];
        if (i != 0) {
          mWorkingFixed = memspace->workspace_int->data[idx - 1];
          if (mWorkingFixed <= i) {
            if ((workingset->nActiveConstr == i) || (mWorkingFixed == i)) {
              workingset->mEqRemoved++;
              workingset->indexEqRemoved[workingset->mEqRemoved - 1] =
                  workingset->Wlocalidx
                      ->data[memspace->workspace_int->data[idx - 1] - 1];
              removeConstr(workingset, memspace->workspace_int->data[idx - 1]);
            } else {
              workingset->mEqRemoved++;
              idxDiag = workingset->Wid->data[mWorkingFixed - 1] - 1;
              idxStartIneq = workingset->Wlocalidx->data[mWorkingFixed - 1];
              workingset->indexEqRemoved[workingset->mEqRemoved - 1] =
                  idxStartIneq;
              workingset->isActiveConstr
                  ->data[(workingset->isActiveIdx[idxDiag] + idxStartIneq) -
                         2] = false;
              workingset->Wid->data[mWorkingFixed - 1] =
                  workingset->Wid->data[i - 1];
              workingset->Wlocalidx->data[mWorkingFixed - 1] =
                  workingset->Wlocalidx->data[i - 1];
              nVar_tmp_tmp = workingset->nVar;
              for (idxStartIneq = 0; idxStartIneq < nVar_tmp_tmp;
                   idxStartIneq++) {
                workingset->ATwset
                    ->data[idxStartIneq +
                           workingset->ldA * (mWorkingFixed - 1)] =
                    workingset->ATwset
                        ->data[idxStartIneq + workingset->ldA * (i - 1)];
              }
              workingset->bwset->data[mWorkingFixed - 1] =
                  workingset->bwset->data[i - 1];
              workingset->Wid->data[i - 1] =
                  workingset->Wid->data[workingset->nActiveConstr - 1];
              workingset->Wlocalidx->data[i - 1] =
                  workingset->Wlocalidx->data[workingset->nActiveConstr - 1];
              mWorkingFixed = workingset->nVar;
              for (idxStartIneq = 0; idxStartIneq < mWorkingFixed;
                   idxStartIneq++) {
                workingset->ATwset
                    ->data[idxStartIneq + workingset->ldA * (i - 1)] =
                    workingset->ATwset
                        ->data[idxStartIneq +
                               workingset->ldA *
                                   (workingset->nActiveConstr - 1)];
              }
              workingset->bwset->data[i - 1] =
                  workingset->bwset->data[workingset->nActiveConstr - 1];
              workingset->nActiveConstr--;
              workingset->nWConstr[idxDiag]--;
            }
          }
        }
      }
    }
  }
  if ((nDepInd != -1) && (workingset->nActiveConstr <= qrmanager->ldq)) {
    idxStartIneq = workingset->nActiveConstr;
    i = workingset->nWConstr[0] + workingset->nWConstr[1];
    mWorkingFixed = workingset->nVar;
    if ((workingset->nWConstr[2] + workingset->nWConstr[3]) +
            workingset->nWConstr[4] >
        0) {
      tol = 100.0 * (real_T)workingset->nVar * 2.2204460492503131E-16;
      for (idx = 0; idx < i; idx++) {
        qrmanager->jpvt->data[idx] = 1;
      }
      nVar_tmp_tmp = i + 1;
      for (idx = nVar_tmp_tmp; idx <= idxStartIneq; idx++) {
        qrmanager->jpvt->data[idx - 1] = 0;
      }
      nVar_tmp_tmp = workingset->nActiveConstr;
      for (idxDiag = 0; idxDiag < nVar_tmp_tmp; idxDiag++) {
        if (mWorkingFixed >= 1) {
          n_t = (ptrdiff_t)mWorkingFixed;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dcopy(&n_t, &workingset->ATwset->data[workingset->ldA * idxDiag],
                &incx_t, &qrmanager->QR->data[qrmanager->ldq * idxDiag],
                &incy_t);
        }
      }
      if (workingset->nVar * workingset->nActiveConstr == 0) {
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = workingset->nActiveConstr;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = workingset->nActiveConstr;
        qrmanager->minRowCol =
            muIntScalarMin_sint32(workingset->nVar, workingset->nActiveConstr);
        xgeqp3(qrmanager->QR, workingset->nVar, workingset->nActiveConstr,
               qrmanager->jpvt, qrmanager->tau);
      }
      idxStartIneq = 0;
      for (idx = workingset->nActiveConstr - 1; idx + 1 > mWorkingFixed;
           idx--) {
        idxStartIneq++;
        memspace->workspace_int->data[idxStartIneq - 1] =
            qrmanager->jpvt->data[idx];
      }
      if (idx + 1 <= workingset->nVar) {
        idxDiag = idx + qrmanager->ldq * idx;
        while ((idx + 1 > i) &&
               (muDoubleScalarAbs(qrmanager->QR->data[idxDiag]) < tol)) {
          idxStartIneq++;
          memspace->workspace_int->data[idxStartIneq - 1] =
              qrmanager->jpvt->data[idx];
          idx--;
          idxDiag = (idxDiag - qrmanager->ldq) - 1;
        }
      }
      countsort(memspace->workspace_int, idxStartIneq, memspace->workspace_sort,
                i + 1, workingset->nActiveConstr);
      for (idx = idxStartIneq; idx >= 1; idx--) {
        removeConstr(workingset, memspace->workspace_int->data[idx - 1]);
      }
    }
    okWorkingSet = feasibleX0ForWorkingSet(
        memspace->workspace_double, solution->xstar, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      idxStartIneq = workingset->nActiveConstr;
      i = workingset->nWConstr[0] + workingset->nWConstr[1];
      mWorkingFixed = workingset->nVar;
      if ((workingset->nWConstr[2] + workingset->nWConstr[3]) +
              workingset->nWConstr[4] >
          0) {
        tol = 1000.0 * (real_T)workingset->nVar * 2.2204460492503131E-16;
        for (idx = 0; idx < i; idx++) {
          qrmanager->jpvt->data[idx] = 1;
        }
        nVar_tmp_tmp = i + 1;
        for (idx = nVar_tmp_tmp; idx <= idxStartIneq; idx++) {
          qrmanager->jpvt->data[idx - 1] = 0;
        }
        nVar_tmp_tmp = workingset->nActiveConstr;
        for (idxDiag = 0; idxDiag < nVar_tmp_tmp; idxDiag++) {
          if (mWorkingFixed >= 1) {
            n_t = (ptrdiff_t)mWorkingFixed;
            incx_t = (ptrdiff_t)1;
            incy_t = (ptrdiff_t)1;
            dcopy(&n_t, &workingset->ATwset->data[workingset->ldA * idxDiag],
                  &incx_t, &qrmanager->QR->data[qrmanager->ldq * idxDiag],
                  &incy_t);
          }
        }
        if (workingset->nVar * workingset->nActiveConstr == 0) {
          qrmanager->mrows = workingset->nVar;
          qrmanager->ncols = workingset->nActiveConstr;
          qrmanager->minRowCol = 0;
        } else {
          qrmanager->usedPivoting = true;
          qrmanager->mrows = workingset->nVar;
          qrmanager->ncols = workingset->nActiveConstr;
          qrmanager->minRowCol = muIntScalarMin_sint32(
              workingset->nVar, workingset->nActiveConstr);
          xgeqp3(qrmanager->QR, workingset->nVar, workingset->nActiveConstr,
                 qrmanager->jpvt, qrmanager->tau);
        }
        idxStartIneq = 0;
        for (idx = workingset->nActiveConstr - 1; idx + 1 > mWorkingFixed;
             idx--) {
          idxStartIneq++;
          memspace->workspace_int->data[idxStartIneq - 1] =
              qrmanager->jpvt->data[idx];
        }
        if (idx + 1 <= workingset->nVar) {
          idxDiag = idx + qrmanager->ldq * idx;
          while ((idx + 1 > i) &&
                 (muDoubleScalarAbs(qrmanager->QR->data[idxDiag]) < tol)) {
            idxStartIneq++;
            memspace->workspace_int->data[idxStartIneq - 1] =
                qrmanager->jpvt->data[idx];
            idx--;
            idxDiag = (idxDiag - qrmanager->ldq) - 1;
          }
        }
        countsort(memspace->workspace_int, idxStartIneq,
                  memspace->workspace_sort, i + 1, workingset->nActiveConstr);
        for (idx = idxStartIneq; idx >= 1; idx--) {
          removeConstr(workingset, memspace->workspace_int->data[idx - 1]);
        }
      }
      okWorkingSet = feasibleX0ForWorkingSet(
          memspace->workspace_double, solution->xstar, workingset, qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1 && (workingset->nWConstr[0] + workingset->nWConstr[1] ==
                   workingset->nVar)) {
      tol = maxConstraintViolation(workingset, solution->xstar);
      if (tol > options->ConstraintTolerance) {
        solution->state = -2;
      }
    }
  } else {
    solution->state = -3;
    idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
    idxDiag = workingset->nActiveConstr;
    for (nVar_tmp_tmp = idxStartIneq; nVar_tmp_tmp <= idxDiag; nVar_tmp_tmp++) {
      workingset->isActiveConstr
          ->data[(workingset->isActiveIdx
                      [workingset->Wid->data[nVar_tmp_tmp - 1] - 1] +
                  workingset->Wlocalidx->data[nVar_tmp_tmp - 1]) -
                 2] = false;
    }
    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr =
        workingset->nWConstr[0] + workingset->nWConstr[1];
  }
}

/* End of code generation (PresolveWorkingSet.c) */
