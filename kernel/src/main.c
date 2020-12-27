#include "system.h"
#include "vga.h"
#include "mem.h"

void kmain()
{
    move(800);
    puts("hello, kernel", 0x03);

    move(960);
    puts("kernel start : ", 0x03);
    puth(kstart, 0x03);
    move(1040);
    puts("kernel end :   ", 0x03);
    puth(kend, 0x03);

    hang();
}
