/**
 * @file stdio/fileno.c
 * @brief fileno
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#include <stdio.h>

#include <errno.h>

int fileno(FILE *stream)
{
    if (stream == NULL) {
        errno = EFAULT;
        return -1;
    }
    return stream->fd;
}
