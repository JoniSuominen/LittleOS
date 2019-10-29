#ifndef INCLUDE_IO_FRAMEBUFFER
#define INCLUDE_IO_FRAMEBUFFER

/* Background colors */
#define FB_GREEN     2
#define FB_DARK_GREY 8

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

void clear_fb();
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_move_cursor(unsigned short pos);
void fb_write(char* string, unsigned int len);
void next_line();

#endif /** INCLUDE_IO_FRAMEBUFFER */