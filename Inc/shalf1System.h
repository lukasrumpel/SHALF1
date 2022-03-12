/*
 * shalf1System.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1SYSTEM_H_
#define INC_SHALF1SYSTEM_H_

#include <stdint.h>
#include <shalf1System.h>
#include <stm32f1xx.h>
#include <system_stm32f1xx.h>
#include <system_stm32f1xx.c>
#include <shalf1GPIO.h>
#include <stdbool.h>

#define HSI_VALUE       ((uint32_t) 16000000u)
#define HSE_VALUE       ((uint32_t) 25000000u)

#define STM32F103C

extern uint32_t getSysClock(void);

#endif /* INC_SHALF1SYSTEM_H_ */
