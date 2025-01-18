/**
 * @file stdlib/strtoul.c
 * @brief strtoul
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.10.1.6
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr, int base)
{
    const char *restrict s = nptr;
    long int mag = 0;
    long int sign = 1;
 
    while (isspace(*s)) {
        s ++;
    }
 
    if (*s == '-') {
        sign = -1;
        s ++;
    }
    else if (*s == '+') {
        s ++;
    }
 
    if (base == 16 && (!strncmp("0x", s, 2) || !strncmp("0X", s, 2))) {
        s += 2;
    }
 
    char d = (char)36;
    while (1) {
        if (*s >= '0' && *s <= '9') {
            d = *s;
            d -= 48;
        }
        else if (*s >= 'A' && *s <= 'Z') {
            d = *s;
            d -= 55;
        }
        else if (*s >= 'a' && *s <= 'z') {
            d = *s;
            d -= 87;
        }
        if (d > base - 1) {
            if (endptr != NULL) {
                *endptr = (char * restrict)s;
            }
            break;
        }
        mag += d;
        mag *= base;
        s += 1;
    }
 
    return (unsigned long int)(mag * sign);
}
