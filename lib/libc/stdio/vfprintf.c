/**
 * @file stdio/vfprintf.c
 * @brief vfprintf
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#include "stdio_static.h"
#include <stdarg.h>
#include <stdio.h>

FILE __stdin = { .fd = 0 };
FILE __stdout = { .fd = 1 };
FILE __stderr = { .fd = 2 };

int vfprintf(FILE *restrict stream, const char *restrict format, va_list arg)
{
    return _vfsprintf(0, stream, NULL, 0, 0, format, arg);
}
