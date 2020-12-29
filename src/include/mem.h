#ifndef KER_MEM_H
#define KER_MEM_H
#include <types.h>

/* mem.c */
extern char *kstart;
extern char *kend;
extern u16 klowmem;

/*
 *  Used for bios memmap entries
 */

struct __attribute__ ((packed)) SMAP_entry {
    u32 base_low;
    u32 base_high;
    u32 size_low;
    u32 size_high;
    u32 type;
    u32 acpi;
};
extern struct SMAP_entry uppmem[64];

#endif
