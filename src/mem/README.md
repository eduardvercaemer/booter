# Memory Managmenet

This is the memory modules, in charge of interfacing with the
physical memory, allocation, etc.

```
#include <mem.h>
require_mem();
```
to utilize the module.

`export.h` defines the exported symbols for this module.

# Exports

Structures:
- `SMAP_entry_t`: an entry in the SMAP table.

Objects:
- `SMAPS_MAX`: max possible amount of SMAP entries in table.
- `mem_lowmem`: amount of available KiB of lowmem.
- `mem_SMAPc`: amount of SMAP entries fetched from BIOS.
- `mem_SMAPs`: array of SMAP entries.

Functions:
- `require_mem`: import this module.
- `mem_logdump`: dump memory info into the log.
- `mem_palloc`: request a page from the keeper.
- `mem_pfree`: return a page to the keeper.

# Internals

## Initialization

When we `require` the memory module, the keeper is initialized with info
from the system memory contained in the SMAP table.

- We look for a usable memory chunk containing address `0x100000`.
- We allocate a page table at this address of size one page (`0x1000`).
- The remaining free memory in the chunk is divided into chunks, beginning
  at the end of the page table.
- Each bit of the page table represents the availability of each page
  (1 = available, 0 = unavailable)

## Allocation

Whenever we request a page from the keeper, it looks for the first available
page from the page table, and returns its pointer, then sets its bit to 0.
If no valid page is found, it returns null.

## Freeing

To free a page, the keeper makes sure the address points to a previuosly
allocated page, if it does, it sets the page bit to 1.

*TODO:*
- Currently, we have a limit of 0x8000 managed pages because of the 4KiB
  page table.
- We are only using memory from one contiguos memory chunk.
- Dump more info about the pages in the keeper.

## Notes

- A page is defined to have size `0x1000`.
- A bit of one indicates an available page.

`16mem.c` is in charge of obtaining the relevant values for
`mem_lowmem`, `SMAP`'s, etc. at the startup of the kernel.
