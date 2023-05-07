/*
 * DAC_lib.c
 *
 *  Created on: Apr 24, 2023
 *      Author: colecosta7
 */
#include "../DAC_lib/DAC_lib.h"

void DAC_init(void){
	//enable SPI clock, GPIO clock
	RCC -> APB2ENR |= (RCC_APB2ENR_SPI1EN);
	RCC -> AHB2ENR |= (RCC_AHB2ENR_GPIOAEN);

	//configure GPIO for MOSI PA7, SCLK PA5, NSS PA4
	GPIOA -> MODER &= ~(GPIO_MODER_MODE5 |
						GPIO_MODER_MODE7 |
						GPIO_MODER_MODE4);
	GPIOA -> MODER |= (GPIO_MODER_MODE5_1 |
						GPIO_MODER_MODE7_1 |
						GPIO_MODER_MODE4_1);	//AF for PA5, PA7, PA4

	GPIOA -> OTYPER &= ~(GPIO_OTYPER_OT5 |
						GPIO_OTYPER_OT7 |
						GPIO_OTYPER_OT4);		//push-pull for all

	GPIOA -> PUPDR &= ~(GPIO_PUPDR_PUPD5 |
						GPIO_PUPDR_PUPD7 |
						GPIO_PUPDR_PUPD4);		//none for all

	GPIOA -> OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5 |
						GPIO_OSPEEDR_OSPEED7 |
						GPIO_OSPEEDR_OSPEED4);	//low speed for all possibly change

	GPIOA -> AFR[0] |= (AF5 << GPIO_AFRL_AFSEL5_Pos |
					AF5 << GPIO_AFRL_AFSEL7_Pos |
					AF5 << GPIO_AFRL_AFSEL4_Pos);	//AF5 Alternate Function for SPI1

	//configure the SPI CR1 register
	SPI1 -> CR1 &= ~(SPI_CR1_BR);
	//SPI1 -> CR1 |= (SPI_CR1_BR_1);	//set baud rate to clk/2

	SPI1 -> CR1 &= ~(SPI_CR1_CPHA | SPI_CR1_CPOL);	//set MODE 0'0

	SPI1 -> CR1 &= ~(SPI_CR1_RXONLY);				//set transmit only mode

	SPI1 -> CR1 &= ~(SPI_CR1_LSBFIRST);				//MSB transferred first

	SPI1 -> CR1 &= ~(SPI_CR1_SSM);					//hardware controlled CS

	SPI1 -> CR1 |= (SPI_CR1_MSTR);					//set master mode for peripheral

	SPI1 -> CR2 |= (SPI_CR2_DS_0 | SPI_CR2_DS_1 |
				 	SPI_CR2_DS_3);					//set data frame 12 bits

	SPI1 -> CR2 |= (SPI_CR2_SSOE);					//set SSOE

	SPI1 -> CR2 |= (SPI_CR2_NSSP);					//pulse mode

	SPI1 -> CR1 |= (SPI_CR1_SPE);					//enable SPI1
}

void DAC_write(uint16_t voltage){
	//or the 12 bit voltage value with configuration byte
	uint16_t data = voltage | 0x3000;
	//wait for TX buffer to be empty
	while (!(SPI1->SR & SPI_SR_TXE)){};
	//set the data register
	SPI1 -> DR = data;

}

uint16_t DAC_volt_conv(uint16_t voltage){
	uint16_t value = (uint16_t)(4095 * voltage / 3300);
	return value;
}


