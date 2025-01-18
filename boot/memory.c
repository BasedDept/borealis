#include "memory.h"

#include <stddef.h>
#include <memory/objpool.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/queue.h>
#include <libfdt.h>
#include "arch/riscv/riscv_sbi.h"
#include "libfdt_env.h"
#include "panic.h"
#include "string.h"

#define MAX(a, b) ((size_t)(a) > (size_t)(b) ? (a) : (b))
#define MIN(a, b) ((size_t)(a) < (size_t)(b) ? (a) : (b))
#define IS_JOINT(aa, sa, ab, sb) (((size_t)(aa) + (size_t)(sa) >= (size_t)(ab) && \
                                   (size_t)(aa) < (size_t)(ab)) || \
                                  ((size_t)(aa) <= (size_t)(ab) + (size_t)(sb) && \
                                   (size_t)(aa) + (size_t)(sa) > (size_t)(ab) + (size_t)(sb)))
#define IS_SUBSET(aa, sa, ab, sb) ((size_t)(aa) >= (size_t)(ab) && \
                                   (size_t)(aa) + (size_t)(sa) <= (size_t)(ab) + (size_t)(sb))
#define IS_AFTER(aa, ab, sb) ((size_t)(aa) > (size_t)(ab) + (size_t)(sb) + 1)
#define IS_BEFORE(aa, sa, ab) ((size_t)(aa) + (size_t)(sa) + 1 < (size_t)(ab))
#define UNION_ADDR(aa, ab) (MIN((aa), (ab)))
#define UNION_SIZE(aa, sa, ab, sb) ((size_t)MAX((size_t)(aa) + (size_t)(sa), (size_t)(ab) + (size_t)(sb)) - (size_t)MIN((aa), (ab)))

extern const struct fdt_header *g_fdt;

struct memchunk {
    void *addr;
    size_t size;
    SLIST_ENTRY(memchunk) ptr;
};
SLIST_HEAD(memchunk_list, memchunk) _freelist;

OBJPOOL_DEFINE(memchunk, struct memchunk, 32)

errno_t memchunk_insert(void *addr, size_t size)
{
    struct memchunk *var, *tvar;
    SLIST_FOREACH_SAFE(var, &_freelist, ptr, tvar) {
        if (IS_SUBSET(addr, size, var->addr, var->size)) {
            return 0;
        }
        struct memchunk *next = SLIST_NEXT(var, ptr);
        if (IS_JOINT(addr, size, var->addr, var->size)) {
            var->addr = (void *)UNION_ADDR(addr, var->addr);
            var->size = UNION_SIZE(addr, size, var->addr, var->size);
            if (next != SLIST_END(&_freelist) && IS_JOINT(var->addr, var->size, next->addr, next->size)) {
                var->addr = UNION_ADDR(var->addr, next->addr);
                var->size = UNION_SIZE(var->addr, var->size, next->addr, next->size);
                SLIST_REMOVE_AFTER(var, ptr);
                memchunk_obj_release(next);
            }
            return 0;
        }
        if (IS_AFTER(var->addr, addr, size)) {
            break;
        }
        if (next == SLIST_END(&_freelist) || IS_BEFORE(addr, size, next->addr)) {
            // check for 3 or more chunk merge
            struct memchunk *new = memchunk_obj_request();
            if (NULL == new) {
                errno = ENOMEM;
                return errno;
            }
            new->addr = addr;
            new->size = size;
            SLIST_INSERT_AFTER(var, new, ptr);
            return 0;
        }
    }
    struct memchunk *new = memchunk_obj_request();
    if (NULL == new) {
        errno = ENOMEM;
        return errno;
    }
    new->addr = addr;
    new->size = size;
    SLIST_INSERT_HEAD(&_freelist, new, ptr);

    return 0;
}

