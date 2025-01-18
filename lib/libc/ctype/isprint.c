/**
 * @file ctype/isprint.c
 * @brief isprint
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isprint(int c)
{
    return c >= '\x20' && c <= '\x7e';
}
