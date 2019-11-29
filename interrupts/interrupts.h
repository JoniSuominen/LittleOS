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
    unsigned short offset_lowerbits;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_higherbits;
} __attribute__((packed));


/**
 * Size and start address of IDT, can be loaded with IDTR register
 */
struct idt_pointer {
  unsigned short size;
  unsigned int address;
}__attribute__((packed)); // force gcc not to use any padding

extern void load_idt(struct idt_pointer);
void interrupt_handler(struct cpu_state cpu,  unsigned int interrupt, struct stack_state stack);
void init_idt();
void keyboard_irq_init();
void keyboard_handler();
extern void interrupt_handler_33();
extern void interrupt_handler_14();



#endif /** INCLUDE_INTERRUPTS_H */