#include "io.h"
#include "framebuffer.h"
#include "string.h"
#include "interrupts.h"
#include "gdt.h"

void kmain(void)
{	//video mem begins here.
  init_gdt();
  init_idt();
  clear_fb();
  char *string = "HELLO WORLD";
  printf(string, TYPE_FRAMEBUFFER, strlen(string));
}
