# payload.S
# C runtime for boot stub (riscv)
# Author: George Witt
# Date: 2024-02-24
#
# Copyright (c) 2024 George Witt
# SPDX-License-Identifier: NOASSERTION

.section .rodata.payload
.align 4
payload:
//.incbin "../kern/kernimg"

.align 4
certificate:
//.incbin "../kern/keys"
