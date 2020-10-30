#!/bin/sh
#
# -- run.sh
# -- Eduard Vercaemer
#
# run bootsector code in qemu
# usage:
#  run.sh <binary>
#

if [ -n "$1" ]; then
        qemu-system-x86_64 -drive file=$1,format=raw
else
        echo "usage: $0 <binary>"
fi
