/*
 * shalf1RCC.c
 *
 *  Created on: Sep 2, 2022
 *      Author: lukasrumpel
 */

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <shalf1RCC.h>

uint8_t pllmul = 0;

/*
  * Desc.: changes the clock settings for the SYSCLK and the peripheralbuses
  * @param: (CLKSrc)sourceOfClock: HSI = 0,
									HSE = 1
  * @param: (SystemClock) mainClock: SYSCLK_64 = 0,
										SYSCLK_32 = 1
  * @param: (APBClock) clockOfAPB1: APB_8MHZ = 0,
										APB_16MHZ = 1,
  * @param: (APBClock) clockOfAPB2: APB_8MHZ = 0,
										APB_16MHZ = 1,
  * @return: none
  */
extern void setClock(CLKSrc sourceOfClock, SystemClock mainClock, APBClock clockOfAPB1, APBClock clockOfAPB2){
	RCC->CR &= ~RCC_CR_PLLON_Msk;
	RCC->CFGR |= sourceOfClock << RCC_CFGR_PLLSRC_Pos;

	if(!sourceOfClock){
		setSysClockPLL(HSIFREQ, mainClock, clockOfAPB1, clockOfAPB2);
		SystemCoreClock = (HSIFREQ * 1000000 >> 1U) * pllmul;
	}
	else{
		RCC->CR &= ~RCC_CR_HSION_Msk;
		RCC->CR |= RCC_CR_HSEON;
		while(!(RCC->CR & RCC_CR_HSERDY )){}
		setSysClockPLL(HSEFREQ, mainClock, clockOfAPB1, clockOfAPB2);
		SystemCoreClock = (HSEFREQ * 1000000 >> 1U) * pllmul;
	}

}

/*
  * Desc.: changes the pll settings, corresponding to the desired clock
  * @param: (uint8_t)sourceOfClock: value of the clock reference in MHZ
  * @param: (SystemClock) mainClock: SYSCLK_64 = 0,
										SYSCLK_32 = 1
  * @param: (APBClock) clockOfAPB1: APB_8MHZ = 0,
										APB_16MHZ = 1,
  * @param: (APBClock) clockOfAPB2: APB_8MHZ = 0,
										APB_16MHZ = 1,
  * @return: none
  */
extern void setSysClockPLL(uint8_t refClock, SystemClock mainClock, APBClock clockOfAPB1, APBClock clockOfAPB2){

	switch(mainClock){
		case 0: //64MHZ SysClock
			if (refClock==8){
				RCC->CFGR |= RCC_CFGR_PLLMULL16;
				pllmul = 16;
			}
			else if (refClock == 16){
				RCC->CFGR |= RCC_CFGR_PLLMULL8;
				pllmul = 8;
			}
			else{
				RCC->CFGR |= RCC_CFGR_PLLMULL16;
				pllmul = 16;
			}
			switch(clockOfAPB1){
			case 0:
				RCC->CFGR |= RCC_CFGR_PPRE1_DIV8;
			break;
			case 1:
				RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
			break;
			default:
				RCC->CFGR |= RCC_CFGR_PPRE1_DIV8;
			break;
			}
			switch(clockOfAPB2){
			case 0:
				RCC->CFGR |= RCC_CFGR_PPRE2_DIV8;
			break;
			case 1:
				RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;
			break;
			default:
				RCC->CFGR |= RCC_CFGR_PPRE2_DIV8;
			break;
			}
			RCC->CR |= RCC_CR_PLLON;
		break;
		case 1: //32MHZ SysClock
			if (refClock == 8){
				RCC->CFGR |= RCC_CFGR_PLLMULL8;
				pllmul = 8;
			}
			else if(refClock == 4){
				RCC->CFGR |= RCC_CFGR_PLLMULL16;
				pllmul = 16;
			}
			else if(refClock == 16){
				RCC->CFGR |= RCC_CFGR_PLLMULL4;
				pllmul = 4;
			}
			else{
				RCC->CFGR |= RCC_CFGR_PLLMULL8;
				pllmul = 8;
			}
			switch(clockOfAPB1){
			case 0:
				RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
			break;
			case 1:
				RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
			break;
			default:
				RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
			break;
			}
			switch(clockOfAPB2){
			case 0:
				RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;
			break;
			case 1:
				RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
			break;
			default:
				RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;
			break;
			}
			RCC->CR |= RCC_CR_PLLON;
		break;
	}
	RCC->CFGR = RCC_CFGR_SW_PLL;

}
