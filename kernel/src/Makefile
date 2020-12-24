AS     = nasm
SFLAGS = -O0 -g -f elf32
CC     = cc
CFLAGS = -O0 -g -nostdlib -m32 -ffreestanding -fno-pie
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

debug: $(IMAGE).bin $(KERNEL).sym
	qemu-system-x86_64 -s -S -drive file=$<,format=raw &
	sleep 1
	gdb -x qemu.gdb

analyze: $(KERNEL).elf
	r2 -a x86 -b 32 $<

clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.elf
	rm -f *.sym

.PHONY: build run debug clean

# --------------------------------------------------------------------------- #

$(IMAGE).bin: $(BOOT).bin $(KERNEL).bin
	cat $^ > $@

$(KERNEL).bin: $(KERNEL).elf
	objcopy -O binary $< $@

$(KERNEL).sym: $(KERNEL).elf
	objcopy --only-keep-debug $< $@

$(KERNEL).elf: $(KOBJS)
	$(LD) $(LFLAGS) -T k32.ld -o $@ $^

$(BOOT).bin: boot.s
	$(AS) -f bin -o $@ $^

# --------------------------------------------------------------------------- #

%.s.o: %.s
	$(AS) $(SFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
