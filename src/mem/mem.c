#include <log.h>
#include "proto.h"

/* init the keeper from system mem context */
static void keeper_init(void)
{
    log_f("initializing keeper\n");

    u32 base, size;

    /* we want a memory chunk at 0x100000 */
    for (int i = 0; i < mem_SMAPc; ++i) {
        base = 0;
        size = 0;

        /* ignore entries beyond 0xffffffff */
        if (mem_SMAPs[i].base_high) continue;
        
        base = mem_SMAPs[i].base_low;
        if (mem_SMAPs[i].size_high) {
            size = 0xffffffff;
        } else {
            size = mem_SMAPs[i].size_low;
        }

        if (base <= 0x100000 && base + size > 0x100000) {
            /* usable memory chunk */
            if (mem_SMAPs[i].type == 1) break;
        }
    }

    if (size == 0) {
        goto failed;
    } else {
        log("<> found raw memory chunk\n");

        /* real chunk size starting at 0x100000*/
        log("<> moving chunk to 0x100000\n");
        size -= 0x100000 - base;
        base  = 0x100000;

        /* we need at least 4k for the page table */
        log("<> allocating page table at beginning of chunk\n");
        if (size < 0x1000)
            goto failed;
        mem_keeper.page_table  = (char*)0x100000;
        size -= 0x1000;
        base  = 0x101000;

        /* align chunk size to 4k */
        log("<> enforcing chunk align\n");
        size -= size % 0x1000;

        /*
         * a page table of 4k gives us 0x1000 btyes or 0x8000 bits
         * a.k.a. we can keep track of 0x8000 pages max.
         */

        /* each page is 4k in size */
        log("<> allocating pages\n");
        mem_keeper.page_cap = size / 0x1000;
        /* for now, we have a max of 0x8000 pages */
        if (mem_keeper.page_cap > 0x8000) {
            log("<> hit max page count of 0x8000\n");
            mem_keeper.page_cap = 0x8000;
            size = mem_keeper.page_cap * 0x1000;
        }

        // each bit in the page table, keeps track of a single
        // page in the chunk
        // 1 = available
        // 0 = unavailable
        for (u32 i = 0; i < 0x1000; ++i) /* clear all page table */
            mem_keeper.page_table[i] = 0;
        for (u32 i = 0; i < mem_keeper.page_cap/8; ++i)
            mem_keeper.page_table[i] = 0xff;
        // handle pages out of complete byte
        if (mem_keeper.page_cap % 8 != 0) {
            log("<> trimming uneven pages\n");
            mem_keeper.page_cap -= mem_keeper.page_cap % 8;
            size = mem_keeper.page_cap * 0x1000;
        }

        /* set remaing values */
        mem_keeper.chunk_base = base;
        mem_keeper.chunk_size = size;

        log("<> final keeper\n");
        log("   <> page table:   %0x\n", mem_keeper.page_table);
        log("   <> page count:   %0x\n", mem_keeper.page_cap);
        log("   <> chunk base:   %0x\n", mem_keeper.chunk_base);
        log("   <> chunk length: %0x\n", mem_keeper.chunk_size);

        goto success;
    }

    success:
        log("<> keeper setup succeeded !!!\n");
        return;

    failed:
        log("<> keeper setup failed !!!\n");
        mem_keeper.chunk_size = 0;
        return;
}

/* ask for the mem module */
extern u8 require_mem(void)
{
    if (require_satisfied) return 1;

    /* we want to log */
    (void) require_log();

    keeper_init();

    require_satisfied = 1;
    return require_satisfied;
}

/* get a memory dump to log */
extern void mem_logdump(void)
{
    log_f("memory module dump\n");

    log("<> kstart:   %0x\n", mem_kstart);
    log("<> kend:     %0x\n", mem_kend);
    log("<> lowmem:   %0x KiB\n", mem_lowmem);
    log("<> SMAP entries: %0x\n", mem_SMAPc);

    log("   ------ base ------"
          " ----- length -----"
          " ------ type ------\n");

    for (int i = 0; i < mem_SMAPc; ++i) {
        log("   %0x%x %0x%x",
            mem_SMAPs[i].base_high,
            mem_SMAPs[i].base_low,
            mem_SMAPs[i].size_high,
            mem_SMAPs[i].size_low);

        switch (mem_SMAPs[i].type) {
        case 1:
            log(" (1) Free Memory");
            u64 high = mem_SMAPs[i].size_high;
            high <<= 32;
        break;
        case 2:
            log(" (2) Reserved Memory");
        break;
        default:
            log(" (x)");
        break;
        }
        log("\n");
    }
    log("<> keeper:\n");
    log("   <> valid chunk ? ");
    if (mem_keeper.chunk_size != 0) {
        log("Y\n");
        log("   <> page table:   %0x\n", mem_keeper.page_table);
        log("   <> page count:   %0x\n", mem_keeper.page_cap);
        log("   <> chunk base:   %0x\n", mem_keeper.chunk_base);
        log("   <> chunk length: %0x\n", mem_keeper.chunk_size);
    } else {
        log("N\n");
    }
}

/* request a page from the keeper */
extern void* mem_palloc(void)
{
    /* we need a valid keeper */
    if (!mem_keeper.chunk_size) {
        return 0;
    }

    return 0;
}

/* return a page to the keeper */
extern void mem_pfree(void *ptr)
{
    if (!ptr) return;
}
