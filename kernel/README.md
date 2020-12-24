# Kernel

Here we start our little kernel. Now that we are
finally able to load a program in protected mode
we can start to write some code in C.

# Layout

The file `boot.s` is in charge of loading the rest
of the image and passing control, that's it.

Then, `entry.s` has the code that is executed after
that, this is our kernel entry point, after the init
process is done, `kmain` is finally called.

`main.c` contains `kmain`, and is the main file for
our kernel.

# Usage

Multiple commands are defined in the Makefile, use:

```
$ make build
```

simply builds the loadable image.

```
$ make debug
```

to build an elf version of the kernel, and load it
into radare to inspect it.

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
