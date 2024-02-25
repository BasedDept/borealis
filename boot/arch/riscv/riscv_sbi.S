# riscv_sbi.S
# RISC-V supervisor binary interface wrappers
# Author: George Witt
# Date: 2024-02-24
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: NOASSERTION

.section .text

.global sbi_debug_console_write
sbi_debug_console_write:
    li a7, 0x4442434e
    li a6, 0x00
    ecall
    ret

.global sbi_console_putchar
sbi_console_putchar:
    li a7, 0x01
    ecall
    ret
