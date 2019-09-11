OBJECTS = loader.o kernel.o io.o framebuffer.o string.o serial.o output.o gdt.o interrupts.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -m elf_i386 -T link.ld 
AS = nasm
ASFLAGS = -f elf32

all: kernel

kernel: $(OBJECTS)
	ld $(LDFLAGS) -o kernel $(OBJECTS) 



%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso