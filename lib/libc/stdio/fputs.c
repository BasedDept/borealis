/**
 * @file stdio/fputs.c
 * @brief fputs
 * @author George Witt
 * @date 2024-09-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <stdio.h>

#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>

int fputs(const char *restrict s, FILE *restrict stream)
{
    int fd = fileno(stream);
    if (fd == -1) {
        return EOF;
    }
    ssize_t res = write(fd, s, strlen(s));

    if (res < 0) return EOF;
    return res > INT_MAX ? INT_MAX : (int)res;
}
