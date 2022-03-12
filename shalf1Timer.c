/*
 * shalf1timer.c
 *
 *  Created on: 27.11.2021
 *      Author: lukas
 */
#include <stm32f1xx.h>
#include <system_stm32f1xx.h>
#include <system_stm32f1xx.c>
#include <shalf1Timer.h>
#include <shalf1GPIO.h>
#include <stdbool.h>


 /*
  * Desc.: activates Clock for Timer
  * @param: (TIM_TypeDef*)timer: Timer which should be activated
  * @return: none
  */
extern void timerBusClkOn(TIM_TypeDef* timer){
	 if (TIM1 == timer)
	    {
	        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	    }
	    else if (TIM2 == timer)
	    {
	        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	    }
	    else if (TIM3 == timer)
	    {
	        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	    }
	    else if (TIM4 == timer)
	    {
	        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	    }
	    else
	    {
	        while(1)
	        {
	            // Timer not supported
	        }
	    }

	    timer->CR1 = 0;  // Reset all bits of TIMx_CR1 to 0
}

/*
  * Desc.: deactivates Clock for Timer
  * @param: (TIM_TypeDef*)timer: Timer which should be deactivated
  * @return: none
  */
extern void timerBusClkOff(TIM_TypeDef* timer){
	 if (TIM1 == timer)
		    {
		        RCC->APB2RSTR |= RCC_APB2ENR_TIM1EN;
		    }
		    else if (TIM2 == timer)
		    {
		        RCC->APB1RSTR |= RCC_APB1ENR_TIM2EN;
		    }
		    else if (TIM3 == timer)
		    {
		        RCC->APB1RSTR |= RCC_APB1ENR_TIM3EN;
		    }
		    else if (TIM4 == timer)
		    {
		        RCC->APB1RSTR |= RCC_APB1ENR_TIM4EN;
		    }
		    else
		    {
		        while(1)
		        {
		            // Timer not supported
		        }
		    }
}

/*
  * Desc.: sets Prescaler for Timer
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (uint16_t) presc: Prescaler Value
  * @return: none
  */
extern void timerSetPrescaler(TIM_TypeDef* timer, uint16_t presc){
	timer->PSC = presc;
}

/*
  * Desc.: sets AutoreloadValue for Timer
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (uint16_t) arrv: Autoreloadvalue
  * @return: none
  */
extern void timerSetAutoReloadValue(TIM_TypeDef* timer, uint16_t arrv){
	timer->ARR = arrv;
}

/*
  * Desc.: enables Interrupt
  * @param: (TIM_TypeDef*)timer: Timer
  * @return: none
  */
extern void timerEnableInterrupt(TIM_TypeDef* timer){
	timer->DIER |= TIM_DIER_UIE;
}

/*
  * Desc.: sets the Timer in One-Pulse-Mode
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (OPM_MODE) opmmode: ONE_PULSE_MODE_OFF
								ONE_PULSE_MODE_ON
  * @return: none
  */
extern void timerSetOnePulseMode(TIM_TypeDef* timer, OPM_MODE opmmode){
	if(opmmode == 1){
		timer->CR1 |= TIM_CR1_OPM ;
	}
	else{
		timer->CR1 &= ~ TIM_CR1_OPM_Msk;
	}
}

/*
  * Desc.: starts Timer
  * @param: (TIM_TypeDef*)timer: Timer
  * @return: none
  */
extern void timerStart(TIM_TypeDef* timer){
	timer->CR1 |= TIM_CR1_CEN;
}

/*
  * Desc.: stops Timer
  * @param: (TIM_TypeDef*)timer: Timer
  * @return: none
  */
extern void timerStop(TIM_TypeDef* timer){
	timer->CR1 |= TIM_CR1_CEN_Msk;
}

/*
  * Desc.: sets the PreloadValue of the Timers Channel
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (uint16_t) preloadValue
  * @param: (CHANNEL_NUM) channel: TIMIO_CH1,
									TIMIO_CH2,
									TIMIO_CH3,
									TIMIO_CH4
  * @return: none
  */
extern void timerSetPreloadValue(TIM_TypeDef* timer, uint16_t preloadValue, CHANNEL_NUM channel){
	switch(channel){
	case 1:
		timer->CCR1 = preloadValue;
		break;
	case 2:
		timer->CCR2 = preloadValue;
		break;
	case 3:
		timer->CCR3 = preloadValue;
		break;
	case 4:
		timer->CCR4 = preloadValue;
		break;
	default:
		break;
	}
}

