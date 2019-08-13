#include "io.h"
#include "serial.h"

/* All serial ports have their ports in same order, only the
 * starting value changes
 * */
#define SERIAL_COM1_BASE  0x3F8
#define SERIAL_DATA_PORT(base)  (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/*  Serial port commands
*   Tell the serial port to expect the data in 2 batches of 8 bytes (first 8 highest, then 8 lowest)
*/
#define SERIAL_LINE_ENABLE_DLAB 0x80

/**
 * Sets the speed of data being set. It is calculated by dividing the default speed
 * of serial port (11520 bits/s) by divisor.
 * Thus the speed is (11520 / divisor)
 * @param com     The COM port to configure
 * @param divisor The divisor   
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}


/**
 * serial_configure_line:
 * Configures the data being set over the serial line.
 * For example 0x03 means data length of 8 bits, no parity bit, one stop bit
 * and a break control
 * Good to know:
 * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b | prty  | s | dl  |
 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
 * 
 * @param com the serial port to configure
 */
void serial_configure_line(unsigned short com) {
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/**
 * serial_configure_modem
 * Configures the data flow of hardware via Ready to transmit (RTS)
 * and Data Terminal Ready (DTR) pins. Value of 1 on these bits indicate
 * we are ready to send data
 * Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr | 
 * 
 */
void serial_configure_modem(unsigned short com) {
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/**
 * serial_is_transmit_fifo_empty:
 * Checks whether the COM ports transmit FIFO queue is empty.
 * Bit 5 declares the status.
 * 
 * @param com the COM port
 */
int serial_is_transmit_fifo_empty(unsigned int com) {
  return inb(SERIAL_LINE_STATUS_PORT(com) & 0x20);
}