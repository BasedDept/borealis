/**
 * @file crt1.c
 * @brief C runtime (hosted)
 * @author George Witt
 * @date 2024-09-07
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct heap_frame {
    size_t n;
    struct heap *prev;
    max_align_t obj;
};

extern char __heap;
struct heap_frame *__hp = NULL;

extern int main(int argc, char **argv);
extern void adainit(void);
extern void adafinal(void);

unsigned long __stack_chk_guard;

__attribute__((no_stack_protector))
void _start_c(char *cmdline)
{
    // compiler specific
    __stack_chk_guard = 0xDEADBEEFF00DBABE;

    // setup heap
    __hp = (struct heap_frame *)&__heap;
    __hp->prev = NULL;

    // tokenize cmdline
    char progname[] = "";
    char *argv[3] = {progname, cmdline, NULL};
    int argc = 2;
    if (cmdline == NULL) {
        argc = 1;
        argv[1] = NULL;
    }

    // language environment init
    adainit();

    main(argc, argv);

    // language environment cleanup
    adafinal();

    // handle error return
}

// compiler specific runtime functions

_Noreturn void __stack_chk_fail(void)
{
    errno = ENOTRECOVERABLE;
    perror("Stack smashing detected! Halting...");
    abort();
}

