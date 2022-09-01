/*
 * shalf1DMA.h
 *
 *      Author: lukas
 */

#ifndef INC_SHALF1DMA_H_
#define INC_SHALF1DMA_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>

#define DMA_MAX_DATA_LEN 65536

typedef enum{
		DMA_OK                         =  0,
	    DMA_INVALID_DMA               = -1,
	    DMA_INVALID_STREAM             = -2,
	    DMA_INVALID_CHANNEL            = -3,
	    DMA_INVALID_DIR                = -4,
	    DMA_INVALID_DATA_LEN           = -5,
	    DMA_INVALID_DATA_FORMAT        = -6,
	    DMA_INVALID_SRC_DATA_FORMAT    = -7,
	    DMA_INVALID_DEST_DATA_FORMAT   = -8,
	    DMA_INVALID_IRQ_TYPE           = -9
}DMA_ERR_CODE;


typedef enum{
	FROM_PER = 0,
	FROM_MEM = 1
}DMA_DIR;

typedef enum{
	DMA_CIRC_OFF = 0,
	DMA_CIRC_ON = 1
}DMA_CIRC;

typedef enum{
	MSIZE_8BIT = 0,
	MSIZE_16BIT = 1,
	MSIZE_32BIT = 2
}DMA_MSIZE;

typedef enum{
	PSIZE_8BIT = 0,
	PSIZE_16BIT = 1,
	PSIZE_32BIT = 2
}DMA_PSIZE;

typedef enum{
	PRIO_LOW= 0,
	PRIO_MED = 1,
	PRIO_HIGH = 2,
	PRIO_VHIGH = 3
}DMA_PRIO;

typedef enum{
	DMA_TEI = 3, //->Transfer Error Interrupt
	DMA_HTI = 2, //->Half Transfer Interrupt
	DMA_TCI = 1 //->Transfer complete Interrupt
}DMA_IRQ_TYPE;

extern DMA_ERR_CODE dmaInit(DMA_TypeDef* dma, DMA_Channel_TypeDef* dmaChannel, uint32_t adrPer, uint32_t adrMem, uint16_t dataLen, DMA_DIR directionOfTransfer, DMA_CIRC circularMode, bool increment, DMA_MSIZE memoryDataSize, DMA_PSIZE peripheralDataSize, DMA_PRIO priority, DMA_IRQ_TYPE interrupt);
extern void dmaStart(DMA_Channel_TypeDef* dmaChannel);
extern void dmaStop(DMA_Channel_TypeDef* dmaChannel);

#endif /* INC_SHALF1DMA_H_ */
