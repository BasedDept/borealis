/**
 * @file stdio/vprintf_s.c
 * @brief vprintf_s
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdarg.h>
#include <stdio.h>
#include "stdio_static.h"

int vprintf_s(const char * restrict format, va_list arg)
{
    return _vfsprintf(1, stdout, NULL, 0, 0, format, arg);
}
