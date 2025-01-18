/**
 * @file panic.c
 * @brief Kernel errors
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include "panic.h"

#include <stdint.h>
#include <stdnoreturn.h>
#include <errno.h>
#include <stdio.h>

// NOLINTNEXTLINE(cert-dcl37-c)
static inline void _putx(unsigned long x)
{
    fputs("0x", stdout);
    for (int i = (sizeof(x) << 3) - 4; i >= 0; i-=4) {
        uint8_t nibble = (x >> i) & 0xf;
        if (nibble > 9) (void)putchar(nibble + 'a' - 10);
        else (void)putchar(nibble + '0');
    }
}

// NOLINTNEXTLINE(cert-dcl37-c)
static inline void _putd(long x)
{
    long y = x;
    char str[22];
    short i = sizeof(str) - 2;
    short off = 1;

    str[21] = '\0';

    if (y < 0) {
        y = -y;
        off--;
    }

    for (; i > 0; i--) {
        str[i] = (char)(y % 10) + '0';
        y /= 10;
        if (0 == y) break;
    }

    i--;
    str[i] = '-';
    off += i;

    fputs(str + off, stdout);
}

#ifndef __PROGNAME
// NOLINTNEXTLINE(cert-dcl37-c)
#define __PROGNAME "(undefined)"
#endif

// NOLINTNEXTLINE(cert-dcl37-c)
noreturn void _panic(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg)
{
    fputs("\x1b[2J\x1b[0;0H\x1b[1;31m"
         "!!! Panic !!!"
         "\x1b[0m"    " ------------------------------------------------------------------\n", stdout);
    fputs("\n"
         "   ###    ##                ###      ##                 ####          ####      \n"
         "  ##      ##  ##        ##    ##     ##                 ####          ####      \n"
         " ##       ## #  #      #  #    ##    ##                 ####          ####      \n"
         " ##    ####   ##  ####  ##     ## ####             ############################ \n"
         " ##               #  #         ##         ######   ############################ \n"
         "  ##              ####        ##        ##      ##                              \n"
         "   ###                      ###                                                 \n\n", stdout);
    fputs("An unrecoverable error has occurred. The system must be rebooted. The following\n"
         "information may be useful for troubleshooting.\n\n", stdout);
    errno = err;
    perror(msg);
    fputs("\n"
         "Program: " __PROGNAME, stdout);
    fputs("\n"
         "File: ", stdout);
    fputs(file, stdout);
    fputs("\n"
         "Line: ", stdout);
    _putd(line);
    fputs("\n"
         "Function: ", stdout);
    fputs(func, stdout);
    fputs("\n"
         "Address: ", stdout);
    _putx((unsigned long)ptr);
    fputs("\n", stdout);

    _halt();
}

// NOLINTNEXTLINE(cert-dcl37-c)
void _oops(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg)
{
    fputs("\x1b[2J\x1b[0;0H\x1b[1;33m"
         "!!! Oops !!!"
         "\x1b[0m"   " -------------------------------------------------------------------\n", stdout);
    fputs("\n"
         " ####### ##                 ### ##   ##     ## ###                 ## #######   \n"
         "          ##               ##    ##   ##    ##   ##               ##            \n"
         "           ##             ##      ##   ##   ##    ##             ##             \n"
         "            ##            ##               ##     ##            ##              \n"
         "             ##           ##             ##       ##           ##               \n"
         "              ##           ##         ####       ##           ##                \n"
         "               ## #######   ###  #####         ###   ####### ##                 \n\n", stdout);
    fputs("An error has occurred. The system will attempt to continue running, but it may\n"
         "be unreliable. The following information may be useful for troubleshooting.\n\n", stdout);
    errno = err;
    perror(msg);
    fputs("\n"
         "Program: " __PROGNAME, stdout);
    fputs("\n"
         "File: ", stdout);
    fputs(file, stdout);
    fputs("\n"
         "Line: ", stdout);
    _putd(line);
    fputs("\n"
         "Function: ", stdout);
    fputs(func, stdout);
    fputs("\n"
         "Address: ", stdout);
    _putx((unsigned long)ptr);
    fputs("\n\n", stdout);
    fputs("--------------------------------------------------------------------------------\n", stdout);
}

__attribute__((noinline))
// NOLINTNEXTLINE(cert-dcl37-c)
noreturn void _panic_wrapper(int err, const char * file, int line,
                                    const char * func, const char * msg)
{
    void *ptr = NULL;
#ifdef __riscv
    __asm__ volatile ("mv %0, ra" : "=r" (ptr) :: "ra");
#endif
    _panic(err, ptr, file, line, func, msg);
}

__attribute__((noinline))
// NOLINTNEXTLINE(cert-dcl37-c)
void _oops_wrapper(int err, const char * file, int line,
                                    const char * func, const char * msg)
{
    void *ptr = NULL;
#ifdef __riscv
    __asm__ volatile ("mv %0, ra" : "=r" (ptr) :: "ra");
#endif
    _oops(err, ptr, file, line, func, msg);
}
