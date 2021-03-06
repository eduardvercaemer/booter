#include <ports.h>
#include <serial.h>

#define PORT_COM1 0x03f8

static u8 require_satisfied;

static int serial_received(void);
static int is_transmit_empty(void);
static int serial_init(void);

static int serial_received(void)
{
    return inb(PORT_COM1 + 5) & 1;
}

static int is_transmit_empty(void)
{
    return inb(PORT_COM1 + 5) & 0x20;
}

static int serial_init(void)
{
    outb(PORT_COM1 + 1, 0x00);    // Disable all interrupts
    outb(PORT_COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(PORT_COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT_COM1 + 1, 0x00);    //                  (hi byte)
    outb(PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(PORT_COM1 + 2, 0xc7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT_COM1 + 4, 0x0b);    // IRQs enabled, RTS/DSR set
    outb(PORT_COM1 + 4, 0x1e);    // Set in loopback mode, test the serial chip
    outb(PORT_COM1 + 0, 0xae);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(inb(PORT_COM1 + 0) != 0xae) {
      return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(PORT_COM1 + 4, 0x0f);
    return 0;
}

extern int require_serial(void)
{
    if (require_satisfied) return 1;

    serial_init();
    return require_satisfied = 1;
}


extern char serial_readb(void)
{
    while (serial_received() == 0) ;
    return inb(PORT_COM1);
}

extern void serial_writeb(char val)
{
    while (is_transmit_empty() == 0) ;
    outb(PORT_COM1, val);
}