errno_t memchunk_delete(void *addr, size_t size)
{
    struct memchunk *var, *tvar;
    struct memchunk *prev = NULL;
    SLIST_FOREACH_SAFE(var, &_freelist, ptr, tvar) {
        if (addr + size >= addr && addr <= var->addr) {
            if (addr + size >= var->addr + var->size) {
                if (prev == NULL) {
                    SLIST_REMOVE_HEAD(&_freelist, ptr);
                    // check large chunk
                    return 0;
                }
                SLIST_REMOVE_AFTER(prev, ptr);
                // check large chunk
                return 0;
            }
            var->size = var->size - (size - (var->addr - addr));
            var->addr = addr + size;
            return 0;
        }
        if (addr <= var->addr + var->size && addr + size >= var->addr + var->size) {
            var->size = var->addr - addr;
            // check large chunk
            return 0;
        }
        if (IS_SUBSET(addr, size, var->addr, var->size)) {
            struct memchunk *new = memchunk_obj_request();
            if (NULL == new) {
                errno = ENOMEM;
                return errno;
            }
            new->addr = addr + size;
            new->size = var->size - (new->addr - var->addr);
            SLIST_INSERT_AFTER(var, new, ptr);
            var->size = addr - var->addr;
            return 0;
        }
    }
    errno = EINVAL;
    return errno;
}

errno_t boot_mem_init(void)
{
    if (0 != fdt_check_header(g_fdt)) {
        errno = EINVAL;
        goto leave;
    }

    int root_node = fdt_path_offset(g_fdt, "/");
    int memory_node = fdt_path_offset(g_fdt, "/memory");
    int reserved_memory_node = fdt_path_offset(g_fdt, "/reserved-memory");

    if (root_node < 0 || memory_node < 0) {
        errno = ENOENT;
        goto leave;
    }

    int lenp;
    const struct fdt_property *prop = fdt_get_property(g_fdt, memory_node, "reg", &lenp);
    if (lenp <= 0) {
        errno = EINVAL;
        goto leave;
    }

    memchunk_obj_init_pool();

    SLIST_INIT(&_freelist);

    for (int i = 0; i < lenp >> 4; i++) {
        memchunk_insert((void *)fdt64_to_cpu(*(uint64_t *)(prop->data)), (size_t)fdt64_to_cpu(*(uint64_t *)(prop->data + 8)));
    }

    int n_entries = fdt_num_mem_rsv(g_fdt);
    for (int i = 0; i < n_entries; i++) {
        uint64_t a, s;
        fdt_get_mem_rsv(g_fdt, i, &a, &s);
        memchunk_delete((void*)a, s);
    }

    int n;
    fdt_for_each_subnode(n, g_fdt, reserved_memory_node) {
        int len = 0;
        prop = fdt_get_property(g_fdt, n, "reg", &len);
        for (int i = 0; i < len; i += 16) {
            memchunk_delete((void *)fdt64_to_cpu(*(fdt64_t *)(prop->data + i)), (size_t)fdt64_to_cpu(*(fdt64_t *)(prop->data + i + 8)));
        }
    }

    puts("--- Available Physical Memory Regions ----");
    puts("Address             Size");
    struct memchunk *var;
    SLIST_FOREACH(var, &_freelist, ptr) {
        printf("%#.16zx  %#.16zx\n", (size_t)(var->addr), (size_t)(var->size));
        {
            static int loop = 0;
            loop++;
            assert(loop <= 100);
        }
    }
    puts("------------------------------------------");

    return 0;
leave:
    panic(errno, "Failed to initialize early memory management");
    return errno;
}

errno_t boot_mem_alloc(void **addr_p, size_t size, size_t alignment)
{
    if (addr_p == NULL) goto leave;
    // TODO: kASLR
    ptrdiff_t rand = 0;
    struct memchunk *var;
    SLIST_FOREACH(var, &_freelist, ptr) {
        if (rand >= var->size) {
            rand -= var->size;
            continue;
        }
        if (var->size - rand >= size) {
            *addr_p = var->addr + rand;
            memchunk_delete(*addr_p, size);
            //putx((uint64_t)(*addr_p));
            return 0;
        }
    }
    *addr_p = NULL;
leave:
    return ENOMEM;
}
