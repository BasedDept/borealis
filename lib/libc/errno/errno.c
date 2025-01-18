/**
 * @file errno/errno.c
 * @brief errno
 * @author George Witt
 * @date 2024-11-29
 *
 * ISO/IEC 9899:1990 7.1.4
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <errno.h>

// errno is a global variable during the early boot process, since there is no
// thread local storage
int __g_errno = 0;

int *__errno()
{
	return &__g_errno;
}
