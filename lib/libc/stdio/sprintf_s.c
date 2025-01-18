/**
 * @file stdio/puts.c
 * @brief puts
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdio.h>

#include <errno.h>

int puts(const char *s)
{
    errno = ENOSYS;
    return EOF;
}
