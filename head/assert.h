/**
 * @file assert.h
 * @brief Diagnostics
 * @author George Witt
 * @date 2024-11-30
 *
 * ISO/IEC 9899:1990 7.2
 * ISO/IEC 9899:1999 7.2
 * ISO/IEC 9899:2011 7.2
 * ISO/IEC 9899:2024 7.2
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#ifdef NDEBUG

/**
 * @def assert
 * @param ignore
 */
#define assert(ignore) ((void)0)

#else

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/**
 * @def assert
 * @param expression
 */
#define assert(expression) \
    ((void)((expression) || \
    (__assert_fail_v199901(#expression, __FILE__, __LINE__, __func__), 0)))

#else

/**
 * @def assert
 * @param expression
 */
#define assert(expression) \
    ((void)((expression) || \
     (__assert_fail(#expression, __FILE__, __LINE__), 0)))

#endif

#endif

#ifndef __ASSERT_H__
#define __ASSERT_H__

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

/**
 * @def static_assert
 */
#define static_assert _Static_assert

#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L

/**
 * @def __STDC_VERSION_ASSERT_H__
 */
#define __STDC_VERSION_ASSERT_H__ 202311L

#endif

#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 202311L

[[noreturn]]
extern void __assert_fail_v199901(const char *, const char *, int,
                                               const char *);

#elif __STDC_VERSION__ >= 201112L && __STDC_VERSION__ <= 202311L

extern _Noreturn void __assert_fail_v199901(const char *, const char *, int,
                                            const char *);

#elif __STDC_VERSION__ >= 199901L && __STDC_VERSION__ <= 201112L

extern void __assert_fail_v199901(const char *, const char *, int,
                                  const char *);
#else

extern void __assert_fail(const char *, const char *, int);

#endif
#endif

#endif /* __ASSERT_H__ */
