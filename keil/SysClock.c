#include "SysClock.h"

void System_Clock_Init(void) {
	RCC->CR &= ~RCC_CR_MSION;
	// Set MSI to 400 kHz
	RCC->CR &= ~RCC_CR_MSIRANGE;
	RCC->CR |= RCC_CR_MSIRANGE_1;
	// Enable MSI
	RCC->CR |= RCC_CR_MSION;
	while((RCC->CR & RCC_CR_MSIRDY) != RCC_CR_MSIRDY);

	// Select MSI as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	while((RCC->CFGR & RCC_CFGR_SWS) != 0);
}
