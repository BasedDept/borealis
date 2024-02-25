/**
 * @file string.h
 * @brief String handling
 * @author George Witt
 * @date 2024-01-02
 *
 * ISO/IEC 9899:1990 7.11
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __STRING_H__
#define __STRING_H__

#define __STDDEF_H_WANT_NULL__
#define __STDDEF_H_WANT_size_t__
#include <stddef.h>

/**
 * @fn strlen
 * @param s
 * @return
 *
 * ISO/IEC 9899:1990 7.11.6.3
 */
size_t strlen(const char * s);

#endif /*__STRING_H__ */
