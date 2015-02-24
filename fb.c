#include "fb.h"
 
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    char *fb = (char *) 0x000B8000;
    fb[i*2] = c;
    fb[i*2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos>>8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

int fb_write(char *buf, unsigned int len) {

    unsigned int i = 0;
    for(i = 0; i < len; i++) {
        fb_write_cell(i, buf[i], FB_BLACK, FB_WHITE);
    }

    return 0;

}