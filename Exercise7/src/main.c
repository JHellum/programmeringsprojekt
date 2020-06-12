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
#include "stm32f30x_conf.h"
#include "ansi.h"
#include "30010_io.h"
#include "charset.h"
#include <string.h>

//int tick=0;
uint8_t flag;

void clockconfig(){

    //Timer
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;


    TIM2->CR1 &=  ~(0x0001 << 0);    //disable timer

    TIM2->CR1 &= ~(0x0001 << 11);   //UIFREMAP
    TIM2->CR1 &= ~(0x0003 << 8);    //CKD
    TIM2->CR1 &= ~(0x0001 << 7);    //ARPE
    TIM2->CR1 &= ~(0x0003 << 5);    //CMS
    TIM2->CR1 &= ~(0x0001 << 4);    //DIR
    TIM2->CR1 &= ~(0x0001 << 3);    //OPM
    TIM2->CR1 &= ~(0x0001 << 2);    //URS
    TIM2->CR1 &= ~(0x0001 << 1);    //UDIS

    TIM2->PSC = 0;
    TIM2->ARR = 639999;

    //Interrupts
    TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
    NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt


    //Enable timer
    TIM2->CR1 |=  (0x0001 << 0);    //Enable timer.
}

void timerupdate(){
 //tick++;
}

void TIM2_IRQHandler(void) {
 flag=1;
 TIM2->SR &= ~0x0001; // Clear interrupt bit
 }

void lcd_create_string(char *s, uint16_t x, uint16_t y, uint8_t *buffer) {
	uint8_t i, j;
	y *= 128;
	for(i = 0; i < strlen(s); i++) {
		for(j = 0; j < 5; j++) {
			buffer[x + y + j] = character_data[s[i] - 0x20][j];
		}
		x += 5;
	}
}

void lcd_scrolling_string(char *s, uint8_t *buffer,int i){
    uint8_t temparray[512], j;

    lcd_create_string(s,i,0,buffer);

    for(j=0; j<128; j++){
        temparray[j]=buffer[j];
    }

    lcd_push_buffer(temparray);

}

void update(char *s,uint8_t *buffer, uint8_t *tempBuffer){

    static int k=0;
    int j;

    for(j=0; j<128;j++){
            if(j == 127){
                buffer[127]=tempBuffer[k];

            }else{
                buffer[j]=buffer[j+1];
            }
    }
    k++;

    if(strlen(s)*5>127){
        if(k>strlen(s)*5)
        k=0;
    }else{
        if(k>127)
        k=0;
    }



}

int main(void){

    clockconfig();
    lcd_init();
    int tick=0;
    uint8_t buffer[512], tempBuffer[512];
    memset(buffer,0x00,512);
    memset(tempBuffer,0x00,512);

    lcd_create_string("hello1 ",0,0,tempBuffer);

    while(1){
        if(flag){
            tick++;
            flag=0;



        if(tick%5==1){
            update("hello1 ",buffer,tempBuffer);

            lcd_push_buffer(buffer);
            //tick=0;
        }
        }
    }
}
