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
#include "30010_io.h"
#include "ansi.h"



typedef struct{
    int32_t h, m, s, hs,tick;
} timerr_t;

timerr_t tim;
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
 tim.tick++;
 tim.hs++;
 tim.s = (tim.hs / 100)%60;
 tim.m = (tim.hs / 100 / 60)%60;
 tim.h = (tim.hs / 100 / 60 / 60)%60;
}

void TIM2_IRQHandler(void) {
 flag=1;
 TIM2->SR &= ~0x0001; // Clear interrupt bit
 }

void readUART(char *buffer){
    uint8_t i;
    for(i=0; i<256; i++){
        buffer[i]=uart_get_char();
        if(buffer[i]=='\0'){
            break;
        }

    }
}

int main(void)
{
    int i=0;
    uint8_t buffer[256];
    uint8_t a[256];

    int start=0;

    tim.hs=0;
    tim.s=0;
    tim.m=0;
    tim.h=0;

    uart_init( 9600 ); // Initialize USB serial at 9600 baud
    clrscr();
    clockconfig();

    box(1,1,31,5,1);
    //TIM2_IRQHandler();
    gotoxy(2,2);
    printf("Time since start: 00.00.00.--\n");gotoxy(2,3);
    printf("Split time 1:     --:--:--.--");gotoxy(2,4);
    printf("Split time 2:     --:--:--.--");


    while(1){

        readUART(buffer);
/*
        if(a[i] != buffer){
            a[i]=buffer;
            i++;
        }*/

        printf("%s",buffer);
        //printf("%s",a);


        if(buffer[0]==0x0D){
            gotoxy(5,5);
            printf("%s",a);
        }


        if(flag){
            timerupdate();
            flag=0;
        }

 /*       if(start){
            if(tim.tick==100){
                    gotoxy(2,2);

                    printf("Time since start: %02d:%02d:%02d.--",tim.h,tim.m,tim.s);
                    tim.tick=0;
            }
        }else{
            if(tim.tick==100){
                    gotoxy(2,2);
                    printf("Time since start: 00.00.00.--");
                    tim.tick=0;
                    tim.hs=0;
            }
        }*/
    }
}
