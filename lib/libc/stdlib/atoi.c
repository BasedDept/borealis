/**
 * @file stdlib/atoi.c
 * @brief strtoul
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdlib.h>

#include <ctype.h>

int atoi(const char *str)
{
    const char *str_l = str;
    int out = 0;
    int neg = 0;
    while (isspace(*str_l)) str_l++;
    if (*str_l == '+') str_l++;
    else if (*str_l == '-') {
        neg = 1;
        str_l++;
    }
    while (*str_l >= '0' && *str_l <= '9') {
        out *= 10;
        out += *str_l - '0';
        str_l++;
    }
    if (neg) {
        out = 0 - out;
    }
    return out;
}
