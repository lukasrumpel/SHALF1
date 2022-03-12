/*
 * shalf1SysTick.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1SYSTICK_H_
#define INC_SHALF1SYSTICK_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <shalf1GPIO.h>

#define SYSTICK_10US 	(100000)
#define SYSTICK_100US 	(10000)
#define SYSTICK_1MS		(1000)
#define SYSTICK_10MS	(100)
#define SYSTICK_100MS	(10)
#define SYSTICK_1S		(1)

extern void systickInit(uint32_t timebase);
extern void systickSetTicks(uint32_t ticks);
extern bool isSysTickExpired();
extern void SysTick_Handler(void);
extern bool SysTickTicked(void);


#endif /* INC_SHALF1SYSTICK_H_ */
