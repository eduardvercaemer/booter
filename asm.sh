#!/bin/sh
#
# -- asm.sh
# -- Eduard Vercaemer
#
# assemble all source code into the binaries
#

for f in ./*.asm
do
        nasm -f bin $f
done
