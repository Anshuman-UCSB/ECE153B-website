#include "LED.h"

void LED_Init(void) {
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; // Enable GPIOC clock

	// Initialize LED0
	GPIOC->MODER &= ~GPIO_MODER_MODE0_1; // Set pin to output
	GPIOC->MODER |= GPIO_MODER_MODE0_0;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT0; // Set pin to push pull
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD0; // Set pin to no PUPD

    // Initialize LED1
	GPIOC->MODER &= ~GPIO_MODER_MODE1_1; // Set pin to output
	GPIOC->MODER |= GPIO_MODER_MODE1_0;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT1; // Set pin to push pull
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD1; // Set pin to no PUPD

    // Initialize LED2
	GPIOC->MODER &= ~GPIO_MODER_MODE2_1; // Set pin to output
	GPIOC->MODER |= GPIO_MODER_MODE2_0;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT2; // Set pin to push pull
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD2; // Set pin to no PUPD

    // Initialize LED3
	GPIOC->MODER &= ~GPIO_MODER_MODE3_1; // Set pin to output
	GPIOC->MODER |= GPIO_MODER_MODE3_0;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT3; // Set pin to push pull
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD3; // Set pin to no PUPD
}

void LED0_Off(void) {
	GPIOC->ODR &= ~GPIO_ODR_OD0;
}

void LED0_On(void) {
	GPIOC->ODR |= GPIO_ODR_OD0;
}

void LED0_Toggle(void) {
	GPIOC->ODR ^= GPIO_ODR_OD0;
}

void LED1_Off(void) {
	GPIOC->ODR &= ~GPIO_ODR_OD1;
}

void LED1_On(void) {
	GPIOC->ODR |= GPIO_ODR_OD1;
}

void LED1_Toggle(void) {
	GPIOC->ODR ^= GPIO_ODR_OD1;
}

void LED2_Off(void) {
	GPIOC->ODR &= ~GPIO_ODR_OD2;
}

void LED2_On(void) {
	GPIOC->ODR |= GPIO_ODR_OD2;
}

void LED2_Toggle(void) {
	GPIOC->ODR ^= GPIO_ODR_OD2;
}

void LED3_Off(void) {
	GPIOC->ODR &= ~GPIO_ODR_OD3;
}

void LED3_On(void) {
	GPIOC->ODR |= GPIO_ODR_OD3;
}

void LED3_Toggle(void) {
	GPIOC->ODR ^= GPIO_ODR_OD3;
}

