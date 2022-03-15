#ifndef __STM32L476R_NUCLEO_BUTTON_H
#define __STM32L476R_NUCLEO_BUTTON_H

#include "stm32l476xx.h"

void BUTTON_Init(void);
char isPressed(int b);

#endif
