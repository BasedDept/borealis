/**
 * @file stdio/vprintf.c
 * @brief vprintf
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdarg.h>
#include <stdio.h>
#include "stdio_static.h"

int vprintf(const char * restrict format, va_list arg)
{
    return _vfsprintf(0, stdout, NULL, 0, 0, format, arg);
}
