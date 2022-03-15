#include "PWM.h"
#include "LED.h"
#include "SysTimer.h"
extern uint32_t volatile msTicks;
extern uint32_t volatile msCounter;

void PWM_Init(void){
    // Clock should be enabled in other peripheral inits
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    GPIOB->MODER &= ~GPIO_MODER_MODE0; // set to output
    GPIOB->MODER |= GPIO_MODER_MODE0_0;
    GPIOA->MODER &= ~GPIO_MODER_MODE4; // set to output
    GPIOA->MODER |= GPIO_MODER_MODE4_0;
    GPIOA->MODER &= ~GPIO_MODER_MODE1; // set to output
    GPIOA->MODER |= GPIO_MODER_MODE1_0;
    
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT0; // Set pin to push pull
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT4; // Set pin to push pull
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT1; // Set pin to push pull

    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0; // Set pin to no PUPD
    GPIOB->ODR&=~GPIO_ODR_OD0;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4; // Set pin to no PUPD
    GPIOA->ODR&=~GPIO_ODR_OD4;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1; // Set pin to no PUPD
    GPIOA->ODR&=~GPIO_ODR_OD1;

}

void Motor(uint32_t duration){
	msCounter = duration;
	while(msCounter){
		GPIOB->ODR|=GPIO_ODR_OD0;
		delay(1);
		GPIOB->ODR&=~GPIO_ODR_OD0;
		//delay(5);
		Green_LED_Toggle();
	}
}

// dir = 1 opens flap
void Flap(uint32_t duration, int dir){
	msCounter = duration;
	uint32_t mask = (dir?GPIO_ODR_OD1:GPIO_ODR_OD4);
	GPIOA->ODR &= ~(GPIO_ODR_OD1|GPIO_ODR_OD4);
	while(msCounter){
		GPIOA->ODR|=mask;
		delay(1);
		GPIOA->ODR&=~mask;
		// delay(5);
		Green_LED_Toggle();
	}
}
