/**
 * @file stdbool.h
 * @brief Boolean type and values
 * @author George Witt
 * @date 2024-01-01
 *
 * ISO/IEC 9899:1999 7.16
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#ifndef __STDBOOL_H__
#define __STDBOOL_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

/**
 * @def bool
 *
 * ISO/IEC 9899:1999 7.16
 */
#define bool _Bool

/**
 * @def true
 *
 * ISO/IEC 9899:1999 7.16
 */
#define true 1

/**
 * @def false
 *
 * ISO/IEC 9899:1999 7.16
 */
#define false 0

/**
 * @def __bool_true_false_are_defined
 *
 * ISO/IEC 9899:1999 7.16
 */
#define __bool_true_false_are_defined 1

#endif /* __STDBOOL_H__ */
#endif
