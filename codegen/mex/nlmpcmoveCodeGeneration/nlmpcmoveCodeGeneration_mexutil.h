/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * nlmpcmoveCodeGeneration_mexutil.h
 *
 * Code generation for function 'nlmpcmoveCodeGeneration_mexutil'
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
real_T b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *parentId);

const mxArray *b_feval(const mxArray *m1, const mxArray *m2, const mxArray *m3,
                       const mxArray *m4, const mxArray *m5, const mxArray *m6,
                       const mxArray *m7, emlrtMCInfo *location);

real_T emlrt_marshallIn(const mxArray *a__output_of_feval_,
                        const char_T *identifier);

const mxArray *feval(const mxArray *m1, const mxArray *m2, const mxArray *m3,
                     emlrtMCInfo *location);

real_T k_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *msgId);

/* End of code generation (nlmpcmoveCodeGeneration_mexutil.h) */
