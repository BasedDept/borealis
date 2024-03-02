/**
 * @file stdio.c
 * @brief Statically linked stdio.h functions
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdio.h>

#include <string.h>
#include <errno.h>
#include "arch.h"

int putchar(int c)
{
    return firmware_putchar(c);
}

int puts(const char *s)
{
    return firmware_puts(s);
}
