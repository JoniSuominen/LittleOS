#include "framebuffer.h"
#include "io.h"

/* framebuffer location */
char *fb = (char*)0xb8000; 

/**
 * Writes a character with defined foreground and background colors onto the position i
 * @param fb -  framebuffer
 * @param i -   the position in the framebuffer
 * @param c -   the character
 * @param fg -  the foreground color  
 * @param bg -  the background color
 */

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
  fb[i] = c;
  fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/**
 * Clears the framebuffer
 * @param fb -  framebuffer
 */
void clear_fb() {
	unsigned int j = 0;
  	/* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while(j < 80 * 25 * 2) {
		/* blank character */
		fb[j] = ' ';
		/* attribute-byte - light grey on black screen */
		fb[j+1] = 0x07; 		
		j = j + 2;
	}
}

/**
 * writes a string to the framebuffer at specified location and moves the cursor to the last string written
 * @param i - string to write to buffer
 * @param len - length of the string we are writing
 */
void write(char* string, unsigned int len) {
  int i = 0;
  int j = 0;
  // loop until we meet null character
  while(string[j] != '\0') {
      fb[i] = string[j];
      fb[i+1] = 0x07;
      j++;
      i += 2;
  }
  fb_move_cursor(len);
}
/**
 * Scrolls the window by one row
 * Currently holds no memory of earlier rows
 */
void scroll_window() {
  for (int i = 0; i < 25 * 80; i++) {
      fb[i] = 80 + i;
  }
}



/**
 * fb_move_cursor:
 * Moves the cursor of framebuffer to the given position
 * 
 * @param pos - The new position of the cursor
 */

void fb_move_cursor(unsigned short pos) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}
