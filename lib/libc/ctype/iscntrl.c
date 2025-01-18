/**
 * @file ctype/iscntrl.c
 * @brief iscntrl
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int iscntrl(int c)
{
    return (c >= '\x00' && c <= '\x1f') || c == '\x7f';
}
