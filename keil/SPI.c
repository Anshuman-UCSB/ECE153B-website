
#include "SPI.h"
#include "SysTimer.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly. 
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";

void SPI2_GPIO_Init(void) {
	// Enable GPIOB clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	// Set PB 9,10,11 to output
	GPIOC->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11|GPIO_MODER_MODE12);
	GPIOC->MODER |= GPIO_MODER_MODE10_0|GPIO_MODER_MODE11_0|GPIO_MODER_MODE12_0;

	// Set to Alternate Function Mode
	GPIOB->MODER &= ~GPIO_MODER_MODE13;
	GPIOB->MODER |= GPIO_MODER_MODE13_1;
	GPIOB->MODER &= ~GPIO_MODER_MODE15;
	GPIOB->MODER |= GPIO_MODER_MODE15_1;

	// Set to Alternate Function 5
	GPIOB->AFR[1] |= 0x55500000;
	
	// Push-Pull output type
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_13);
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_15);
	// Very High Output Speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED15;
	// No Pull
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD15;
}

void SPI2_Init(void){
	// Enable SPI2 clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	
	// Set RCC SPI reset bit
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;
	// Clear it to reset SPI2
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_SPI2RST;

	// Disable the SPI enable bit
	SPI2->CR1 &= ~SPI_CR1_SPE;

	// Configure the peripheral for full-duplex communication
	SPI2->CR1 &= ~SPI_CR1_RXONLY;
	
	// Configure the peripheral for 2-line unidirectional data mode
	SPI2->CR1 &= ~SPI_CR1_BIDIMODE;
	
	// Disable output in bidirectional mode
	SPI2->CR1 &= ~SPI_CR1_BIDIOE;
	
	// Configure the frame format as MSB firs
	SPI2->CR1 &= ~SPI_CR1_LSBFIRST;
	
	// Configure the frame format to 8-bit mode
	SPI2->CR2 |= SPI_CR2_DS_0;
	SPI2->CR2 |= SPI_CR2_DS_1;
	SPI2->CR2 |= SPI_CR2_DS_2;
	SPI2->CR2 &= ~SPI_CR2_DS_3;
	
	// Use Motorola SPI mode
	SPI2->CR2 &= ~ SPI_CR2_FRF;

	// Configure the clock to low polarity
	SPI2->CR1 &= ~SPI_CR1_CPOL;
	
	// Configure the clock to first clock transition
	SPI2->CR1 &= ~SPI_CR1_CPHA;

	// Set the baud rate prescaler to 16
	SPI2->CR1 |=  SPI_CR1_BR_0;
	SPI2->CR1 |=  SPI_CR1_BR_1;
	SPI2->CR1 &= ~SPI_CR1_BR_2;

	// Disable hardware CRC calculation
	SPI2->CR1 &= ~SPI_CR1_CRCEN;

	// Set SPI2 to master mode
	SPI2->CR1 |= SPI_CR1_MSTR;

	// Enable software SSM
	SPI2->CR1 |= SPI_CR1_SSM;

	// Enable NSS pulse generation
	SPI2->CR2 |= SPI_CR2_NSSP;

	// Set the FIFO threshold to 1/4 (required for 8-bit mode)
	SPI2->CR2 |= SPI_CR2_FRXTH;
	
	// Enable the SPI peripheral
	SPI2->CR1 |= SPI_CR1_SPE;
}
 
void SPI_Transfer_Byte(SPI_TypeDef* SPIx, uint8_t write_data, int isData) {
	// Wait for the Transmit Buffer Empty flag to become set.
	setCS(0);
	delay(1);
	setDC(isData);
	delay(1);
	while((SPI2->SR&SPI_SR_TXE) == 0);
	
	// Write data to the SPIx->DR register to begin transmission.
	*((volatile uint8_t*)&SPIx->DR) = write_data;

	// Wait for the Busy to become unset.
	while((SPI2->SR&SPI_SR_BSY) != 0);

	setCS(1);
	delay(1);
}

void setReset(int boolean){
	if(boolean){
		GPIOC->ODR |= GPIO_ODR_OD10;
	}else{
		GPIOC->ODR &= ~GPIO_ODR_OD10;
	}
}

void setCS(int boolean){
	if(boolean){
		GPIOC->ODR |= GPIO_ODR_OD12;
	}else{
		GPIOC->ODR &= ~GPIO_ODR_OD12;
	}
}

void setDC(int boolean){
	if(boolean){
		GPIOC->ODR |= GPIO_ODR_OD11;
	}else{
		GPIOC->ODR &= ~GPIO_ODR_OD11;
	}
}

void initializeDisplay(void){
	SPI2_GPIO_Init();
	SPI2_Init();
	setReset(0);
	delay(20);
	setReset(1);

	uint8_t commands[21] = {
		0xAE, // Display Off
		0xA8, // Set MUX Ratio
		0x3F,
		0xD3, // Set Display Offset
		0x00,
		0x40, // Set Display Start Line
		0xA0, // Set Segment re-map
		0xC0, // Set COM Output Scan Direction
		0xDA, // Set COM Pins hardware configuration
		0x02,
		0x81, // Set Contrast Control
		0x7F,
		0x20, // Set Memory Addressing Mode to horizontal scroll
		0x00,
		0xA4, // Disable Entire Display On
		0xA6, // Set Normal Display
		0xD5, // Set Osc Frequency
		0x80,
		0x8D, // Enable charge pump regulator
		0x14,
		0xAF, // Display On
	};
	// uint8_t commands[20] = {0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA0, 0xC0, 0xDA, 0x02, 0x81, 0x7f, 0x20, 0x00, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF};

	int i;
	for(i =0 ;i<21;i++){
		SPI_Transfer_Byte(SPI2, commands[i], 0);
	}
}
