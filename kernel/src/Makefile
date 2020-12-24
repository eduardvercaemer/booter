AS     = nasm
SFLAGS = -f elf32
CC     = cc
CFLAGS = -nostdlib -m32 -ffreestanding -fno-pie
LD     = ld
LFLAGS = -m elf_i386

# --------------------------------------------------------------------------- #

IMAGE  = image
BOOT   = boot
KERNEL = kernel
KOBJS  = \
	entry.s.o \
	main.o \
	misc.o \
	ports.o \
	vga.o \

# --------------------------------------------------------------------------- #

build: $(IMAGE).bin

run: $(IMAGE).bin
	qemu-system-x86_64 -drive file=$<,format=raw

debug: $(IMAGE).bin
	gdb -x qemu.gdb

analyze: $(KERNEL).o
	r2 -a x86 -b 32 $<

clean:
	rm -f *.o
	rm -f *.bin

.PHONY: build run debug clean

# --------------------------------------------------------------------------- #

$(IMAGE).bin: $(BOOT).bin $(KERNEL).bin
	cat $^ > $@

$(KERNEL).bin: $(KOBJS)
	$(LD) $(LFLAGS) -T k32.ld -o $@ $^

$(KERNEL).o: $(KOBJS)
	$(LD) $(LFLAGS) -T k32.ld --oformat=elf32-i386 -o $@ $^

$(BOOT).bin: boot.s
	$(AS) -f bin -o $@ $^

# --------------------------------------------------------------------------- #

%.s.o: %.s
	$(AS) $(SFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
