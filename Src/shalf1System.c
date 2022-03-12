/*
 * shalf1System.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1System.h>
#include <stm32f1xx.h>
#include <system_stm32f1xx.h>
//#include <system_stm32f1xx.c>
#include <shalf1GPIO.h>
#include <stdbool.h>



 uint32_t getSysClock(void){
	uint32_t pllm = 0;
	uint32_t SysClock = 0;
	uint32_t CFGRSWSVal = RCC->CFGR & RCC_CFGR_SWS;
	switch(CFGRSWSVal){
		case RCC_CFGR_SWS_HSI:
			SysClock = HSI_VALUE;
			break;
		case RCC_CFGR_SWS_HSE:
			SysClock = HSE_VALUE;
		case RCC_CFGR_SWS_PLL:
			pllm = RCC->CFGR & RCC_CFGR_PLLMULL;
			SysClock = HSE_VALUE * pllm;
			break;
		default:
			SysClock = HSI_VALUE;
			break;
	}
	return SysClock;
}
