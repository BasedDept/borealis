/**
 * @file ctype/isdigit.c
 * @brief isdigit
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:1990 ?
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isdigit(int c)
{
    return c >= '0' && c <= '9';
}
