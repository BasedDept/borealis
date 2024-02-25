# head.S
# Master boot record (riscv)
# Author: George Witt
# Date: 2024-02-24
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: NOASSERTION

.extern __stack
.extern __global_pointer$

.section .boot,"aR"
.global _mbr
_mbr:

.org 0
   csrw sie, zero
   csrw sip, zero

   mv a0, a0
   mv a1, a1

   j _start

.org 446
table:

.org 510
signature: .byte 0x55, 0xaa
