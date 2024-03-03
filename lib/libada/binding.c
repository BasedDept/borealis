/**
 * @file binding.c
 * @brief GNAT C bindings
 * @author George Witt
 * @date 2024-03-02
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stddef.h>

int __install_handler_g = 0;

void __gnat_runtime_finalize(void) {}

void __gnat_runtime_initialize(int install_handler)
{
    __install_handler_g = install_handler;
}

int __gl_main_priority = 0;
int __gl_time_slice_val = 0;
char __gl_wc_encoding = 0;
char __gl_locking_policy = 0;
char __gl_queuing_policy = 0;
char __gl_task_dispatching_policy = 0;
void *__gl_priority_specific_dispatching = NULL;
int __gl_num_specific_dispatching = 0;
int __gl_main_cpu = 0;
void *__gl_interrupt_states = NULL;
int __gl_num_interrupt_states = 0;
int __gl_unreserve_all_interrupts = 0;
int __gl_detect_blocking = 0;
int __gl_default_stack_size = 0;
void *__gl_bind_env_addr = NULL;
