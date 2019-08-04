#include "io.h"
#include "framebuffer.h"

void kmain(void)
{	//video mem begins here.
  clear_fb();
  fb_write_cell(0, 'A', FB_GREEN, FB_DARK_GREY);
  fb_move_cursor(26);
  fb_write_string(80, "HELLO WORLD!");
	return;
}
