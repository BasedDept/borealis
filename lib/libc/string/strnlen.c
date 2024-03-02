/**
 * @file string/strnlen.c
 * @brief strnlen
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9945:2009 XBD.13 string.h
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <string.h>

size_t strnlen(const char *s, size_t maxlen)
{
   for (size_t i = 0; i < maxlen; i++) {
      if (*(s + i) == '\0') {
         return i + 1;
      }
   }

   return maxlen;
}
