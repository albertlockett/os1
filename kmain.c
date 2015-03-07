#include "io.h"
#include "fb.h"
#include "serial.h"

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
}
