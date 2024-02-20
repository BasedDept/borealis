/**
 * @file stdarg.h
 * @brief Variable arguments
 * @author George Witt
 * @date 2024-02-03
 *
 * ISO/IEC 9899:1990 7.8
 * ISO/IEC 9899:1999 7.15
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __STDARG_H__
#define __STDARG_H__

/**
 * @typedef va_list
 *
 * ISO/IEC 9899:1990 7.8
 */
typedef __builtin_va_list va_list;

/**
 * @def va_start
 * @param ap
 * @param parmN
 *
 * ISO/IEC 9899:1990 7.8.1.1
 */
#define va_start(ap, parmN) ((void)__builtin_va_start(ap, parmN))

/**
 * @def va_arg
 * @param ap
 * @param type
 * @return
 *
 * ISO/IEC 9899:1990 7.8.1.2
 */
#define va_arg(ap, type) ((type)__builtin_va_arg(ap, type))

/**
 * @def va_end
 * @param ap
 *
 * ISO/IEC 9899:1990 7.8.1.3
 */
#define va_end(ap) ((void)__builtin_va_end(ap))

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/**
 * @def va_copy
 * @param dest
 * @param src
 *
 * ISO/IEC 9899:1999 7.15.1.2
 */
#define va_copy(dest, src) ((void)__builtin_va_copy(dest, src))

#endif

#endif /* __STDARG_H__ */
