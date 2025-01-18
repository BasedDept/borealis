/**
 * @file ctype/isupper.c
 * @brief isupper
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}
