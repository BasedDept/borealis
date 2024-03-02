/**
 * @file errno/errno.c
 * @brief errno
 * @author George Witt
 * @date 2024-03-02
 *
 * ISO/IEC 9899:1990 7.1.4
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <errno.h>

// errno is a global variable during the early boot process, since there is no
// thread local storage
int errno_g = 0;

int *__errno_location()
{
	return &errno_g;
}
