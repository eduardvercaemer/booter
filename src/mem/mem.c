#include <log.h>
#include "proto.h"

/* init the bookkeeper from system mem context */
static void bookkeep_init(void)
{
    log_f("initializing bookkeeping\n");

    /* we want memory at 0x100000 */
    u32 base, size = 0;
    for (int i = 0; i < mem_SMAPc; ++i) {
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
        log("<> no valid chunk found !\n");
        mem_books.valid_chunk = 0;
        return;
    } else {
        log("<> found valid chunk !\n");
        log("<> base:   %0x\n", base);
        log("<> length: %0x\n", size);
        mem_books.valid_chunk = 1;
        return;
    }
}

/* ask for the mem module */
extern u8 require_mem(void)
{
    if (require_satisfied) return 1;

    /* we want to log */
    (void) require_log();

    bookkeep_init();

    require_satisfied = 1;
    return require_satisfied;
}

/* get a memory dump to log */
extern void mem_logdump(void)
{
    u64 upp_total = 0;

    log_f("memory setup dump\n");

    log(" kstart:\n");
    log(" <> %0x\n", mem_kstart);
    log(" kend:\n");
    log(" <> %0x\n", mem_kend);
    log(" lowmem:\n");   
    log(" <> %0x KiB\n", mem_lowmem);
    log(" uppmem:\n");
    log(" <> SMAP entries: %0x\n", mem_SMAPc);

    log("    ------ base ------"
           " ----- length -----"
           " ------ type ------\n");

    for (int i = 0; i < mem_SMAPc; ++i) {
        log("    %0x%x %0x%x",
            mem_SMAPs[i].base_high,
            mem_SMAPs[i].base_low,
            mem_SMAPs[i].size_high,
            mem_SMAPs[i].size_low);

        switch (mem_SMAPs[i].type) {
        case 1:
            log(" (1) Free Memory");
            u64 high = mem_SMAPs[i].size_high;
            high <<= 32;
            upp_total += high;
            upp_total += mem_SMAPs[i].size_low;
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

    log("\n <> total: %0x\n", upp_total);
}

