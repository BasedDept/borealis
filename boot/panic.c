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

static inline void _putx(unsigned long x)
{
    puts("0x");
    for (int i = (sizeof(x) << 3) - 4; i >= 0; i-=4) {
        uint8_t nibble = (x >> i) & 0xf;
        if (nibble > 9) (void)putchar(nibble + 'a' - 10);
        else (void)putchar(nibble + '0');
    }
}

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

    puts(str + off);
}

#ifndef __PROGNAME
#error "__PROGNAME not defined!"
#endif

noreturn void _panic(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg)
{
    puts("\x1b[2J\x1b[0;0H\x1b[1;31m"
         "!!! Panic !!!"
         "\x1b[0m"    " ------------------------------------------------------------------\n");
    puts("\n"
         "   ###    ##                ###      ##                 ####          ####      \n"
         "  ##      ##  ##        ##    ##     ##                 ####          ####      \n"
         " ##       ## #  #      #  #    ##    ##                 ####          ####      \n"
         " ##    ####   ##  ####  ##     ## ####             ############################ \n"
         " ##               #  #         ##         ######   ############################ \n"
         "  ##              ####        ##        ##      ##                              \n"
         "   ###                      ###                                                 \n\n");
    puts("An unrecoverable error has occurred. The system must be rebooted. The following\n"
         "information may be useful for troubleshooting.\n\n");
    errno = err;
    perror(msg);
    puts("\n"
         "Program: " __PROGNAME);
    puts("\n"
         "File: ");
    puts(file);
    puts("\n"
         "Line: ");
    _putd(line);
    puts("\n"
         "Function: ");
    puts(func);
    puts("\n"
         "Address: ");
    _putx((unsigned long)ptr);
    puts("\n");

    _halt();
}

void _oops(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg)
{
    puts("\x1b[2J\x1b[0;0H\x1b[1;33m"
         "!!! Oops !!!"
         "\x1b[0m"   " -------------------------------------------------------------------\n");
    puts("\n"
         " ####### ##                 ### ##   ##     ## ###                 ## #######   \n"
         "          ##               ##    ##   ##    ##   ##               ##            \n"
         "           ##             ##      ##   ##   ##    ##             ##             \n"
         "            ##            ##               ##     ##            ##              \n"
         "             ##           ##             ##       ##           ##               \n"
         "              ##           ##         ####       ##           ##                \n"
         "               ## #######   ###  #####         ###   ####### ##                 \n\n");
    puts("An error has occurred. The system will attempt to continue running, but it may\n"
         "be unreliable. The following information may be useful for troubleshooting.\n\n");
    errno = err;
    perror(msg);
    puts("\n"
         "Program: " __PROGNAME);
    puts("\n"
         "File: ");
    puts(file);
    puts("\n"
         "Line: ");
    _putd(line);
    puts("\n"
         "Function: ");
    puts(func);
    puts("\n"
         "Address: ");
    _putx((unsigned long)ptr);
    puts("\n\n");
    puts("--------------------------------------------------------------------------------\n");
}
