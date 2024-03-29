/**
 * @file crt1.c
 * @brief C runtime for boot stub (riscv)
 * @author George Witt
 * @date 2024-03-02
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */

#include <stdint.h>
#include <stdnoreturn.h>
#include <errno.h>
#include <panic.h>

extern noreturn void _halt(void);
extern int main(void);
extern struct fdt_header *fdt;
extern void adainit(void);
extern void adafinal(void);

unsigned long __stack_chk_guard;

void __attribute__((no_stack_protector)) _start_c(uint64_t hartid,
                                                  uint64_t opaque)
{
    fdt = (void *)opaque;
    __stack_chk_guard = 0xDEADBEEFF00DBABE;
    adainit();
    (void)main();
    adafinal();
}

noreturn void __stack_chk_fail(void)
{
    panic(ENOTRECOVERABLE, "Stack smashing detected!");
}
