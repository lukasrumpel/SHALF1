/*
 * shalf1EXTI.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1EXTI.h>
#include <shalf1GPIO.h>
#include <stdbool.h>
 /*
  * Desc.: setzt die Bits im AFIO EXTICR Register, um die Inputs als Interruptquellen zu setzen, hierzu gibt es vier EXTICR Register, welche jeweils vier PINs aller Ports beschreiben
  * @param: PORT, PIN
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
 * Des.: setzt das zugehoerige Bit im IMR (Interrupt Mask Register), aktiviert also die Ijnterruptquelle
 * @param: Nummer des Interrupt
 * @return: keine
 */
extern void extiEnableIrq(irq_NUM irq){
	EXTI->IMR |= 1 << irq; //schiebt das Bit an die korrespondierende Stelle des IMR
}

/*
 * Des.: loeascht das zugehoerige Bit im IMR (Interrupt Mask Register), deaktiviert also die Ijnterruptquelle
 * @param: Nummer des Interrupt
 * @return: keine
 */
extern void extiDisableIrq(irq_NUM irq){
	EXTI->IMR &= ~(1 << irq);
}
/*
 * Des.: konfiguriert, ob bei steigender oder fallender Flanke ein ISR ausgeloest werden soll
 * @param: steigende (TRUE) oder fallende (FALSE) Flanke, Irq Nummer
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

