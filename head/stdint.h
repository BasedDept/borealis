/**
 * @file stdint.h
 * @brief Integer types
 * @author George Witt
 * @date 2024-12-15
 *
 * ISO/IEC 9899:1999 7.18
 * ISO/IEC 9899:2011 7.20
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

#undef __int8_t__
#define __int8_t__ signed char
#undef __uint8_t__
#define __uint8_t__ unsigned char
#undef __int16_t__
#define __int16_t__ short
#undef __uint16_t__
#define __uint16_t__ unsigned short
#undef __int32_t__
#define __int32_t__ int
#undef __uint32_t__
#define __uint32_t__ unsigned int

#undef __int64_t__
#undef __uint64_t__
#undef __INTPTR_MIN__
#undef __INTPTR_MAX__
#undef __UINTPTR_MAX__
#undef __PTRDIFF_MIN__
#undef __PTRDIFF_MAX__
#undef __SIZE_MAX__
#undef __RSIZE_MAX__
#if defined(__riscv) && __riscv_xlen == 64
#define __int64_t__ long
#define __uint64_t__ unsigned long
#undef __int128_t__
#define __int128_t__ __int128
#undef __uint128_t__
#define __uint128_t__ unsigned __int128
#define __INTPTR_MIN__ (-1-0x7fffffffffffffffl)
#define __INTPTR_MAX__ (0x7fffffffffffffffl)
#define __UINTPTR_MAX__ (0xfffffffffffffffful)
#define __PTRDIFF_MIN__ (-1-0x7fffffffffffffffl)
#define __PTRDIFF_MAX__ (0x7fffffffffffffffl)
#define __SIZE_MAX__ (0xfffffffffffffffful)
#define __RSIZE_MAX__ (0x7ffffffffffffffful)
#define __INT64_C__(value) value ## L
#define __UINT64_C__(value) value ## UL

#else
#define __int64_t__ long long
#define __uint64_t__ unsigned long long
#define __INTPTR_MIN__ (-1-0x7fffffff)
#define __INTPTR_MAX__ (0x7fffffff)
#define __UINTPTR_MAX__ (0xffffffffu)
#define __PTRDIFF_MIN__ (-1-0x7fffffffl)
#define __PTRDIFF_MAX__ (0x7fffffffl)
#define __SIZE_MAX__ (0xfffffffful)
#define __RSIZE_MAX__ (0x7ffffffful)
#define __INT64_C__(value) value ## LL
#define __UINT64_C__(value) value ## ULL

#endif

#undef __intptr_t__
#define __intptr_t__ long
#undef __uintptr_t__
#define __uintptr_t__ unsigned long

#ifndef __STDINT_H__
#define __STDINT_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

/**
 * @typedef intN_t
 *
 * ISO/IEC 9899:1999 7.18.1.1
 */
typedef __int8_t__ int8_t;
typedef __int16_t__ int16_t;
typedef __int32_t__ int32_t;
#ifdef __int64_t__
typedef __int64_t__ int64_t;
#endif
#ifdef __int128_t__
typedef __int128_t__ int128_t;
#endif

/**
 * @typedef uintN_t
 *
 * ISO/IEC 9899:1999 7.18.1.1
 */
typedef __uint8_t__ uint8_t;
typedef __uint16_t__ uint16_t;
typedef __uint32_t__ uint32_t;
#ifdef __uint64_t__
typedef __uint64_t__ uint64_t;
#endif
#ifdef __uint128_t__
typedef __uint128_t__ uint128_t;
#endif

/**
 * @typedef int_leastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.2
 */
typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
#ifdef __int64_t__
typedef int64_t int_least64_t;
#else
typedef long long int_least64_t;
#endif
#ifdef __int128_t__
typedef int128_t int_least128_t;
#endif

/**
 * @typedef uint_leastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.2
 */
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
#ifdef __uint64_t__
typedef uint64_t uint_least64_t;
#else
typedef unsigned long long uint_least64_t;
#endif
#ifdef __uint128_t__
typedef uint128_t uint_least128_t;
#endif

/**
 * @typedef int_fastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.3
 */
