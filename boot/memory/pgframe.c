#include "pgframe.h"
#include <stdint.h>
#include <stdalign.h>


static inline ppn_t ptrtoppn(void *ptr)
{
    return (uintptr_t)ptr >> 12;
}

static inline void *ppntoptr(ppn_t ppn)
{
    return (void *)(ppn << 12);
}

static inline void pte_set_perm(pte_t e, uint8_t perm)
{
}

ppn_t pgt_map_page(ppn_t page, uint32_t count)
{
    
}

