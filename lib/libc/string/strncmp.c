/**
 * @file string/strncmp.c
 * @brief strncmp
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.4.4
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int strncmp(const char *s1, const char *s2, size_t n)
{
   for (ptrdiff_t i = 0; i < n; i++) {
      ptrdiff_t cmp = (s1 + i) - (s2 + i);
      if (cmp != 0) {
         return cmp;
      }
      if (*(s1 + i) == '\0') {
         return 0;
      }
   }
   return 0;
}
