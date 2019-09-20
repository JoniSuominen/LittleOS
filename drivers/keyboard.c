#include "keyboard.h"
#include "../io.h"
#include "../string.h"

char * keyboard_map[] = {
    "ERR", "ESC", "1", "2", "3", "4", "5",
    "6", "7", "8", "9", "0", "-_", "+=", "BKSP", "Tab",
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[",
    "]", "Enter", "Ctrl", "A", "S", "D", "F", "G", "H", "J",
    "K", "L", ":", "'", "~", "L SH", "|", "Z", "X", "C", "V",
    "B", "N", "M", ",", ".", "?", "R SH", "PrtScr", "Alt", "Spc",
    "CpsLck", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9",
    "F10"
};


void keyboard_handler() {
  unsigned char status;
  char keycode;

  outb(0x20, 0x20);

  status = inb(KEYBOARD_STATUS_PORT);

  if (status & 0x01) {
    keycode = inb(KEYBOARD_DATA_PORT);
    char * string = keyboard_map[(int)keycode];
    if (keycode < 0) {
      return;
    }
    printf(string, TYPE_FRAMEBUFFER, strlen(string));
  }
}

void keyboard_irq_init() {
  // 0xFD equals 11111101 - this only enables the keyboard.
  outb(0x21, 0xFD);
}