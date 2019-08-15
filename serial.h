#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

/**
 * Sets the speed of data being set. It is calculated by dividing the default speed
 * of serial port (11520 bits/s) by divisor.  
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/**
 * serial_configure_line:
 * Configures the data being set over the serial line.
 */
void serial_configure_line(unsigned short com);

/**
 * serial_configure_modem
 * Configures the data flow of hardware via Ready to transmit (RTS)
 * and Data Terminal Ready (DTR) pins. Value of 1 on these bits indicate
 * we are ready to send data
 * 
 */
void serial_configure_modem(unsigned short com);

/**
 * serial_is_transmit_fifo_empty:
 * Checks whether the COM ports transmit FIFO queue is empty.
 * Bit 5 declares the status.
 */
int serial_is_transmit_fifo_empty(unsigned int com);

/**
 * serial_write:
 * Writes a string of specified length to COM port
 */
void serial_write(unsigned short com, char* string, unsigned int len);

#endif /** INCLUDE_IO_H */