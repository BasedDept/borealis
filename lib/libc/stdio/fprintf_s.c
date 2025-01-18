/**
 * @file stdio/fprintf_s.c
 * @brief fprintf_s
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>

#include <stdarg.h>

int fprintf_s(FILE * restrict stream, const char * restrict format, ...)
{
    va_list arg;
    va_start(arg, format);

    int out = vfprintf_s(stream, format, arg);

    va_end(arg);
    return out;
}
