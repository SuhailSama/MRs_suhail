/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * driver1.c
 *
 * Code generation for function 'driver1'
 *
 */

/* Include files */
#include "driver1.h"
#include "BFGSUpdate.h"
#include "computeLinearResiduals.h"
#include "evalObjAndConstr.h"
#include "evalObjAndConstrAndDerivatives.h"
#include "nlmpcmoveCodeGeneration_data.h"
#include "nlmpcmoveCodeGeneration_emxutil.h"
#include "nlmpcmoveCodeGeneration_internal_types.h"
#include "nlmpcmoveCodeGeneration_types.h"
#include "rt_nonfinite.h"
#include "saveJacobian.h"
#include "saveState.h"
#include "step.h"
#include "test_exit.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include "blas.h"
#include "mwmathutil.h"
#include <stddef.h>
#include <string.h>

/* Function Definitions */
void b_driver(const emxArray_real_T *bineq, const real_T lb[51],
              const real_T ub[51], e_struct_T *TrialState,
              struct_T *MeritFunction, const n_struct_T *FcnEvaluator,
              const o_struct_T *FiniteDifferences, i_struct_T *memspace,
              j_struct_T *WorkingSet, f_struct_T *QRManager,
              g_struct_T *CholManager, h_struct_T *QPObjective,
              const emxArray_real_T *fscales_lineq_constraint,
              const emxArray_real_T *fscales_cineq_constraint,
              const real_T fscales_ceq_constraint[32], real_T Hessian[2601])
{
  static const char_T qpoptions_SolverName[7] = {'f', 'm', 'i', 'n',
                                                 'c', 'o', 'n'};
  static const int8_T b_iv[2601] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1};
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  ptrdiff_t lda_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  b_struct_T Flags;
  d_struct_T b_expl_temp;
  d_struct_T c_expl_temp;
  p_struct_T expl_temp;
  const real_T *fscales_cineq_constraint_data;
  const real_T *fscales_lineq_constraint_data;
  real_T alpha;
  real_T constrViolationEq;
  real_T constrViolationIneq;
  int32_T b_mIneq;
  int32_T b_mLinEq;
  int32_T b_mLinIneq;
  int32_T exitflagLnSrch;
  int32_T exitg1;
  int32_T i;
  int32_T k;
  int32_T mConstr;
  int32_T mEq;
  int32_T mFixed;
  int32_T mIneq;
  int32_T mLB;
  int32_T mLinEq;
  int32_T mLinIneq;
  int32_T mUB;
  int32_T nVar_tmp_tmp;
  int32_T qpoptions_MaxIterations;
  int32_T y;
  char_T TRANSA;
  boolean_T evalWellDefined;
  boolean_T exitg2;
  boolean_T socTaken;
  boolean_T tooSmallX;
  fscales_cineq_constraint_data = fscales_cineq_constraint->data;
  fscales_lineq_constraint_data = fscales_lineq_constraint->data;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  for (i = 0; i < 2601; i++) {
    Hessian[i] = b_iv[i];
  }
  nVar_tmp_tmp = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  mEq = WorkingSet->sizes[1];
  mIneq = WorkingSet->sizes[2];
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  mConstr =
      (((WorkingSet->sizes[0] + WorkingSet->sizes[1]) + WorkingSet->sizes[2]) +
       WorkingSet->sizes[3]) +
      WorkingSet->sizes[4];
  mLinIneq = WorkingSet->sizes[2] - TrialState->mNonlinIneq;
  mLinEq = WorkingSet->sizes[1] - TrialState->mNonlinEq;
  y = ((WorkingSet->sizes[2] + WorkingSet->sizes[3]) + WorkingSet->sizes[4]) +
      (WorkingSet->sizes[0] << 1);
  qpoptions_MaxIterations = 10 * muIntScalarMax_sint32(WorkingSet->nVar, y);
  TrialState->steplength = 1.0;
  test_exit(memspace, MeritFunction, fscales_lineq_constraint,
            fscales_cineq_constraint, WorkingSet, TrialState, QRManager, lb, ub,
            &Flags.gradOK, &Flags.fevalOK, &Flags.done, &Flags.stepAccepted,
            &Flags.failedLineSearch, &Flags.stepType);
  saveJacobian(TrialState, nVar_tmp_tmp, mIneq, WorkingSet->Aineq,
               TrialState->iNonIneq0, mEq, WorkingSet->Aeq, TrialState->iNonEq0,
               WorkingSet->ldA);
  saveState(TrialState);
  if (!Flags.done) {
    TrialState->sqpIterations++;
  }
  emxInitStruct_struct_T11(&expl_temp);
  while (!Flags.done) {
    while (!(Flags.stepAccepted || Flags.failedLineSearch)) {
      if (Flags.stepType != 3) {
        b_updateWorkingSetForNewQP(TrialState->xstarsqp, WorkingSet, mIneq,
                                   TrialState->mNonlinIneq, TrialState->cIneq,
                                   mEq, TrialState->mNonlinEq, TrialState->cEq,
                                   mLB, lb, mUB, ub, mFixed);
      }
      b_expl_temp.IterDisplayQP = false;
      b_expl_temp.RemainFeasible = false;
      b_expl_temp.ProbRelTolFactor = 1.0;
      b_expl_temp.ConstrRelTolFactor = 1.0;
      b_expl_temp.PricingTolerance = 0.0;
      b_expl_temp.ObjectiveLimit = rtMinusInf;
      b_expl_temp.ConstraintTolerance = 1.0E-6;
      b_expl_temp.OptimalityTolerance = 2.2204460492503131E-14;
      b_expl_temp.StepTolerance = 1.0E-6;
      b_expl_temp.MaxIterations = qpoptions_MaxIterations;
      for (i = 0; i < 7; i++) {
        b_expl_temp.SolverName[i] = qpoptions_SolverName[i];
      }
      c_expl_temp = b_expl_temp;
      Flags.stepAccepted = step(&Flags.stepType, Hessian, lb, ub, TrialState,
                                MeritFunction, memspace, WorkingSet, QRManager,
                                CholManager, QPObjective, &c_expl_temp);
      if (Flags.stepAccepted) {
        for (b_mLinIneq = 0; b_mLinIneq < nVar_tmp_tmp; b_mLinIneq++) {
          TrialState->xstarsqp[b_mLinIneq] +=
              TrialState->delta_x->data[b_mLinIneq];
        }
        evalObjAndConstr(
            FcnEvaluator->objfun.workspace.runtimedata.x,
            FcnEvaluator->objfun.workspace.runtimedata.lastMV,
            FcnEvaluator->objfun.workspace.runtimedata.ref,
            FcnEvaluator->objfun.workspace.runtimedata.OutputWeights,
            FcnEvaluator->objfun.workspace.runtimedata.MVWeights,
            FcnEvaluator->objfun.workspace.runtimedata.MVRateWeights,
            FcnEvaluator->objfun.workspace.runtimedata.ECRWeight,
            FcnEvaluator->objfun.workspace.runtimedata.MVScaledTarget,
            FcnEvaluator->nonlcon.workspace.runtimedata.x,
            FcnEvaluator->nonlcon.workspace.runtimedata.OutputMin,
            FcnEvaluator->nonlcon.workspace.runtimedata.OutputMax,
            FcnEvaluator->mCineq, FcnEvaluator->mCeq,
            FcnEvaluator->ScaleProblem, TrialState->xstarsqp, TrialState->cIneq,
            TrialState->iNonIneq0, TrialState->cEq, TrialState->iNonEq0,
            fscales_cineq_constraint, fscales_ceq_constraint,
            &TrialState->sqpFval, &y);
        Flags.fevalOK = (y == 1);
        TrialState->FunctionEvaluations++;
        computeLinearResiduals(TrialState->xstarsqp, nVar_tmp_tmp,
                               TrialState->cIneq, mLinIneq, WorkingSet->Aineq,
                               bineq, WorkingSet->ldA, TrialState->cEq, mLinEq,
                               WorkingSet->Aeq, WorkingSet->ldA);
        if (Flags.fevalOK) {
          constrViolationEq = 0.0;
          if (mEq >= 1) {
            for (k = 0; k < mEq; k++) {
              constrViolationEq += muDoubleScalarAbs(TrialState->cEq[k]);
            }
          }
          constrViolationIneq = 0.0;
          for (y = 0; y < mIneq; y++) {
            if (TrialState->cIneq->data[y] > 0.0) {
              constrViolationIneq += TrialState->cIneq->data[y];
            }
          }
          MeritFunction->phiFullStep =
              TrialState->sqpFval +
              MeritFunction->penaltyParam *
                  (constrViolationEq + constrViolationIneq);
        } else {
          MeritFunction->phiFullStep = rtInf;
        }
      }
      if ((Flags.stepType == 1) && Flags.stepAccepted && Flags.fevalOK &&
          (MeritFunction->phi < MeritFunction->phiFullStep) &&
          (TrialState->sqpFval < TrialState->sqpFval_old)) {
        Flags.stepType = 3;
        Flags.stepAccepted = false;
      } else {
        if ((Flags.stepType == 3) && Flags.stepAccepted) {
          socTaken = true;
        } else {
          socTaken = false;
        }
        evalWellDefined = Flags.fevalOK;
        i = WorkingSet->nVar;
        b_mLinIneq = TrialState->mIneq - TrialState->mNonlinIneq;
        b_mLinEq = TrialState->mEq - TrialState->mNonlinEq;
        alpha = 1.0;
        exitflagLnSrch = 1;
        constrViolationEq = MeritFunction->phiFullStep;
        if (WorkingSet->nVar >= 1) {
          n_t = (ptrdiff_t)WorkingSet->nVar;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dcopy(&n_t, &TrialState->delta_x->data[0], &incx_t,
                &TrialState->searchDir->data[0], &incy_t);
        }
        do {
          exitg1 = 0;
          if (TrialState->FunctionEvaluations < 5100) {
            if (evalWellDefined &&
                (constrViolationEq <=
                 MeritFunction->phi +
                     alpha * 0.0001 * MeritFunction->phiPrimePlus)) {
              exitg1 = 1;
            } else {
              alpha *= 0.7;
              for (y = 0; y < i; y++) {
                TrialState->delta_x->data[y] =
                    alpha * TrialState->xstar->data[y];
              }
              if (socTaken) {
                constrViolationEq = alpha * alpha;
                if (i >= 1) {
                  n_t = (ptrdiff_t)i;
                  incx_t = (ptrdiff_t)1;
                  incy_t = (ptrdiff_t)1;
                  daxpy(&n_t, &constrViolationEq,
                        &TrialState->socDirection->data[0], &incx_t,
                        &TrialState->delta_x->data[0], &incy_t);
                }
              }
              tooSmallX = true;
              y = 0;
              exitg2 = false;
              while ((!exitg2) && (y <= i - 1)) {
                if (1.0E-6 *
                        muDoubleScalarMax(
                            1.0, muDoubleScalarAbs(TrialState->xstarsqp[y])) <=
                    muDoubleScalarAbs(TrialState->delta_x->data[y])) {
                  tooSmallX = false;
                  exitg2 = true;
                } else {
                  y++;
                }
              }
              if (tooSmallX) {
                exitflagLnSrch = -2;
                exitg1 = 1;
              } else {
                for (y = 0; y < i; y++) {
                  TrialState->xstarsqp[y] = TrialState->xstarsqp_old[y] +
                                            TrialState->delta_x->data[y];
                }
                evalObjAndConstr(
                    FcnEvaluator->objfun.workspace.runtimedata.x,
                    FcnEvaluator->objfun.workspace.runtimedata.lastMV,
                    FcnEvaluator->objfun.workspace.runtimedata.ref,
                    FcnEvaluator->objfun.workspace.runtimedata.OutputWeights,
                    FcnEvaluator->objfun.workspace.runtimedata.MVWeights,
                    FcnEvaluator->objfun.workspace.runtimedata.MVRateWeights,
                    FcnEvaluator->objfun.workspace.runtimedata.ECRWeight,
                    FcnEvaluator->objfun.workspace.runtimedata.MVScaledTarget,
                    FcnEvaluator->nonlcon.workspace.runtimedata.x,
                    FcnEvaluator->nonlcon.workspace.runtimedata.OutputMin,
                    FcnEvaluator->nonlcon.workspace.runtimedata.OutputMax,
                    FcnEvaluator->mCineq, FcnEvaluator->mCeq,
                    FcnEvaluator->ScaleProblem, TrialState->xstarsqp,
                    TrialState->cIneq, TrialState->iNonIneq0, TrialState->cEq,
                    TrialState->iNonEq0, fscales_cineq_constraint,
                    fscales_ceq_constraint, &TrialState->sqpFval, &y);
                computeLinearResiduals(
                    TrialState->xstarsqp, i, TrialState->cIneq, b_mLinIneq,
                    WorkingSet->Aineq, bineq, WorkingSet->ldA, TrialState->cEq,
                    b_mLinEq, WorkingSet->Aeq, WorkingSet->ldA);
                TrialState->FunctionEvaluations++;
                evalWellDefined = (y == 1);
                b_mIneq = TrialState->mIneq;
                y = TrialState->mEq;
                if (evalWellDefined) {
                  constrViolationEq = 0.0;
                  if (TrialState->mEq >= 1) {
                    for (k = 0; k < y; k++) {
                      constrViolationEq +=
                          muDoubleScalarAbs(TrialState->cEq[k]);
                    }
                  }
                  constrViolationIneq = 0.0;
                  for (y = 0; y < b_mIneq; y++) {
                    if (TrialState->cIneq->data[y] > 0.0) {
                      constrViolationIneq += TrialState->cIneq->data[y];
                    }
                  }
                  constrViolationEq =
                      TrialState->sqpFval +
                      MeritFunction->penaltyParam *
                          (constrViolationEq + constrViolationIneq);
                } else {
                  constrViolationEq = rtInf;
                }
              }
            }
          } else {
            exitflagLnSrch = 0;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
        Flags.fevalOK = evalWellDefined;
        TrialState->steplength = alpha;
        if (exitflagLnSrch > 0) {
          Flags.stepAccepted = true;
        } else {
          Flags.failedLineSearch = true;
        }
      }
    }
    if (Flags.stepAccepted && (!Flags.failedLineSearch)) {
      for (y = 0; y < nVar_tmp_tmp; y++) {
        TrialState->xstarsqp[y] =
            TrialState->xstarsqp_old[y] + TrialState->delta_x->data[y];
      }
      for (y = 0; y < mConstr; y++) {
        TrialState->lambdasqp->data[y] +=
            TrialState->steplength *
            (TrialState->lambda->data[y] - TrialState->lambdasqp->data[y]);
      }
      saveState(TrialState);
      Flags.gradOK = true;
      TrialState->FunctionEvaluations += FiniteDifferences->numEvals;
      memcpy(&expl_temp.ceq_constraint[0], &fscales_ceq_constraint[0],
             32U * sizeof(real_T));
      i = expl_temp.cineq_constraint->size[0];
      expl_temp.cineq_constraint->size[0] = fscales_cineq_constraint->size[0];
      emxEnsureCapacity_real_T(expl_temp.cineq_constraint, i);
      y = fscales_cineq_constraint->size[0];
      for (i = 0; i < y; i++) {
        expl_temp.cineq_constraint->data[i] = fscales_cineq_constraint_data[i];
      }
      i = expl_temp.lineq_constraint->size[0];
      expl_temp.lineq_constraint->size[0] = fscales_lineq_constraint->size[0];
      emxEnsureCapacity_real_T(expl_temp.lineq_constraint, i);
      y = fscales_lineq_constraint->size[0];
      for (i = 0; i < y; i++) {
        expl_temp.lineq_constraint->data[i] = fscales_lineq_constraint_data[i];
      }
      expl_temp.objective = 1.0;
      evalObjAndConstrAndDerivatives(
          FcnEvaluator->objfun.workspace.runtimedata.x,
          FcnEvaluator->objfun.workspace.runtimedata.lastMV,
          FcnEvaluator->objfun.workspace.runtimedata.ref,
          FcnEvaluator->objfun.workspace.runtimedata.OutputWeights,
          FcnEvaluator->objfun.workspace.runtimedata.MVWeights,
          FcnEvaluator->objfun.workspace.runtimedata.MVRateWeights,
          FcnEvaluator->objfun.workspace.runtimedata.ECRWeight,
          FcnEvaluator->objfun.workspace.runtimedata.MVScaledTarget,
          FcnEvaluator->nonlcon.workspace.runtimedata.x,
          FcnEvaluator->nonlcon.workspace.runtimedata.OutputMin,
          FcnEvaluator->nonlcon.workspace.runtimedata.OutputMax,
          FcnEvaluator->nVar, FcnEvaluator->mCineq, FcnEvaluator->mCeq,
          FcnEvaluator->ScaleProblem, TrialState->xstarsqp, TrialState->grad,
          TrialState->cIneq, TrialState->iNonIneq0, TrialState->cEq,
          TrialState->iNonEq0, WorkingSet->Aineq, TrialState->iNonIneq0,
          WorkingSet->ldA, WorkingSet->Aeq, TrialState->iNonEq0,
          WorkingSet->ldA, &expl_temp, &TrialState->sqpFval, &y);
      TrialState->FunctionEvaluations++;
      Flags.fevalOK = (y == 1);
    } else {
      TrialState->sqpFval = TrialState->sqpFval_old;
      memcpy(&TrialState->xstarsqp[0], &TrialState->xstarsqp_old[0],
             51U * sizeof(real_T));
      if (TrialState->mIneq >= 1) {
        n_t = (ptrdiff_t)TrialState->mIneq;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        dcopy(&n_t, &TrialState->cIneq_old->data[0], &incx_t,
              &TrialState->cIneq->data[0], &incy_t);
      }
      y = TrialState->mEq;
      if (0 <= y - 1) {
        memcpy(&TrialState->cEq[0], &TrialState->cEq_old[0],
               y * sizeof(real_T));
      }
    }
    b_test_exit(&Flags, memspace, MeritFunction, fscales_lineq_constraint,
                fscales_cineq_constraint, WorkingSet, TrialState, QRManager, lb,
                ub);
    if ((!Flags.done) && Flags.stepAccepted) {
      Flags.stepAccepted = false;
      Flags.stepType = 1;
      Flags.failedLineSearch = false;
      y = (mFixed + mEq) + TrialState->iNonIneq0;
      b_mIneq = mFixed + TrialState->iNonEq0;
      for (b_mLinIneq = 0; b_mLinIneq < nVar_tmp_tmp; b_mLinIneq++) {
        TrialState->delta_gradLag->data[b_mLinIneq] =
            TrialState->grad->data[b_mLinIneq];
      }
      if (nVar_tmp_tmp >= 1) {
        constrViolationEq = -1.0;
        n_t = (ptrdiff_t)nVar_tmp_tmp;
        incx_t = (ptrdiff_t)1;
        incy_t = (ptrdiff_t)1;
        daxpy(&n_t, &constrViolationEq, &TrialState->grad_old->data[0], &incx_t,
              &TrialState->delta_gradLag->data[0], &incy_t);
      }
      if (TrialState->mNonlinEq > 0) {
        h_xgemv(nVar_tmp_tmp, TrialState->mNonlinEq, WorkingSet->Aeq,
                WorkingSet->ldA * (TrialState->iNonEq0 - 1) + 1,
                WorkingSet->ldA, TrialState->lambdasqp, b_mIneq,
                TrialState->delta_gradLag);
        if ((nVar_tmp_tmp >= 1) && (TrialState->mNonlinEq >= 1)) {
          constrViolationEq = -1.0;
          constrViolationIneq = 1.0;
          TRANSA = 'N';
          m_t = (ptrdiff_t)nVar_tmp_tmp;
          n_t = (ptrdiff_t)TrialState->mNonlinEq;
          lda_t = (ptrdiff_t)WorkingSet->ldA;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dgemv(&TRANSA, &m_t, &n_t, &constrViolationEq,
                &TrialState->JacCeqTrans_old->data[0], &lda_t,
                &TrialState->lambdasqp->data[b_mIneq - 1], &incx_t,
                &constrViolationIneq, &TrialState->delta_gradLag->data[0],
                &incy_t);
        }
      }
      if (TrialState->mNonlinIneq > 0) {
        h_xgemv(nVar_tmp_tmp, TrialState->mNonlinIneq, WorkingSet->Aineq,
                WorkingSet->ldA * (TrialState->iNonIneq0 - 1) + 1,
                WorkingSet->ldA, TrialState->lambdasqp, y,
                TrialState->delta_gradLag);
        if ((nVar_tmp_tmp >= 1) && (TrialState->mNonlinIneq >= 1)) {
          constrViolationEq = -1.0;
          constrViolationIneq = 1.0;
          TRANSA = 'N';
          m_t = (ptrdiff_t)nVar_tmp_tmp;
          n_t = (ptrdiff_t)TrialState->mNonlinIneq;
          lda_t = (ptrdiff_t)WorkingSet->ldA;
          incx_t = (ptrdiff_t)1;
          incy_t = (ptrdiff_t)1;
          dgemv(&TRANSA, &m_t, &n_t, &constrViolationEq,
                &TrialState->JacCineqTrans_old->data[0], &lda_t,
                &TrialState->lambdasqp->data[y - 1], &incx_t,
                &constrViolationIneq, &TrialState->delta_gradLag->data[0],
                &incy_t);
        }
      }
      saveJacobian(TrialState, nVar_tmp_tmp, mIneq, WorkingSet->Aineq,
                   TrialState->iNonIneq0, mEq, WorkingSet->Aeq,
                   TrialState->iNonEq0, WorkingSet->ldA);
      BFGSUpdate(nVar_tmp_tmp, Hessian, TrialState->delta_x,
                 TrialState->delta_gradLag, memspace->workspace_double);
      TrialState->sqpIterations++;
    }
  }
  emxFreeStruct_struct_T11(&expl_temp);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (driver1.c) */
