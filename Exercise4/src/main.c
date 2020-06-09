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

void vectorinit(vector_t *v, int32_t a){
    v->x=calccos(a);
    v->y=calcsin(a);
}

void ballinit(ball_t *o, vector_t v, int x, int y){
    o->x=x;
    o->y=y;

    o->x <<= 14;
    o->y <<= 14;

    o->v=v;
}


void rotateVector(vector_t *vec, int32_t v){
    int32_t tempx;
    tempx=FIX14_MULT(vec->x<<14, calccos(v))-FIX14_MULT(vec->y<<14, calcsin(v));
    vec->y=FIX14_MULT(vec->x<<14, calcsin(v))+FIX14_MULT(vec->y<<14, calccos(v));
    vec->x=tempx;
}

void ballpos(ball_t *o, int x1, int y1, int x2, int y2){



    x1++;
    x1<<=14;
    x2<<=14;
    y1++;
    y1<<=14;
    y2<<=14;

    gotoxy(o->x>>14,o->y>>14);
    printf(" ");

    o->x += o->v.x;
    o->y += o->v.y;

    if(o->x<=x1){
    o->x=x1+x1-o->x;
    o->v.x*=-1;
    }

    if(o->y<=y1){
    o->y=y1+y1-o->y;
    o->v.y*=-1;
    }

    if(o->x>=x2){
    o->x=x2+x2-o->x;
    o->v.x*=-1;
    }

    if(o->y>=y2){
    o->y=y2+y2-o->y;
    o->v.y*=-1;
    }



}

void drawball(ball_t o){
    gotoxy(o.x>>14,o.y>>14);
    printf("o");
}

int main(void)
{
    uart_init( 9600 ); // Initialize USB serial at 9600 baud
    clrscr();
    box(4,2,80,30,1);
    int i=0;


    vector_t v;
    ball_t o;

    vectorinit(&v,300);
    ballinit(&o, v, 10,10);



while(i<600){
     ballpos(&o,4,2,80,30);
     drawball(o);
     i++;
}
  while(1){

  }
}
