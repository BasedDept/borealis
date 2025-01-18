/**
 * @file string/strncpy.c
 * @brief strncpy
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.2.1
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

#include <stddef.h>

char *strncpy(char *restrict s1, const char *restrict s2, size_t n)
{
	for (int i = 0; i < (int)n; i++) {
		s1[i] = s2[i];
		if (s2[i] == 0) break;
	}
	return s1;
}
