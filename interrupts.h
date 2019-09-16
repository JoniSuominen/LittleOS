#ifndef INCLUDE_INTERRUPTS_H
#define INCLUDE_INTERRUPTS_H
/**
 * Holds register states for interrupt handler so the code being interrupted knows
 * registers have changed
 */
struct cpu_state {
  unsigned int eax;
  unsigned int ebx;
  unsigned int ecx;
  unsigned int esp;
  unsigned int edx;
  unsigned int ebp; 
  unsigned int esi;
  unsigned int edi;
} __attribute__((packed));

/**
 * Holds stack state for interrupt handler 
 */
struct stack_state {
  unsigned int error_code;
  unsigned int eip;
  unsigned int cs;
  unsigned int eflag;
} __attribute__((packed));

/**
 * 8-byte entry in IDT
 */
struct idt_entry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
} __attribute__((packed));

void load_idt(unsigned int address, unsigned short size);

/**
 * Size and start address of IDT, can be loaded with IDTR register
 */
struct idt_pointer {
  unsigned int address;
  unsigned short size;
}__attribute__((packed)); // force gcc not to use any padding

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt);
void init_idt();
void keyboard_irq_init();
void keyboard_handler();
void interrupt_handler_33();



#endif /** INCLUDE_INTERRUPTS_H */