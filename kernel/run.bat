:: creates bootable image from assembly boot code and C payload

nasm -f bin boot.asm -o boot.bin
gcc -nostdlib -m32 -c kernel.c -o kernel.o
objcopy -O binary --only-section=.text kernel.o kernel.text
type boot.bin kernel.text > image.bin
qemu-system-x86_64 -drive file=image.bin,format=raw