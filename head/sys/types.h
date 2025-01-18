/**
 * @file sys/types.h
 * @brief data types
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#if !defined(__SYS_TYPES_H_WANT_ssize_t__) && !defined(__SYS_TYPES_H_WANT_mode_t__) && !defined(__SYS_TYPES_H_WANT_dev_t__)
#ifndef LIBC_SYS_TYPES_H
#define LIBC_SYS_TYPES_H

#define __SYS_TYPES_H_WANT_ssize_t__
#define __SYS_TYPES_H_WANT_mode_t__
#define __SYS_TYPES_H_WANT_dev_t__


#endif
#endif

#if defined(__SYS_TYPES_H_WANT_ssize_t__)

typedef signed long ssize_t;

#undef __SYS_TYPES_H_WANT_ssize_t__
#endif

#if defined(__SYS_TYPES_H_WANT_mode_t__)

typedef int mode_t;

#undef __SYS_TYPES_H_WANT_mode_t__
#endif

#if defined(__SYS_TYPES_H_WANT_dev_t__)

typedef int dev_t;

#undef __SYS_TYPES_H_WANT_dev_t__
#endif
