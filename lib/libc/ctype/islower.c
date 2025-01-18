/**
 * @file ctype/islower.c
 * @brief islower
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int islower(int c)
{
    return c >= 'a' && c <= 'z';
}
