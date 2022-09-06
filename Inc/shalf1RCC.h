/*
 * shalf1RCC.h
 *
 *  Created on: Sep 2, 2022
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1RCC_H_
#define INC_SHALF1RCC_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>

#define HSEFREQ  8
#define HSIFREQ  8

typedef enum{
	APB_8MHZ = 0,
	APB_16MHZ = 1,
}APBClock;

typedef enum{
	HSI = 0,
	HSE = 1
}CLKSrc;

typedef enum{
	SYSCLK_64 = 0,
	SYSCLK_32 = 1
}SystemClock;

extern void setClock(CLKSrc sourceOfClock, SystemClock mainClock, APBClock clockOfAPB1, APBClock clockOfAPB2);
extern void setSysClockPLL(uint8_t refClock, SystemClock mainClock, APBClock clockOfAPB1, APBClock clockOfAPB2);

#endif /* INC_SHALF1RCC_H_ */