/*
  * Desc.: returns the PreloadValue of a Timer
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (CHANNEL_NUM) channel: TIMIO_CH1,
									TIMIO_CH2,
									TIMIO_CH3,
									TIMIO_CH4
  * @return: (uint16_t) preloadValue
  */
extern uint16_t timerGetPreloadValue(TIM_TypeDef* timer, CHANNEL_NUM channel){
	switch(channel){
	case 1:
		return timer->CCR1;
		break;
	case 2:
		return timer->CCR2;
		break;
	case 3:
		return timer->CCR3;
		break;
	case 4:
		return timer->CCR4;
		break;
	default:
		break;
	}
	return 0;
}

/*
  * Desc.: resets Counter
  * @param: (TIM_TypeDef*)timer: Timer
  * @return: none
  */
extern void timerResetCounter(TIM_TypeDef* timer){
	timer->CNT = 0;
}

/*
  * Desc.: configures CamComp Channel of a Timer
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (CHANNEL_NUM) channel: TIMIO_CH1,
									TIMIO_CH2,
									TIMIO_CH3,
									TIMIO_CH4
  * @param: (CHANNEL_TYPE) type: TIMIO_OUTPUT,
									TIMIO_INPUT
  * @param: (CAPCOMP_MODE) mode: CHN_FROZEN,
									CHN_ACTIVE,
									CHN_INACTIVE,
									CHN_TOOGLE,
									CHN_FORCE_LOW,
									CHN_FORCE_HIGH,
									CHN_PWN_MODE_1,
									CHN_PWN_MODE_2
  *
  * @return: none
  */
extern void timerSetCapCompMode(TIM_TypeDef* timer, CHANNEL_NUM channel, CHANNEL_TYPE type, CAPCOMP_MODE mode){
	switch(channel){
	case 1:
		timer->CCMR1 &= ~(TIM_CCMR1_CC1S_Msk | TIM_CCMR1_OC1CE_Msk | TIM_CCMR1_OC1M_Msk) ;
		timer->CCMR1 |= mode << 4;
		timer->CCER |= TIM_CCER_CC1E;
		break;
	case 2:
		timer->CCMR1 &= ~(TIM_CCMR1_CC2S_Msk | TIM_CCMR1_OC2CE_Msk | TIM_CCMR1_OC2M_Msk) ;
		timer->CCMR1 |= mode << 12;
		timer->CCER |= TIM_CCER_CC2E;
		break;
	case 3:
		timer->CCMR2 &= ~(TIM_CCMR2_CC3S_Msk | TIM_CCMR2_OC3CE_Msk | TIM_CCMR2_OC3M_Msk) ;
		timer->CCMR2 |= mode << 4;
		timer->CCER |= TIM_CCER_CC3E;
		break;
	case 4:
		timer->CCMR2 &= ~(TIM_CCMR2_CC4S_Msk | TIM_CCMR2_OC4CE_Msk | TIM_CCMR2_OC4M_Msk) ;
		timer->CCMR2 |= mode << 12;
		timer->CCER |= TIM_CCER_CC4E;
		break;
	default:
		break;
	}
}

/*
  * Desc.: configures CapComp Output Type
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (CHANNEL_NUM) channel: TIMIO_CH1,
									TIMIO_CH2,
									TIMIO_CH3,
									TIMIO_CH4
  * @param: (CAPCOMP_TYPE) type: CHN_ENABLE,
									CHN_POLARITY,
									CHN_COMPL_ENABLE,
									CHN_COMPL_POLARITY
  * @return: none
  */
extern void timerSelectCapCompOutputType(TIM_TypeDef* timer, CHANNEL_NUM channel, CAPCOMP_TYPE type){
	switch(channel){
	case 1:
		timer->CCER |= type;
		break;
	case 2:
		timer->CCER |= type << 4;
		break;
	case 3:
		timer->CCER |= type << 8;
		break;
	case 4:
		timer->CCER |= type << 12;
		break;
	default:
		break;
	}
}

/*
  * Desc.: sets repetition counter Value
  * @param: (TIM_TypeDef*)timer: Timer
  * @param: (uint16_t) repetitions
  * @return: none
  */
extern void timerSetRepetitionCounter(TIM_TypeDef* timer,  uint16_t repetitions){
	if((timer == TIM1) /*|| (timer == TIM8)*/){ //uncomment for Highdensity und XL Desity
		timer->RCR = repetitions;
	}
	else{
		return;
	}
}

