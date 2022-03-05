#include "stm32l476xx.h"

#include "EXTI.h"
#include "LED.h"
#include "SysClock.h"

#include <string.h>
#include <stdio.h>

int main(void){
	System_Clock_Init();
	LED_Init();
	EXTI_Init();

	while(1);

	return 0;
}

// int main(void) {	
// 	LED_Init();
// 	// Set mode of PA5 to output
//     GPIOA->MODER &= ~GPIO_MODER_MODE3_1; 
//     GPIOA->MODER |=  GPIO_MODER_MODE3_0;
//     // Set output type of PA5 to push - pull
//     GPIOA->OTYPER &= ~GPIO_OTYPER_OT3;
//     //Set PA5 to No PUPD
//     GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3;

	
// 	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
// 	GPIOC->MODER &= ~GPIO_MODER_MODE8;
// 	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD8;
// 	GPIOC->MODER &= ~GPIO_MODER_MODE13;
// 	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
        

// 	int counter = 0;
// 	while(1) {
// 		counter+=1;
//         LED0_Toggle();
// 		if (counter % 2 == 1)
// 			LED1_Toggle();

//         for(volatile int i = 0; i < 500000; i++);
// 	}

// 	return 0;
// }

// void Init(){
//     // Enable HSI
//     RCC->CR |= ((uint32_t)RCC_CR_HSION);
//     while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );

//     // Select HSI as system clock source
//     RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
//     RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;
//     while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );

//     // Enable GPIO Clock
//     RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;    // Enable clock for GPIO A
//     RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;    // Enable clock for GPIO C
    
// 	// Initialize Green LED
//     // Set mode of PA5 to output
//     GPIOA->MODER &= ~GPIO_MODER_MODE5_1; 
//     GPIOA->MODER |=  GPIO_MODER_MODE5_0;

//     // Set output type of PA5 to push - pull
//     GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
//     //Set PA5 to No PUPD
//     GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;

//     // Initialize User Button
//     // Set mode of PC13 to input
//     GPIOC->MODER &= ~GPIO_MODER_MODE13;

//     // Set PC13 to No PUPD
//     GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
// }


// void delay(int ticks){
//     #define TICK_CYCLE_COUNT 1000ULL
//     for(volatile unsigned long long i = 0;i<ticks*TICK_CYCLE_COUNT;i++);
// }


// int main(void){
//     // Initialization
//     Init();

//     // Polling to Check for User Button Presses
//     char pressed = 0, state = 0, prevPressed = 0, tick = 0;

//     for(;;delay(1)){                                    // infinite loop, delay by one tick each iteration
//         prevPressed = pressed;                          // set prevPressed to last button input before updating
//         pressed = (GPIOC->IDR & GPIO_IDR_ID13) == 0;    // update button press to masked PC13 for button
//         if(state)                                       // If we are in the odd state:
//             GPIOA->ODR ^= (++tick % 100 == 0)<<5;       //     toggle the led status if tick is a multiple of 100
//         else                                            // If in even state:
//             GPIOA->ODR |= 1<<5;                         //     turn LED on
//         state^=(!prevPressed && pressed);               // If the button is on the posedge of press, toggle state
// 	}
//     return 0;
// }
