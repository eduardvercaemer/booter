#include <types.h>
#include <mem.h>
__asm__(".code16gcc\n\t");

extern void k16_get_lowmem(void)
{
    __asm__ __volatile__ (
        "clc\n\t"
        "int     $0x12\n\t"
        "movw    %%ax, %0"
        : "=g" (mem_lowmem)
    );
}

extern void k16_get_uppmem(void)
{
    u32 contID = 0;
    int entries = 0, signature, bytes;
    struct SMAP_entry *buffer = mem_SMAPs;

    do {
        __asm__ __volatile__ (
            "int    $0x15\n\t"
            : "=a" (signature), "=c" (bytes), "=b" (contID)
            : "a" (0xE820), "b" (contID), "c" (24), "d" (0x534d4150), "D" (buffer)
        );

        if (signature != 0x534d4150) {
            mem_SMAPc = 0x35;
            return;
        }

        if (bytes > 20 && (buffer->acpi & 0x0001) == 0) {
            // ignore this entry
        }
        else {
            ++buffer;
            ++entries;
        }
    } while (contID != 0 && entries < SMAPS_MAX);

    mem_SMAPc = entries;
}
