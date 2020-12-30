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

For now, we simply look for an SMAP entry containing `0x100000`,
after that, we simply bookkeep the memory in this chunk, starting
at `0x100000`.

## Notes

`16mem.c` is in charge of obtaining the relevant values for
`mem_lowmem`, `SMAP`'s, etc. at the startup of the kernel.
