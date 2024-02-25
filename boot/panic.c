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
      if (nibble > 9) (void)putchar(nibble + 87);
      else (void)putchar(nibble + 48);
   }
}

noreturn void _panic(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg)
{
    puts("\x1b[2J\x1b[0;0H");
    puts("\x1b[1;31m!!! Panic !!!\x1b[0m ------------------------------------------------------------------\n");
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
    puts("\nProgram: " __PROGNAME);
    puts("\nFile: ");
    puts(file);
    puts("\nLine: ");
    //puts(line);
    puts("\nFunction: ");
    puts(func);
    puts("\n");
    puts("Address: ");
    _putx((unsigned long)ptr);
    puts("\n");
    _halt();
}

void _oops(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg)
{
    puts("\x1b[2J\x1b[0;0H");
    puts("\x1b[1;33m!!! Oops !!!\x1b[0m -------------------------------------------------------------------\n");
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
    puts("\nProgram: " __PROGNAME);
    puts("\nFile: ");
    puts(file);
    puts("\nLine: ");
    //puts(line);
    puts("\nFunction: ");
    puts(func);
    puts("\n");
    puts("Address: ");
    _putx((unsigned long)ptr);
    puts("\n\n");
    puts("--------------------------------------------------------------------------------\n");
}