typedef int8_t int_fast8_t;
#if __WORD_BIT__ == 64
typedef int64_t int_fast16_t;
typedef int64_t int_fast32_t;
#else
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
#endif
typedef int64_t int_fast64_t;
#ifdef __int128_t__
typedef int128_t int_fast128_t;
#endif

/**
 * @typedef uint_fastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.3
 */
typedef uint8_t uint_fast8_t;
#if __WORD_BIT__ == 64
typedef uint64_t uint_fast16_t;
typedef uint64_t uint_fast32_t;
#else
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
#endif
typedef uint64_t uint_fast64_t;
#ifdef __uint128_t__
typedef uint128_t uint_fast128_t;
#endif

/**
 * @typedef intptr_t
 *
 * ISO/IEC 9899:1999 7.18.1.4
 */
typedef __intptr_t__ intptr_t;

/**
 * @typedef uintptr_t
 *
 * ISO/IEC 9899:1999 7.18.1.4
 */
typedef __uintptr_t__ uintptr_t;

/**
 * @typedef intmax_t
 *
 * ISO/IEC 9899:1999 7.18.1.5
 */
#ifdef __int128_t__
typedef __int128_t__ intmax_t;
#else
typedef long long intmax_t;
#endif

/**
 * @typedef uintmax_t
 *
 * ISO/IEC 9899:1999 7.18.1.5
 */
#ifdef __uint128_t__
typedef __uint128_t__ uintmax_t;
#else
typedef unsigned long long uintmax_t;
#endif

/**
 * @def INTN_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.1
 */
#define INT8_MIN (-1-0x7f)
#define INT16_MIN (-1-0x7fff)
#define INT32_MIN (-1-0x7fffffff)
#define INT64_MIN (-1-0x7fffffffffffffffl)
#ifdef __int128_t__
#define INT128_MIN ((int128_t)(-1-0x7fffffffffffffffffffffffffffffff))
#endif

/**
 * @def INTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.1
 */
#define INT8_MAX (0x7f)
#define INT16_MAX (0x7fff)
#define INT32_MAX (0x7fffffff)
#define INT64_MAX (0x7fffffffffffffffl)
#ifdef __int128_t__
#define INT128_MAX ((int128_t)(0x7fffffffffffffffffffffffffffffff))
#endif

/**
 * @def UINTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.1
 */
#define UINT8_MAX (0xff)
#define UINT16_MAX (0xffff)
#define UINT32_MAX (0xffffffffu)
#define UINT64_MAX (0xfffffffffffffffful)
#ifdef __uint128_t__
#define UINT128_MAX ((uint128_t)(0xffffffffffffffffffffffffffffffff))
#endif

/**
 * @def INT_LEASTN_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.2
 */
#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST64_MIN INT64_MIN
#ifdef __int128_t__
#define INT_LEAST128_MIN INT128_MIN
#endif

/**
 * @def INT_LEASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.2
 */
#define INT_LEAST8_MAX INT8_MAX
#define INT_LEAST16_MAX INT16_MAX
#define INT_LEAST32_MAX INT32_MAX
#define INT_LEAST64_MAX INT64_MAX
#ifdef __int128_t__
#define INT_LEAST128_MAX INT128_MAX
#endif

/**
 * @def UINT_LEASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.2
 */
#define UINT_LEAST8_MAX UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX
#ifdef __uint128_t__
#define UINT_LEAST128_MAX UINT128_MAX
#endif

/**
 * @def INT_FASTN_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.3
 */
#define INT_FAST8_MIN INT8_MIN
#define INT_FAST16_MIN INT32_MIN
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST64_MIN INT64_MIN
#ifdef __int128_t__
#define INT_FAST128_MIN INT128_MIN
#endif

/**
 * @def INT_FASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.3
 */
#define INT_FAST8_MAX INT8_MAX
#define INT_FAST16_MAX INT32_MAX
#define INT_FAST32_MAX INT32_MAX
#define INT_FAST64_MAX INT64_MAX
#ifdef __int128_t__
#define INT_FAST128_MAX INT128_MAX
#endif

