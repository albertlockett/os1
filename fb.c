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

unsigned short __fb_position = 0;
unsigned short __fb_cursor_row = 0;
unsigned short __fb_cursor_col = 0;

void fb_scroll() {
	
	int col;
	int row;
	char *fb = (char *) 0x000B8000;

	for(row =  1; row < 25; row ++) {
		for(col =  0; col < 80;  col ++) {
			int position = col + row * 80;
			unsigned char c 	= fb[position * 2];
			unsigned char color = fb[position * 2 + 1];

			unsigned char color_fg = (color & 0x0F) >> 4;
			unsigned char color_bg = (color & 0x0f);

			fb_write_cell(position - 80, c,  color_fg, color_bg);

		}
	}

	for(col = 0; col < 80; col ++) { 
		
		int last_row_offset = 24 * 80;
		fb_write_cell(last_row_offset + col, ' ', FB_BLACK, FB_WHITE);
	}


}

void fb_clear() {

	int i;
	for(i = 0; i < 24; i++ ) {
		fb_scroll();
	}

	__fb_cursor_row = 0;
	__fb_cursor_col = 0;
	fb_move_cursor(0);


}


unsigned short fb_get_position() {
	unsigned short position = (__fb_cursor_row * 80) + __fb_cursor_col;
	return position;
}

void fb_increment_cursor_row() {
	if(__fb_cursor_row ==  24) {
		fb_scroll();
	} else {
		__fb_cursor_row++;
	}
}

void fb_increment_cursor_col() {
	if(++__fb_cursor_col == 80) {
		__fb_cursor_col =  0;
		fb_increment_cursor_row();
	}

	fb_move_cursor(fb_get_position());
}



int fb_write(char *buf, unsigned int len) {
    unsigned int i;
	unsigned short start_pos = fb_get_position();

    for(i = 0; start_pos + i < start_pos + len; i++) {
        fb_write_cell(start_pos + i, buf[i], FB_BLACK, FB_WHITE);
		fb_increment_cursor_col();
    }

    return 0;

}
