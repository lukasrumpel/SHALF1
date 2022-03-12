/*
 * shalf1EXTI.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1EXTI.h>
#include <shalf1GPIO.h>
#include <stdbool.h>
 /*
  * Desc.: sets the Bits in AFIO EXTICR Register, to set the Interrupts as Sources. Ther are four EXTICR Registers (4 Pins per EXTICR)
  * @param: (PORT) port: Port
  * @param: (Pin) pin: Pin
  * @return: none
  */
extern void extiConfigureEXTI(PORT port, PIN_NUM pin){
	uint8_t mask = port;
	uint8_t shift;
	uint8_t index;
	switch(pin){
	case 0:
	case 1:
	case 2:
	case 3:
		shift = pin * 4;
		index = 0;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		shift = (pin-4)*4;
		index = 1;
		break;
	case 8:
	case 9:
	case 10:
	case 11:
		shift = (pin-8)*4;
		index = 2;
		break;
	case 12:
	case 13:
	case 14:
	case 15:
		shift = (pin-12)*4;
		index = 3;
		break;
	}

	AFIO->EXTICR[index] &= ~0xFFFF;
	AFIO->EXTICR[index] |= (mask << shift);
}

/*
 * Des.: stes the corresponding Bit in the IMR Register, activates the Interruptsource
 * @param: (irq_Num) irq: EXTI_P0,
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
 * @return: none
 */
extern void extiEnableIrq(irq_NUM irq){
	EXTI->IMR |= 1 << irq; //schiebt das Bit an die korrespondierende Stelle des IMR
}

/*
 * Des.: clears the Bit in the IMR, deactivates Interrupt
 * @param: (irq_Num) irq: EXTI_P0,
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
 * @return: none
 */
extern void extiDisableIrq(irq_NUM irq){
	EXTI->IMR &= ~(1 << irq);
}
/*
 * Des.: configures if the ISR is triggered on rising or falling Edge
 * @param: (bool) rising: true -> rising Edge; false -> falling Edge
 * @param: (irq_Num) irq: EXTI_P0,
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
 * @return: none
 */
extern void extiSetTriggerEdge(bool rising, irq_NUM irq){
	if(rising == true){
		EXTI->RTSR |= 1 << irq;
	}
	else{
		EXTI->FTSR |= 1 << irq;
	}
}

