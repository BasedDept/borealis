/**
 * @file crt0.c
 * @brief C runtime for boot stub (riscv)
 * @author George Witt
 * @date 2024-11-14
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */

#ifndef __riscv
#error "Wrong arch!"
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <panic.h>
#include <libfdt.h>
#include <string.h>
#include <sys/stat.h>

#include <arch.h>
#include <hal.h>

extern struct fdt_header *g_fdt;

struct file_operations {
    int handle;
    ssize_t (*write)(int handle, const char *buf, size_t size);
};

extern struct stat g_files[];
extern struct file_operations g_chrdevs[];

extern void _start_c(char *cmdline);

[[clang::no_stack_protector]]
static inline ptrdiff_t string_build(ptrdiff_t i, size_t n, char dest[restrict n], const char *src)
{
    if (src == NULL || dest == NULL) {
        return i;
    }

    ptrdiff_t l_i;
    for (l_i = i; l_i < n; l_i++) {
        if (src[l_i - i] == '\0') break;
        dest[l_i] = src[l_i - i];
    }
    return l_i;
}

[[clang::no_stack_protector]]
static inline char *u64toa(uint64_t d, char a[static 21])
{
    uint64_t y = d;

    a[20] = '\0';

    short i;
    for (i = 19; i >= 0; i--) {
        a[i] = (char)(y % 10) + '0';
        y /= 10;
        if (0 == y) break;
    }

    if (i >= 19) {
        a[i] = '0';
        i = 18;
    }

    return a + i + 1;
}

// NOLINTNEXTLINE(cert-dcl37-c)
[[maybe_unused, clang::no_stack_protector]]
void _start_rv_env(uint64_t hartid, struct fdt_header *opaque)
{
    if (0 != fdt_check_header(opaque)) {
        return;
    }

    g_fdt = opaque;

    const char *bootargs = NULL;
    int bootargs_l = 0;
    int chosen_node = fdt_path_offset(opaque, "/chosen");
    if (chosen_node >= 0) {
        bootargs = fdt_getprop(opaque, chosen_node, "bootargs", &bootargs_l);
    }

    static char cmdline[256];

    if (bootargs_l > sizeof(cmdline)) {
        return;
    }

    ptrdiff_t i = 0;
    char buf[21];
    if (bootargs != NULL) i = string_build(i, sizeof(cmdline), cmdline, bootargs);
    i = string_build(i, sizeof(cmdline), cmdline, " -t ");
    i = string_build(i, sizeof(cmdline), cmdline, u64toa(hartid, buf));
    i = string_build(i, sizeof(cmdline), cmdline, " -d ");
    i = string_build(i, sizeof(cmdline), cmdline, u64toa((uintptr_t)opaque, buf));
    if (i >= sizeof(cmdline)) {
        return;
    }
    cmdline[i] = '\0';

    g_chrdevs[0].write = &fw_write;
    g_files[0].st_mode = S_IFCHR;
    g_files[1].st_mode = S_IFCHR;
    g_files[1].st_rdev = 0;
    g_files[2].st_mode = S_IFCHR;
    g_files[2].st_rdev = 0;

    _start_c(cmdline);

    return;
}

[[gnu::naked]]
void _start(void)
{
    __asm__ volatile ("la sp, __stack");

    //__asm__ volatile ("la tp, __stack");

    __asm__ volatile (".option push                 \n\t"
                      ".option norelax              \n\t"
                      "    la gp, __global_pointer$ \n\t"
                      ".option pop                      ");

    __asm__ volatile ("call _start_rv_env");

    __asm__ volatile (".global _halt \n\t"
                      "_halt:        \n\t"
                      "    wfi       \n\t"
                      "    j _halt       ");
}
