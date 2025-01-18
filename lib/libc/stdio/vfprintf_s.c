/**
 * @file stdio/vfprintf_s.c
 * @brief vfprintf_s
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#define __STDC_WANT_LIB_EXT1__ 1
#include "stdio_static.h"
#include <stdarg.h>
#include <stdio.h>

int vfprintf_s(FILE *restrict stream, const char *restrict format, va_list arg)
{
    return _vfsprintf(1, stream, NULL, 0, 0, format, arg);
}
