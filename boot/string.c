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

void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
	for (int i = 0; i < (int)n; i++) {
		((unsigned char*)s1)[i] = ((unsigned char*)s2)[i];
	}
	return s1;
}

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

int strncmp(const char *s1, const char *s2, size_t n)
{
   for (size_t i = 0; i < n; i++) {
      int cmp = (s1 + i) - (s2 + i);
      if (cmp != 0) {
         return cmp;
      }
      if (*(s1 + i) == '\0') {
         return 0;
      }
   }
   return 0;
}

void *memchr(const void *s, int c, size_t n)
{
   for (size_t i = 0; i < n; i++) {
      if (*(((unsigned char *)s) + i) == (unsigned char)c) {
         return (void *)(s + i);
      }
   }
   return NULL;
}

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

void *memset(void *s, int c, size_t n)
{
	for (int i = 0; i < (int)n; i++) {
		((unsigned char*)s)[i] = ((unsigned char)c);
	}
	return s;
}

size_t strlen(const char * s)
{
   for (size_t i = 0;; i++) {
      if (*(s + i) == '\0') {
         return i;
      }
   }
}

size_t strnlen(const char *s, size_t maxlen)
{
   for (size_t i = 0; i < maxlen; i++) {
      if (*(s + i) == '\0') {
         return i + 1;
      }
   }

   return maxlen;
}
