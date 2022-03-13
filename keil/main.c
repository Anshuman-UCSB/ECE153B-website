#include "stm32l476xx.h"

#include "LED.h"
#include "BUTTON.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "RNG.h"
#include "SPI.h"
#include "UART.h"
#include "OLED.h"
#include "hash.h"
#include "PWM.h"
#include "Config.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern uint32_t volatile msTicks;


int CHOOSE = 1;
int BUTTONS = 2;
int LOSE_PENALTY = 1500;
int ROUND_STARTUP = 500;
int VIBRATION_TIME = 50;
uint32_t DURATION = 3000;

int main(void){
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	BUTTON_Init();
	initializeDisplay();
	RNG_Init();
	PWM_Init();
	// delay(1000);
	// Motor(1000);


	// drawImage(title);

	gameStartup();

	int i, j, count, start;
	while(1){
		delay(1000);
		//Green_LED_Toggle();
		// delay(2000);
		// delay(2000);


		// SETUP
		for(i = 0;i<BUTTONS;i++) LED_Off(i);
		delay(ROUND_STARTUP);
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
		drawImage(win);
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
		drawImage(lose);
		for(i = 0;i<BUTTONS;i++) LED_Off(i);
		delay(500);
		for(i = 0;i<BUTTONS;i++)
			LED_On(i);
		delay(LOSE_PENALTY);
		for(i = 0;i<BUTTONS;i++)
			LED_Off(i);
	}
}
