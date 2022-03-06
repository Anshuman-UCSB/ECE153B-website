#ifndef __STM32L476R_NUCLEO_LED_H
#define __STM32L476R_NUCLEO_LED_H

#include "stm32l476xx.h"

void LED_Init(void);

void Green_LED_Toggle(void);

void LED_Off(int led);
void LED_On(int led);
void LED_Set(int led, int val);
void LED_Toggle(int led);

void LED0_Off(void);
void LED0_On(void);
void LED0_Set(int val);
void LED0_Toggle(void);

void LED1_Off(void);
void LED1_On(void);
void LED1_Set(int val);
void LED1_Toggle(void);

void LED2_Off(void);
void LED2_On(void);
void LED2_Set(int val);
void LED2_Toggle(void);

void LED3_Off(void);
void LED3_On(void);
void LED3_Set(int val);
void LED3_Toggle(void);

#endif
