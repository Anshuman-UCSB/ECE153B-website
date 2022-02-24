#include "stm32l476xx.h"

#include "LED.h"

#include <string.h>
#include <stdio.h>


int main(void) {
	LED_Init();
	int counter = 0;
	while(1) {
		counter+=1;
        LED0_Toggle();
		if (counter % 2 == 1)
			LED1_Toggle();

        for(volatile int i = 0; i < 500000; i++);
	}
}
