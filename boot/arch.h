/**
 * @file arch.h
 * @brief Arch abstractions
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#ifndef BOOT_ARCH_H
#define BOOT_ARCH_H

#ifdef __riscv
#include "arch/riscv/riscv_sbi.h"

#include <stdbool.h>

extern size_t strlen(const char * s);

static inline int firmware_puts(const char *s)
{
    static bool legacy = false;
    size_t len = 0;
    long r = 0;

    if (legacy == false) {
        struct sbiret res = { .error = SBI_ERR_FAILED, .value = 0 };
        len = strlen(s);
        res = sbi_debug_console_write(len, (unsigned long)s, 0);
        if (res.error == SBI_ERR_NOT_SUPPORTED)
            legacy = true;
        if (res.error == SBI_SUCCESS)
            return res.value;
        r = res.error;
    }

    const char * s_i = (const char *)s;
    while ('\0' != s_i[0]) {
        r = sbi_console_putchar((int)(s_i[0]));
        if (r != 0)
            return -1;
        s_i = &(s_i[1]);
    }

    return 0;
}

static inline int firmware_putchar(int c)
{
    return (int)sbi_console_putchar(c);
}
#endif

#endif