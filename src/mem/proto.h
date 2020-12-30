#ifdef MEM_PROTO_H
#error __FILE__ " included more than once"
#endif
#define MEM_PROTO_H
#include "export.h"

/* structure definitions */
typedef struct keeper {
    u32             chunk_base;
    u32             chunk_size;
    u32             page_cap;
    char*           page_table;
} keeper_t;

/* require */
static u8           require_satisfied = 0;

/* extracted from linking process */
extern char         _kstart;
extern char         _kend;
static char         *mem_kstart = &_kstart;
static char         *mem_kend   = &_kend;

/* (export) system memory context */
u16                 mem_lowmem = 0;
u16                 mem_SMAPc = 0;
SMAP_entry_t        mem_SMAPs[SMAPS_MAX];

/* bookkeeping context */
static keeper_t     mem_keeper;

/* private mem api */
static void         keeper_init(void);
