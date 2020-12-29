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

    log_info("printing pixels ...");
    for (int y = 20; y < 40; ++y)
        for (int x = 20; x < 40; ++x)
            pixel(x, y, 0x03);

    log_info("[KERN]: hanging");
    hang();
}
