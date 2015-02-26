#include "io.h"
#include "fb.h"

void run()
{   int i;
	for(i = 0; i < 20; i++) {
	    fb_write("hello world hello world ", 20);  
	    fb_write("hello world hello world ", 20);  
   	 	fb_write("hello world hello world ", 20);  
   	 	fb_write("hello world hello world ", 20);  
	    fb_write("hello world hello world ", 20);  
	    fb_write("hello world hello world ", 20);  
	    fb_write("hello world hello world ", 20);  
	}

	fb_clear();
	fb_write("albert ", 6);

}
