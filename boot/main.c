/**
 * @file main.c
 * @brief Kernel boot stub main
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <panic.h>

const struct fdt_header *fdt = NULL;

extern void *payload;

int main(void)
{
    oops(451, "Hello world!");

    puts("Goodbye.\n");

    #ifndef NDEBUG
    panic(0, "This is a test. The program reached the end of main().");
    #endif

    return 0;
}
