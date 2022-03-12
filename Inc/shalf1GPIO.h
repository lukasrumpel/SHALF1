/*
 * shalf1GPIO.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1GPIO_H_
#define INC_SHALF1GPIO_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PIN_NUM;

typedef enum{
	ANALOG = 0,
	FLOATING,
	IN_PUPD
}INPUT_MODE;

typedef enum {
	GP_PP = 0, //Genral purpose push pull
	GP_OD, //general purpose opendrain
	AF_PP, //alternate function Push pull
	AF_OD//alternate function opendrain
}PIN_MODE;

typedef enum{
	INPUT = 0,
	OUT_10MHZ,
	OUT_2MHZ,
	OUT_50MHZ
}GPIO_MODE;

extern void gpioInitPort(GPIO_TypeDef *port);
extern void gpioSetupPin(GPIO_TypeDef *port, PIN_NUM pin, GPIO_MODE pinmode);
extern void gpioSetupInput(GPIO_TypeDef *port, PIN_NUM pin, INPUT_MODE mode);
extern void gpioSetupMode(GPIO_TypeDef *port, PIN_NUM pin, PIN_MODE mode);
extern void gpioSetPin(GPIO_TypeDef *port, PIN_NUM pin);
extern void gpioResetPin(GPIO_TypeDef *port, PIN_NUM pin);
extern void gpioSetPullupPulldown(GPIO_TypeDef *port, PIN_NUM pin, bool pullup);
extern bool gpioGetPinVal(GPIO_TypeDef *port, PIN_NUM pin);
extern uint16_t gpioGetPortVal(GPIO_TypeDef *port);
extern void gpioTogglePin(GPIO_TypeDef *port, PIN_NUM pin);
extern void afioInit();

#endif /* INC_SHALF1GPIO_H_ */
