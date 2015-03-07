#include "io.h"

// SERIAL PORT ================================================================

/* IO Ports -- */
/* All the IO ports are calcualated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same order
 * but they start at different values
 */

#define SERIAL_COM1_BASE                0x3F8   /* COM1 base port */
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* IO Port Commands --- */
/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits
 */
#define SERIAL_LINE_ENABLE_DLAB         0x80 

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial port
 *  is 115200 bits/s. The argument is a divsior of that number, hence the 
 *  resulting speed is (115200 /divisor) bit/s
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);


 /** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com);


/** serial_configure_buffer
 *  Configure the buffer for the serial port
 *
 *  @param com the buffer port to configure
 */
void serial_configure_buffer(unsigned short com);


/** serial_configure_modem
 *  Configure the serial port buffer
 * 
 *  @param the modem io port for the serial port
 */
void serial_configure_modem(unsigned short com);


/** serial_configure_default
 *  helper function to do default configuration of serial port
 *
 * @param com the base address of com port to use
 */
void serial_configure_default(unsigned short com);


/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);


/** serial_write_char
 *  write one character to the com port
 * 
 *  @param com the base address of com port to write to
 *  @param c the characer to write to port
 */
void serial_write_char(unsigned short com, char c);


/** serial_write
 *  write the contents of the character buffer to the string for the specified
 *  number of characters
 *
 *  @param com the base address of the com port to write to
 *  @param buff the buffer of characters
 *  @param l the number of characters in the buffer to write
 */
void serial_write(unsigned short com, char * buff, int l);
