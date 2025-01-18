/**
 * @file unistd.h
 * @brief standard symbolic constants and types
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#ifndef LIBC_UNISTD_H
#define LIBC_UNISTD_H

#include <stddef.h>
#include <stdio.h>
ssize_t write(int filedes, const void *buf, size_t nbyte);

#endif
