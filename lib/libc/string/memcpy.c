/**
 * @file string/memcpy.c
 * @brief memcpy
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

void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
	for (int i = 0; i < (int)n; i++) {
		((unsigned char*)s1)[i] = ((unsigned char*)s2)[i];
	}
	return s1;
}
