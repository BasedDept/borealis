/**
 * @file float.h
 * @brief Characteristics of floating types
 * @author George Witt
 * @date 2024-02-03
 *
 * ISO/IEC 9899:1990 7.1.5
 * ISO/IEC 9899:1999 7.7
 * ISO/IEC 9899:2011 7.7
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __FLOAT_H__
#define __FLOAT_H__

#if defined(__STDC_HOSTED__) && __STDC_HOSTED__ == 1

/**
 * @def FLT_ROUNDS
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_ROUNDS (__flt_rounds())

int __flt_rounds(void);

#else

#define FLT_ROUNDS 1

#endif

/**
 * @def FLT_RADIX
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_RADIX (2)

/**
 * @def FLT_MANT_DIG
 * @def DBL_MANT_DIG
 * @def LDBL_MANT_DIG
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_MANT_DIG (24)
#define DBL_MANT_DIG (53)
#define LDBL_MANT_DIG (113)

/**
 * @def FLT_DIG
 * @def DBL_DIG
 * @def LDBL_DIG
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_DIG (6)
#define DBL_DIG (15)
#define LDBL_DIG (33)

/**
 * @def FLT_MIN_EXP
 * @def DBL_MIN_EXP
 * @def LDBL_MIN_EXP
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_MIN_EXP (-125)
#define DBL_MIN_EXP (-1021)
#define LDBL_MIN_EXP (-16381)

/**
 * @def FLT_MIN_10_EXP
 * @def DBL_MIN_10_EXP
 * @def LDBL_MIN_10_EXP
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_MIN_10_EXP (-37)
#define DBL_MIN_10_EXP (-307)
#define LDBL_MIN_10_EXP (-4931)

/**
 * @def FLT_MAX_EXP
 * @def DBL_MAX_EXP
 * @def LDBL_MAX_EXP
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_MAX_EXP (128)
#define DBL_MAX_EXP (1024)
#define LDBL_MAX_EXP (16384)

/**
 * @def FLT_MAX_10_EXP
 * @def DBL_MAX_10_EXP
 * @def LDBL_MAX_10_EXP
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_MAX_10_EXP (38)
#define DBL_MAX_10_EXP (308)
#define LDBL_MAX_10_EXP (4932)

/**
 * @def FLT_MAX
 * @def DBL_MAX
 * @def LDBL_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_MAX (3.402823466e+38F)
#define DBL_MAX (1.79769313486231571e+308)
#define LDBL_MAX (1.189731495357231765085759326628007016e+4932L)

/**
 * @def FLT_EPSILON
 * @def DBL_EPSILON
 * @def LDBL_EPSILON
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_EPSILON (1.192092896e-07F)
#define DBL_EPSILON (2.22044604925031308e-16)
#define LDBL_EPSILON (1.925929944387235853055977942584927319e-34L)

/**
 * @def FLT_MIN
 * @def DBL_MIN
 * @def LDBL_MIN
 *
 * ISO/IEC 9899:1990 5.2.4.2.2
 */
#define FLT_MIN (1.175494351e-38F)
#define DBL_MIN (2.22507385850720138e-308)
#define LDBL_MIN (3.362103143112093506262677817321752603e-4932L)

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/**
 * @def FLT_EVAL_METHOD
 *
 * ISO/IEC 9899:1999 5.2.4.2.2
 */
#define FLT_EVAL_METHOD 0

/**
 * @def DECIMAL_DIG
 *
 * ISO/IEC 9899:1999 5.2.4.2.2
 */
#define DECIMAL_DIG (36)

#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

/**
 * @def FLT_HAS_SUBNORM
 * @def DBL_HAS_SUBNORM
 * @def LDBL_HAS_SUBNORM
 *
 * ISO/IEC 9899:2011 5.2.4.2.2
 */
#define FLT_HAS_SUBNORM 1
#define DBL_HAS_SUBNORM 1
#define LDBL_HAS_SUBNORM 1

/**
 * @def FLT_DECIMAL_DIG
 * @def DBL_DECIMAL_DIG
 * @def LDBL_DECIMAL_DIG
 *
 * ISO/IEC 9899:2011 5.2.4.2.2
 */
#define FLT_DECIMAL_DIG (9)
#define DBL_DECIMAL_DIG (17)
#define LDBL_DECIMAL_DIG (36)

/**
 * @def FLT_TRUE_MIN
 * @def DBL_TRUE_MIN
 * @def LDBL_TRUE_MIN
 *
 * ISO/IEC 9899:2011 5.2.4.2.2
 */
#define FLT_TRUE_MIN (1.401298464-45F)
#define DBL_TRUE_MIN (4.94065645841246544e-324)
#define LDBL_TRUE_MIN (6.475175119438025110924438958227646553e-4966L)

#endif

#endif /* __FLOAT_H__ */
