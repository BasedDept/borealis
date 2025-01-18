/**
 * @file stdio/fputc.c
 * @brief fputc
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>

int fputc(int c, FILE *stream)
{
    assert(c >= CHAR_MIN && c <= CHAR_MAX);
    char s[2] = "\0";
    s[0] = c;
    int fd = fileno(stream);
    if (fd == -1) {
        return EOF;
    }
    ssize_t res = write(fd, s, sizeof(s));

    if (res < 0) return EOF;
    return res > INT_MAX ? INT_MAX : (int)res;
}
