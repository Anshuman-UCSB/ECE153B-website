#include <stdio.h>

#include "Config.h"
#include "UART.h"

extern int CHOOSE;
extern int BUTTONS;
extern int LOSE_PENALTY;
extern int ROUND_STARTUP;
extern int VIBRATION_TIME;
extern uint32_t DURATION;

void gameStartup(void){
	Init_USARTx(1);

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

	// Vibration Time: how long the motor vibrates for to dispense treats
	printf("\nSet amount of treats (High/Medium/Low): ");
	scanf("%c", &ans);
	switch(ans){
		case 'h': case 'H':
			VIBRATION_TIME = 100;
			printf("\nAmount of treats was set to High\n");
			break;
		case 'm': case 'M':
			VIBRATION_TIME = 50;
			printf("\nAmount of treats was set to Medium\n");
			break;
		case 'l': case 'L':
			VIBRATION_TIME = 30;
			printf("\nAmount of treats was set to Low\n");
			break;
		default:
			DURATION = 50;
			printf("\nInvalid input using Medium\n");
	}

	printf("\n\nGame is starting\n");
}

