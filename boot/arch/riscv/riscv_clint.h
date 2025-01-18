/**
 * @file arch/riscv/
 * @brief RISC-V
 * @author
 * @date 2024-11-16
 *
 * Copyright (c) 2024 Western Digital Corporation or its affiliates.
 * SPDX-License-Identifier: BSD-2-Clause
 */
#if 0
#define iogroup_acquire(iogroup) __iogroup_acquire_ ## iogroup ()
#define iogroup_release(iogroup) __iogroup_release_ ## iogroup ()

#define iowr(ioreg, a) __iowr_ ## ioreg (a)
#define iowrl(ioreg, a) __iowrl_ ## ioreg (a)
#define iowrll(ioreg, a) __iowrl_ ## ioreg (a)

static inline void iowrl(CSR_SSTATUS, unsigned long a)
{
    asm ("csrw sstatus, %0" :: "r" (a));
}

static inline void iowrl(CSR_SIE, unsigned int a)
{
    asm ("csrw sie, %0" :: "r" (a));
}

static inline void iowrl(CSR_STVEC, unsigned int a)
{
    asm ("csrw stvec, %0" :: "r" (a));
}

static inline void iowrl(CSR_SCOUNTEREN, unsigned int a)
{
    asm ("csrw scounteren, %0" :: "r" (a));
}
#endif
