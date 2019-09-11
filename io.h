#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#define TYPE_FRAMEBUFFER 0
#define TYPE_SERIAL 1
/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 * 
 *  @param port THE I/O port to send the data to
 *  @param data the data to send to the I/O port
 */

void outb(unsigned short port, unsigned char data);

void load_gdt(unsigned int address, unsigned short size);

void load_segment_registers();

/**F
 * Reads the data from given I/O port. Defined in io.s
 * 
 * @param The I/O port to read data from
 */
int inb(unsigned short port);

void printf(char *data, unsigned int type, unsigned int len);

#endif /** INCLUDE_IO_H */