#include <system.h>
#include <vga.h>

void kmain()
{
    //move(800);
    //puts("hello, vga", 0x03);
    
    init_graphics();

    pixel(7, 0, 0x02);

    hang();
}
