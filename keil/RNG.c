#include "RNG.h"
#include <stdio.h>
#include <stdlib.h>

void RNG_Init(void){
    // Enable RNG Clock
    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;

    // Set MSI as RNG clock
    RCC->CCIPR |= RCC_CCIPR_CLK48SEL;

    // Reset Clock
    RCC->AHB2RSTR |= RCC_AHB2RSTR_RNGRST;
    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_RNGRST;

    // Enable RNG
    RNG->CR |= RNG_CR_RNGEN;

    while((RNG->SR & RNG_SR_DRDY) == 0);

    srand(RNG->DR);
}
