#include "stm32l476xx.h"

// #include "EXTI.h"
#include "LED.h"
#include "BUTTON.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "RNG.h"
#include "SPI.h"
#include "UART.h"
#include "OLED.h"
#include "hash.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern uint32_t volatile msTicks;


int CHOOSE = 1;
int BUTTONS = 2;
int LOSE_PENALTY = 1500;
int ROUND_STARTUP = 500;
uint32_t DURATION = 3000;


void Init_USARTx(int x){
	if (x == 1){
		UART1_Init();
		UART1_GPIO_Init();
		USART_Init(USART1);
	}
	else if (x == 2){
		UART2_Init();
		UART2_GPIO_Init();
		USART_Init(USART2);
	}
	else{
		// Do nothing...
	}
}

void gameStartup(void){
	char ans = ' ';
	// On startup set parameters
	printf("Set game parameters\n");
	printf("Enter 'L' for low, 'M' for medium and 'H' for high\n\n");

	// Choose: Number of buttons per round that are lit
	printf("Set the number of buttuns per round that are lit up (1/2/4): ");
	scanf("%c", &ans);
	switch(ans){
		case 'h': case 'H':
			CHOOSE = 4;
			printf("\nNumber of buttons was set to 4\n");
			break;
		case 'm': case 'M':
			CHOOSE = 2;
			printf("\nNumber of buttons was set to 2\n");
			break;
		case 'l': case 'L':
			CHOOSE = 1;
			printf("\nNumber of buttons was set to 1\n");
			break;
		default:
			CHOOSE = 1;
			printf("\nInvalid input using 1\n");
	}

	// Loose Penalty: How much time lights stay on for after a loss
	printf("\nSet how long lights stay on after a loss (.5s/1.5s/3s): ");
	scanf("%c", &ans);
	switch(ans){
		case 'h': case 'H':
			LOSE_PENALTY = 3000;
			printf("\nLose Penalty was set to 3.0s\n");
			break;
		case 'm': case 'M':
			LOSE_PENALTY = 1500;
			printf("\nLose Penalty was set to 1.5s\n");
			break;
		case 'l': case 'L':
			LOSE_PENALTY = 500;
			printf("\nLose Penalty was set to .5s\n");
			break;
		default:
			LOSE_PENALTY = 1500;
			printf("\nInvalid input using 1.5s\n");
	}

	// Round Startup: Delay at beinning of round for lighting up buttons
	printf("\nSet time delay at the beginning of each round for lighting up buttons (.1s/.5s/1.5s): ");
	scanf("%c", &ans);
	switch(ans){
		case 'h': case 'H':
			ROUND_STARTUP = 1500;
			printf("\nRound Startup was set to 1.5s\n");
			break;
		case 'm': case 'M':
			ROUND_STARTUP = 500;
			printf("\nRound Startup was set to .5s\n");
			break;
		case 'l': case 'L':
			ROUND_STARTUP = 100;
			printf("\nRound Startup was set to .1s\n");
			break;
		default:
			ROUND_STARTUP = 500;
			printf("\nInvalid input using .5s\n");
	}
	
	// Duration: How long you have to press all the buttons
	printf("\nSet how long you have to press all the buttons before you lose the round (1s/3s/5s): ");
	scanf("%c", &ans);
	switch(ans){
		case 'h': case 'H':
			DURATION = 5000;
			printf("\nDuration was set to 5s\n");
			break;
		case 'm': case 'M':
			DURATION = 3000;
			printf("\nDuration was set to 3s\n");
			break;
		case 'l': case 'L':
			DURATION = 1000;
			printf("\nDuration was set to 1s\n");
			break;
		default:
			DURATION = 3000;
			printf("\nInvalid input using 3s\n");
	}

	printf("\n\nGame is starting\n");
}


int main(void){
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	BUTTON_Init();
	//Init_USARTx(1);
	initializeDisplay();
	RNG_Init();

	drawImage(title);

	//gameStartup();


	while(1){

		drawImage(win);
		delay(2000);
		drawImage(lose);
		delay(2000);


		// // SETUP
		// for(i = 0;i<BUTTONS;i++) LED_Off(i);
		// delay(ROUND_STARTUP);
		// count = CHOOSE;
		// while(count){
		// 	i = rand()%BUTTONS;
		// 	if(LED_State(i) == 0){
		// 		count--;
		// 		LED_On(i);
		// 	}
		// }
		// // By here, <count> led's have been turned on
		// start = msTicks;
		// while(msTicks-start < DURATION){
		// 	for(i = 0;i<BUTTONS;i++){
		// 		if(isPressed(i)) LED_Off(i);
		// 	}
		// 	count = 0;
		// 	for(i = 0;i<BUTTONS;i++)
		// 		count|=LED_State(i);
		// 	if(count == 0)
		// 		goto win;
		// }
		// goto incorrect;

		// // WIN STATE
		// win:
		// for(i = 0;i<BUTTONS;i++) LED_Off(i);
		// delay(100);
		// for(i=0;i<4;i++){
		// 	for(j=0;j<BUTTONS;j++)
		// 		LED_Toggle(j);
		// 	delay(150);
		// }
		// delay(1000);
		// continue;

		// // LOSE STATE
		// incorrect:
		// for(i = 0;i<BUTTONS;i++) LED_Off(i);
		// delay(500);
		// for(i = 0;i<BUTTONS;i++)
		// 	LED_On(i);
		// delay(LOSE_PENALTY);
		// for(i = 0;i<BUTTONS;i++)
		// 	LED_Off(i);
	}
}
