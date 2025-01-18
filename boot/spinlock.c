/**
 * @file spinlock.h
 * @brief Spinlock mutual exclusion
 * @author George Witt
 * @date 2024-11-16
 *
 * Copyright (c) 2024 George Witt
 * SPDX-License-Identifier: NOASSERTION
 */
#include "spinlock.h"
#include <stdint.h>
#include "arch/riscv/riscv_asm.h"

static int n_locks = 0; //atomic, thread local

void spinlock_destroy(spinlock_t *mtx)
{
}

int spinlock_init(spinlock_t *mtx)
{
    mtx->locked = 0;
    return 0;
}

int spinlock_lock(spinlock_t *mtx)
{
}

int spinlock_trylock(spinlock_t *mtx)
{
}

int spinlock_unlock(spinlock_t *mtx)
{
}
