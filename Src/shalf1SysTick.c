/*
 * shalf1SysTick.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1SysTick.h>
#include <shalf1GPIO.h>
#include <stdbool.h>
#include <stm32f1xx.h>
#include <stm32f1xx.h>
#include <system_stm32f1xx.h>
//#include <system_stm32f1xx.c>
#include <stdint.h>
#include <stdbool.h>

bool timerTrigger = false;
uint32_t tick = 0;

 /*
  * Desc.: sets period of SysTick
  * @param: (uint32_t)divider: 1ms / divider = time of period
  * @return: keine
  */
extern void systickInit(uint32_t timebase){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / timebase);
}

/*
 * Desc.: sets the intervall, depending on Time Base
 * @param: number of Ticks
 * @return: none
 */
extern void systickSetTicks(uint32_t ticks){
	tick = ticks;
}

/*
 * Desc.: checks if SysTick is expired
 * @param: timer
 * @return (bool) expired -> true
 */
extern bool isSysTickExpired(){
	bool timerState = false;

	if(tick == 0){
		timerState = true;
	}

	return timerState;
}

/*
 * Desc.: SysTick ISR Handler
 * @param: none
 * @return: none
 */
extern void SysTick_Handler(void){
	--tick;
}




