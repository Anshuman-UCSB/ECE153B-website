#include "RNG.h"

void RNG_Init(void){
    // Enable RNG Clock
    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;

    // Set MSI as RNG clock
    

    // Reset Clock
    RCC->AHB2RSTR |= RCC_AHB2RSTR_RNGRST;
    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_RNGRST;

    // Enable RNG
    RNG->CR |= RNG_CR_RNGEN;
    // Enable RNG Interrupt
    RNG->CR |= RNG_CR_IE;

    while((RNG->SR & RNG_SR_DRDY) == 0);
}
