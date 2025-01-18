/**
 * @file stdio/putchar.c
 * @brief putchar
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdio.h>

int putchar(int c)
{
    return putc(c, stdout);
}
