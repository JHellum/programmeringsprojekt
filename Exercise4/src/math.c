#include "math.h"
#include "exlut.h"
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