/**
 * @def UINT_FASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.3
 */
#define UINT_FAST8_MAX UINT8_MAX
#define UINT_FAST16_MAX UINT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX
#ifdef __uint128_t__
#define UINT_FAST128_MAX UINT128_MAX
#endif

/**
 * @def INTPTR_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.4
 */
#define INTPTR_MIN __INTPTR_MIN__

/**
 * @def INTPTR_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.4
 */
#define INTPTR_MAX __INTPTR_MAX__

/**
 * @def UINTPTR_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.4
 */
#define UINTPTR_MAX __UINTPTR_MAX__

/**
 * @def INTMAX_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.5
 */
#ifdef __uint128_t__
#define INTMAX_MIN INT128_MIN
#else
#define INTMAX_MIN INT_LEAST64_MIN
#endif

/**
 * @def INTMAX_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.5
 */
#ifdef __uint128_t__
#define INTMAX_MAX INT128_MAX
#else
#define INTMAX_MAX INT_LEAST64_MAX
#endif

/**
 * @def UINTMAX_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.5
 */
#ifdef __uint128_t__
#define UINTMAX_MAX UINT128_MAX
#else
#define UINTMAX_MAX UINT_LEAST64_MAX
#endif

/**
 * @def PTRDIFF_MIN
 * @def PTRDIFF_MAX
 *
 * ISO/IEC 9899:1999 7.18.3
 */
#define PTRDIFF_MIN __PTRDIFF_MIN__
#define PTRDIFF_MAX __PTRDIFF_MAX__

/**
 * @def SIG_ATOMIC_MIN
 * @def SIG_ATOMIC_MAX
 *
 * ISO/IEC 9899:1999 7.18.3
 */
#define SIG_ATOMIC_MIN (-1-0x7fffffff)
#define SIG_ATOMIC_MAX (0x7fffffff)

/**
 * @def SIZE_MAX
 *
 * ISO/IEC 9899:1999 7.18.3
 */
#define SIZE_MAX __SIZE_MAX__

/**
 * @def WCHAR_MIN
 * @def WCHAR_MAX
 *
 * ISO/IEC 9899:1999 7.18.3
 */
#define WCHAR_MIN (-1-0x7fffffff)
#define WCHAR_MAX (0x7fffffff)

/**
 * @def WINT_MIN
 * @def WINT_MAX
 *
 * ISO/IEC 9899:1999 7.18.3
 */
#define WINT_MIN (-1-0x7fffffffffffffffll)
#define WINT_MAX (0x7fffffffffffffffll)

/**
 * @def INTN_C
 * @param value
 *
 * ISO/IEC 9899:1999 7.18.4.1
 */
#define INT8_C(value) value
#define INT16_C(value) value
#define INT32_C(value) value
#define INT64_C __INT64_C__
#ifdef __int128_t__
#define INT128_C(value) ((int128_t)value)
#endif

/**
 * @def UINTN_C
 * @param value
 *
 * ISO/IEC 9899:1999 7.18.4.1
 */
#define UINT8_C(value) value
#define UINT16_C(value) value
#define UINT32_C(value) value ## U
#define UINT64_C __UINT64_C__
#ifdef __uint128_t__
#define UINT128_C(value) ((uint128_t)value)
#endif

/**
 * @def INTMAX_C
 * @param value
 *
 * ISO/IEC 9899:1999 7.18.4.2
 */
#ifdef __int128_t__
#define INTMAX_C(value) ((int128_t)value)
#else
#define INTMAX_C(value) value ## LL
#endif

/**
 * @def UINTMAX_C
 * @param value
 *
 * ISO/IEC 9899:1999 7.18.4.2
 */
#ifdef __uint128_t__
#define UINTMAX_C(value) ((uint128_t)value)
#else
#define UINTMAX_C(value) value ## ULL
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1

/**
 * @def RSIZE_MAX
 *
 * ISO/IEC 9899:2011 K.3.2
 */
#define RSIZE_MAX __RSIZE_MAX__

#endif
#endif

#endif /* __STDINT_H__ */
#endif
