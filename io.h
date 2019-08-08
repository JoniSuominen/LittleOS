#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 * 
 *  @param port THE I/O port to send the data to
 *  @param data the data to send to the I/O port
 */

void outb(unsigned short port, unsigned char data);

/**
 * Reads the data from given I/O port. Defined in io.s
 * 
 * @param The I/O port to read data from
 */
void inb(unsigned short port);
#endif /** INCLUDE_IO_H */