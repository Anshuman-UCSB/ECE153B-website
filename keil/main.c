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


int CHOOSE = 2;
int BUTTONS = 4;
int LOSE_PENALTY = 1500;
int ROUND_STARTUP = 500;
int VIBRATION_TIME = 50;
uint32_t DURATION = 3000;
int simulated_buttons[4];
int i, j, count, start;

int main(void){
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	BUTTON_Init();
	initializeDisplay();
	RNG_Init();
	PWM_Init();

	drawImage(title);

	gameStartup();
	delay(1000);
	while(1){
		// SETUP
		ClearScreen();
		for(i = 0;i<BUTTONS;i++) LED_Off(i);
		delay(ROUND_STARTUP);
		count = CHOOSE;
		for(i=0;i<4;i++) simulated_buttons[i] = 0;
		while(count){
			i = rand()%BUTTONS;
			if(simulated_buttons[i]==0)
				simulated_buttons[i] = 1;
			count = CHOOSE;
			for(i = 0;i<4;i++)
				count -= simulated_buttons[i];
		}
		for(i = 0;i<BUTTONS;i++){
			if(simulated_buttons[i]){
				while(LED_State(i)==0)
					LED_On(i);
			}
		}
		// By here, <count> led's have been turned on
		start = msTicks;
		count = CHOOSE;
		while(msTicks-start < DURATION){
			for(i = 0;i<BUTTONS;i++){
				if(isPressed(i) && LED_State(i)){
					LED_Off(i);
					count--;
				}
			}
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
		Flap(1000, 1);
		delay(1000);
		Motor(1000);
		delay(1000);
		Flap(1000, 0);
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
