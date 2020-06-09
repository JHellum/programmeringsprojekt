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

void initLed(){

    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

    // Set pin PB4(red) to output
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
    GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
    GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000001 << (4 * 2));

    // Set pin PC7(green) to output
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
    GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
    GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000001 << (7 * 2));

    // Set pin PA9(blue) to output
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
    GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
    GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000001 << (9 * 2));
}

void setColor(char color){
    switch(color){

        case 'r': GPIOB->ODR &= ~(0x0001 << 4); break;
        case 'g': GPIOC->ODR &= ~(0x0001 << 7); break;
        case 'b': GPIOA->ODR &= ~(0x0001 << 9); break;

        case 'c': GPIOA->ODR &= ~(0x0001 << 9);
                  GPIOC->ODR &= ~(0x0001 << 7); break;

        case 'm': GPIOA->ODR &= ~(0x0001 << 9);
                  GPIOB->ODR &= ~(0x0001 << 4); break;

        case 'y': GPIOB->ODR &= ~(0x0001 << 4);
                  GPIOC->ODR &= ~(0x0001 << 7); break;

        case 'w': GPIOA->ODR &= ~(0x0001 << 9);
                  GPIOB->ODR &= ~(0x0001 << 4);
                  GPIOC->ODR &= ~(0x0001 << 7); break;

        case 'x': GPIOA->ODR |= (0x0001 << 9);
                  GPIOB->ODR |= (0x0001 << 4);
                  GPIOC->ODR |= (0x0001 << 7); break;

        default: GPIOA->ODR |= (0x0001 << 9);
                 GPIOB->ODR |= (0x0001 << 4);
                 GPIOC->ODR |= (0x0001 << 7); break;
    }

}

void setLed(uint8_t val){

    switch(readJoystick()){
        case 1: setColor('r'); break;
        case 2: setColor('g'); break;
        case 4: setColor('b'); break;
        case 8: setColor('y'); break;
        case 16:setColor('w'); break;
        default: setColor('x'); break;
    }
}

int main(void)
{
    uart_init( 9600 ); // Initialize USB serial at 9600 baud
    clrscr();
    setJoystick();
    initLed();
  while(1)
  {
    clrscr();

    switch(readJoystick()){
        case 1: printf("UP!"); break;
        case 2: printf("DOWN!"); break;
        case 4: printf("LEFT!"); break;
        case 8: printf("RIGHT!"); break;
        case 16: printf("CENTER!"); break;
        default: printf("Waiting for input!");break;
    }

    setLed(readJoystick());
  }
}
