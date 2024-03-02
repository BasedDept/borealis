/**
 * @file string/strlen.c
 * @brief strlen
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.11.6.3
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

size_t strlen(const char *s)
{
   for (size_t i = 0;; i++) {
      if (*(s + i) == '\0') {
         return i;
      }
   }
}
