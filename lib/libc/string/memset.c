/**
 * @file string/memset.c
 * @brief memset
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.6.1
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

#include <stddef.h>

void *memset(void *s, int c, size_t n)
{
	for (int i = 0; i < (int)n; i++) {
		((unsigned char*)s)[i] = ((unsigned char)c);
	}
	return s;
}
