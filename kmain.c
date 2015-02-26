#include "io.h"
#include "fb.h"

void run()
{   
    // try writing message to port
    char* c = (char *) 10000;
    c[0] = 'a';
    c[1] = 'b';

    fb_write("ab", 2);  

}