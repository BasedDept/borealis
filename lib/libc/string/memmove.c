/**
 * @file string/memmove.c
 * @brief memmove
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.2.2
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

void *memmove(void *s1, const void *s2, size_t n)
{
   if (s1 == s2) return s1;

   size_t o_n = n - (s1 - s2);
   o_n = o_n >= n ? n : o_n;

   if (o_n < n) {
      (void)memcpy(s1 + o_n, s2 + o_n, n - o_n);
   }
   return memcpy(s1, s2, o_n);
}
