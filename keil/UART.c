#include "UART.h"

void UART1_Init(void) {
	// Enable USART1 clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	// Select system clock as source
	RCC->CCIPR &= ~RCC_CCIPR_USART1SEL;
	RCC->CCIPR |= RCC_CCIPR_USART1SEL_0;
}


void UART2_Init(void) {
	// Enable USART2 clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	// Select system clock as source
	RCC->CCIPR &= ~RCC_CCIPR_USART2SEL;
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
}

void Init_USARTx(int x){
	if (x == 1){
		UART1_Init();
		UART1_GPIO_Init();
		USART_Init(USART1);
	}
	else if (x == 2){
		UART2_Init();
		UART2_GPIO_Init();
		USART_Init(USART2);
	}
	else{
		// Do nothing...
	}
}

void UART1_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set to alternate function mode
	GPIOB->MODER &= ~GPIO_MODER_MODE6;
	GPIOB->MODER |= GPIO_MODER_MODE6_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE7;
	GPIOB->MODER |= GPIO_MODER_MODE7_1;
	
	// Set alternatate function AF7 for PB6&7
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL6|GPIO_AFRL_AFRL7);
	GPIOB->AFR[0] |= 0x77000000;

	// very high speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;

	// push-pull output type
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT6;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT7;

	// pull-up resistors
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD6|GPIO_PUPDR_PUPD7);
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_0;
}

void UART2_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	// Set to alternate function mode
	GPIOA->MODER &= ~GPIO_MODER_MODE2;
	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE3;
	GPIOA->MODER |= GPIO_MODER_MODE3_1;
	
	// Set alternatate function AF7
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2|GPIO_AFRL_AFSEL3);
	GPIOA->AFR[0] |= 0x7700;

	// very high speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;

	// push-pull output type
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT2;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT3;

	// pull-up resistors
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2|GPIO_PUPDR_PUPD3);
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0;

}

void USART_Init(USART_TypeDef* USARTx) {
	// disable USART
	USARTx->CR1 &= ~USART_CR1_UE;
	
	// set word length to 8 bits
	USARTx->CR1 &= ~(USART_CR1_M);
	// set oversampling to 16 times
	USARTx->CR1 &= ~USART_CR1_OVER8;
	// set one stop bit
	USARTx->CR2 &= ~USART_CR2_STOP;

	// set baud rate to 9600 by setting USARTDIV to 8333
	USARTx->BRR &= 0xFFFF0000; 	// reset bottom 16 bits
	USARTx->BRR |= 8333;		// set USARTDIV to 8333

	// enable transmitter and reciever
	USARTx->CR1 |= USART_CR1_TE | USART_CR1_RE;

	// reenable USART
	USARTx->CR1 |= USART_CR1_UE;
}

uint8_t USART_Read (USART_TypeDef * USARTx) {
	// SR_RXNE (Read data register not empty) bit is set by hardware
	while (!(USARTx->ISR & USART_ISR_RXNE));  // Wait until RXNE (RX not empty) bit is set
	// USART resets the RXNE flag automatically after reading DR
	return ((uint8_t)(USARTx->RDR & 0xFF));
	// Reading USART_DR automatically clears the RXNE flag 
}

void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	int i;
	// TXE is cleared by a write to the USART_DR register.
	// TXE is set by hardware when the content of the TDR 
	// register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++) {
		while (!(USARTx->ISR & USART_ISR_TXE));   	// wait until TXE (TX empty) bit is set
		// Writing USART_DR automatically clears the TXE flag 	
		USARTx->TDR = buffer[i] & 0xFF;
		USART_Delay(300);
	}
	while (!(USARTx->ISR & USART_ISR_TC));   		  // wait until TC bit is set
	USARTx->ISR &= ~USART_ISR_TC;
}   

void USART_Delay(uint32_t us) {
	uint32_t time = 100*us/7;    
	while(--time);   
}

