#include "OLED.h"
#include "SPI.h"
#include "SysTimer.h"

void ClearScreen(void){
    int i;
    for(i = 0; i < 1024; i++){
		SPI_Transfer_Byte(SPI2, 0xFF, 1);
        delay(1);
    }
}