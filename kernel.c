#include "io/io.h"
#include "io/framebuffer.h"
#include "utils/string.h"
#include "interrupts/interrupts.h"
#include "segmentation/gdt.h"

void kmain(void)
{	//video mem begins here.

  init_gdt();
  init_idt();
  clear_fb();
  char * string = "HELLO JONI";
  printf(string, TYPE_SERIAL, strlen(string));
}