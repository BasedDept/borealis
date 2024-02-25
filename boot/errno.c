/**
 * @file errno.c
 * @brief Statically linked errno.h functions
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
 #include <errno.h>

// errno is a global variable during the early boot process, since only the boot
// core is used
int errno_g = 0;

int *__errno_location()
{
	return &errno_g;
}
