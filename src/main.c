#include <system.h>
#include <vga.h>
#include <serial.h>
#include <log.h>

void kmain()
{
    //move(800);
    //puts("hello, vga", 0x03);

    init_serial();
    log_info("[SERIAL]: init");
    
    init_graphics();
    log_info("[GRAPHICS]: init");
    pixel(7, 0, 0x02);

    log_info("[KERN]: hanging");
    hang();
}
