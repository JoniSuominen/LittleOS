#include "io.h"
#include "framebuffer.h"
#include "string.h"

void kmain(void)
{	//video mem begins here.
  clear_fb();
  char *string = "HELLO WORLD";
  fb_write("HELLO WORLD", strlen(string));
	return;
}
