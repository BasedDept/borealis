/**
 * @file stdlib.h
 * @brief General utilities
 * @author George Witt
 * @date 2024-02-25
 *
 * ISO/IEC 9899:1990 7.10
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */

#ifndef __STDLIB_H__
#define __STDLIB_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

/**
 * @fn strtoul
 * @param nptr
 * @param endptr
 * @param base
 * @return
 *
 * ISO/IEC 9899:1990 7.10.1.6
 */
unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr,
                          int base);

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 0
#else

#define __STDDEF_H_WANT_size_t__
#include <stddef.h>

/**
 * @typedef errno_t
 *
 * ISO/IEC 9899:2011 K.3.6
 */
typedef int errno_t;

/**
 * @typedef rsize_t
 *
 * ISO/IEC 9899:2011 K.3.6
 */
typedef size_t rsize_t;

/**
 * @typedef rsize_t
 *
 * ISO/IEC 9899:2011 K.3.3
 */
typedef void (*constraint_handler_t)(const char *restrict msg,
                                     void *restrict ptr, errno_t error);
//__STDC_ANALYZABLE__ 1

int atoi(const char *str);

void *aligned_alloc(size_t alignment, size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

_Noreturn void abort(void);

constraint_handler_t set_constraint_handler_s(constraint_handler_t handler);
void abort_handler_s(const char * restrict msg, void * restrict ptr,
                     errno_t error);
void ignore_handler_s(const char * restrict msg, void * restrict ptr,
                      errno_t error);

extern constraint_handler_t __constraint_handler_s; /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#endif
#endif

#endif /* __STDLIB_H__ */
