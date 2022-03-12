/*
 * shalf1Timer.h
 *
 *      Author: lukasrumpel
 *
 */

#ifndef INC_SHALF1TIMER_H_
#define INC_SHALF1TIMER_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <shalf1GPIO.h>


typedef enum{
	BASIC_TIM = 0,
	GP_TIM,
	AGB_TIM,
	ADV_TIM
}TIMER_FAMILY;

typedef enum{
	DIV_BY_1 = 0,
	DIV_BY_2,
	DIV_BY_4
}CLK_DIV;

typedef enum{
	ARPE_BUFF_ON = 0,
	ARPE_BUFF_OFF
}ARPE_BUF;

typedef enum{
	PWM_EDGE = 0,
	PWM_CENTER1,
	PWM_CENTER2,
	PWM_CENTER3
}PWM_MODE;

typedef enum{
	CNT_UP = 0,
	CNT_DOWN
}DIR;

typedef enum{
	ONE_PULSE_MODE_OFF = 0,
	ONE_PULSE_MODE_ON
}OPM_MODE;

typedef enum{
	UPDATE_ALL_SOURCES = 0,
	UPDATE_OVERFLOW_UNDERFLOW
}URS;

typedef enum{
	UPDATE_ENABLE = 0,
	UPDATE_DISABLE
}UDIS;

typedef enum{
	TIM_START = 0,
	TIM_STOP
}START_TIM;

typedef enum{
	CHN_FROZEN = 0,
	CHN_ACTIVE,
	CHN_INACTIVE,
	CHN_TOOGLE,
	CHN_FORCE_LOW,
	CHN_FORCE_HIGH,
	CHN_PWN_MODE_1,
	CHN_PWN_MODE_2
}CAPCOMP_MODE;

typedef enum{
	TIMIO_CH1 = 1,
	TIMIO_CH2,
	TIMIO_CH3,
	TIMIO_CH4
}CHANNEL_NUM;

typedef enum{
	TIMIO_OUTPUT = 0,
	TIMIO_INPUT
}CHANNEL_TYPE;

typedef enum{
	UP = true,
	DOWN = false
}COUNT_DIR;

typedef enum{
	COMPL_OFF = 0,
	COMPL_ON
}COMPLEMENT_MODE;

typedef enum{
	CHN_ENABLE         = 1,
	CHN_POLARITY       = 2,
	CHN_COMPL_ENABLE   = 4,
	CHN_COMPL_POLARITY = 8
}CAPCOMP_TYPE;

typedef enum
{
    MOE_OFF = 0,
    MOE_ON
} BDTR_MOE;

typedef enum
{
    AOE_SW_ONLY = 0,
    AOE_SW_AND_EVENT
} BDTR_AOE;

typedef enum
{
    BKP_ACT_HIGH = 0,
    BKP_ACT_LOW
} BDTR_BKP_POLARITY;

typedef enum
{
    BRK_ENABLE = 0,
    BRK_DISABLE
} BDTR_BKE;

extern void timerBusClkOn(TIM_TypeDef* timer);
extern void timerBusClkOff(TIM_TypeDef* timer);
extern void timerSetPrescaler(TIM_TypeDef* timer, uint16_t presc);
extern void timerSetAutoReloadValue(TIM_TypeDef* timer, uint16_t arrv);
extern void timerEnableInterrupt(TIM_TypeDef* timer);
extern void timerSetOnePulseMode(TIM_TypeDef* timer, OPM_MODE opmmode);
extern void timerStart(TIM_TypeDef* timer);
extern void timerStop(TIM_TypeDef* timer);
extern void timerSetPreloadValue(TIM_TypeDef* timer, uint16_t preloadValue, CHANNEL_NUM channel);
extern uint16_t timerGetPreloadValue(TIM_TypeDef* timer, CHANNEL_NUM channel);
extern void timerResetCounter(TIM_TypeDef* timer);
extern void timerSetCapCompMode(TIM_TypeDef* timer, CHANNEL_NUM channel, CHANNEL_TYPE type, CAPCOMP_MODE mode);
extern void timerSelectCapCompOutputType(TIM_TypeDef* timer, CHANNEL_NUM channel, CAPCOMP_TYPE type);
extern void timerSetRepetitionCounter(TIM_TypeDef* timer,  uint16_t repetitions);


#endif /* INC_SHALF1TIMER_H_ */
