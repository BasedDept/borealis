/**
 * @file stdio/fprintf.c
 * @brief fprintf
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdarg.h>
#include <stdio.h>

int fprintf(FILE * restrict stream, const char * restrict format, ...)
{
    va_list arg;
    va_start(arg, format);

    int out = vfprintf(stream, format, arg);

    va_end(arg);
    return out;
}
