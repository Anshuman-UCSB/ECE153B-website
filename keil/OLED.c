#include "OLED.h"
#include "SPI.h"
#include "SysTimer.h"

void ClearScreen(void){
    int i;
    for(i = 0; i < 1024; i++){
		SPI_Transfer_Byte(SPI2, 0x00, 1);
    }
}

void drawImage(uint8_t* img){
	int i;
	ClearScreen();
	for(i = 0;i<1024;i++){
		SPI_Transfer_Byte(SPI2, img[i], 1);
	}
}

