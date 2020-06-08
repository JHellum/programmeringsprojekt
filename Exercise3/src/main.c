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

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )


void printFix(int32_t i) {
 // Prints a signed 16.16 fixed point number
 if ((i & 0x80000000) != 0) { // Handle negative numbers
 printf("-");
 i = ~i + 1;
 }
 printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
 // Print a maximum of 4 decimal digits to avoid overflow
 }
int32_t expand(int32_t i) {
 // Converts an 18.14 fixed point number to 16.16
 return i << 2;
 }
int32_t calcsin(int32_t x){

    //-768

    if (x<0) x+=512*(-x/512+1);

     x%=512;
    return SIN[x];
}
int32_t calccos(int32_t x){
    return calcsin(x+128);
}

typedef struct {
    int32_t x, y;
} vector_t;

void rotateVector(vector_t *vec, int32_t v){
    int32_t tempx;
    tempx=FIX14_MULT(vec->x<<14, calccos(v))-FIX14_MULT(vec->y<<14, calcsin(v));
    vec->y=FIX14_MULT(vec->x<<14, calcsin(v))+FIX14_MULT(vec->y<<14, calccos(v));
    vec->x=tempx;
}


int main(void)
{
    uart_init( 9600 );
    clrscr();
/*
    int32_t v = -14;
    vector_t vec;
    vec.x=6;
    vec.y=4;


    rotateVector(&vec,v);

    printFix(expand(vec.x));
    printf("\n");
    printFix(expand(vec.y));
    printf("\n");*/
     printf("h\n");
    printFix(expand(calcsin(10000)));
    printf("\ng\n");
    printFix(expand(calcsin(-10000)));
    printf("\ng\n");
    //printf("%d, %d\n", vec.x,vec.y);

  while(1)
  {

  }
}
