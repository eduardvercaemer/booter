#ifndef KER_MEM_H
#define KER_MEM_H
#include <types.h>

struct __attribute__ ((packed)) SMAP_entry {
    u32 base_low;
    u32 base_high;
    u32 size_low;
    u32 size_high;
    u32 type;
    u32 acpi;
};

/* mem.c */
extern char  *mem_kstart;
extern char  *mem_kend;
extern u16    mem_lowmem;
extern u16    mem_SMAPc;
extern struct SMAP_entry mem_SMAPs[];

extern void mem_logdump(void);

#endif
