#include "SysClock.h"

void System_Clock_Init(void) {
	// Select MSI as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;		// set System clock source to MSI

	// Set MSI clock range
	RCC->CR &= ~RCC_CR_MSIRANGE;
	RCC->CR |= RCC_CR_MSIRANGE_7; 	// Set MSI to 8MHz

	// Use the MSI clock range that is defined in RCC_CR
	RCC->CR |= RCC_CR_MSIRGSEL; // Use bits in RCC_CR MSIRANGE

	// Enable MSI oscillator
	RCC->CR |= RCC_CR_MSION; // Turn on MSI

	// Wait until MSI is ready
	while((RCC->CR & RCC_CR_MSIRDY) == 0);

	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	// Select HSI as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while((RCC->CFGR & RCC_CFGR_SWS) == 0);
}

// void System_Clock_Init(void) {
// 	RCC->CR &= ~RCC_CR_MSION;
// 	// Set MSI to 400 kHz
// 	RCC->CR &= ~RCC_CR_MSIRANGE;
// 	RCC->CR |= RCC_CR_MSIRANGE_1;
// 	// Enable MSI
// 	RCC->CR |= RCC_CR_MSION;
// 	while((RCC->CR & RCC_CR_MSIRDY) != RCC_CR_MSIRDY);

// 	// Select MSI as system clock source
// 	RCC->CFGR &= ~RCC_CFGR_SW;
// 	while((RCC->CFGR & RCC_CFGR_SWS) != 0);
// }
