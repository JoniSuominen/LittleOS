#include "interrupts.h"
#include "io.h"

static int const IDT_SIZE = 512;

struct IDT_ENTRY IDT[IDT_SIZE];


void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt) {
  if (interrupt ==  17) {

  }
}

void init_idt() {
  unsigned long handler_address;
  unsigned long idt_address;
  unsigned long idt_ptr[2];

  /* populate idt entry of keyboard */
  IDT[0x21].offset_lowerbits = handler_address & 0xffff;
  IDT[0x21].selector = 0x08; // make the selector point to kernel code segment
  IDT[0x21].zero = 0;
  IDT[0x21].type_attr = 0x8e;
  IDT[0x21].offset_higherbits = (handler_address & 0xffff0000) >> 16;


  /**
   * PIC 1 starts at 0x20, PIC 2 starts at 0xA0
   * 
   * */

  // ICW1 - initialization,  make the port expect 3 more data entries
  outb(0x20, 0x11);
  outb(0xA0, 0x11);

  // ICW2 - offset values for interrupt number
  outb(0x21, 0x20);
  outb(0xA1, 0x28);

  // ICW3 - cascading
  outb(0x21, 0x00);
  outb(0xA1, 0x00);

  // ICW4, environment info

  outb(0x21, 0x01);
  outb(0xA1, 0x01);

  // mask interrupts

  outb(0x21, 0xff);
  outb(0xA1, 0xff);

  // fill the IDT descriptor
  idt_address = (unsigned long) IDT;
  idt_ptr[0] = (sizeof (struct IDT_ENTRY) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
  idt_ptr[0] = idt_address >> 16;
  
  load_idt(idt_ptr);
}

void keyboard_irq_init(void) {
  // 0xFD equals 11111101 - this only enables the keyboard.
  outb(0x21, 0xFD);
}