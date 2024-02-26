/**
 * @file string.h
 * @brief String handling
 * @author George Witt
 * @date 2024-02-25
 *
 * ISO/IEC 9899:1990 7.11
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __STRING_H__
#define __STRING_H__

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L && \
    (!defined(_POSIX_C_SOURCE) || !defined(_XOPEN_SOURCE))
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#endif

#define __STDDEF_H_WANT_NULL__
#define __STDDEF_H_WANT_size_t__
#include <stddef.h>

/**
 * @fn memcpy
 * @param s1
 * @param s2
 * @param n
 * @return
 *
 * ISO/IEC 9899:1990 7.11.2.1
 */
void *memcpy(void *restrict s1, const void *restrict s2, size_t n);

/**
 * @fn memmove
 * @param s1
 * @param s2
 * @param n
 * @return
 *
 * ISO/IEC 9899:1990 7.11.2.2
 */
void *memmove(void *s1, const void *s2, size_t n);

/**
 * @fn memcmp
 * @param s1
 * @param s2
 * @param n
 * @return
 *
 * ISO/IEC 9899:1990 7.11.4.1
 */
int memcmp(const void *s1, const void *s2, size_t n);

/**
 * @fn strncmp
 * @param s1
 * @param s2
 * @param n
 * @return
 *
 * ISO/IEC 9899:1990 7.11.4.4
 */
int strncmp(const char *s1, const char *s2, size_t n);

/**
 * @fn memchr
 * @param s
 * @param c
 * @param n
 * @return
 *
 * ISO/IEC 9899:1990 7.11.5.1
 */
void *memchr(const void *s, int c, size_t n);

/**
 * @fn strchr
 * @param s
 * @param c
 * @return
 *
 * ISO/IEC 9899:1990 7.11.5.2
 */
char *strchr(const char *s, int c);

/**
 * @fn strrchr
 * @param s
 * @param c
 * @return
 *
 * ISO/IEC 9899:1990 7.11.5.5
 */
char *strrchr(const char *s, int c);

/**
 * @fn memset
 * @param s
 * @param c
 * @param n
 * @return
 *
 * ISO/IEC 9899:1990 7.11.6.1
 */
void *memset(void *s, int c, size_t n);

/**
 * @fn strlen
 * @param s
 * @return
 *
 * ISO/IEC 9899:1990 7.11.6.3
 */
size_t strlen(const char * s);

#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L) || \
    (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 700)

/**
 * @fn strnlen
 * @param s
 * @param maxlen
 * @return
 *
 * ISO/IEC 9945:2009 XBD.13 string.h
 */
size_t strnlen(const char *s, size_t maxlen);

#endif

#endif /*__STRING_H__ */
