#include "io.h"

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
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);


/** fb_move_cursor:
 *  used to move the cursor within the frame buffer
 *
 *  param pos position within frame buffer to move cursor to
 */
void fb_move_cursor(unsigned short pos);


/** fb_scroll:
 *  scrolls the contents of the frame buffer up one row, inserters blank row
 *  at the bottom
 */
void fb_scroll();


/** fb_clear():
 *  clears the contents of the framebuffer and resuts cursot to 0
 */
void fb_clear();


/** fb_get_position():
 *  gets the current numerical position of the cursor
 */
unsigned short fb_get_position();


/** fb_increment_cursor_row:
 *  move the cursor down one row
 */
void fb_increment_cursor_row();


/** fb_increment_cursor_col:
 *  moves the cusor right one column
 */
void fb_increment_cursor_col();


/** fb_write:
 *  write some text to the cursor
 *
 *  param buf pointer to character string
 *  param len length of string to write
 */
int fb_write(char *buf, unsigned int len);
