/**
 * @file stdio/perror.c
 * @brief perror
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.9.10.4
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdio.h>

#include <errno.h>

#define CONSOLE_BOLD "\x1b[1m"
#define CONSOLE_RESET "\x1b[0m"

void perror(const char *s)
{
    // bold signifies stderr
    puts(CONSOLE_BOLD);
    puts(s);
    switch (errno) {
    case EDOM:
        puts(": Numerical argument out of domain (EDOM)\n");
        break;
    case ERANGE:
        puts(": Numerical result out of range (ERANGE)\n");
        break;
    case EILSEQ:
        puts(": Invalid or incomplete multibyte or wide character (EILSEQ)\n");
        break;
    case ENOTRECOVERABLE:
        puts(": State not recoverable (ENOTRECOVERABLE)\n");
        break;
    case EEASTEREGG:
        puts(": Easter Egg (EEASTEREGG)\n");
        break;
    default:
        puts("\n");
    }
    puts(CONSOLE_RESET);
}
