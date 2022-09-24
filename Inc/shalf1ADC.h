/*
 * shalf1ADC.h
 *
 *  Created on: 06.09.2022
 *      Author: lukas
 */

#ifndef INC_SHALF1ADC_H_
#define INC_SHALF1ADC_H_

#include <shalf1.h>
#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum{
	TIM1_CC1 = 0,
	TIM1_CC2 = 1,
	TIM1_CC3 = 2,
	TIM2_CC2 = 3,
	TIM3_TRGO = 4,
	TIM4_CC4 = 5,
	EXTI_11 = 6,
	SWSTART = 7
}TRIG_SRC;

typedef enum{
	NO_CHN = -1,
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
}ADC_CHN;

typedef enum{
	DATA_RIGHT = 0,
	DATA_LEFT = 1
}DATA_ALIGNMENT;

typedef enum{
	CYCLES_1_5 = 0,
	CYCLES_7_5 = 1,
	CYCLES_13_5 = 2,
	CYCLES_28_5 = 3,
	CYCLES_41_5 = 4,
	CYCLES_55_5 = 5,
	CYCLES_71_5 = 6,
	CYCLES_239_5 = 7
}ADC_CYCLES;

typedef enum{
	OK = 0,
	channelNotInRange_Err = -1,
	numberOfConversionsNotInRange_Err = -2,
	triggerSource_Err = -3,
	noDMAavailableForADC_Err = -4,
	invalidAlignment = -5
}ADC_ERR_CODES;


extern void initADC(ADC_TypeDef* adc);
extern ADC_ERR_CODES adcSetupSequence(ADC_TypeDef* adc, ADC_CHN channel, uint8_t numberInSequence);
extern ADC_ERR_CODES adcSetSequenceLength(ADC_TypeDef* adc, uint8_t numberOfConversions);
extern void adcSetTrigger(ADC_TypeDef* adc, TRIG_SRC source);
extern uint16_t adcRead(ADC_TypeDef* adc, ADC_CHN channel);
extern ADC_ERR_CODES adcInitDMA(ADC_TypeDef* adc, uint32_t adrPer, uint32_t adrMem, uint16_t dataLen);
extern void adcDMAReload();
extern void adcCalibrate(ADC_TypeDef* adc);
extern ADC_ERR_CODES adcDataAlignment(ADC_TypeDef* adc, DATA_ALIGNMENT alignment);
extern ADC_ERR_CODES adcSetCyclesOfConversion(ADC_TypeDef* adc, ADC_CYCLES numberOfCycles, ADC_CHN channel);


#endif /* INC_SHALF1ADC_H_ */
