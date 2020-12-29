SRCDIR   = ./src
BUILDDIR = ./build
SCRIPTS  = ./scripts

# --------------------------------------------------------------------------- #

AS     = nasm
SFLAGS = -O0 -g -f elf32
CC     = cc
CFLAGS = -O0 -g -nostdlib -m32 -ffreestanding -fno-pie -I$(SRCDIR)/include
CFLAGS += -Werror -Wfatal-errors
LD     = ld
LFLAGS = -m elf_i386
QEMU   = qemu-system-x86_64

# --------------------------------------------------------------------------- #

IMAGE  = image
BOOT   = boot
KERNEL = kernel
KOBJS  = \
	entry.s.o \
	$(patsubst ./%.c,%.o,$(shell cd $(SRCDIR) && find -name "*.c"))
KLINK   = $(SCRIPTS)/k32.ld
QEMUDBG = $(SCRIPTS)/qemu.gdb

QEMU_RUN = $(QEMU) \
	-m 512M \
	-serial stdio \
	-display none \
	-drive file=$(BUILDDIR)/$(IMAGE).bin,format=raw

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
	@$(QEMU_RUN)

debug: build
	@$(QEMU_RUN) -s -S &
	@sleep 1
	@gdb -x $(QEMUDBG)

analyze: build
	@r2 -m x86 -b 32 $(BUILDDIR)/$(KERNEL).elf

clean:
	@rm -rf $(BUILDDIR)

dirs:
	@[[ -d $(BUILDDIR) ]] || mkdir $(BUILDDIR)
	@[[ -d $(BUILDDIR)/vga ]] || mkdir $(BUILDDIR)/vga
	@[[ -d $(BUILDDIR)/serial ]] || mkdir $(BUILDDIR)/serial

.PHONY: build run debug clean dirs

# --------------------------------------------------------------------------- #

$(BUILDDIR)/$(IMAGE).bin: $(BUILDDIR)/$(BOOT).bin $(BUILDDIR)/$(KERNEL).bin
	@echo "   > generating final image"
	@cat $^ > $@

$(BUILDDIR)/$(KERNEL).bin: $(BUILDDIR)/$(KERNEL).elf
	@echo "   > extracting kernel binary"
	@objcopy -O binary $< $@

$(BUILDDIR)/$(KERNEL).sym: $(BUILDDIR)/$(KERNEL).elf
	@echo "   > extracting kernel symbols"
	@objcopy --only-keep-debug $< $@

$(BUILDDIR)/$(KERNEL).elf: $(KOBJS_)
	@echo "   > linking kernel"
	@$(LD) $(LFLAGS) -T $(KLINK) -o $@ $^

$(BUILDDIR)/$(BOOT).bin: $(SRCDIR)/boot.s
	@echo "   > assembling boot sector"
	@$(AS) -f bin -o $@ $^

# --------------------------------------------------------------------------- #

$(BUILDDIR)/%.s.o: $(SRCDIR)/%.s
	@echo -e " [$(AS)]\t$(notdir $@)"
	@$(AS) $(SFLAGS) -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo -e " [$(CC)]\t$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<
