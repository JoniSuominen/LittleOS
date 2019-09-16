#include "interrupts.h"
#include "io.h"
#include "string.h"

static const int IDT_SIZE = 512;
static const int KEYBOARD_STATUS_PORT = 0x64;
static const int KEYBOARD_DATA_PORT = 0x60;


struct idt_entry IDT[512];


void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt) {
  if (interrupt ==  21) {
    keyboard_handler();
  }
}

void init_idt() {
  unsigned long handler_address = (unsigned int) interrupt_handler_33;
  unsigned long idt_address;
  struct idt_pointer idt_pntr = {0, 0};
  struct idt_pointer *idt_ptr = &idt_pntr;

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
  idt_ptr->address = (unsigned int) &(IDT);
  idt_ptr->size = sizeof(sizeof(struct idt_entry) * IDT_SIZE);
  
  load_idt(idt_ptr->address, idt_ptr->size);
  keyboard_irq_init();
}

void keyboard_irq_init() {
  // 0xFD equals 11111101 - this only enables the keyboard.
  outb(0x21, 0xFD);
}

void keyboard_handler() {
  unsigned char status;
  char keycode;

  outb(0x20, 0x20);

  status = inb(KEYBOARD_STATUS_PORT);

  if (status & 0x01) {
    keycode = inb(KEYBOARD_DATA_PORT);
    if (keycode < 0)
      return;
    printf("a", TYPE_FRAMEBUFFER, strlen("a"));
  }
}