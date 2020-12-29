#include <mem.h>
#include <log.h>

/* constants */
#define SMAPS_MAX 64

/* extracted from linking process */
extern char _kstart;
extern char _kend;

/* exported values */
char  *mem_kstart = &_kstart;           /* address were kernel starts */
char  *mem_kend = &_kend;               /* address were kernel ends */
u16    mem_lowmem = 0;                  /* amount of KiB of lowmem */
u16    mem_SMAPc = 0;                   /* amount of SMAP entries */
struct SMAP_entry mem_SMAPs[SMAPS_MAX]; /* uppmem entry table */

/* get a memory dump to log */
extern void mem_logdump(void)
{
    log("["__FILE__"] :: Memory Dump\n");

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
}
