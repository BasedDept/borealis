/**
 * @file hal.c
 * @brief hardware abstraction layer
 * @author George Witt
 * @date 2024-12-08
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier:
 */

#include <assert.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __riscv
#include "arch/riscv/riscv.h"
#include "arch/riscv/riscv_sbi.h"
//#include <stdbool.h>
//#include <sys/types.h>

ssize_t fw_write(int handle, const char *buf, size_t size)
{
    struct sbiret res = sbi_debug_console_write(size, (unsigned long)buf, 0);
    if (res.error == SBI_SUCCESS) {
        return res.value;
    }
    else {
        return -1;
    }
}

#else

#endif

// TODO: Move out

struct file_operations {
    int handle;
    ssize_t (*write)(int handle, const char *buf, size_t size);
};

#define MAX_FILES 8
#define MAX_CHRDEVS 8

struct stat g_files[MAX_FILES] = {0};
struct file_operations g_chrdevs[MAX_CHRDEVS] = {0};

ssize_t write(int filedes, const void *buf, size_t nbyte)
{
    if (filedes < 0 || filedes > MAX_FILES) {
        return -1;
    }
    switch (g_files[filedes].st_mode) {
        case S_IFCHR:;
            unsigned int chr_idx = g_files[filedes].st_rdev;
            assert(chr_idx < MAX_CHRDEVS);
            if (g_chrdevs[chr_idx].write == NULL) {
                return -1;
            }
            return g_chrdevs[chr_idx].write(g_chrdevs[chr_idx].handle, buf, nbyte);
    }
    return -1;
}

