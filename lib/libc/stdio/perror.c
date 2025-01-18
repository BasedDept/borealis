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

void perror(const char *s)
{
    // bold signifies stderr
    fputs(s, stderr);
    switch (errno) {
    case EDOM:
        fputs(": Numerical argument out of domain (EDOM)\n", stderr);
        break;
    case ERANGE:
        fputs(": Numerical result out of range (ERANGE)\n", stderr);
        break;
    case EILSEQ:
        fputs(": Invalid or incomplete multibyte or wide character (EILSEQ)\n", stderr);
        break;
    case ENOTRECOVERABLE:
        fputs(": State not recoverable (ENOTRECOVERABLE)\n", stderr);
        break;
    case EEASTEREGG:
        fputs(": Easter Egg (EEASTEREGG)\n", stderr);
        break;
    default:
        fputs("\n", stderr);
    }
}
