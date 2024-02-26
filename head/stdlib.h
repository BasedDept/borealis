/**
 * @file stdlib.h
 * @brief General utilities
 * @author George Witt
 * @date 2024-02-25
 *
 * ISO/IEC 9899:1990 7.10
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __STDLIB_H__
#define __STDLIB_H__

/**
 * @fn strtoul
 * @param nptr
 * @param endptr
 * @param base
 * @return
 *
 * ISO/IEC 9899:1990 7.10.1.6
 */
unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr,
                          int base);

#endif /* __STDLIB_H__ */
