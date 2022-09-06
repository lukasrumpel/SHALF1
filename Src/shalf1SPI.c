/*
 * shalf1SPI.c
 *
 *  Created on: 03.03.2022
 *      Author: lukas
 */

#include <shalf1GPIO.h>
#include <shalf1SPI.h>

/*
  * Desc.: Initializes the SPI Module with the given Parameters
  * @param: (SPI_TypeDef*)spi: SPI
  * @param: (SPI_CLOCK_DIV) clockdivider: CLK_DIV_2 ,
	    									CLK_DIV_4,
	    									CLK_DIV_8,
	    									CLK_DIV_16,
	    									CLK_DIV_32,
	    									CLK_DIV_64,
	    									CLK_DIV_128,
	    									CLK_DIV_256
  * @param: (SPI_DATALEN) datalen: SPI_DATA_8BIT,
									SPI_DATA_16_BIT
  * @param: (SPI_SSM) ssm: SSM_OFF,
							SSM_ON
  * @param: (SPI_SSI_LVL) ssi_lvl: SSI_LVL_LOW,
									SSI_LVL_HIGH
  * @param: (SPI_OPMODE) opmode: MASTER,
									SLAVE
  * @param: (SPI_PHASE) phase: SPI_PHASE_EDGE_1,
								SPI_PHASE_EDGE_2
  * @param: (SPI_POLARITY) polarity: SPI_IDLE_LOW,
										SPI_IDLE_HIGH
  * @return: none
  */
extern void spiInit(SPI_TypeDef *spi, SPI_CLOCK_DIV clockdivider, SPI_DATALEN datalen, SPI_SSM ssm, SPI_SSI_LVL ssi_lvl, SPI_OPMODE opmode, SPI_PHASE phase, SPI_POLARITY polarity){
	uint16_t cr1 = 0;
	if(spi == SPI1){
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	}
	else if(spi == SPI2){
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	}

	switch(clockdivider){
	case CLK_DIV_2:
		cr1 &= ~(SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2 );
		break;
	case CLK_DIV_4:
		cr1 |= SPI_CR1_BR_0;
		break;
	case CLK_DIV_8:
		cr1 |= SPI_CR1_BR_1;
		break;
	case CLK_DIV_16:
		cr1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1;
		break;
	case CLK_DIV_32:
		cr1 |= SPI_CR1_BR_2;
		break;
	case CLK_DIV_64:
		cr1 |= SPI_CR1_BR_0 | SPI_CR1_BR_2;
		break;
	case CLK_DIV_128:
		cr1 |= SPI_CR1_BR_1 | SPI_CR1_BR_2;
		break;
	case CLK_DIV_256:
		cr1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;
		break;
	default:
		cr1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;
		break;
	}

	if(datalen == SPI_DATA_8BIT){
		cr1 &= ~SPI_CR1_DFF_Msk;
	}
	else{
		cr1 |= SPI_CR1_DFF;
	}

	if(ssm == SSM_ON){
		cr1 |= SPI_CR1_SSM;
	}
	else{
		cr1 &= ~SPI_CR1_SSM_Msk;
	}

	if((ssm == SSM_ON) && (ssi_lvl == SSI_LVL_HIGH)){
		cr1 |= SPI_CR1_SSI;
	}
	else if((ssm == SSM_ON) && (ssi_lvl == SSI_LVL_LOW)){
		cr1 &= ~SPI_CR1_SSI_Msk;
	}

	if(opmode == MASTER){
		cr1 |= SPI_CR1_MSTR;
	}
	else{
		cr1 &= ~SPI_CR1_MSTR_Msk;
	}

	if(phase == SPI_PHASE_EDGE_1){
		cr1 &= ~SPI_CR1_CPHA_Msk;
	}
	else{
		cr1 |= SPI_CR1_CPHA;
	}

	if(polarity == SPI_IDLE_LOW){
		cr1 &= ~SPI_CR1_CPOL_Msk;
	}
	else{
		cr1 |= SPI_CR1_CPOL;
	}

	spi->CR1 = cr1;
	spiEnable(spi);
}

/*
  * Desc.: enables the SPI in it's Control Register
  * @param: (SPI_TypeDef*)spi: SPI
  * @return: none
  */
extern void spiEnable(SPI_TypeDef *spi){
	spi->CR1 |= SPI_CR1_SPE;
}

/*
  * Desc.: disables the SPI in it's Control Register
  * @param: (SPI_TypeDef*)spi: SPI
  * @return: none
  */
extern void spiDisable(SPI_TypeDef *spi){
	spi->CR1 &= ~SPI_CR1_SPE_Msk;
}

/*
  * Desc.: Transceive function for SPI (Master!)
  * @param: (SPI_TypeDef*)spi: SPI
  * @param: (GPIO_TypeDef*) cs_port: Port of CS PIN
  * @param: (PIN_NUM) cs_pin: CS PIN
  * @param: (uint8_t) data: data to be sent
  * @param: (bool) manCS: manual Chipselect, CS is controlled from somewhere else
  * @return: (uint8_t) received data
  */
extern uint8_t spiTransceive(SPI_TypeDef *spi, GPIO_TypeDef *cs_port, PIN_NUM cs_pin, uint8_t data, bool manCS){
	static uint8_t state = SPI_SEND_BYTE_1;
	uint8_t rx_byte;

	switch(state){
	case SPI_SEND_BYTE_1:
		if(!manCS){
			gpioResetPin(cs_port, cs_pin);
		}

		while(!(SPI1->SR & SPI_SR_TXE)){}

		spi->DR = data;

		while(SPI1->SR & SPI_SR_BSY){}

		state = SPI_SEND_BYTE_2;
		break;
	case SPI_SEND_BYTE_2:
		while(!(SPI1->SR & SPI_SR_TXE)){}

		spi->DR = data;

		while(SPI1->SR & SPI_SR_BSY){}

		state = SPI_SEND_BYTE_1;
		if(!manCS){
			gpioSetPin(cs_port, cs_pin);
		}
		break;
	}

	rx_byte = spi->DR;

	return rx_byte;
}


