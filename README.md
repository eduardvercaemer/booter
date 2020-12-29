# Kernel

Here we start our little kernel. Now that we are
finally able to load a program in protected mode
we can start to write some code in C.

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

