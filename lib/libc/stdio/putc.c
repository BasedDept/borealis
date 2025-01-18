/**
 * @file stdio/putc.c
 * @brief putc
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdio.h>

int putc(int c, FILE *stream)
{
    return fputc(c, stream);
}
