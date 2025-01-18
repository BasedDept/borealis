/**
 * @file arch/riscv/riscv_sbi.h
 * @brief RISC-V SBI wrappers
 * @author George Witt
 * @date 2024-02-24
 *
 * RISC-V Supervisor Binary Interface Specification v2.0
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */
#ifndef BOOT_ARCH_RISCV_RISCV_SBI_H
#define BOOT_ARCH_RISCV_RISCV_SBI_H

#include <stdint.h>

#define SBI_SUCCESS                (0L)
#define SBI_ERR_FAILED            (-1L)
#define SBI_ERR_NOT_SUPPORTED     (-2L)
#define SBI_ERR_INVALID_PARAM     (-3L)
#define SBI_ERR_DENIED            (-4L)
#define SBI_ERR_INVALID_ADDRESS   (-5L)
#define SBI_ERR_ALREADY_AVAILABLE (-6L)
#define SBI_ERR_ALREADY_STARTED   (-7L)
#define SBI_ERR_ALREADY_STOPPED   (-8L)
#define SBI_ERR_NO_SHMEM          (-9L)

struct sbiret {
    long error;
    long value;
};

[[gnu::naked]]
static inline struct sbiret sbi_debug_console_write(unsigned long num_bytes,
                                                    unsigned long base_addr_lo,
                                                    unsigned long base_addr_hi)
{
    __asm__ ("li a7, 0x4442434e \n\t"
             "li a6, 0x00       \n\t"
             "ecall             \n\t"
             "ret");
}

[[gnu::naked]]
static inline long sbi_console_putchar(int ch)
{
    __asm__ ("li a7, 0x01  \n\t"
             "ecall        \n\t"
             "ret");
}

#if 0
static inline struct sbiret sbi_debug_console_write(unsigned long num_bytes,
                                                    unsigned long base_addr_lo,
                                                    unsigned long base_addr_hi)
{
    struct sbiret ret;
    __asm__ ("mv a0, %2      \n\t"
             "mv a1, %3      \n\t"
             "mv a2, %4      \n\t"
             "li a7, 0x4442434e \n\t"
             "li a6, 0x00       \n\t"
             "ecall             \n\t"
             "mv %0, a0      \n\t"
             "mv %1, a1"
             : "=r" (ret.error), "=r" (ret.value)
             : "r" (num_bytes), "r" (base_addr_lo), "r" (base_addr_hi)
             : "a0", "a1", "a6", "a7");
    return ret;
}

static inline long sbi_console_putchar(int ch)
{
    long ret;
    __asm__ ("mv a0, %1 \n\t"
             "li a7, 0x01  \n\t"
             "ecall        \n\t"
             "mv %0, a0"
             : "=r" (ret)
             : "r" (ch)
             : "a0", "a7");
    return ret;
}
#endif

#endif
