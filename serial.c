#include "io.h"
#include "serial.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) 
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

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


void serial_configure_default(unsigned short com) 
{
	serial_configure_baud_rate(com, 1);
	serial_configure_line(com);
	serial_configure_buffer(com);
	serial_configure_modem(com);
}


int serial_is_transmit_fifo_empty(unsigned int com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}


void serial_write_char(unsigned short com, char c) 
{
	outb(SERIAL_DATA_PORT(com), (0x00 >> 0) & 0x00FF);
	outb(SERIAL_DATA_PORT(com), c & 0x00FF);
}


void serial_write(unsigned short com, char * buff, int l)
{
	int i;
	for(i = 0; i < l; i++) {
		while(!serial_is_transmit_fifo_empty(com));
		serial_write_char(com, buff[i]);
	}
}
