/**
 * @file string/strchr.c
 * @brief strchr
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.5.2
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

char *strchr(const char *s, int c)
{
   const char *cur = s;
   do {
      if (*cur == (char)c) {
         return (char *)cur;
      }
      cur++;
   } while (*cur != '\0');

   return NULL;
}
