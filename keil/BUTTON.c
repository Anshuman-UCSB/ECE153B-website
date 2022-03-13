#include "BUTTON.h"
#include <assert.h>

void BUTTON_Init(void){    
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  
    
    GPIOC->MODER &= ~GPIO_MODER_MODE5;	// set to input mode	
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD5;	// set to pull-up
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD5_0;

	GPIOC->MODER &= ~GPIO_MODER_MODE6;	// set to input mode	
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD6;  // set to pull-up
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD6_0;
	
    GPIOC->MODER &= ~GPIO_MODER_MODE8;	// set to input mode	
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD8;	// set to pull-up
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD8_0;

    GPIOC->MODER &= ~GPIO_MODER_MODE9;	// set to input mode	
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD9;	// set to pull-up
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD9_0;
}

char isPressed(int b){
    switch(b){
        case 0: return ((GPIOC->IDR & GPIO_IDR_ID5) == 0);
        case 1: return ((GPIOC->IDR & GPIO_IDR_ID6) == 0);
        case 2: return ((GPIOC->IDR & GPIO_IDR_ID8) == 0);
        case 3: return ((GPIOC->IDR & GPIO_IDR_ID9) == 0);
    }
    assert(0);
}

