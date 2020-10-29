# booter
Bootloader and some basic programs in boot sector code

# BIOS interrupts
The BIOS provides basic services via interrupts, the different services
are defined in the `interrupts.asm` file.

The full reference for this interrupts is
[https://www.stanislavs.org/helppc/idx_interrupt.html](https://www.stanislavs.org/helppc/idx_interrupt.html)

## Video Services

The video services are provided via `int 0x10`:
- `int 0x10,0` -> set video mode
- `int 0x10,e` -> write text in teletype mode
