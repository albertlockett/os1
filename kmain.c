#include "io.h"
#include "fb.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
    return arg1 + arg2 + arg3;
}


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
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

 /** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(unsigned short com)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com)
{
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

// TODO:Implement these functions
// serial configure
//serial_write


void run()
{   
    // try writing message to port
    char* c = (char *) 10000;
    c[0] = 'a';
    c[1] = 'b';

    fb_write((char*) 10000, 2);


    // Write something to serial port
    unsigned short com = SERIAL_COM1_BASE;

    serial_configure_baud_rate(com, 1);
    serial_configure_line(com);
    serial_configure_buffer(com);
    serial_configure_modem(com);

    outb(SERIAL_DATA_PORT(com), (0x00 >> 0) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), 0x41 & 0x00FF);

    outb(SERIAL_DATA_PORT(com), (0x00 >> 0) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), 0x0a & 0x00FF);

}