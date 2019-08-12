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

/**
 * Sets the speed of data being set. It is calculated by dividing the default speed
 * of serial port (11520 bits/s) by divisor.
 * Thus the speed is (11520 / divisor)
 * @param com     The COM port to configure
 * @param divisor The divisor   
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/**
 * serial_configure_line:
 * Configures the data being set over the serial line.
 * For example 0x03 means data length of 8 bits, no parity bit, one stop bit
 * and a break control
 * @param com the serial port to configure
 */
void serial_configure_line(unsigned short com);
#endif /** INCLUDE_IO_H */