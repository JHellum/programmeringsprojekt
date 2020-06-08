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
#include "exlut.h"
#include "math.h"


//#include <Windows.h>

#include <unistd.h>



#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

typedef struct {
    int32_t x, y;
} vector_t;

typedef struct {
    int32_t x, y;
    vector_t v;
}ball_t;


void rotateVector(vector_t *vec, int32_t v){
    int32_t tempx;
    tempx=FIX14_MULT(vec->x<<14, calccos(v))-FIX14_MULT(vec->y<<14, calcsin(v));
    vec->y=FIX14_MULT(vec->x<<14, calcsin(v))+FIX14_MULT(vec->y<<14, calccos(v));
    vec->x=tempx;
}


void ballposupdate(ball_t *o, int a, int b, int c, int d){
   /*gotoxy(o->x,o->y);
   printf(" ");*/
    //o->x++;
   // o->y++;
if(o->x<=a || o->x>=c){
    o->v.x*=-1;
}

if(o->y<=b || o->y>=d){
    o->v.y*=-1;
}
    o->x+=o->v.x;
    o->y+=o->v.y;
}
void drawball(ball_t o){
    gotoxy(o.x,o.y);
    printf("o");
}

int main(void)
{
    uart_init( 9600 ); // Initialize USB serial at 9600 baud
    clrscr();
    box(4,2,80,30,1);
    int i=0;
    vector_t v;
    v.x=3;
    v.y=1;

    ball_t o;
    o.x=10;
    o.y=10;
    o.v=v;

while(i<400){
     ballposupdate(&o, 4, 2, 80, 30);
     drawball(o);
     i++;
}
  while(1){

  }
}
