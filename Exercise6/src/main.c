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

void setJoystick(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

    // Set pin PC0 to input
    GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
    GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

     // Set pin PC1 to input
    GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
    GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00

    // Set pin PA4 to input
    GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
    GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00

    // Set pin PB0 to input
    GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
    GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00

    // Set pin PB5 to input
    GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
    GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00
}

uint16_t readJoystick(){

    uint8_t valbyte=0;

    uint16_t up     = GPIOA->IDR & (0x0001 << 4);   //Read from pin PA4
    uint16_t down   = GPIOB->IDR & (0x0001 << 0);   //Read from pin PB0
    uint16_t left   = GPIOC->IDR & (0x0001 << 1);   //Read from pin PC1
    uint16_t right  = GPIOC->IDR & (0x0001 << 0);   //Read from pin PC0
    uint16_t center = GPIOB->IDR & (0x0001 << 5);   //Read from pin PB5

    if(up)          {valbyte |=1<<0;}
    else if(down)   {valbyte |=1<<1;}
    else if(left)   {valbyte |=1<<2;}
    else if(right)  {valbyte |=1<<3;}
    else if(center) {valbyte |=1<<4;}
    else            {valbyte =0;}


    return valbyte;
}

int main(void)
{
    int start=0;
    int newj=0;
    int oldj=0;

    tim.hs=0;
    tim.s=0;
    tim.m=0;
    tim.h=0;

    uart_init( 9600 ); // Initialize USB serial at 9600 baud
    clrscr();
    clockconfig();
    setJoystick();
    box(1,1,31,5,1);
    //TIM2_IRQHandler();
    gotoxy(2,2);
    printf("Time since start: 00.00.00.--\n");
    gotoxy(2,3);
    printf("Split time 1:     --:--:--.--");
    gotoxy(2,4);
    printf("Split time 2:     --:--:--.--");


    while(1){
        oldj=newj;
        newj=readJoystick();



        if(flag){
            timerupdate();
            flag=0;
        }

        if(oldj != newj){
            switch(newj){
            case 1: printf("UP!\n");    break;
            case 2: printf("DOWN!\n");  break;

            case 4://left
                if(start){
                    gotoxy(2,3);
                    printf("Split time 1:     %02d:%02d:%02d.%02d",tim.h,tim.m,tim.s,tim.hs%100);
                }

                break;

            case 8://right
                if(start){
                    gotoxy(2,4);
                    printf("Split time 3:     %02d:%02d:%02d.%02d",tim.h,tim.m,tim.s,tim.hs%100);
                }
                break;
            case 16:
                if(start){
                    gotoxy(2,2);
                    printf("Time since start: 00.00.00.--");
                }
                start= ~start;
                break;

            default: break;
            }
        }

        if(start){
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
        }
    }
}
