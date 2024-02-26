/**
 * @file ctype.c
 * @brief Statically linked ctype.h functions
 * @author George Witt
 * @date 2024-02-25
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <ctype.h>

int isspace(int c) {
   switch (c) {
   case ' ':
   case '\f':
   case '\n':
   case '\r':
   case '\t':
   case '\v':
      return 1;
   }
   return 0;
}
