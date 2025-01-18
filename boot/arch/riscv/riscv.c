/**
 * @file arch/riscv/riscv.c
 * @brief RISC-V helpers
 * @author George Witt
 * @date 2024-11-16
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

[[gnu::naked]]
void *riscv_read_sp(void)
{
    __asm__ volatile ("mv a0, sp");
    __asm__ volatile ("ret");
}

