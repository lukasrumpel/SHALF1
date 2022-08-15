/*
 * shalf1DMA.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1DMA.h>
#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>

uint32_t interruptBit = 0;
uint8_t shift = 0; //for Interruptclear

/*
  * Desc.: Initializes the DMA
  * @param: (DMA_TypeDef*) dma: DMA
  * @param: (DMA_Channel_TypeDef*) dmaChannel: channel
  * @param: (uint32_t) src: source for the DMA operation
  * @param: (uint32_t) dest: destination for DMA operation
  * @param: (uint16_t) dataLen: number of Bytes to be transmitted
  * @param: (DMA_DIR) direction: FROM_MEM = 0,
									FROM_PER = 1
  * @param: (DMA_CIRC) circularMode: DMA_CIRC_OFF = 0,
										DMA_CIRC_ON = 1
  * @param: (bool) increment: increment of Data (true -> on, false -> off)
  * @param: (DMA_MSIZE) memoryDataSize: MSIZE_8BIT = 0,
											MSIZE_16BIT = 1,
											MSIZE_32BIT = 2
  * @param: (DMA_PSIZE) peripheralDataSize: PSIZE_8BIT = 0,
												PSIZE_16BIT = 1,
												PSIZE_32BIT = 2
  * @param: (DMA_PRIO) priority: PRIO_LOW= 0,
									PRIO_MED = 1,
									PRIO_HIGH = 2,
									PRIO_VHIGH = 3
  * @param: (DMA_IRQ_TYPE) interrupt: DMA_TEI = 3, //->Transfer Error Interrupt
										DMA_HTI = 2, //->Half Transfer Interrupt
										DMA_TCI = 1 //->Transfer complete Interrupt
  * @return: (DMA_ERR_CODE) error code
  */
extern DMA_ERR_CODE dmaInit(DMA_TypeDef* dma, DMA_Channel_TypeDef* dmaChannel, uint32_t adrPer, uint32_t adrMem, uint16_t dataLen, DMA_DIR directionOfTransfer, DMA_CIRC circularMode, bool increment, DMA_MSIZE memoryDataSize, DMA_PSIZE peripheralDataSize, DMA_PRIO priority, DMA_IRQ_TYPE interrupt){

	if(dma == DMA1){
		RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	}
/*
	else if(dma == DMA2){
		RCC->AHBENR |= RCC_AHBENR_DMA2EN;
	}
*/
	else{
		return DMA_INVALID_DMA;
	}

	dmaChannel->CCR &= ~DMA_CCR_EN_Msk;
	while(dmaChannel->CCR & DMA_CCR_EN){}

	dmaChannel->CPAR = adrPer;
	dmaChannel->CMAR = adrMem;
	dmaChannel->CNDTR = dataLen;
	dmaChannel->CCR |= directionOfTransfer << DMA_CCR_DIR_Pos;
	dmaChannel->CCR |= circularMode << DMA_CCR_CIRC_Pos;

	if(directionOfTransfer == FROM_MEM){
		if(increment){
			dmaChannel->CCR |= DMA_CCR_MINC;
		}
		else{
			dmaChannel->CCR &= ~DMA_CCR_MINC_Msk;
		}
	}
	else if(directionOfTransfer == FROM_PER){
		if(increment){
			dmaChannel->CCR |= DMA_CCR_PINC;
		}
		else{
			dmaChannel->CCR &= ~DMA_CCR_PINC_Msk;
		}
	}
	else{
		return DMA_INVALID_DIR;
	}

	dmaChannel->CCR |= memoryDataSize << DMA_CCR_MSIZE_Pos;
	dmaChannel->CCR |= peripheralDataSize << DMA_CCR_PSIZE_Pos;

	dmaChannel->CCR |= priority << DMA_CCR_PL_Pos;

	dmaChannel->CCR |= 1 << interrupt;

	if(dmaChannel == DMA1_Channel1){
		NVIC_EnableIRQ(DMA1_Channel1_IRQn);
		shift = 0 + interrupt;
	}
	else if(dmaChannel == DMA1_Channel2){
		NVIC_EnableIRQ(DMA1_Channel2_IRQn);
		shift = 4 + interrupt;
	}
	else if(dmaChannel == DMA1_Channel3){
		NVIC_EnableIRQ(DMA1_Channel3_IRQn);
		shift = 8 + interrupt;
	}
	else if(dmaChannel == DMA1_Channel4){
		NVIC_EnableIRQ(DMA1_Channel4_IRQn);
		shift = 12 + interrupt;
	}
	else if(dmaChannel == DMA1_Channel5){
		NVIC_EnableIRQ(DMA1_Channel5_IRQn);
		shift = 16 + interrupt;
	}
	else if(dmaChannel == DMA1_Channel6){
		NVIC_EnableIRQ(DMA1_Channel6_IRQn);
		shift = 20 + interrupt;
	}
	else if(dmaChannel == DMA1_Channel7){
		NVIC_EnableIRQ(DMA1_Channel7_IRQn);
		shift = 24 + interrupt;
	}
	else{
		dmaChannel->CCR = 0;
		dmaChannel->CMAR = 0;
		dmaChannel->CPAR = 0;
		dmaChannel->CNDTR = 0;
		return DMA_INVALID_CHANNEL;
	}

	return DMA_OK;
}

/*
  * Desc.: starts the DMA Channel
  * @param: (DMA_Channel_TypeDef*)dmaChannel: Channel of DMA
  * @return: none
  */
extern void dmaStart(DMA_Channel_TypeDef* dmaChannel){
	dmaChannel->CCR |= DMA_CCR_EN;
}

/*
  * Desc.: stops the DMA Channel
  * @param: (DMA_Channel_TypeDef*)dmaChannel: Channel of DMA
  * @return: none
  */
extern void dmaStop(DMA_Channel_TypeDef* dmaChannel){
	dmaChannel->CCR &= ~DMA_CCR_EN_Msk;
	while(dmaChannel->CCR & DMA_CCR_EN){}
}

//IRQ Handlers
void DMA_Channel1_IRQHandler(void){
	if(DMA1->ISR & (1<<shift)){
		DMA1->IFCR |= (1<<shift);
	}
}

void DMA_Channel2_IRQHandler(void){
	if(DMA1->ISR & (1<<shift)){
		DMA1->IFCR |= (1<<shift);
	}
}

void DMA_Channel3_IRQHandler(void){
	if(DMA1->ISR & (1<<shift)){
		DMA1->IFCR |= (1<<shift);
	}
}

void DMA_Channel4_IRQHandler(void){
	if(DMA1->ISR & (1<<shift)){
		DMA1->IFCR |= (1<<shift);
	}
}

void DMA_Channel5_IRQHandler(void){
	if(DMA1->ISR & (1<<shift)){
		DMA1->IFCR |= (1<<shift);
	}
}

void DMA_Channel6_IRQHandler(void){
	if(DMA1->ISR & (1<<shift)){
		DMA1->IFCR |= (1<<shift);
	}
}

void DMA_Channel7_IRQHandler(void){
	if(DMA1->ISR & (1<<shift)){
		DMA1->IFCR |= (1<<shift);
	}
}
