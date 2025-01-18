/**
 * @file ctype/isgraph.c
 * @brief isgraph
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isgraph(int c)
{
    return c >= '\x21' && c <= '\x7e';
}
