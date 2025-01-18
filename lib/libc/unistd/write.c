/**
 * @file unistd/write.c
 * @brief write
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */
#include <unistd.h>
#include <sys/cdefs.h>

#define __NR_write 1

#define __asm_syscall(n) \
    asm ("li a7, " __STRING(n) "  \n\t" \
         "ecall        \n\t" \
         "ret")

#define __asm_sysret(addr) \
    asm ("sret")

#define __asm_return asm("ret")

[[gnu::naked]]
ssize_t write(int filedes, const void *buf, size_t nbyte)
{
    __asm_syscall(__NR_write);
    __asm_return;
}
