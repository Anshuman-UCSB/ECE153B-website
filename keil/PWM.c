#include "PWM.h"
#include "LED.h"
#include "SysTimer.h"
extern uint32_t volatile msTicks;
extern uint32_t volatile msCounter;

void PWM_Init(void){
    // Clock should be enabled in other peripheral inits
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    GPIOB->MODER &= ~GPIO_MODER_MODE0; // set to output
    GPIOB->MODER |= GPIO_MODER_MODE0_0;
    
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT0; // Set pin to push pul

    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5; // Set pin to no PUPD
    GPIOB->ODR&=~GPIO_ODR_OD0;

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
