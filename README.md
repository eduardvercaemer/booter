# B00ter

Bootloader and some basic programs in boot sector code

# BIOS interrupts

The BIOS provides basic services via interrupts, the different services
are defined in the `interrupts.inc` file.

[For the full bios interrupts reference](https://www.stanislavs.org/helppc/idx_interrupt.html)

## BIOS Services

Different services require arguments in certain registers, the main argument
usually goes in `AH`, the notation for this is `int 0x--,-` where the first
number is the interrupt, and the second is the argument in `AH`.

The video services are provided via `int 0x10`:
- `int 0x10,0` -> set video mode
- `int 0x10,e` -> write text in teletype mode

The keyboard services are provided via `int 0x16`:
- `int 0x16,0` -> wait for a keypress and return character

# Usage

Programs are assembled with `nasm` to binary format, and run in `qemu`.

- `run.sh` will assemble and run the provided program in qemu automatically
- `run.bat` same but for windows (requires nasm and qemu installed)

# Programs

- `hello.asm` is a simple prgram, that will use `int 0x10` to print strings
  to the screen.

- `step.asm` is a hello world, but it will print the characters one at a time,
  whenever a key is pressed, using `int 0x16,0`

- `echo.asm` will echo keyboard input to screen, until the `return` key is
  pressed, using the same `int`'s

- `pixel.asm` will set a VGA graphics mode, and draw a single red pixel using
  screen coordinates, utilizing `ìnt 0x10,c`

- `memmap.asm` will print characters in the screen, by directly writing to
  VGA mapped memory

# Resources

List of resources on the topic:

- [Bios Interrupts Reference](https://www.stanislavs.org/helppc/idx_interrupt.html)
- [VGA - Video Hardware](http://www.osdever.net/FreeVGA/home.htm)
- [Writing Boot Sector Code](https://susam.in/blog/writing-boot-sector-code/)
- [Intel 64 and IA-32 Architectures Software Developer’s Manual Combined Volumes](https://software.intel.com/content/dam/develop/public/us/en/documents/325462-sdm-vol-1-2abcd-3abcd.pdf)
- [I/O Ports list](http://bochs.sourceforge.net/techspec/PORTS.LST)