/**
 * @file arch/riscv/sbi.h
 * @brief RISC-V SBI wrappers
 * @author George Witt
 * @date 2024-02-24
 *
 * RISC-V Supervisor Binary Interface Specification v2.0
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */
#ifndef BOOT_ARCH_RISCV_SBI_H
#define BOOT_ARCH_RISCV_SBI_H

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

extern struct sbiret sbi_debug_console_write(unsigned long num_bytes,
                                             unsigned long base_addr_lo,
                                             unsigned long base_addr_hi);

extern long sbi_console_putchar(int ch);

#endif
