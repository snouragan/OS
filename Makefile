CC=i686-elf-gcc
AS=i686-elf-as
LD=i686-elf-gcc

CFLAGS=-ffreestanding -O2 -std=gnu99 -Iinclude -Wall -Wextra -Werror -mgeneral-regs-only
AFLAGS=
LFLAGS=-ffreestanding -nostdlib -lgcc -O2

FILES=boot.o kernel.o io.o keyboard.o gdt.o lgdt.o string.o
HEADERS=include/keyboard.h include/io.h include/string.h include/gdt.h
OSNAME=myos

.PHONY: all
all: $(OSNAME).iso

$(OSNAME).iso: $(OSNAME).bin grub.cfg
	mkdir -p isodir/boot/grub; \
	cp grub.cfg isodir/boot/grub; \
	cp $(OSNAME).bin isodir/boot; \
	grub-mkrescue -o $(OSNAME).iso isodir

$(OSNAME).bin: $(FILES) $(HEADERS) linker.ld
	$(LD) $(LFLAGS) -T linker.ld -o $(OSNAME).bin $(FILES)

%.o: %.S
	$(AS) $(AFLAGS) -o $@ $<

%.o: %.s
	$(AS) $(AFLAGS) -o $@ $<

%.s: %.c
	$(CC) $(CFLAGS) -S -o $@ $<

.PHONY: unmake
unmake: clean
	@if [ -f "$(OSNAME).bin" ]; then rm $(OSNAME).bin; fi
	@if [ -f "$(OSNAME).iso" ]; then rm $(OSNAME).iso; fi
	
.PHONY: clean
clean:
	@if [ -d isodir ]; then rm -rf isodir; fi
	@find . -regextype posix-extended -regex '(.*\.s)|(.*\.o)' -delete
