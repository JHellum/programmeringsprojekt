/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include <string.h>

int16_t power(int16_t a, int16_t exp) {
// calculates a^exp
int16_t i, r = a;
for (i = 1; i < exp; i++)
r *= a;
return(r);
}

void window(int x1, int y1, int x2, int y2, char *head, int style){

    int cornertl;
    int cornertr;
    int cornerbl;
    int cornerbr;

    int lineh;
    int linev;

    int t1;
    int t2;

    if(style>0){
        cornertl=201;
        cornertr=187;
        cornerbl=200;
        cornerbr=188;

        linev = 186;
        lineh = 205;

        t1 = 185;
        t2 = 204;
    }else{
        cornertl=218;
        cornertr=191;
        cornerbl=192;
        cornerbr=217;

        linev = 179;
        lineh = 196;

        t1 = 180;
        t2 = 195;
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

    int headlength=strlen(head);

    if(x2-x1<headlength+4){
        x2=x1+headlength+3;
    }

    if(y2-y1<2){
        y2=y1+1;
    }

    int width  = x2-x1;
    int height = y2-y1;


    //topline print
    gotoxy(x1,y1);
    printf("%c%c", cornertl,t1);
    color(0,7);
    printf("%s",head);
    color(15,0);
    for(int i=0; i<=width-4-headlength;i++){
        printf(" ");
    }
    printf("%c%c", t2,cornertr);

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


int main(void)
{
uart_init( 9600 ); // Initialize USB serial at 9600 baud
clrscr();
//(15,0);
window(2,2,2,2, "Hejsa",1);

window(3,5,8,16, "REEEEEEEEE",0);

window(-1,0,0,0,"Test",1);
}

/*int16_t a;
printf("\n\n x x^2 x^3 x^4\n");
for (a = 0; a < 10; a++)
printf("%8d%8d%8d%8d\n",a, power(a, 2), power(a, 3), power(a, 4));*/
