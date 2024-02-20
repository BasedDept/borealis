/**
 * @file limits.h
 * @brief Sizes of integer types
 * @author George Witt
 * @date 2024-02-11
 *
 * ISO/IEC 9899:1990 7.1.5
 * ISO/IEC 9899:1999 7.10
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __LIMITS_H__
#define __LIMITS_H__

/**
 * @def CHAR_BIT
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define CHAR_BIT (8)

/**
 * @def MB_LEN_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define MB_LEN_MAX (4)

/**
 * @def SCHAR_MIN
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define SCHAR_MIN (-128)

/**
 * @def SCHAR_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define SCHAR_MAX (127)

/**
 * @def UCHAR_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define UCHAR_MAX (255)


/**
 * @def CHAR_MIN
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#if '\xff' > 0
#define CHAR_MIN (0)
#else
#define CHAR_MIN SCHAR_MIN
#endif

/**
 * @def CHAR_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#if '\xff' > 0
#define CHAR_MAX UCHAR_MAX
#else
#define CHAR_MAX SCHAR_MAX
#endif

/**
 * @def SHRT_MIN
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define SHRT_MIN (-32768)

/**
 * @def SHRT_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define SHRT_MAX (32767)

/**
 * @def USHRT_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define USHRT_MAX (65535)

/**
 * @def INT_MIN
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define INT_MIN (-2147483648)

/**
 * @def INT_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define INT_MAX (2147483647)

/**
 * @def UINT_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#define UINT_MAX (4294967295U)

/**
 * @def LONG_MIN
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#if defined(__riscv) && __riscv_xlen == 32
#define LONG_MIN INT_MIN
#else
#define LONG_MIN (-9223372036854775808L)
#endif

/**
 * @def LONG_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#if defined(__riscv) && __riscv_xlen == 32
#define LONG_MAX INT_MAX
#else
#define LONG_MAX (9223372036854775807L)
#endif

/**
 * @def ULONG_MAX
 *
 * ISO/IEC 9899:1990 5.2.4.2.1
 */
#if defined(__riscv) && __riscv_xlen == 32
#define ULONG_MAX UINT_MAX
#else
#define ULONG_MAX (18446744073709551615UL)
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/**
 * @def LLONG_MIN
 *
 * ISO/IEC 9899:1999 5.2.4.2.1
 */
#define LLONG_MIN (-9223372036854775808LL)

/**
 * @def LLONG_MAX
 *
 * ISO/IEC 9899:1999 5.2.4.2.1
 */
#define LLONG_MAX (9223372036854775807LL)

/**
 * @def ULLONG_MAX
 *
 * ISO/IEC 9899:1999 5.2.4.2.1
 */
#define ULLONG_MAX (18446744073709551615ULL)

#endif

#endif /* __LIMITS_H__ */
