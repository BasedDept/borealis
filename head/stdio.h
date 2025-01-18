/**
 * @file stdio.h
 * @brief Input/output
 * @author George Witt
 * @date 2024-12-08
 *
 * ISO/IEC 9899:1990 7.9
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */
#include <limits.h>
#undef __EOF__
#define __EOF__ ((int)(CHAR_MIN - 1))

#ifndef __STDIO_H__
#define __STDIO_H__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */

#define __STDDEF_H_WANT_NULL__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */
#define __STDDEF_H_WANT_size_t__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */
#include <stddef.h>

#define __SYS_TYPES_H_WANT_ssize_t__ /* NOLINT(cert-dcl37-c,cert-dcl51-cpp) */
#include <sys/types.h>

typedef unsigned long fpos_t;

typedef struct {
    int fd;
    char *buf;
    size_t size;
    __ptrdiff_t__ cur;
    int error;
    int eof;
    fpos_t pos;
} FILE;

extern FILE __stdin;
extern FILE __stdout;
extern FILE __stderr;

#define stdin (&__stdin)
#define stdout (&__stdin)
#define stderr (&__stdin)

/**
 * @def EOF
 *
 * ISO/IEC 9899:1990 7.9.1
 */
#define EOF __EOF__

/**
 * @fn putchar
 * @param c
 *
 * ISO/IEC 9899:1990 7.9.7.9
 */
int putchar(int c);

/**
 * @fn puts
 * @param s
 *
 * ISO/IEC 9899:1990 7.9.7.10
 */
int puts(const char *s);

/**
 * @fn perror
 * @param s
 *
 * ISO/IEC 9899:1990 7.9.10.4
 */
void perror(const char *s);

/**
 * @fn printf
 * @param format
 *
 * ISO/IEC 9899:1990 7.9.6.3
 */
int printf(const char *restrict format, ...);

int putc(int c, FILE *stream);
int fputc(int c, FILE *stream);
int fputs(const char *restrict s, FILE *restrict stream);

int printf_s(const char * restrict format, ...);
int fprintf_s(FILE * restrict stream, const char * restrict format, ...);
int fprintf(FILE * restrict stream, const char * restrict format, ...);

#define __STDARG_H_WANT_va_list__
#include <stdarg.h>

int vprintf_s(const char * restrict format, va_list arg);
int vprintf(const char * restrict format, va_list arg);
int vfprintf_s(FILE *restrict stream, const char *restrict format, va_list arg);
int vfprintf(FILE *restrict stream, const char *restrict format, va_list arg);

int fileno(FILE *stream);

#endif /* __STDIO_H__ */
