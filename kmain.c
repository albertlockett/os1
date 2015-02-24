#include "io.h"
//#include "fb.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
    return arg1 + arg2 + arg3;
}

// FRAME BUFFER ===============================================================

// Text colors
#define FB_BLACK        0
#define FB_BLUE         1
#define FB_GREEN        2
#define FB_CYAN         3
#define FB_RED          4
#define FB_MAGENTA      5
#define FB_BROWN        6
#define FB_LT_GREY      7
#define FB_DARK_GREY    8
#define FB_LT_BLUE      9
#define FB_LT_GREEN    10
#define FB_LT_CYAN     11
#define FB_LT_RED      12
#define FB_LT_MAGENTA  13
#define FB_LT_BROWN    14
#define FB_WHITE       15

// IO PORTS
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

// IO PORT COMMANDS
#define FB_HIGH_BYTE_COMMAND    14 // move cursor command low
#define FB_LOW_BYTE_COMMAND     15 // move cursor command high


/** fb_write_cell:
 *  used to write a character to a cell in the framebuffer
 *
 * param i which cell to write to
 * param c the ascii char to write
 * param fg foreground color
 * param bf background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    char *fb = (char *) 0x000B8000;
    fb[i*2] = c;
    fb[i*2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/** fb_move_cursor:
 *  used to move the cursor within the frame buffer
 *
 *  param pos position within frame buffer to move cursor to
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos>>8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}


/** fb_write:
 *  write some text to the cursor
 *
 *  param buf pointer to character string
 *  param len length of string to write
 */
void fb_write(char *buf, unsigned int len){

    unsigned int i = 0;
    for(i = 0; i < len; i++) {
        fb_write_cell(i, buf[i], FB_BLACK, FB_WHITE);
    }

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