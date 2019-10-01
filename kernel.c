#include "io/io.h"
#include "io/framebuffer.h"
#include "utils/string.h"
#include "interrupts/interrupts.h"
#include "segmentation/gdt.h"
#include "multiboot.h"

void kmain(unsigned int ebx)
{	//video mem begins here.

  clear_fb();
  multiboot_info_t  *mbinfo = (multiboot_info_t *) ebx;
  unsigned int * modules = (unsigned int*) mbinfo->mods_addr;
  typedef void (*call_module_t)(void);
  if (mbinfo->mods_count > 0) {
    char *string = "modules loaded, modules count: ";
    printf(string, TYPE_FRAMEBUFFER, strlen(string));
    printf(itoa(mbinfo->mods_count, 10), TYPE_FRAMEBUFFER, strlen(itoa(mbinfo->mods_count, 10)));
    unsigned int addr = modules[0];
    unsigned int size = modules[1];
    call_module_t start_program = (call_module_t)addr;
    start_program();
  } else {
    char * string = "no modules loaded";
    printf(string, TYPE_SERIAL, strlen(string));
  }
  init_gdt();
  init_idt();
} 