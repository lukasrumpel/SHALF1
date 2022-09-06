/*
 * shalf1USART.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1USART_H_
#define INC_SHALF1USART_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <shalf1GPIO.h>
#include <string.h>

#define BUFFERSIZE (128)

typedef struct{
	uint8_t inPtr;
	uint8_t outPtr;
	uint8_t buffer[BUFFERSIZE];
}USART_BUFFER_t;

typedef enum{
	USART_ENABLE = 0,
	USART_DISABLE
}USART_MODE_t;

typedef enum{
	USART_ON = 0,
	USART_OFF
}USART_BUSCLK;

typedef enum{
	NO_PARITY = 0,
	EVEN_PARITY,
	ODD_PARITY
}USART_PARITY;

typedef enum{
	LEN_8BIT = 0,
	LEN_9BIT
}USART_WORDLEN;

typedef enum{
    HALF_BIT        = 0,
    HALF_STOP       = 0,
    ONE_BIT         = 1,
    ONE_STOP        = 1,
    ONE_DOT_FIVE    = 2,
    TWO_BIT         = 3,
    TWO_STOP        = 3
}USART_STOPBITS;

typedef enum{
	OVER16 = 0,
	OVER8
}USART_OVER;

typedef enum
{
    RECEIVER_OFF = 0,
    RECEIVER_ON
} USART_RX;

typedef enum
{
    TRANSMITTER_OFF = 0,
    TRANSMITTER_ON
} USART_TX;

typedef enum
{
    OFF = 0,
    ON
} USART_IRQ_MODE;

typedef enum
{
    USART_IRQ_TXEIE = 0,
    USART_IRQ_CTSIE,
    USART_IRQ_TCIE,
    USART_IRQ_RXNEIE,
    USART_IRQ_IDLE,
    USART_IRQ_PEIE,
    USART_IRQ_LBDIE,
    USART_IRQ_EIE
} USART_IRQ_TYPES;

typedef enum
{
    USART_CTS_FLG,
    USART_LBD_FLG,
    USART_TC_FLG,
    USART_RXNE_FLG
} USART_IRQ_FLAG_t;

typedef enum{
	DMA_RECEIVE_OFF,
	DMA_RECEIVE_ON
}USART_DMA_RXMode;

typedef enum{
	DMA_TRANSMIT_OFF,
	DMA_TRANSMIT_ON
}USART_DMA_TXMode;

extern void USARTEnable(USART_TypeDef* USART);
extern void USARTDisable(USART_TypeDef* USART);
extern void USARTSetBaudrate(USART_TypeDef* usart, uint16_t brrVal);
extern void USARTRXOn(USART_TypeDef* usart, USART_RX on_off);
extern void USARTTXOn(USART_TypeDef* usart, USART_TX on_off);
extern void USARTIRQ(USART_TypeDef* usart, USART_IRQ_TYPES irq_type, bool enable_disable);
extern void USARTSendString(USART_TypeDef* usart, char* str);
extern void USARTSendChar(USART_TypeDef* usart, char character);
extern char USARTGetChar(USART_TypeDef *usart);
extern void USARTGetString(USART_TypeDef *usart, char *str, uint16_t leng);
extern void usartSetDmaTxMode(USART_TypeDef *usart, USART_DMA_TXMode dmaMode);
extern void usartSetDmaRxMode(USART_TypeDef *usart, USART_DMA_RXMode dmaMode);

#endif /* INC_SHALF1USART_H_ */
