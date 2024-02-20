/**
 * @file stdint.h
 * @brief Integer types
 * @author George Witt
 * @date 2024-02-11
 *
 * ISO/IEC 9899:1999 7.18
 * ISO/IEC 9899:2011 7.20
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#ifndef __STDINT_H__
#define __STDINT_H__

/**
 * @typedef intN_t
 *
 * ISO/IEC 9899:1999 7.18.1.1
 */
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
#if defined(__riscv) && __riscv_xlen == 32
typedef long long int64_t;
#else
typedef long int64_t;
#endif

/**
 * @typedef uintN_t
 *
 * ISO/IEC 9899:1999 7.18.1.1
 */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#if defined(__riscv) && __riscv_xlen == 32
typedef unsigned long long uint64_t;
#else
typedef unsigned long uint64_t;
#endif

/**
 * @typedef int_leastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.2
 */
typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

/**
 * @typedef uint_leastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.2
 */
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

/**
 * @typedef int_fastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.3
 */
typedef int8_t int_fast8_t;
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;

/**
 * @typedef uint_fastN_t
 *
 * ISO/IEC 9899:1999 7.18.1.3
 */
typedef uint8_t uint_fast8_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

/**
 * @typedef intptr_t
 *
 * ISO/IEC 9899:1999 7.18.1.4
 */
typedef long intptr_t;

/**
 * @typedef uintptr_t
 *
 * ISO/IEC 9899:1999 7.18.1.4
 */
typedef unsigned long uintptr_t;

/**
 * @typedef intmax_t
 *
 * ISO/IEC 9899:1999 7.18.1.5
 */
typedef long long intmax_t;

/**
 * @typedef uintmax_t
 *
 * ISO/IEC 9899:1999 7.18.1.5
 */
typedef unsigned long long uintmax_t;

/**
 * @def INTN_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.1
 */
#define INT8_MIN (-1-0x7f)
#define INT16_MIN (-1-0x7fff)
#define INT32_MIN (-1-0x7fffffff)
#define INT64_MIN (-1-0x7fffffffffffffffl)

/**
 * @def INTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.1
 */
#define INT8_MAX (0x7f)
#define INT16_MAX (0x7fff)
#define INT32_MAX (0x7fffffff)
#define INT64_MAX (0x7fffffffffffffffl)

/**
 * @def UINTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.1
 */
#define UINT8_MAX (0xff)
#define UINT16_MAX (0xffff)
#define UINT32_MAX (0xffffffffu)
#define UINT64_MAX (0xfffffffffffffffful)

/**
 * @def INT_LEASTN_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.2
 */
#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST64_MIN INT64_MIN

/**
 * @def INT_LEASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.2
 */
#define INT_LEAST8_MAX INT8_MAX
#define INT_LEAST16_MAX INT16_MAX
#define INT_LEAST32_MAX INT32_MAX
#define INT_LEAST64_MAX INT64_MAX

/**
 * @def UINT_LEASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.2
 */
#define UINT_LEAST8_MAX UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

/**
 * @def INT_FASTN_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.3
 */
#define INT_FAST8_MIN INT8_MIN
#define INT_FAST16_MIN INT32_MIN
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST64_MIN INT64_MIN

/**
 * @def INT_FASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.3
 */
#define INT_FAST8_MAX INT8_MAX
#define INT_FAST16_MAX INT32_MAX
#define INT_FAST32_MAX INT32_MAX
#define INT_FAST64_MAX INT64_MAX

/**
 * @def UINT_FASTN_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.3
 */
#define UINT_FAST8_MAX UINT8_MAX
#define UINT_FAST16_MAX UINT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

/**
 * @def INTPTR_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.4
 */
#if defined(__riscv) && __riscv_xlen == 32
#define INTPTR_MIN (-1-0x7fffffff)
#else
#define INTPTR_MIN (-1-0x7fffffffffffffff)
#endif

/**
 * @def INTPTR_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.4
 */
#if defined(__riscv) && __riscv_xlen == 32
#define INTPTR_MAX (0x7fffffff)
#else
#define INTPTR_MAX (0x7fffffffffffffff)
#endif

/**
 * @def UINTPTR_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.4
 */
#if defined(__riscv) && __riscv_xlen == 32
#define UINTPTR_MAX (0xffffffffu)
#else
#define UINTPTR_MAX (0xffffffffffffffffu)
#endif

/**
 * @def INTMAX_MIN
 *
 * ISO/IEC 9899:1999 7.18.2.5
 */
#define INTMAX_MIN (-1-0x7fffffffffffffffll)

/**
 * @def INTMAX_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.5
 */
#define INTMAX_MAX (0x7fffffffffffffffll)

/**
 * @def UINTMAX_MAX
 *
 * ISO/IEC 9899:1999 7.18.2.5
 */
#define UINTMAX_MAX (0xffffffffffffffffllu)

/**
 * @def PTRDIFF_MIN
 * @def PTRDIFF_MAX
 *
 * ISO/IEC 9899:1999 7.18.3
 */
#if defined(__riscv) && __riscv_xlen == 32
#define PTRDIFF_MIN (-1-0x7fffffff)
#define PTRDIFF_MAX (0x7fffffff)
#else
#define PTRDIFF_MIN (-1-0x7fffffffffffffff)
#define PTRDIFF_MAX (0x7fffffffffffffff)
#endif

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
#if defined(__riscv) && __riscv_xlen == 32
#define SIZE_MAX (0xffffffffu)
#else
#define SIZE_MAX (0xffffffffffffffffu)
#endif

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
#if defined(__riscv) && __riscv_xlen == 32
#define INT64_C(value) value ## LL
#else
#define INT64_C(value) value ## L
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
#if defined(__riscv) && __riscv_xlen == 32
#define UINT64_C(value) value ## ULL
#else
#define UINT64_C(value) value ## UL
#endif

/**
 * @def INTMAX_C
 * @param value
 *
 * ISO/IEC 9899:1999 7.18.4.2
 */
#if defined(__riscv) && __riscv_xlen == 32
#define INTMAX_C(value) value ## LL
#else
#define INTMAX_C(value) value ## L
#endif

/**
 * @def UINTMAX_C
 * @param value
 *
 * ISO/IEC 9899:1999 7.18.4.2
 */
#if defined(__riscv) && __riscv_xlen == 32
#define UINTMAX_C(value) value ## ULL
#else
#define UINTMAX_C(value) value ## UL
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1

/**
 * @def RSIZE_MAX
 *
 * ISO/IEC 9899:2011 K.3.2
 */
#define RSIZE_MAX ((rsize_t)SIZE_MAX)

#endif
#endif

#endif /* __STDINT_H__ */
#endif
