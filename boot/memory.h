#ifndef BOOT_MEMORY_H
#define BOOT_MEMORY_H

#include <errno.h>
#include <stddef.h>

errno_t boot_mem_init(void);
errno_t boot_mem_alloc(void **addr_p, size_t size, size_t alignment);

#endif
