#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

/**
 * Size and start address of GDT
 */
struct gdt_pointer {
  unsigned short size;
  unsigned int address;
} __attribute__((packed)); // force gcc not to use any padding

void load_gdt(struct gdt_pointer);


/**
 * Segment descriptor data
 */
struct gdt_entry {
  unsigned short limit;
  unsigned short base_lower;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_upper;
} __attribute__((packed));

void create_descriptor(int index, unsigned long limit,
    unsigned long base,
    unsigned char access, 
    unsigned char gran);

void init_gdt();


#endif /** INCLUDE_GDT_H */