#include "system.h"
#include "vga.h"

void kmain()
{
    move(800);
    putc('X', 0x03);
    putc('Y', 0x03);
    putc('Z', 0x03);

    move(810);
    puts("hello, world", 0x03);

    hang();
}
