/*
 * shalf1ADC.c
 *
 *      Author: lukas
 */

#include <shalf1ADC.h>
#include <shalf1.h>

bool dmaModeFlag = false;
uint16_t numberOfChannels = 0;
uint32_t adrMemBuff = 0;
uint32_t adrPerBuff = 0;

/*
  * Desc.: Initializes the desired ADC
  * @param: (ADC_TypeDef*) adc: ADC to activate
  * @return: none
  */
extern void initADC(ADC_TypeDef* adc){
	if(adc == ADC1){
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}
	else if(adc == ADC2){
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
	else{

	}
	adcCalibrate(adc);
}

/*
  * Desc.: Sets up the measurement sequence of the ADC, determines which channel comes at which position in sequence.
  * @param: (ADC_TypeDef*) adc: ADC
  * @param: (ADC_CHN) channel: NO_CHN = -1,
								ADC_CH0 = 0,
								ADC_CH1 = 1,
								ADC_CH2 = 2,
								ADC_CH3 = 3,
								ADC_CH4 = 4,
								ADC_CH5 = 5,
								ADC_CH6 = 6,
								ADC_CH7 = 7,
								ADC_CH8 = 8,
								ADC_CH9 = 9,
								ADC_CH10 = 10,
								ADC_CH11 = 11,
								ADC_CH12 = 12,
								ADC_CH13 = 13,
								ADC_CH14 = 14,
								ADC_CH15 = 15,
								ADC_CH16 = 16,
								ADC_CH17 = 17
  * @param: (uint8_t) numberinSequence: position in sequence of the channel
  * @return: (ADC_ERR_CODES) error code, e.g. channel not in range
  */
extern ADC_ERR_CODES adcSetupSequence(ADC_TypeDef* adc, ADC_CHN channel, uint8_t numberInSequence){
	adc->SQR3 = 0;
	adc->SQR2 = 0;
	adc->SQR1 = 0;
	if(numberInSequence <= 6 && numberInSequence >= 1){
		adc->SQR3 |= channel << (numberInSequence-1)*5;
		return OK;
	}
	else if (numberInSequence <= 12 && numberInSequence >= 7){
		adc->SQR2 |= channel << ((numberInSequence-6)-1)*5;
		return OK;
	}
	else if(numberInSequence <= 16 && numberInSequence >= 13){
		adc->SQR1 |= channel << ((numberInSequence-12)-1)*5;
		return OK;
	}
	else{
		return channelNotInRange_Err;
	}
}

/*
  * Desc.: Determines how many conversions shoulb be done per sequence.
  * @param: (ADC_TypeDef*) adc: ADC
  * @param: (uint8_t) numberOfConversions: how many conversions in sequence?
  * @return: (ADC_ERR_CODES) too many/few conversions
  */
extern ADC_ERR_CODES adcSetSequenceLength(ADC_TypeDef* adc, uint8_t numberOfConversions){
	adc->SQR1 &= ~ADC_SQR1_L_Msk;
	if(numberOfConversions >= 0 && numberOfConversions <= 16){
		adc->SQR1 |= numberOfConversions << ADC_SQR1_L_Pos;
		return OK;
	}
	else{
		return numberOfConversionsNotInRange_Err;
	}
}

/*
  * Desc.: This method configures the source for the start of a conversion sequence.
  * @param: (ADC_TypeDef*) adc: ADC
  * @param: (TRIG_SRC) source: TIM1_CC1 = 0,
								TIM1_CC2 = 1,
								TIM1_CC3 = 2,
								TIM2_CC2 = 3,
								TIM3_TRGO = 4,
								TIM4_CC4 = 5,
								EXTI_11 = 6,
								SWSTART = 7
  * @return: none
  */
extern void adcSetTrigger(ADC_TypeDef* adc, TRIG_SRC source){
	 adc->CR2 |= source << ADC_CR2_EXTSEL_Pos;
	 ADC1->CR2 |= ADC_CR2_ADON;
}

/*
  * Desc.: Starts the conversion by software. If the DMA Mode is disabled, this function reads a single channel (corresponding to the given parameter 'channel'). However, if DMA Mode is enabled 'NO_CHN' should be given. The ADC converts the sequence and the DMA writes the values in the defined array.
  * @param: (ADC_TypeDef*) adc: ADC
  * @param: (ADC_CHN) channel: NO_CHN = -1,
								ADC_CH0 = 0,
								ADC_CH1 = 1,
								ADC_CH2 = 2,
								ADC_CH3 = 3,
								ADC_CH4 = 4,
								ADC_CH5 = 5,
								ADC_CH6 = 6,
								ADC_CH7 = 7,
								ADC_CH8 = 8,
								ADC_CH9 = 9,
								ADC_CH10 = 10,
								ADC_CH11 = 11,
								ADC_CH12 = 12,
								ADC_CH13 = 13,
								ADC_CH14 = 14,
								ADC_CH15 = 15,
								ADC_CH16 = 16,
								ADC_CH17 = 17
  * @param: (uint8_t) numberinSequence: position in sequence of the channel
  * @return: (ADC_ERR_CODES) error code, e.g. channel not in range
  */
extern uint16_t adcRead(ADC_TypeDef* adc, ADC_CHN channel){
	if (channel >= -1 && channel <= 17){
		if(!dmaModeFlag){
			if (channel > -1){
				adcSetupSequence(adc, channel, 1);
				adcSetSequenceLength(adc, 0);
			}
			else{
				return channelNotInRange_Err;
			}
		}

		adc->CR2 |= ADC_CR2_ADON;
		adc->SR = 0;
		adc->CR2 |= ADC_CR2_SWSTART;

		while(!(adc->SR & ADC_SR_EOC)){}
		if (!dmaModeFlag){
			if (channel > -1){
				return adc->DR;
			}
			else{
				return channelNotInRange_Err;
			}
		}
		else{
			dmaStop(DMA1_Channel1);
			return 0;
		}
	}
	else{
		return channelNotInRange_Err;
	}
}

/*
  * Desc.: Configuration function for the DMA Mode. Reads from the peripheral an writes to a memory address. Shoulb be called just for initialization/ first sequence.
  * @param: (ADC_TypeDef*) adc: ADC
  * @param: (uint32_t) adrPer: adress of the Dataregister of the ADC
  * @param: (uint32_t) adrMem: adress of the destination in memory
  * @param: (uint16_t) dataLen: number of elemts to be written
  * @return: (ADC_ERR_CODES) code of error
  */
extern ADC_ERR_CODES adcInitDMA(ADC_TypeDef* adc, uint32_t adrPer, uint32_t adrMem, uint16_t dataLen){
	adc->CR2 |= ADC_CR2_DMA;
	if (adc==ADC1){
		dmaInit(DMA1, DMA1_Channel1, adrPer, adrMem, dataLen+1, FROM_PER, DMA_CIRC_OFF, 1, 0, MSIZE_16BIT, MSIZE_16BIT, PRIO_HIGH , DMA_TCI );
		dmaStart(DMA1_Channel1);
		dmaModeFlag = true;
		numberOfChannels = dataLen+1;
		adrMemBuff = adrMem;
		adrPerBuff = adrPer;
		return OK;
	}
#if defined(HIGH_DENS) || defined(XL_DENS)
	else if(adc == ADC3){
		dmaInit(DMA2, DMA1_Channel5, adrPer, adrMem, dataLen, FROM_PER, DMA_CIRC_OFF, true, false, MSIZE_32BIT, MSIZE_32BIT, PRIO_VHIGH , DMA_TCI );
		dmaStart(DMA2_Channel5);
		dmaModeFlag = true;
		return OK;
	}
#endif
	else{
		return noDMAavailableForADC_Err;
	}
}

/*
  * Desc.: Before every following sequence this function should be called to reset the parameters of the DMA.
  * @param: none
  * @return: none
  */
extern void adcDMAReload(){
	if(dmaModeFlag){
		dmaInit(DMA1, DMA1_Channel1, adrPerBuff, adrMemBuff, numberOfChannels, FROM_PER, DMA_CIRC_OFF, 1, 0, MSIZE_16BIT, MSIZE_16BIT, PRIO_HIGH , DMA_TCI );
		dmaStart(DMA1_Channel1);
	}
}

/*
  * Desc.: Calibrates the ADC for increased accuracy.
  * @param: (ADC_TypeDef*) adc: ADC
  * @return: none
  */
extern void adcCalibrate(ADC_TypeDef* adc){
	adc->CR2 |= ADC_CR2_CAL;
	while(!(adc->CR2 & ADC_CR2_CAL)){}
}

/*
  * Desc.: Configures the data alignment of the Data Register (default right aligned)
  * @param: (ADC_TypeDef*) adc: ADC
  * @param: (DATA_ALIGNMENT) alignment: alignment of Data Register
  * @return: (ADC_ERR_CODES) code of error, e.g. invalid alignment
  */
extern ADC_ERR_CODES adcDataAlignment(ADC_TypeDef* adc, DATA_ALIGNMENT alignment){
	if (alignment == DATA_RIGHT || alignment == DATA_LEFT){
		adc->CR2 |= alignment << ADC_CR2_ALIGN_Pos;
		return OK;
	}
	else{
		return invalidAlignment;
	}
}

/*
  * Desc.: Function for configuring the number of cycles per conversion. 
  * @param: (ADC_TypeDef*) adc: ADC
  * @param: (ADC_CYCLES) numberOfCycles: CYCLES_1_5 = 0,
											CYCLES_7_5 = 1,
											CYCLES_13_5 = 2,
											CYCLES_28_5 = 3,
											CYCLES_41_5 = 4,
											CYCLES_55_5 = 5,
											CYCLES_71_5 = 6,
											CYCLES_239_5 = 7
  * @param: (ADC_CHN) channel: NO_CHN = -1,
								ADC_CH0 = 0,
								ADC_CH1 = 1,
								ADC_CH2 = 2,
								ADC_CH3 = 3,
								ADC_CH4 = 4,
								ADC_CH5 = 5,
								ADC_CH6 = 6,
								ADC_CH7 = 7,
								ADC_CH8 = 8,
								ADC_CH9 = 9,
								ADC_CH10 = 10,
								ADC_CH11 = 11,
								ADC_CH12 = 12,
								ADC_CH13 = 13,
								ADC_CH14 = 14,
								ADC_CH15 = 15,
								ADC_CH16 = 16,
								ADC_CH17 = 17						
  * @return: (ADC_ERR_CODES) code of error, e.g. channel not in range
  */
extern ADC_ERR_CODES adcSetCyclesOfConversion(ADC_TypeDef* adc, ADC_CYCLES numberOfCycles, ADC_CHN channel){
	if ((channel >= 0) && (channel <= 9)){
		adc->SMPR2 |= numberOfCycles << (channel*3);
		return OK;
	}
	else if((channel >= 10) && (channel <= 17)){
		adc->SMPR1 |= numberOfCycles << ((channel-10)*3);
		return OK;
	}
	else{
		return channelNotInRange_Err;
	}
}
