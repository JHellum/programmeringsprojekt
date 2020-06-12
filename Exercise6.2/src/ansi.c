#define ESC 0x1B
#include "ansi.h"
void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr(){
    printf("%c[0;0H", ESC);
    printf("%c[J", ESC);
}

void clrreol(){
    printf("%c[K", ESC);
}

void gotoxy(uint8_t x, uint8_t y){
    printf("%c[%d;%dH", ESC,y,x);
}

void underline(uint8_t onn){
    int v;
    if (onn == 1){v=04;}
    else{v=24;}

    printf("%c[%dm", ESC,v);
}

void box(int x1, int y1, int x2, int y2, int style){

    int cornertl;
    int cornertr;
    int cornerbl;
    int cornerbr;

    int lineh;
    int linev;

    int width;
    int height;

    if(style>0){
        cornertl=201;
        cornertr=187;
        cornerbl=200;
        cornerbr=188;

        linev = 186;
        lineh = 205;
    }else{
        cornertl=218;
        cornertr=191;
        cornerbl=192;
        cornerbr=217;

        linev = 179;
        lineh = 196;
    }

    if(x1<1||x2<1||y1<1||y2<1){
        x1=1;
        x2=1;
        y1=1;
        y2=1;
    }

    if(x1>x2){
        int dummy=x1;
        x1=x2;
        x2=dummy;
    }
    if(y1>y2){
        int dummy=y1;
        y1=y2;
        y2=dummy;
    }

    width  = x2-x1;
    height = y2-y1;


    //topline print
    gotoxy(x1,y1);
    printf("%c", cornertl);
    for(int i=0; i<=width-2;i++){
        printf("%c",lineh);
    }
    printf("%c",cornertr);

    //bottomline print
    gotoxy(x1,y2);
        printf("%c",cornerbl);
    for(int i=0; i<=width-2;i++)
        printf("%c",lineh);
        printf("%c",cornerbr);

    //side print
    for(int i=1;i<height;i++){
        gotoxy(x1,y1+i);
        printf("%c",linev);
        gotoxy(x2,y1+i);
        printf("%c",linev);
    }


}
