/**
 * @file stdio/puts.c
 * @brief puts
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <limits.h>
#include <stdio.h>

int puts(const char *s)
{
    int r1 = fputs(s, stdout);
    if (r1 < 0) return r1;
    int r2 = fputs("\n", stdout);
    if (r2 < 0) return r2;
    return (INT_MAX - r1 >= r2) ? r1 + r2 : INT_MAX;
}
