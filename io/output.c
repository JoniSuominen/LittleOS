#include "io.h"
#include "framebuffer.h"
#include "serial.h"

#define SERIAL_COM1_BASE  0x3F8

void printf(char * data, unsigned int type, unsigned int len) {
  if (type) {
    serial_write(SERIAL_COM1_BASE, data, len);
  } else {
    fb_write(data, len);
    
  }
}