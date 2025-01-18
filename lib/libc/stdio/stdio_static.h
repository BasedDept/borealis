/**
 * @file stdio/stdio_static.h
 * @brief stdio static defs
 * @author George Witt
 * @date 2024-11-27
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */

#include <stdio.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>

int _vfsprintf(int k,
               FILE *restrict stream,
               char *restrict s,
               size_t n,
               rsize_t max,
               const char *restrict format,
               va_list arg);

