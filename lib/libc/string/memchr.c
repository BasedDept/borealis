/**
 * @file string/memchr.c
 * @brief memchr
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.5.1
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

void *memchr(const void *s, int c, size_t n)
{
   for (size_t i = 0; i < n; i++) {
      if (*(((unsigned char *)s) + i) == (unsigned char)c) {
         return (void *)(s + i);
      }
   }
   return NULL;
}
