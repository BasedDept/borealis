/**
 * @file ctype/isxdigit.c
 * @brief isxdigit
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isxdigit(int c)
{
    return (c >= '0' && c <= '9') ||
           (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
