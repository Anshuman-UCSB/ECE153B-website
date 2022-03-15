#ifndef __STM32L476R_NUCLEO_PWM_H
#define __STM32L476R_NUCLEO_PWM_H

#include "stm32l476xx.h"

void PWM_Init(void);
void Motor(uint32_t duration);
void Flap(uint32_t duration, int dir);

#endif
