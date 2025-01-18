/**
 * @file stdio/printf.c
 * @brief printf
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdarg.h>
#include <stdio.h>

int printf(const char * restrict format, ...)
{
    va_list arg;
    va_start(arg, format);

    int out = vfprintf(stdout, format, arg);

    va_end(arg);
    return out;
}
