# Kernel

Here we start our little kernel. Now that we are
finally able to load a program in protected mode
we can start to write some code in C.

# Layout

We have to main binary images, `boot.bin`, which
is in charge of setting our GDT, pur stack, etc.
and `kernel.bin`, wihch is our kernel, that will
be loaded by `boot.bin` into memory and then handle
control to it.

# Usage

Multiple commands are defined in the Makefile, use:

```
$ make build
```

to build the whole image.

```
$ make debug
```

to build the image and open the kernel binary
in radare with the correct options.

```
$ make run
```

to build the image and run with qemu.

```
$ make clean
```

to remove any build files.

# Kernel Functionality

Since once we are in protected we are unable to use
any BIOS services, we are required to implement any
functionality ourselves.

## Console Output

We can use a global `cursor` to represent our position
in the screen, we can then use this information and
the VGA memory area to draw any characters to the
screen _(see function `putc`)_.

## Input

_TODO:_

## System

We have a simple function `hang` that simply loops
the processor.
