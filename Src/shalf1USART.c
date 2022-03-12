/*
 * shalf1USART.c
 *
 *  Created on: 30.01.2022
 *      Author: lukas
 */


#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>
#include <shalf1GPIO.h>
#include <string.h>
#include <shalf1USART.h>

#define USART_TX_EMPTY(usart)  ((usart)->SR & USART_SR_TXE)
#define USART_WAIT(usart)      do { while(!USART_TX_EMPTY(usart)); } while(0)

/*
  * Desc.: enables Clock for the corresponding USART and activates the USART in it's Control Register
  * @param: (USART_TypeDef*)usart: USART
  * @return: none
  */
void USARTEnable(USART_TypeDef* usart){
	if(usart == USART1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		USART1->CR1 |= USART_CR1_UE;
	}
	else if(usart == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		USART2->CR1 |= USART_CR1_UE;
	}
	else if(usart == USART3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		USART3->CR1 |= USART_CR1_UE;
	}
	else{
		return;
	}
}

/*
  * Desc.: disables USART in it's control Register and disables Clock for the USART Module
  * @param: (USART_TypeDef*)usart: USART
  * @return: none
  */
void USARTDisable(USART_TypeDef* usart){
	if(usart == USART1){
			USART1->CR1 &= ~USART_CR1_UE_Msk;
			RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
		}
		else if(usart == USART2){
			USART2->CR1 &= ~USART_CR1_UE_Msk;
			RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
		}
		else if(usart == USART3){
			USART3->CR1 &= ~USART_CR1_UE_Msk;
			RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
		}
		else{
			return;
		}
}

/*
  * Desc.: sets the Baudrate for the USART (system clock > 36 MHZ!), default: 115200 bps
  * @param: (USART_TypeDef*)usart: USART
  * @param: (uint16_t) brrVal: Baudrate
  * @return: none
  */
void USARTSetBaudrate(USART_TypeDef* usart, uint16_t brrVal){
	if(brrVal != 0){
		usart -> BRR |= (SystemCoreClock / 2 / brrVal);
	}
	else{
		usart->BRR |= 0x8B;
	}
}

/*
  * Desc.: enables the Receiver of the corresponding USART
  * @param: (USART_TypeDef*)usart: USART
  * @param: (USART_RX) on_off: indicates if the Receiver shall be activated
  * @return: none
  */
void USARTRXOn(USART_TypeDef* usart, USART_RX on_off){
	if(on_off == RECEIVER_ON){
		usart->CR1 |= USART_CR1_RE;
	}
	else{
		usart->CR1 &= USART_CR1_RE_Msk;
	}
}

/*
  * Desc.: enables the Transmitter of the corresponding USART
  * @param: (USART_TypeDef*)usart: USART
  * @param: (USART_RX) on_off: indicates if the Transmitter shall be activated
  * @return: none
  */
void USARTTXOn(USART_TypeDef* usart, USART_TX on_off){
	if(on_off == TRANSMITTER_ON){
			usart->CR1 |= USART_CR1_TE;
		}
		else{
			usart->CR1 &= USART_CR1_TE_Msk;
		}
}

/*
  * Desc.: function for configuring the IRQ of the USART
  * @param: (USART_TypeDef*)usart: USART
  * @param: (USART_IRQ_TYPES) irq_types:USART_IRQ_TXEIE, (TX Interrupt)
    									USART_IRQ_CTSIE,(CTS Interrupt)
    									USART_IRQ_TCIE,(Transmission complete Interrupt)
    									USART_IRQ_RXNEIE,(REceive Interrupt)
    									USART_IRQ_PEIE,(PE Interrupt)
    									USART_IRQ_LBDIE,(LIN Break Detection Interrupt)
    									USART_IRQ_EIE(Error Interrupt)
  *  @param: (bool) enable_disable: determines if the interrupt shall be enabled or disabled
  * @return: none
  */
extern void USARTIRQ(USART_TypeDef* usart, USART_IRQ_TYPES irq_type, bool enable_disable){
	switch(irq_type){
	case USART_IRQ_TXEIE:
		if(enable_disable){
			usart->CR1 |= USART_CR1_TXEIE;
		}
		else{
			usart->CR1 &= ~USART_CR1_TXEIE_Msk;
		}
		break;
	case USART_IRQ_CTSIE:
		if(enable_disable){
			usart->CR3 |= USART_CR3_CTSIE;
		}
		else{
			usart->CR3 &= ~USART_CR3_CTSIE_Msk;
		}
		break;
	case USART_IRQ_TCIE:
		if(enable_disable){
			usart->CR1 |= USART_CR1_TCIE;
		}
		else{
			usart->CR1 &= ~USART_CR1_TCIE_Msk;
		}
		break;
	case USART_IRQ_RXNEIE:
		if(enable_disable){
			usart->CR1 |= USART_CR1_RXNEIE;
		}
		else{
			usart->CR1 &= ~USART_CR1_RXNEIE_Msk;
		}
		break;
	case USART_IRQ_PEIE:
		if(enable_disable){
			usart->CR1 |= USART_CR1_PEIE;
		}
		else{
			usart->CR1 &= ~USART_CR1_PEIE_Msk;
		}
		break;
	case USART_IRQ_LBDIE:
		if(enable_disable){
			usart->CR2 |= USART_CR2_LBDIE;
		}
		else{
			usart->CR2 &= ~USART_CR2_LBDIE_Msk;
		}
		break;
	case USART_IRQ_EIE:
		if(enable_disable){
			usart->CR3 |= USART_CR3_EIE;
		}
		else{
			usart->CR3 &= ~USART_CR3_EIE_Msk;
		}
		break;
	default:
		return;
	}
}

/*
  * Desc.: send a String over the USART
  * @param: (USART_TypeDef*)usart: USART
  * @param: (char*) str: String to be sent
  * @return: none
  */
extern void USARTSendString(USART_TypeDef* usart, char* str){
	while(*str){
		USART_WAIT(usart);
		usart->DR = *str++ & 0x01FF;
		USART_WAIT(usart);
	}
}

/*
  * Desc.: send a Char over the USART
  * @param: (USART_TypeDef*)usart: USART
  * @param: (char*) character: char to be sent
  * @return: none
  */
extern void USARTSendChar(USART_TypeDef* usart, char character){
	USART_WAIT(usart);
	usart ->DR = character;
	USART_WAIT(usart);
}

/*
  * Desc.: receives a Char over the USART (non ISR version!)
  * @param: (USART_TypeDef*)usart: USART
  * @return: (char): received Character
  */
extern char USARTGetChar(USART_TypeDef *usart){
	char received;
	while(!(usart->SR & USART_SR_RXNE)){
	}
	received = usart->DR & 0x01FF;
	return received;
}

/*
  * Desc.: receives a String with given length over the USART (non ISR version!)
  * @param: (USART_TypeDef*)usart: USART
  * @param: (char*) str: String to receive
  * @param:	(uint16_t) leng: length of the String
  * @return: none
  */
extern void USARTGetString(USART_TypeDef *usart, char *str, uint16_t leng){
	char rcv;
	while((rcv != '\n') && (leng != 0) ){
		rcv = USARTGetChar(usart);
		*str++ = rcv;
		leng--;
	}
	*str = '\0';
}
