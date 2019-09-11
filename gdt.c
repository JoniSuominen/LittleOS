#include "gdt.h"
#include "io.h"

static int const GDT_SIZE = 3;
struct gdt_entry GDT[GDT_SIZE];

void gdt_init() {
  struct gdt_pointer *gdt_pointer;
  
  // null descriptor
  create_descriptor(0, 0,0,0,0,0,0);

  // kernel code descriptor
  unsigned char limit_flags = 0xF << 4;
  unsigned char access = 0b10011010;
  limit_flags &= 0xC;
  create_descriptor(1, 0xFFFF, 0, 0,  access, limit_flags, 0);
  create_descriptor(2, 0xFFFF, 0, 0,  access, limit_flags, 0);

  gdt_pointer->address = &GDT;
  gdt_pointer->size = sizeof(sizeof(struct gdt_entry) * GDT_SIZE);
  load_gdt(gdt_pointer->address, gdt_pointer->size);


}

void create_descriptor(int index, unsigned short limit,
    unsigned short base_lower,
    unsigned char base_middle,
    unsigned char access, 
    unsigned char limit_flags,
    unsigned char base_upper) {
  GDT[index].limit = limit;
  GDT[index].base_lower = base_lower;
  GDT[index].base_middle = base_middle;
  GDT[index].access = access;
  GDT[index].limit_flags = limit_flags;
  GDT[index].base_upper = base_upper;
}