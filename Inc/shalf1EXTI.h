/*
 * shalf1EXTI.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1EXTI_H_
#define INC_SHALF1EXTI_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <shalf1GPIO.h>

typedef enum{
	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G
}PORT;

typedef enum{
	EXTI_P0 = 0,
	EXTI_P1,
	EXTI_P2,
	EXTI_P3,
	EXTI_P4,
	EXTI_P5,
	EXTI_P6,
	EXTI_P7,
	EXTI_P8,
	EXTI_P9,
	EXTI_P10,
	EXTI_P11,
	EXTI_P12,
	EXTI_P13,
	EXTI_P14,
	EXTI_P15,
	EXTI_PVDOUT,
	EXTI_RTCALARM,
	EXTI_USBWAKEUP,
	EXTI_ETHERNETWAKEUP,
}irq_NUM;

extern void extiConfigureEXTI(PORT port, PIN_NUM pin);
extern void extiEnableIrq(irq_NUM irq);
extern void extiDisableIrq(irq_NUM irq);
extern void extiSetTriggerEdge(bool rising, irq_NUM irq);


#endif /* INC_SHALF1EXTI_H_ */
