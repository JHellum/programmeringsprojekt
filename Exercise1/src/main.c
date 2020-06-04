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
    int width  = x2-x1;
    int height = y2-y1;
    //printf("12345678901234567890");
    //printf("1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n");
    //
    gotoxy(x1,y1);
    printf("%c%c", 201,185);
    color(0,7);
    printf("%s",head);
    color(15,0);
    for(int i=0; i<=width-4-strlen(head);i++){
        printf(" ");
    }
    printf("%c%c", 204,187);

    gotoxy(x1,y2);
        printf("%c",200);
    for(int i=0; i<=width-2;i++)
        printf("%c",205);
        printf("%c",188);

    for(int i=1;i<height;i++){
        gotoxy(x1,y1+i);
        printf("%c",186);
        gotoxy(x2,y1+i);
        printf("%c",186);
    }


  //  for(int i = x1; x1<)

}


int main(void)
{
uart_init( 9600 ); // Initialize USB serial at 9600 baud
clrscr();
//(15,0);
window(2,2,14,14, "Hejsa",1);

window(6,15,21,25, "REEE",1);
}

/*int16_t a;
printf("\n\n x x^2 x^3 x^4\n");
for (a = 0; a < 10; a++)
printf("%8d%8d%8d%8d\n",a, power(a, 2), power(a, 3), power(a, 4));*/
