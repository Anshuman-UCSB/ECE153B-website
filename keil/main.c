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

int PATTERN_SIZE = 2;
int BUTTONS = 2;

int main(void){
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	BUTTON_Init();
	RNG_Init();

	// srand("SOME RANDOM NUMBER"); // TODO: REILEY

	int i, j;
	int button;
	struct Queue* q = createQueue();
	while(1){
		// PATTERN STATE
		clear(q);
		for(i = 0;i<PATTERN_SIZE;i++){
			button = rand()%BUTTONS;
			push(q, button);
			LED_On(button);
			delay(1000);
			LED_Off(button);
			delay(100);
		}
		
		// PLAY STATE
		while(1){
			for(i = 0;i<BUTTONS;i++){
				if(isPressed(i)){
					LED_On(i);
					if(i != pop(q))
						goto incorrect;
					while(isPressed(i)); // wait till released
					LED_Off(i);
					if(isEmpty(q))
						goto win;
				}
			}
			delay(1);
		}
		
		// WIN STATE
		win:
		delay(500);
		for(i=0;i<4;i++){
			for(j=0;j<4;j++)
				LED_Toggle(j);
			delay(300);
		}
		delay(1000);
		continue;

		// LOSE STATE
		incorrect:
		delay(500);
		for(i = 0;i<4;i++)
			LED_On(i);
		delay(3000);
		for(i = 0;i<4;i++)
			LED_Off(i);
	}
}
