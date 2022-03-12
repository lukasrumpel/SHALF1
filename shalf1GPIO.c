/*
 * shalf1GPIO.c
 *
 *  Created on: 31.08.2021
 *      Author: lukas
 */

#include <shalf1GPIO.h>

/*
  * Desc.: enables the Clock for the corresponding GPIO Port
  * @param: (GPIO_TypeDef*) port: Port which should be supplied with Clock
  * @return: none
  */
extern void gpioInitPort(GPIO_TypeDef *port){
		if (port == GPIOA){
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		}
		else if(port == GPIOB){
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		}
		else if(port == GPIOC){
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		}
		else if(port == GPIOD){
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
		}
		else if(port == GPIOE){
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
		}
}

/*
  * Desc.: sets the PIN as Input or Output (10MHz/2MHz/50MHz)
  * @param: (GPIO_TypeDef*) port: GPIO Port of the Pin
  * @param: (GPIO_MODE) pinmode: INPUT = 0,
									OUT_10MHZ,
									OUT_2MHZ,
									OUT_50MHZ
  * @return: none
  */
extern void gpioSetupPin(GPIO_TypeDef *port, PIN_NUM pin, GPIO_MODE pinmode){
	if(pin < 8){
		port -> CRL &= ~(0b1111 << (pin*4));
		port ->CRL |= (pinmode << (pin*4));
	}
	else{
		port->CRH &= ~(0b1111 << ((pin-8)*4));
		port->CRH |= (pinmode << ((pin-8)*4));
	}
}

/*
  * Desc.: sets the Mode for the INPUT Pin
  * @param: (GPIO_TypeDef*) port: Port
  * @param: (PIN_NUM) pin: PIN
  * @param: (INPUT_MODE) mode: ANALOG = 0,
								FLOATING,
								IN_PUPD
  * @return: none
  */
extern void gpioSetupInput(GPIO_TypeDef *port, PIN_NUM pin, INPUT_MODE mode){
	if(pin < 8){
			port ->CRL |= (mode << ((pin*4)+2));
		}
		else{
			port->CRH |= (mode << (((pin-8)*4)+2));
		}
}

/*
  * Desc.: sets the Operating Mode of the PIN
  * @param: (GPIO_TypeDef*) port: Port
  * @param: (PIN_NUM) pin: Pin
  * @param: (PIN_MODE) mode: Operating Mode of the Pin
  	  	  	  	  	  	  	  	GP_PP, -> Genral purpose push pull
								GP_OD, -> general purpose opendrain
								AF_PP, -> alternate function Push pull
								AF_OD  -> alternate function opendrain
  * @return: none
  */
extern void gpioSetupMode(GPIO_TypeDef *port, PIN_NUM pin, PIN_MODE mode){
	if(pin < 8){
			port ->CRL |= (mode << ((pin*4)+2));
		}
		else{
			port->CRH |= (mode << (((pin-8)*4)+2));
		}
}

/*
  * Desc.: sets the corresponding Bit in the ODR Register, via BSRR (atomic)
  * @param: (GPIO_TypeDef*) port: Port
  * @param: (PIN_NUM) pin: Pin
  * @return: none
  */
extern void gpioSetPin(GPIO_TypeDef *port, PIN_NUM pin){
	port->BSRR |= 1 << pin;
}

/*
  * Desc.: resets the corresponding Bit in the ODR Register, via BSRR (atomic)
  * @param: (GPIO_TypeDef*) port: Port
  * @param: (PIN_NUM) pin: Pin
  * @return: none
  */
extern void gpioResetPin(GPIO_TypeDef *port, PIN_NUM pin){
	port->BSRR |= (1<<(pin+16));
}

/*
  * Desc.: sets the internal Pullup-/Pulldown Resistors for the corresponding Pins
  * @param: (GPIO_TypeDef*) port: Port
  * @param: (PIN_NUM) pin: Pin
  * @param: (bool)pullup: true -> activate Pullup; false -> activate Pulldown
  * @return: none
  */
extern void gpioSetPullupPulldown(GPIO_TypeDef *port, PIN_NUM pin, bool pullup){
	if((pullup == true)){
		port -> ODR |=  (1<< pin);
	}
	else{
		port->ODR &= ~(1<<pin);
	}
}

/*
  * Desc.: returns the current value of a Pin stored in the IDR Register
  * @param: (GPIO_TypeDef*) port: Port
  * @param: (PIN_NUM) pin: Pin
  * @return: (bool) state of Pin
  */
extern bool gpioGetPinVal(GPIO_TypeDef *port, PIN_NUM pin){
	return (port->IDR & (1<<pin));
}

/*
  * Desc.: returns Value of a whole Port
  * @param: (GPIO_TypeDef*) port: Port
  * @return: (uint16_t) state of Port
  */
extern uint16_t gpioGetPortVal(GPIO_TypeDef *port){
	return port->IDR;
}

/*
  * Desc.: Toogles Pin
  * @param: (GPIO_TypeDef*) port: Port
  * @param: (PIN_NUM) pin: Pin
  * @return: none
  */
extern void gpioTogglePin(GPIO_TypeDef *port, PIN_NUM pin){
	if (gpioGetPinVal(port, pin))
		{
			gpioResetPin(port, pin);
		}
		else
		{
			gpioSetPin(port, pin);
		}
}

/*
  * Desc.: enables the Clock for alternative functions, this Clock must be activated in Order to use alternative pinfunctions!
  * @param: none
  * @return: none
  */
extern void afioInit(){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

