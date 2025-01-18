/**
 * @file sys/stat.h
 * @brief data returned by the stat() function
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#ifndef LIBC_SYS_STAT_H
#define LIBC_SYS_STAT_H

#define __SYS_TYPES_H_WANT_mode_t__
#define __SYS_TYPES_H_WANT_dev_t__
#include <sys/types.h>

#define S_IFCHR 2

struct stat {
    mode_t st_mode;
    dev_t st_rdev;
};

#endif
