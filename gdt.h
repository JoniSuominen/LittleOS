#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

/**
 * Size and start address of GDT
 */
struct gdt_pointer {
  unsigned int address;
  unsigned short size;
} __attribute__((packed)); // force gcc not to use any padding

void load_gdt(unsigned int address, unsigned short size);


/**
 * Segment descriptor data
 */
struct gdt_entry {
  unsigned short limit;
  unsigned short base_lower;
  unsigned char base_middle;
  unsigned char access;
  unsigned char limit_flags;
  unsigned char base_upper;
} __attribute__((packed));

void create_descriptor(int index, unsigned short limit,
    unsigned short base_lower,
    unsigned char base_middle,
    unsigned char access, 
    unsigned char limit_flags,
    unsigned char base_upper);

void init_gdt();


#endif /** INCLUDE_GDT_H */