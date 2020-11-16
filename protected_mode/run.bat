:: assemble, build image, and run
nasm -f bin boot_32.asm -o boot_32.bin
nasm -f bin payload_32.asm -o payload_32.bin
type boot_32.bin payload_32.bin > image_32.bin
qemu-system-x86_64 -drive file=image_32.bin,format=raw