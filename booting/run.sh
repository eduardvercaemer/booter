#!/usr/bin/bash

nasm -f bin booter.asm -o booter.bin
nasm -f bin payload.asm -o payload.bin
cat booter.bin payload.bin > image.bin
qemu-system-x86_64 -drive file=image.bin,format=raw
