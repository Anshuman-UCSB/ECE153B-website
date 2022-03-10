#include "stm32l476xx.h"

#include "EXTI.h"
#include "LED.h"
#include "BUTTON.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "RNG.h"
#include "SPI.h"
#include "UART.h"

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
	printf("Enter \'H\' for high, \'M\' for medium and \'L\' for low\n\n");

	// Choose: Number of buttons per round that are lit
	printf("Set the number of buttuns per round that are lit up: ");
	scanf("%c", &ans);
	if(ans == 'h' || ans == 'H'){
		CHOOSE = 4;
		printf("\nNumber of buttons was set to High\n");
	}
	else if(ans == 'm' || ans == 'M'){
		CHOOSE = 3;
		printf("\nNumber of buttons was set to Medium\n");
	}
	else if(ans == 'l' || ans == 'L'){
		CHOOSE = 1;
		printf("\nNumber of buttons was set to Low\n");
	}
	else{
		printf("\nInvalid input using default\n");
		CHOOSE = 1;
	}

	// Loose Penalty: How much time lights stay on for after a loss
	printf("\nSet how long lights stay on after a loss: ");
	scanf("%c", &ans);
	if(ans == 'h' || ans == 'H'){
		LOSE_PENALTY = 3000;
		printf("\nLose Penalty was set to High\n");
	}
	else if(ans == 'm' || ans == 'M'){
		LOSE_PENALTY = 1500;
		printf("\nLose Penalty was set to Medium\n");
	}
	else if(ans == 'l' || ans == 'L'){
		LOSE_PENALTY = 500;
		printf("\nLose Penalty was set to Low\n");
	}
	else{
		printf("\nInvalid input using default\n");
		LOSE_PENALTY = 1500;
	}

	// Round Startup: Delay at beinning of round for lighting up buttons
	printf("\nSet time delay at the beginning of each round for lighting up buttons: ");
	scanf("%c", &ans);
	if(ans == 'h' || ans == 'H'){
		ROUND_STARTUP = 1500;
		printf("\nRound Startup was set to High\n");
	}
	else if(ans == 'm' || ans == 'M'){
		ROUND_STARTUP = 500;
		printf("\nRound Startup was set to Medium\n");
	}
	else if(ans == 'l' || ans == 'L'){
		ROUND_STARTUP = 100;
		printf("\nRound Startup was set to Low\n");
	}
	else{
		printf("\nInvalid input using default\n");
		ROUND_STARTUP = 500;
	}
	
	// Duration: How long you have to press all the buttons
	printf("\nSet how long you have to press all the buttons before you loose the round: ");
	scanf("%c", &ans);
	if(ans == 'h' || ans == 'H'){
		DURATION = 5000;
		printf("\nDuration was set to High\n");
	}
	else if(ans == 'm' || ans == 'M'){
		DURATION = 3000;
		printf("\nDuration was set to Medium\n");
	}
	else if(ans == 'l' || ans == 'L'){
		DURATION = 1000;
		printf("\nDuration was set to Low\n");
	}
	else{
		printf("\nInvalid input using default\n");
		DURATION = 3000;
	}

	printf("\n\nGame is starting\n");
}


int main(void){
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	BUTTON_Init();
	Init_USARTx(1);
	initializeDisplay();
	// RNG_Init();

	// srand("SOME RANDOM NUMBER"); // TODO: REILEY

	uint32_t start;
	int i,j, count;
	char rxByte;

	gameStartup();


	while(1){

		scanf("%c", &rxByte);
		printf("Recieved %c", &rxByte);
		if(rxByte == 'y' || rxByte == 'Y'){
			printf("The green LED has been turned on\n");
			Green_LED_Toggle();
		}else if(rxByte == 'n' || rxByte == 'N'){
			printf("The green LED has been turned off\n");
			Green_LED_Toggle();
		}else{
			printf("Unrecognized command, please enter a valid command.\n");
		}
		// I2C_SendData(I2C1, SlaveAddress, &Data_Send, 1);


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
		delay(LOSE_PENALTY);
		for(i = 0;i<BUTTONS;i++)
			LED_Off(i);
	}
}
