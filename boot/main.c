/**
 * @file main.c
 * @brief Kernel boot stub main
 * @author George Witt
 * @date 2024-02-24
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdalign.h>
#include <errno.h>
#include "panic.h"
#include "memory.h"
#include <libfdt.h>
#include <fdt.h>
#include <hal.h>

const struct fdt_header *g_fdt = NULL;

extern void *payload;

struct args parse_kernel_cmdline(const char *cmdline, size_t l, char *buf, size_t n);

char pl0[] = "oaurbohilshlorhihgliulhri";
char pl1[] = "oernpgiuhaeriugshoierughli";

char *strtok(char *restrict str, const char *restrict delim)
{
    static char *next = NULL;

    if (str != NULL) next = str;
    else if (next == NULL) return NULL;

    char *part = next;
    char *l_str = str;
    while (*l_str != '\0') {
        const char *l_delim = delim;
        while (*l_delim != '\0') {
            if (*l_str == *l_delim) {
                next = l_str + 1;
                return part;
            }
            l_delim++;
        }
        l_str++;
    }
    next = NULL;
    return part;
}

const char *copy_str_until(size_t n, char dest[n], const char *src, char delim)
{
    for (int i = 0; i < n; i++) {

        dest[i] = src[i];

        if (dest[i] == delim) {
            dest[i] = '\0';
            return src + i + 1;
        }

        if (i >= n - 1) {
            return NULL;
        }
    }
    return NULL;
}

void *device_fdt_to_addr(const void *fdt, int node)
{
    return NULL;
}

void device_init(const void *fdt, int node)
{
    char name[32];
    copy_str_until(sizeof(name), name, fdt_get_name(fdt, node, NULL), '@');

    if (strncmp(name, "reserved-memory", sizeof(name)) == 0) {
    }
    else if (strncmp(name, "memory", sizeof(name)) == 0) {

    }
    else if (strncmp(name, "cpus", sizeof(name)) == 0) {
    }
}

void dbg_print_fdt(const void *fdt, int parent)
{
    if (parent < 0) {
        puts("end\n");
        return;
    }
    int n;
    fdt_for_each_subnode(n, fdt, parent) {
        char s[64];
        int res = fdt_get_path(g_fdt, n, s, 64);
        if (res != 0) fputs("fail!\n", stdout);
        else fputs(s, stdout);
        fputs(": ", stdout);
        const char *name = fdt_get_name(fdt, n, NULL);
        const char *ua = copy_str_until(64, s, name, '@');
        fputs(s, stdout);
        fputs(" ", stdout);
        fputs(!ua ? "" : ua, stdout);
        puts("");
        dbg_print_fdt(fdt, n);
    }

    return;
}
int main(int argc, char *argv[argc + 1])
{
    //oops(451, "Hello world!");
    //_putx((uintptr_t)g_fdt);

    fputs("\nStarting Northern Lights", stdout);
    if (argc > 1) {
        fputs(" with cmdline: \n    ", stdout);
        fputs(argv[1], stdout);
    }
    puts("\n");

    int parent = fdt_path_offset(g_fdt, "/");
    if (parent < 0) {
        panic(0, "not found");
    }

    puts("--- Device Tree -----------------------------------------");
    dbg_print_fdt(g_fdt, parent);
    puts("---------------------------------------------------------");

    boot_mem_init();

    panic_;
    //#ifndef NDEBUG
    //panic(0, "This is a test. The program reached the end of main().");
    //#endif

    return 0;
}
