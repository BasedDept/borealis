/**
 * @file string/strrchr.c
 * @brief strrchr
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.5.5
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

char *strrchr(const char *s, int c)
{
   const char *cur = s;
   const char *out = NULL;
   do {
      if (*cur == (char)c) {
         out = cur;
      }
      cur++;
   } while (*cur != '\0');

   return (char *)out;
}
