/**
 * @file hal.h
 * @brief Hardware abstraction layer
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: 
 */
#ifndef BOOT_HAL_H
#define BOOT_HAL_H

#include <stddef.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <stdbool.h>

typedef long reg_t;

typedef union {
    unsigned long opaque;
} pte_t;

typedef union {
    unsigned long opaque;
} csr_t;

#define asm_reg_dump_ asm ("sd ra, 24(sp) \n\t call _diag_dump_regs")
#define panic_ asm_reg_dump_; _diag_panic()

#define asm_syscall_(n) \
    asm ("li a7, " __STRING(n) "  \n\t" \
         "ecall        \n\t" \
         "ret")

#define asm_sysret_(addr) \
    asm ("sret")

#define asm_return_ asm("ret")

static inline void *read_sp(void)
{
    register void *sp = 0;
    asm ("mv %0, sp" : "=r" (sp));
    return sp;
}

typedef unsigned long irq_mask_t;

#define SSTATUS_SIE 0x00000002ul;

static inline bool irq_are_enabled(void)
{
    register unsigned long sstatus;
    asm ("csrr %0, sstatus" : "=r" (sstatus));
    return sstatus & SSTATUS_SIE;
}

static inline void irqs_enable(void)
{
    register unsigned long rs1 = SSTATUS_SIE;
    asm ("csrrs zero, sstatus, %0" :: "r" (rs1));
}

static inline void irqs_disable(void)
{
    register unsigned long rs1 = SSTATUS_SIE;
    asm ("csrrc zero, sstatus, %0" :: "r" (rs1));
}

static inline void irq_mask_set(irq_mask_t m)
{
    asm ("csrrs zero, sie, %0" :: "r" ((unsigned long)m));
}

static inline void irq_mask_clear(irq_mask_t m)
{
    asm ("csrrc zero, sie, %0" :: "r" ((unsigned long)m));
}

void _diag_panic(void);
void _diag_dump_regs(void);

ssize_t fw_write(int handle, const char *buf, size_t size);

int diag_safe_print(const char *s);
int diag_safe_printx(unsigned long x);
int diag_print_stack_trace(const void *fp, const void *stack);

void panic_test(void);

#endif
