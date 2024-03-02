/**
 * @file string/memcmp.c
 * @brief memcmp
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.4.1
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
   for (size_t i = 0; i < n; i++) {
      int cmp = *(((unsigned char*)s1) + i) - *(((unsigned char*)s2) + i);
      if (cmp != 0) {
         return cmp;
      }
   }
   return 0;
}
