AS     = nasm
SFLAGS = -O0 -g -f elf32
CC     = cc
CFLAGS = -O0 -g -nostdlib -m32 -ffreestanding -fno-pie
LD     = ld
LFLAGS = -m elf_i386
QEMU   = qemu-system-x86_64

# --------------------------------------------------------------------------- #

SRCDIR   = ./src
BUILDDIR = ./build
SCRIPTS  = ./scripts

# --------------------------------------------------------------------------- #

IMAGE  = image
BOOT   = boot
KERNEL = kernel
KOBJS  = \
	entry.s.o \
	main.o \
	misc.o \
	ports.o \
	vga_text.o \
	mem.o
KLINK   = $(SCRIPTS)/k32.ld
QEMUDBG = $(SCRIPTS)/qemu.gdb

# --------------------------------------------------------------------------- #

KOBJS_ = $(patsubst %.o,$(BUILDDIR)/%.o,$(KOBJS))

# --------------------------------------------------------------------------- #

build: \
	dirs \
	$(BUILDDIR)/$(KERNEL).elf \
	$(BUILDDIR)/$(KERNEL).sym \
	$(BUILDDIR)/$(KERNEL).bin \
	$(BUILDDIR)/$(IMAGE).bin

run: build
	@$(QEMU) -drive file=$(BUILDDIR)/$(IMAGE).bin,format=raw

debug: build
	@$(QEMU) -s -S -drive file=$(BUILDDIR)/$(IMAGE).bin,format=raw &
	@sleep 1
	@gdb -x $(QEMUDBG)

analyze: build
	@r2 -m x86 -b 32 $(BUILDDIR)/$(KERNEL).elf

clean:
	@rm -rf $(BUILDDIR)

dirs:
	@[[ -d $(BUILDDIR) ]] || mkdir $(BUILDDIR)

.PHONY: build run debug clean dirs

# --------------------------------------------------------------------------- #

$(BUILDDIR)/$(IMAGE).bin: $(BUILDDIR)/$(BOOT).bin $(BUILDDIR)/$(KERNEL).bin
	cat $^ > $@

$(BUILDDIR)/$(KERNEL).bin: $(BUILDDIR)/$(KERNEL).elf
	objcopy -O binary $< $@

$(BUILDDIR)/$(KERNEL).sym: $(BUILDDIR)/$(KERNEL).elf
	objcopy --only-keep-debug $< $@

$(BUILDDIR)/$(KERNEL).elf: $(KOBJS_)
	$(LD) $(LFLAGS) -T $(KLINK) -o $@ $^

$(BUILDDIR)/$(BOOT).bin: $(SRCDIR)/boot.s
	$(AS) -f bin -o $@ $^

# --------------------------------------------------------------------------- #

$(BUILDDIR)/%.s.o: $(SRCDIR)/%.s
	$(AS) $(SFLAGS) -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<
