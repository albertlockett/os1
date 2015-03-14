#include "io.h"
#include "fb.h"
#include "serial.h"
#include "gdt.h"
#include "interrupt.h"

void run()
{  

	fb_clear();
	fb_write("starting operating system", 25);
	fb_increment_cursor_row();

	// configure serial port
	fb_write("configuring serial port", 23);
	serial_configure_default(SERIAL_COM1_BASE);


	// begin logging to serial port
	serial_write(SERIAL_COM1_BASE, "serial port initialized", 30);


	// load global descriptors table
	struct gdt seg1;
	seg1.address = 0x08;
	seg1.size = 0xFF;
	load_gdt(seg1);

}

void interrupt_handler()
{
	serial_write(SERIAL_COM1_BASE, "int triggered", 14);
}

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7

#define PIC_ACK     0x20

/** pic_acknowledge:
 *  Acknowledges an interrupt from either PIC 1 or PIC 2.
 *
 *  @param num The number of the interrupt
 */
void pic_acknowledge(unsigned int interrupt)
{
    if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT) {
      return;
    }

    if (interrupt < PIC2_START_INTERRUPT) {
      outb(PIC1_PORT_A, PIC_ACK);
    } else {
      outb(PIC2_PORT_A, PIC_ACK);
    }
}
