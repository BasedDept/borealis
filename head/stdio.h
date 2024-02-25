/**
 * @file stdio.h
 * @brief Input/output
 * @author George Witt
 * @date 2024-02-24
 *
 * ISO/IEC 9899:1990 7.9
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __STDIO_H__
#define __STDIO_H__

#define __STDDEF_H_WANT_NULL__
#define __STDDEF_H_WANT_size_t__
#include <stddef.h>

/**
 * @def EOF
 *
 * ISO/IEC 9899:1990 7.9.1
 */
#define EOF (-1)

/**
 * @fn putchar
 * @param c
 *
 * ISO/IEC 9899:1990 7.9.7.9
 */
int putchar(int c);

/**
 * @fn puts
 * @param s
 *
 * ISO/IEC 9899:1990 7.9.7.10
 */
int puts(const char *s);

/**
 * @fn perror
 * @param s
 *
 * ISO/IEC 9899:1990 7.9.10.4
 */
void perror(const char *s);

#endif /* __STDIO_H__ */
