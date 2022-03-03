#include "EXTI.h"
#include "LED.h"

void EXTI_Init(void) {
	// Initialize User Button
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;    // Enable clock for GPIO C
	GPIOC->MODER &= ~GPIO_MODER_MODE13;		// Set mode of PC13 to input
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;		// Set PC13 to No PUPD

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;    // Enable clock for GPIO C
	GPIOC->MODER &= ~GPIO_MODER_MODE9;		// Set mode of PC13 to input
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD9;		// Set PC13 to No PUPD
	
	// Configure SYSCFG EXTI
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI9;
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI9_PC;
	
	// Configure EXTI Trigger
	EXTI->RTSR1 &= ~(EXTI_RTSR1_RT13); // set to falling edge
	EXTI->FTSR1 |= EXTI_RTSR1_RT13;

    EXTI->RTSR1 &= ~(EXTI_RTSR1_RT9); // set to falling edge
	EXTI->FTSR1 |= EXTI_RTSR1_RT9;
	
	// Enable EXTI
	EXTI->IMR1 |= EXTI_IMR1_IM13;

    EXTI->IMR1 |= EXTI_IMR1_IM9;
	
	// Configure and Enable in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);

    NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_SetPriority(EXTI9_5_IRQn, 0);
}

void EXTI9_5_IRQHandler(void){
    // Clear EXTI PR1 pending bit 9
    EXTI->PR1 |= EXTI_PR1_PIF9;

	// Toggle Green LED
	Green_LED_Toggle();
    LED0_Toggle();

}

void EXTI15_10_IRQHandler(void){
	// Clear EXTI PR1 pending bit 13
	EXTI->PR1 |= EXTI_PR1_PIF13;

	// Toggle Green LED
	Green_LED_Toggle();
    LED0_Toggle();
}
