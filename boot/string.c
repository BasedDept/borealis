/**
 * @file string.c
 * @brief Statically linked string.h functions
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <string.h>

size_t strlen(const char * s)
{
   for (size_t i = 0;; i++) {
      if (*(s + i) == '\0') {
         return i;
      }
   }
}
