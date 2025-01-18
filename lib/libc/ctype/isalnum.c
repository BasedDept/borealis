/**
 * @file ctype/isalnum.c
 * @brief isalnum
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isalnum(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}
