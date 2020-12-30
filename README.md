# Kernel

Here we start our little kernel. Now that we are
finally able to load a program in protected mode
we can start to write some code in C.

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

## Kernel Layout
```
< 0x8000 ->   ...   > Kernel Binary
<   ...  -> 0x7ffff > Top of Stack
```

```
boot.s    -> load kernel to 0x8000
entry.s   -> init kernel real mode
16(...).c -> real mode functionality
+ 16mem.c -> use bios to get memory info
entry.s   -> enter protected mode
entry.s   -> call kmain
main.c    -> kmain
+ log.c   -> kernel logging capabilities
+ ...     -> ...
```

## Kernel Loading

The kernel gets loaded by `boot.s` at address `0x8000`, some space
after the boot sector area.

After this, the startup code at `entry.s` initializes the environment
for our kernel real mode phase, including setting up the stack.
Once this is done, we can work in real mode with our code from files
`16*.c`.

After all work is done, we enter protected mode and set the code and
data segments for the same memory layout. Then we call `kmain`.

# Source Code Layout

The file `boot.s` is in charge of loading the rest
of the image and passing control, that's it.

Then, `entry.s` has the code that is executed after
that, this is our kernel entry point, after the init
process is done, `kmain` is finally called.

`main.c` contains `kmain`, and is the main file for
our kernel.

For now, the kernel is loaded at address `0x8000`,
where the startup code is executed. The stacks is
setup to begin at address `0x7FFFF`.

## Files

Source code is stored in `./src`, any build files
will be stored in `./build`, and misc scripts are
stored in `./scripts`.

# Build System

The build process is as follows:

- The bootloader is assembled from the single file
  `boot.s`, this will be the code loaded as boot
  sector.
- The kernel startup code is in `entry.s`, this will
  be compiled into a regular elf.
- Other kernel objects are compiled.
- All these objects are linked together with our
  link script `k32.kd`.
- A binary is extracted from the kernel elf.
- We combine the bootloader and kernel into a final
  binary image.

# Usage

Multiple commands are defined in the Makefile, use:

```
$ make build
```

assembles the bootloder, build the kernel, and generates
an image with both.

```
$ make analyze
```

to build an elf version of the kernel, and load it
into radare to inspect it.

```
$ make debug
```

runs the kernel in qemu and gives you control of a gdb
session attached to the emulated system.

```
$ make run
```

to build the image and run with qemu.

```
$ make clean
```

to remove any build files.

