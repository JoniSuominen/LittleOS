#ifndef INCLUDE_IDT_H
#define INCLUDE_IDT_H


unsigned int idt[512];

/**
 * Size and start address of IDT, can be loaded with IDTR register
 */
struct idt_pointer {
  unsigned int address;
  unsigned short size;
}__attribute__((packed)); // force gcc not to use any padding

#endif /** INCLUDE_IDT_H */