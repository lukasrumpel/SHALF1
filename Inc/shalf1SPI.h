/*
 * shalf1SPI.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1SPI_H_
#define INC_SHALF1SPI_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <shalf1GPIO.h>

typedef enum{
	MASTER,
	SLAVE
}SPI_OPMODE;

typedef enum{
	TWO_LINE_UNI,
	ONE_LINE_BIDI
}SPI_BIDIMODE;

typedef enum{
	DATA_FORMAT_8,
	DATA_FORMAT_16
}SPI_DATAFORMAT;

typedef enum{
		CLK_DIV_2 = 0,
	    CLK_DIV_4,
	    CLK_DIV_8,
	    CLK_DIV_16,
	    CLK_DIV_32,
	    CLK_DIV_64,
	    CLK_DIV_128,
	    CLK_DIV_256
}SPI_CLOCK_DIV;

typedef enum{
	SPI_DATA_8BIT,
	SPI_DATA_16_BIT
}SPI_DATALEN;

typedef enum{
	SSM_OFF,
	SSM_ON
}SPI_SSM;

typedef enum{
	SSI_LVL_LOW,
	SSI_LVL_HIGH
}SPI_SSI_LVL;

typedef enum{
	SPI_PHASE_EDGE_1,
	SPI_PHASE_EDGE_2
}SPI_PHASE;

typedef enum{
	SPI_IDLE_LOW,
	SPI_IDLE_HIGH
}SPI_POLARITY;

typedef enum{
	SPI_SEND_BYTE_1,
	SPI_SEND_BYTE_2
}SPI_8BIT_STATE;

extern void spiInit(SPI_TypeDef *spi, SPI_CLOCK_DIV clockdivider, SPI_DATALEN datalen, SPI_SSM ssm, SPI_SSI_LVL ssi_lvl, SPI_OPMODE opmode, SPI_PHASE phase, SPI_POLARITY polarity);
extern void spiEnable(SPI_TypeDef *spi);
extern void spiDisable(SPI_TypeDef *spi);
extern uint8_t spiTransceive(SPI_TypeDef *spi, GPIO_TypeDef *cs_port, PIN_NUM cs_pin, uint8_t data);

#endif /* INC_SHALF1SPI_H_ */
