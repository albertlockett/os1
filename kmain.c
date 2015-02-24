#include "io.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
    return arg1 + arg2 + arg3;
}

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

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    char *fb = (char *) 0x000B8000;
    fb[i*2] = c;
    fb[i*2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

// CUSROR MOVING 
// io ports
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

// io port commands
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos>>8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

void run()
{
    fb_move_cursor(0);
    fb_write_cell(0, 'H', FB_BLACK, FB_WHITE);
    fb_write_cell(1, 'E', FB_BLACK, FB_WHITE);
    fb_write_cell(2, 'L', FB_BLACK, FB_WHITE);
    fb_write_cell(3, 'L', FB_BLACK, FB_WHITE);
    fb_write_cell(4, '0', FB_BLACK, FB_WHITE);
    fb_write_cell(5, ' ', FB_BLACK, FB_WHITE);
    fb_write_cell(6, 'W', FB_BLACK, FB_WHITE);
    fb_write_cell(7, 'O', FB_BLACK, FB_WHITE);
    fb_write_cell(8, 'R', FB_BLACK, FB_WHITE);
    fb_write_cell(9, 'L', FB_BLACK, FB_WHITE);
    fb_write_cell(10, 'D', FB_BLACK, FB_WHITE);
    fb_write_cell(11, ' ', FB_BLACK, FB_WHITE);
    fb_write_cell(12, ' ', FB_BLACK, FB_WHITE);
    fb_write_cell(13, ' ', FB_BLACK, FB_WHITE);
}