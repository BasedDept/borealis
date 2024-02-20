/**
 * @file stddef.h
 * @brief Common definitions
 * @author George Witt
 * @date 2024-02-04
 *
 * ISO/IEC 9899:1990 7.1.6
 * ISO/IEC 9899:2011 7.19
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#if !defined(__STDDEF_H_WANT_NULL__)

#ifndef __STDDEF_H__
#define __STDDEF_H__

#define __STDDEF_H_WANT_NULL__

/**
 * @def offsetof
 * @param type
 * @param member_designator
 *
 * ISO/IEC 9899:1990 7.1.6
 */
#define offsetof(type, member_designator) __builtin_offsetof(type, member_designator)

/**
 * @typedef ptrdiff_t
 *
 * ISO/IEC 9899:1990 7.1.6
 */
typedef signed long ptrdiff_t;

/**
 * @typedef size_t
 *
 * ISO/IEC 9899:1990 7.1.6
 */
typedef unsigned long size_t;

/**
 * @typedef wchar_t
 *
 * ISO/IEC 9899:1990 7.1.6
 */
typedef int wchar_t;


#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

/**
 * @typedef max_align_t
 *
 * ISO/IEC 9899:2011 7.19
 */
typedef long double max_align_t;

#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1

/**
 * @typedef rsize_t
 *
 * ISO/IEC 9899:2011 K.3.3
 */
typedef size_t rsize_t;

#endif
#endif

#endif /* __STDDEF_H__ */
#endif

#if defined(__STDDEF_H_WANT_NULL__)
/**
 * @def NULL
 *
 * ISO/IEC 9899:1990 7.1.6
 */
#define NULL ((void*)0)

#undef __STDDEF_H_WANT_NULL__
#endif
