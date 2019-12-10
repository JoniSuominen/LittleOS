#include "io/io.h"
#include "io/framebuffer.h"
#include "utils/string.h"
#include "interrupts/interrupts.h"
#include "segmentation/gdt.h"
#include "multiboot.h"
#include "segmentation/pages.h"
#include "segmentation/kheap.h"
#include "utils/common.h"
#include "vfs/initrd.h"
#include "vfs/vfs.h"


extern uint32_t placement_address;

void kmain(unsigned int ebx)
{	//video mem begins here.
  multiboot_info_t  *mbinfo = (multiboot_info_t *) (ebx);
  init_gdt();
  init_idt();
  
  /*
  uint32_t initrd_location = *((uint32_t*)mbinfo->mods_addr);
  uint32_t initrd_end = *(uint32_t *)(mbinfo->mods_addr + 4);
  placement_address = initrd_end;
  */
  clear_fb();
  next_line();
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
  printf("d: ", TYPE_FRAMEBUFFER, strlen("d: "));
  printf("0x", TYPE_FRAMEBUFFER, strlen("0x"));
  printf(itoa(d, 16), TYPE_FRAMEBUFFER, strlen(itoa(d, 16)));
  next_line();

  uint32_t e = kmalloc(8);
  printf("e: ", TYPE_FRAMEBUFFER, strlen("e: "));
  printf("0x", TYPE_FRAMEBUFFER, strlen("0x"));
  printf(itoa(e, 16), TYPE_FRAMEBUFFER, strlen(itoa(e, 16)));
  next_line();

  char * string6  = "Free'ing out d and e...";
  printf(string6, TYPE_FRAMEBUFFER, strlen(string6));
  next_line();
  kfree((uint32_t *)d);
  kfree((uint32_t *)e);

  char *mallocString = "Next malloc now allocates address of e, ";
  printf(mallocString, TYPE_FRAMEBUFFER, strlen(mallocString));
  uint32_t f = kmalloc(8);
  printf("f: ", TYPE_FRAMEBUFFER, strlen("f: "));
  printf("0x", TYPE_FRAMEBUFFER, strlen("0x"));
  printf(itoa(f, 16), TYPE_FRAMEBUFFER, strlen(itoa(f, 16)));
  next_line();
  
  /*
  fs_root = initialize_initrd(initrd_location);
  int i = 0;
struct dirent *node = 0;
while ( (node = readdir_fs(fs_root, i)) != 0)
{
  printf("Found file: ", TYPE_FRAMEBUFFER, strlen("Found file: "));
  next_line();
  printf(node->name, TYPE_FRAMEBUFFER, strlen(node->name));
  next_line();
  fs_node_t *fsnode = finddir_fs(fs_root, node->name);
  if ((fsnode->flags&0x7) == FS_DIRECTORY) {
    printf("\n\t(directory)\n", TYPE_FRAMEBUFFER, strlen("\n\t(directory)\n"));
        asm volatile("xchg %bx, %bx");
    next_line();
  }
  else
  {
    asm volatile("xchg %bx, %bx");
    printf("\n\t contents: \"", TYPE_FRAMEBUFFER, strlen("\n\t contents: \""));
    next_line();
    char buf[256];
    uint32_t sz = read_fs(fsnode, 0, 256, buf);
    uint32_t j;
    for (j = 0; j < sz; j++){
      write_char(buf[j]);
    }
    printf("\"\n", TYPE_FRAMEBUFFER, strlen("\"\n"));
  }
  i++;
}
*/


  
  
} 

