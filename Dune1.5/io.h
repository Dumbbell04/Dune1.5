/*
* raw(?) I/O
*/
#ifndef _IO_H_
#define _IO_H_

#include "common.h"

KEY get_key(void);
void printc(POSITION pos, char ch, int color);
void gotoxy(POSITION pos);
void set_color(int color);
void draw_rect(int color, int start_x, int start_y, int width, int height, char fill_char);
void clear_screen();


#endif
	