#ifndef INCLUDE_KEYBOARD
#define INCLUDE_KEYBOARD

/* The keyboard ports */
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define FB_DATA_PORT 0x3D5


void keyboard_handler();
void keyboard_irq_init();
#endif /** INCLUDE_IO_FRAMEBUFFER */