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

# Internals

Inner workings of the module.

## Initialization

When we `require` the memory module, the `bookkeep` init is run,
this inits the bookeeping state.

- We look for a usable memory chunk containing address `0x100000`.
- We allocate a page table at this address of size one page (`0x1000`).
- The remaining free memory in the chunk is divided into chunks, beginning
  at the end of the page table.
- Each bit of the page table represents the availability of each page
  (1 = available, = = unavailable)

*TODO:*
- Currently, we have a limit of 0x8000 managed pages because of the 4KiB
  page table.
- We are only using memory from one contiguos memory chunk.

## Notes

`16mem.c` is in charge of obtaining the relevant values for
`mem_lowmem`, `SMAP`'s, etc. at the startup of the kernel.
