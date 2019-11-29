#include "io/io.h"
#include "io/framebuffer.h"
#include "utils/string.h"
#include "interrupts/interrupts.h"
#include "segmentation/gdt.h"
#include "multiboot.h"
#include "segmentation/pages.h"
#include "segmentation/kheap.h"
#include "utils/common.h"


void kmain(unsigned int ebx)
{	//video mem begins here.
  multiboot_info_t  *mbinfo = (multiboot_info_t *) ebx;
  init_gdt();
  init_idt();
  
  clear_fb();
  char * string = "Initializing paging...";
  printf(string, TYPE_FRAMEBUFFER, strlen(string));
  initialize_paging();
  next_line();
  char * string2 = "Initialized paging succesfully";
  printf(string2, TYPE_FRAMEBUFFER, strlen(string2));
  next_line();
  //unsigned int *ptr = (unsigned int *) 0xA0000000; 
  //unsigned int page_fault = *ptr;
  char * string3 = "Initializing heap...";
  printf(string3, TYPE_FRAMEBUFFER, strlen(string3));
  next_line();
  char * string4 = "Initializing heap succesfully!";
  printf(string4, TYPE_FRAMEBUFFER, strlen(string4));
  next_line();

  char * string5  = "Trying out malloc...";
  printf(string5, TYPE_FRAMEBUFFER, strlen(string5));
  next_line();
  
  uint32_t d = kmalloc(8);
  printf("0x", TYPE_FRAMEBUFFER, strlen("0x"));
  printf(itoa(d, 16), TYPE_FRAMEBUFFER, strlen(itoa(d, 16)));
  next_line();
  uint32_t e = kmalloc(8);
  printf("0x", TYPE_FRAMEBUFFER, strlen("0x"));
  printf(itoa(e, 16), TYPE_FRAMEBUFFER, strlen(itoa(e, 16)));
  next_line();
  kfree((uint32_t *)d);
  kfree((uint32_t *)e);
  uint32_t f = kmalloc(8);
  printf("0x", TYPE_FRAMEBUFFER, strlen("0x"));
  printf(itoa(f, 16), TYPE_FRAMEBUFFER, strlen(itoa(f, 16)));
  next_line();
  
  
} 

