#!/bin/sh
#
# -- run.sh
# -- Eduard Vercaemer
#
# assemble and run bootsector program in qemu
# usage:
#  run.sh <program name>
#

if [ -n "$1" ]; then
        nasm -f bin -I./src ./src/$1.asm -o ./bin/$1.bin
        qemu-system-x86_64 -drive file=./bin/$1.bin,format=raw
else
        echo "usage: $0 <program name>"
fi
