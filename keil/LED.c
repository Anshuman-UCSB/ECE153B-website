#include "LED.h"

void LED_Init(void) {
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; // Enable GPIOC clock

	// Greed LED
	GPIOA->MODER &= ~GPIO_MODER_MODE5_1; // Set pin to output
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT5; // Set pin to push pull
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5; // Set pin to no PUPD

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

void Green_LED_Toggle(void) {	GPIOA->ODR ^= GPIO_ODR_OD5;}
void Green_LED_On(void)		{	GPIOA->ODR |= GPIO_ODR_OD5;}
void Green_LED_Off(void)		{	GPIOA->ODR |= GPIO_ODR_OD5;}


void LED_Off(int led){
	switch(led){
		case 0:	LED0_Off();	break;
		case 1:	LED1_Off();	break;
		case 2:	LED2_Off();	break;
		case 3:	LED3_Off();	break;
	}
}
void LED_On(int led){
	switch(led){
		case 0:	LED0_On();	break;
		case 1:	LED1_On();	break;
		case 2:	LED2_On();	break;
		case 3:	LED3_On();	break;
	}
}
void LED_Set(int led, int val){
	switch(led){
		case 0:	LED0_Set(val);	break;
		case 1:	LED1_Set(val);	break;
		case 2:	LED2_Set(val);	break;
		case 3:	LED3_Set(val);	break;
	}
}
void LED_Toggle(int led){
	switch(led){
		case 0:	LED0_Toggle();	break;
		case 1:	LED1_Toggle();	break;
		case 2:	LED2_Toggle();	break;
		case 3:	LED3_Toggle();	break;
	}
}
int LED_State(int led){
	switch(led){
		case 0:	return LED0_State();
		case 1:	return LED1_State();
		case 2:	return LED2_State();
		case 3:	return LED3_State();
	}
	return 0;
}

void LED0_Off(void)  		{	GPIOC->ODR &= ~GPIO_ODR_OD0;}
void LED0_On(void)  		{	GPIOC->ODR |= GPIO_ODR_OD0;}
void LED0_Toggle(void)  	{	GPIOC->ODR ^= GPIO_ODR_OD0;}
int LED0_State(void)  		{	return GPIOC->ODR & GPIO_ODR_OD0;}
void LED0_Set(int val){
	if(val)
		LED0_On();
	else
		LED0_Off();
}

void LED1_Off(void)  		{	GPIOC->ODR &= ~GPIO_ODR_OD1;}
void LED1_On(void)  		{	GPIOC->ODR |= GPIO_ODR_OD1;}
void LED1_Toggle(void)  	{	GPIOC->ODR ^= GPIO_ODR_OD1;}
int LED1_State(void)  		{	return GPIOC->ODR & GPIO_ODR_OD1;}
void LED1_Set(int val){
	if(val)
		LED1_On();
	else
		LED1_Off();
}

void LED2_Off(void)  		{	GPIOC->ODR &= ~GPIO_ODR_OD2;}
void LED2_On(void)  		{	GPIOC->ODR |= GPIO_ODR_OD2;}
void LED2_Toggle(void)  	{	GPIOC->ODR ^= GPIO_ODR_OD2;}
int LED2_State(void)  		{	return GPIOC->ODR & GPIO_ODR_OD2;}
void LED2_Set(int val){
	if(val)
		LED2_On();
	else
		LED2_Off();
}

void LED3_Off(void)  		{	GPIOC->ODR &= ~GPIO_ODR_OD3;}
void LED3_On(void)  		{	GPIOC->ODR |= GPIO_ODR_OD3;}
void LED3_Toggle(void)  	{	GPIOC->ODR ^= GPIO_ODR_OD3;}
int LED3_State(void)  		{	return GPIOC->ODR & GPIO_ODR_OD2;}
void LED3_Set(int val){
	if(val)
		LED3_On();
	else
		LED3_Off();
}
