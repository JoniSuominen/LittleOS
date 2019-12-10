OBJECTS = loader.o kernel.o io/io.o io/framebuffer.o utils/string.o  utils/common.o io/serial.o io/output.o segmentation/gdt.o interrupts/interrupts.o interrupts/idt.o interrupts/interrupt_handler.o drivers/keyboard.o segmentation/pages.o segmentation/paging.o segmentation/kheap.o segmentation/memory.o algorithms/ordered_array.o vfs/initrd.o vfs/vfs.o
CC = gcc
CFLAGS = -m32 -g -nostdlib -fno-builtin -fno-stack-protector \
		-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -Wno-unused-variable -Wno-unused-parameter -Wno-incompatible-pointer-types \
		-fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
LDFLAGS = -m elf_i386 -T link.ld 
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) -o kernel.elf $(OBJECTS)

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
		    -b boot/grub/stage2_eltorito    \
		    -no-emul-boot                   \
		    -boot-load-size 4               \
		    -A os                           \
		    -input-charset utf8             \
		    -quiet                          \
		    -boot-info-table                \
		    -o os.iso                       \
		    iso

run: os.iso	
	bochs -f bochsrc.txt -q




%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso */*.o *.out bochslog.txt copy.txt
