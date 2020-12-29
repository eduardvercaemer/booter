# Memory Layout

## Real Mode Address Space
```
< 0x00000000 - 0x000003ff > (1 KiB)     | Real Mode IVT       |
< 0x00000400 - 0x000004ff > (256 B)     | BDA                 |______________
< 0x00000500 - 0x00007bff > (~30 KiB)   | Conventional Mem.   |
< 0x00007c00 - 0x00007dff > (512 B)     | Boot Sector         |   usable
< 0x00007e00 - 0x0007ffff > (480.5 KiB) | Conventional Mem.   |______________
< 0x00080000 - 0x0009ffff > (128 KiB)   | EBDA                |
< 0x000a0000 - 0x000bffff > (128 KiB)   | Video Display Mem.  |
< 0x000c0000 - 0x000c7fff > (32 KiB)    | Video BIOS          |
< 0x000c8000 - 0x000effff > (160 KiB)   | BIOS Expansions     |
< 0x000f0000 - 0x000fffff > (64 KiB)    | Motherboard BIOS    |
```
