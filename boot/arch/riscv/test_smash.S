# crt0.S
# C runtime for boot stub (riscv)
# Author: George Witt
# Date: 2024-09-07
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: NOASSERTION

.section .text
.global _start

_start:
   la sp, __stack
   la tp, __stack
.option push
.option norelax
   la gp, __global_pointer$
.option pop

   call _get_cmdline
   call _start_c

.global _halt
   _halt:
   wfi
   j _halt

.global _test_smash
_test_smash:
   la t0, __stack
   mv t1, sp
_loop:
   sd zero, 0(t1)
   add t1, t1, 8
   blt t1, t0, _loop
   ret
