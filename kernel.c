#include "io/io.h"
#include "io/framebuffer.h"
#include "utils/string.h"
#include "interrupts/interrupts.h"
#include "segmentation/gdt.h"
#include "multiboot.h"
#include "segmentation/pages.h"


void kmain(unsigned int ebx)
{	//video mem begins here.
  multiboot_info_t  *mbinfo = (multiboot_info_t *) ebx;
  init_gdt();
  init_idt();
  
  clear_fb();
  initialize_paging();
  char * string = "Initialized paging succesfully";
  printf(string, TYPE_FRAMEBUFFER, strlen(string));
} 
