/**
 * @file panic.h
 * @brief Kernel errors
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#ifndef BOOT_PANIC_H
#define BOOT_PANIC_H

#include <stdnoreturn.h>
#include <stddef.h>

extern noreturn void _halt(void);
extern void _oops(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg);
extern noreturn void _panic(int err, void *ptr, const char *file, int line,
                                    const char *func, const char *msg);

#define panic(err, msg) _panic_wrapper(err, __FILE__, __LINE__, __func__, msg)
#define oops(err, msg) _oops_wrapper(err, __FILE__, __LINE__, __func__, msg)

#define halt() (puts("\x1b[1m!!! Halt !!!\x1b[0m\n") + (_halt(), 0))

__attribute__((noinline))
noreturn void _panic_wrapper(int err, const char * file, int line,
                                    const char * func, const char * msg);

__attribute__((noinline))
void _oops_wrapper(int err, const char * file, int line,
                                    const char * func, const char * msg);

#endif
