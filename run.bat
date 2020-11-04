:: assemble and run program in qemu
::
:: usage: .\run.bat <program name>

nasm -f bin -I.\src .\src\%1.asm -o .\bin\%1.bin
qemu-system-x86_64 -drive file=.\bin\%1.bin,format=raw