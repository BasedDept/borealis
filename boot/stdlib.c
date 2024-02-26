/**
 * @file stdlib.c
 * @brief Statically linked stdlib.h functions
 * @author George Witt
 * @date 2024-02-25
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdlib.h>

#include <ctype.h>
#include <string.h>

unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr, int base)
{
   const char * restrict s = nptr;
   long int mag = 0;
   long int sign = 1;

   while (isspace(*s)) {
      s ++;
   }

   if (*s == '-') {
      sign = -1;
      s ++;
   }
   else if (*s == '+') {
      s ++;
   }

   if (base == 16 && (!strncmp("0x", s, 2) || !strncmp("0X", s, 2))) {
      s += 2;
   }

   char d = 36;
   while (1) {
      if (*s >= '0' && *s <= '9') {
         d = *s - 48;
      }
      else if (*s >= 'A' && *s <= 'Z') {
         d = *s - 65 + 10;
      }
      else if (*s >= 'a' && *s <= 'z') {
         d = *s - 97 + 10;
      }
      if (d > base - 1) {
         if (endptr != NULL) {
            *endptr = (char * restrict)s;
         }
         break;
      }
      mag += d;
      mag *= base;
      s += 1;
   }

   return (unsigned long int)(mag * sign);
}
