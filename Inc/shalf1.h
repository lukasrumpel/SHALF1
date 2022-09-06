/*
 * shalf1.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1_H_
#define INC_SHALF1_H_

#include <shalf1DMA.h>
#include <shalf1EXTI.h>
#include <shalf1GPIO.h>
#include <shalf1I2C.h>
#include <shalf1RCC.h>
#include <shalf1SPI.h>
#include <shalf1SysTick.h>
#include <shalf1Timer.h>
#include <shalf1USART.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#if defined(__STM32F101x6_H) || defined(__STM32F102x6_H) || defined(__STM32F103x6_H)
	#define LOW_DENS
#elif defined(__STM32F100xB_H) || defined(__STM32F101xB_H) || defined(__STM32F102xB_H) || defined(__STM32F103xB_H)
	#define MED_DENS
#elif defined(__STM32F100xE_H) || defined(__STM32F101xE_H) || defined(__STM32F103xE_H) || defined(__STM32F105xC_H) || defined(__STM32F107xC_H)
	#define HIGH_DENS
#else
	#define XL_DENS
#endif

#define SHALF1SYSCLOCK 	SYSCLK_32
#define SHALF1APB1CLK	APB_8MHZ
#define SHALF1APB2CLK	APB_8MHZ
#define SHALF1CLKSRC	HSI

typedef enum{
	noError = 0,
	densityNotSupported = -1
}SHALF1_ErrCode;

extern SHALF1_ErrCode initSHALF1(void);
extern void initClock(void);

#endif /* INC_SHALF1_H_ */
