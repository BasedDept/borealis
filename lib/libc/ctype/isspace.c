/**
 * @file ctype/isspace.c
 * @brief isspace
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.3.1.9
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isspace(int c) {
    return (c >= '\t' && c <= '\r') || c == ' ';
}
