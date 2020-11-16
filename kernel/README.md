# Kernel

Here we start our little kernel. Now that we are
finally able to load a program in protected mode
we can start to write some code in C.

# Introduction

We first have our 'bootloader' from before, that
setups protected mode and loads the payload just
like before, then we pass control to our payload.

This time, our payload is a program we wrote in C,
we compile it to 32 bits for protected mode, and
then we extract the plain binary .text section
from it.

To have some sort of entry point, the bootloader
jumps straight to the first instruction in our
payload, thus we begin with a function that calls
our `main` method.

To run this kernel, simply run
```
> .\run.bat
```
this assembles, compiles and generates the needed
binary disc image for our virtual machine to run.

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