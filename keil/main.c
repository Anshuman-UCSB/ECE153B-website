#include "stm32l476xx.h"

#include "EXTI.h"
#include "LED.h"
#include "BUTTON.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "queue.h"
#include "RNG.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern uint32_t volatile msTicks;

int CHOOSE = 1;
int BUTTONS = 2;
uint32_t DURATION = 3000;

int main(void){
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	BUTTON_Init();
	// RNG_Init();

	// srand("SOME RANDOM NUMBER"); // TODO: REILEY

	uint32_t start;
	int i,j, count;
	while(1){

		// SETUP
		for(i = 0;i<BUTTONS;i++) LED_Off(i);
		delay(500);
		count = CHOOSE;
		while(count){
			i = rand()%BUTTONS;
			if(LED_State(i) == 0){
				count--;
				LED_On(i);
			}
		}
		// By here, <count> led's have been turned on
		start = msTicks;
		while(msTicks-start < DURATION){
			for(i = 0;i<BUTTONS;i++){
				if(isPressed(i)) LED_Off(i);
			}
			count = 0;
			for(i = 0;i<BUTTONS;i++)
				count|=LED_State(i);
			if(count == 0)
				goto win;
		}
		goto incorrect;

		// WIN STATE
		win:
		for(i = 0;i<BUTTONS;i++) LED_Off(i);
		delay(100);
		for(i=0;i<4;i++){
			for(j=0;j<BUTTONS;j++)
				LED_Toggle(j);
			delay(150);
		}
		delay(1000);
		continue;

		// LOSE STATE
		incorrect:
		for(i = 0;i<BUTTONS;i++) LED_Off(i);
		delay(500);
		for(i = 0;i<BUTTONS;i++)
			LED_On(i);
		delay(1500);
		for(i = 0;i<BUTTONS;i++)
			LED_Off(i);
	}
}
