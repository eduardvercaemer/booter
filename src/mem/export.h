#ifndef MEM_EXPORT_H
#define MEM_EXPORT_H

typedef struct __attribute__ ((packed)) SMAP_entry {
    u32 base_low;
    u32 base_high;
    u32 size_low;
    u32 size_high;
    u32 type;
    u32 acpi;
} SMAP_entry_t;

/* used by 16mem.c to fetch data from BIOS */
#define             SMAPS_MAX       64
extern u16          mem_lowmem;
extern u16          mem_SMAPc;
extern SMAP_entry_t mem_SMAPs[SMAPS_MAX];

/* public mem API */
extern u8           require_mem(void);
extern void         mem_logdump(void);

extern void*        mem_palloc(void);
extern void         mem_pfree(void *ptr);

#endif
