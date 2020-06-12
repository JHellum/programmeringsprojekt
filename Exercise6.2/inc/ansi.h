#include <stdint.h>
#include <stdio.h>

#ifndef _ANSI_H_
#define _ANSI_H_

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void clrscr();
void clrreol();
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t onn);
void box(int x1, int y1, int x2, int y2, int style);
#endif /* _ANSI_H_ */
