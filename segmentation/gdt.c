#include "gdt.h"
#include "../io/io.h"
#include "../io/framebuffer.h"
#include "../utils/string.h"

static int const GDT_SIZE = 3;
struct gdt_entry GDT[3];

void init_gdt() {
  
  struct gdt_pointer gdt_ptr;
  
  // null descriptor
  create_descriptor(0, 0,0,0,0);

  // kernel code descriptor
  unsigned char limit_flags = 0xF << 4;
  unsigned char access = 0b10011010;
  limit_flags &= 0xC;
  create_descriptor(1, 0xFFFFFFFF, 0,  0x9A, 0xCF);

  // kernel data descriptor
  create_descriptor(2, 0xFFFFFFFF, 0, 0x92, 0xCF);
  
  gdt_ptr.address = (unsigned int) &GDT;
  gdt_ptr.size = (sizeof(struct gdt_entry) * GDT_SIZE) - 1;
  load_gdt(gdt_ptr);
  
  load_segment_registers();
  
  printf("HELLO WORLD", TYPE_SERIAL, strlen("HELLO WORLD"));


}


void create_descriptor(int index, unsigned long limit,
    unsigned long base,
    unsigned char access, 
    unsigned char gran) {
  GDT[index].limit = limit;
  GDT[index].base_lower = (base & 0xFFFF);
  GDT[index].base_middle = (base >> 16) & 0xFF;
  GDT[index].access = access;
  GDT[index].granularity = gran;
  GDT[index].base_upper = (base >> 24) & 0xFF;
}