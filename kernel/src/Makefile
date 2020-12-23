AS     = nasm
SFLAGS = -f elf32
CC     = cc
CFLAGS = -nostdlib -m32 -ffreestanding -fno-pie
LD     = ld
LFLAGS =

IMAGE  = image.bin
BOOT   = boot.bin
KERNEL = kernel.bin
KOBJS  = entry.o main.o system.o vga.o

build: $(IMAGE)

run:
	$(MAKE) build && \
	qemu-system-x86_64 -drive file=$(IMAGE),format=raw

debug:
	$(MAKE) build && \
	r2 -a x86 -b 32 -m 0x8000 $(KERNEL)

clean:
	rm -f *.o
	rm -f *.bin

.PHONY: build run debug clean


$(IMAGE): $(BOOT) $(KERNEL)
	cat $^ > $@

$(KERNEL): $(KOBJS)
	$(LD) $(LFLAGS) -T k32.ld -m elf_i386 -o $@ $^

$(BOOT): boot.s
	$(AS) -f bin -o $@ $^



%.s.o: %.s
	$(AS) $(SFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
