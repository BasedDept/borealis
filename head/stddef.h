/**
 * @file stddef.h
 * @brief Common definitions
 * @author George Witt
 * @date 2024-02-24
 *
 * ISO/IEC 9899:1990 7.1.6
 * ISO/IEC 9899:2011 7.19
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#undef __ptrdiff_t__
#define __ptrdiff_t__ signed long

#ifndef __UCHAR_H__
#define __UCHAR_H__
#include <uchar.h>
#undef __UCHAR_H__
#endif
#undef __wchar_t__
#define __wchar_t__ __char32_t__

#if !defined(__STDDEF_H_WANT_NULL__) && !defined (__STDDEF_H_WANT_size_t__)

#ifndef __STDDEF_H__
#define __STDDEF_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define __STDDEF_H_WANT_NULL__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */
#define __STDDEF_H_WANT_size_t__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

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
typedef __ptrdiff_t__ ptrdiff_t;

/**
 * @typedef wchar_t
 *
 * ISO/IEC 9899:1990 7.1.6
 */
typedef __wchar_t__ wchar_t;
//__STDC_ISO__10646__ yyyymmL
//199305
//199602
//199610
//199711
//199712
//199806
//199807
//199809
//199810
//199811
//199905
//199907
//199908
//200009
//200111
//200207
//200312
//200511
//200607
//200802
//200807
//200812
//200910
//201007
//201103
//201206
//201304
//201409
//201505
//201605
//201712
//201901
//201906
//202012
//202307
//__STDC_MB_MIGHT_NEQ_WC__ 1



#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

/**
 * @typedef max_align_t
 *
 * ISO/IEC 9899:2011 7.19
 */
typedef long double max_align_t;

#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1

//__STDC_LIB_EXT1__

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

#if defined(__STDDEF_H_WANT_size_t__)
/**
 * @typedef size_t
 *
 * ISO/IEC 9899:1990 7.1.6
 */
typedef unsigned long size_t;

#undef __STDDEF_H_WANT_size_t__
#endif
