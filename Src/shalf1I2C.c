/*
 * shalf1I2C.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1GPIO.h>
#include <shalf1I2C.h>

#define WAIT_BUSY(i2c) 	( { while (i2c->SR2 & I2C_SR2_BUSY) ; } )
#define WAIT_SB(i2c)	( { while (!(i2c->SR1 & I2C_SR1_SB)) ; } )
#define WAIT_ADDR(i2c)	( { while (!(i2c->SR1 & I2C_SR1_ADDR)) ; } )
#define WAIT_TXE(i2c)	( { while(!(i2c->SR1 & I2C_SR1_TXE)) ; } )
#define WAIT_TRANS(i2c)	( { while(!(i2c->SR1 & I2C_SR1_BTF)) ; })
#define WAIT_RXNE(i2c)	( { while(!(i2c->SR1 & I2C_SR1_RXNE)) ; } )


/*
  * Desc.: Initializes the I2C Module with the given Parameters as I2C Master
  * @param: (I2C_TypeDef*)i2c: I2C
  * @param: (I2C_PCLK) clockdivider: I2C_2MHZ,
										I2C_10MHZ,
										I2C_20MHZ,
										I2C_25MHZ,
										I2C_50MHZ
  * @param: (I2C_DUTYCYCLE) dutycycle: I2C_DUTY_CYCLE_2 = 0,
										IC2_DUTY_CYCLE_16_9
  * @param: (I2C_CLOCKSPEED) clkspeed: I2C_CLK_100 = 0,
										I2C_CLK_400
  * @return: none
  */
extern void i2cInit(I2C_TypeDef* i2c, I2C_PCLK pclk, I2C_DUTYCYCLE dutycycle, I2C_CLOCKSPEED clkspeed){
	if(i2c == I2C1){
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	}
	else if(i2c == I2C2){
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	}
	else{
		return;
	}

	i2c->CR1 &= ~I2C_CR1_PE_Msk;
	i2c->CR1 = 0x0;
	i2c->CR2 = pclk/1000000;
	i2c->CCR = 0x00;

	if(clkspeed == I2C_CLK_100){
		i2c->CCR &= ~I2C_CCR_FS_Msk;
		i2c->CCR = 0x0050;
	}
	else if(clkspeed == I2C_CLK_400){
		i2c->CCR |= I2C_CCR_FS;
	}
	else{
		return;
	}

	i2c->TRISE = 0x0011;
	i2c->CR1 |= I2C_CR1_PE;
}

/*
  * Desc.: Writes a Single Byte to Slave
  * @param: (I2C_TypeDef*)i2c: I2C
  * @param: (uint8_t) addr: address of slave device
  * @param: (uint8_t) data: data
  * @return: none
  */
extern void i2cWriteByte(I2C_TypeDef* i2c, uint8_t addr, uint8_t data){

	WAIT_BUSY(i2c);

	i2c->CR1 |= I2C_CR1_START;

	WAIT_SB(i2c);

	i2c->DR = addr<<1;

	WAIT_ADDR(i2c);

	i2c->SR1;
	i2c->SR2;

	WAIT_TXE(i2c);

	i2c->DR = data;

	WAIT_TRANS(i2c);

	i2c->CR1 |= I2C_CR1_STOP;
}

/*
  * Desc.: Reades a Single Byte from Slave
  * @param: (I2C_TypeDef*)i2c: I2C
  * @param: (uint8_t) addr: address of slave device
  * @return: (uint8_t) data from slave
  */
extern uint8_t i2cReadByte(I2C_TypeDef* i2c, uint8_t addr){
	uint8_t data;
	WAIT_BUSY(i2c);

	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);
	i2c->DR = addr << 1;
	WAIT_ADDR(i2c);
	i2c->SR1;
	i2c->SR2;
	WAIT_TXE(i2c);

	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);
	i2c->DR = (addr<<1) | 1;
	WAIT_ADDR(i2c);

	//i2c->CR1 &= ~I2C_CR1_ACK_Msk;

	i2c->SR1;
	i2c->SR2;

	i2c-> CR1 |= I2C_CR1_STOP;

	WAIT_RXNE(i2c);

	data = i2c->DR;
	return data;
}

/*
  * Desc.: Writes a Single Byte to a Register
  * @param: (I2C_TypeDef*)i2c: I2C
  * @param: (uint8_t) addr: address of slave device
  * @param: (uint8_t) reg: address of register
  * @return: none
  */
extern void i2cWriteReg(I2C_TypeDef* i2c, uint8_t addr, uint8_t reg, uint8_t data){
	WAIT_BUSY(i2c);

	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);

	i2c->DR = addr<<1;
	WAIT_ADDR(i2c);

	i2c->SR1;
	i2c->SR2;

	WAIT_TXE(i2c);

	i2c->DR = reg;
	WAIT_TXE(i2c);

	i2c->DR = data;

	WAIT_TRANS(i2c);

	i2c->CR1 |= I2C_CR1_STOP;
}

/*
  * Desc.: Reades a Single Byte from Slave
  * @param: (I2C_TypeDef*)i2c: I2C
  * @param: (uint8_t) addr: address of slave device
  * @return: (uint8_t) data from slave
  */
extern uint8_t i2cReadReg(I2C_TypeDef* i2c, uint8_t addr, uint8_t reg){
	uint8_t data;

	WAIT_BUSY(i2c);
	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);
	i2c->DR = addr<<1;
	WAIT_ADDR(i2c);
	i2c->SR1;
	i2c->SR2;
	i2c->DR = reg;
	WAIT_TXE(i2c);
	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);
	i2c->DR = i2c->DR = (addr<<1) | 0b00000001;
	WAIT_ADDR(i2c);
	//i2c->CR1 &= ~I2C_CR1_ACK_Msk;
	i2c->SR1;
	i2c->SR2;
	i2c->CR1 |= I2C_CR1_STOP;
	WAIT_RXNE(i2c);
	data = i2c->DR;
	return data;
}

/*
  * Desc.: Writes a series of Bytes to a slave device
  * @param: (I2C_TypeDef*)i2c: I2C
  * @param: (uint8_t) addr: address of slave device
  * @param: (uint8_t) reg: address of start register
  * @param: (uint8_t*) data: data
  * @param: (uint8_t) len: number of bytes to send
  * @return: none
  */
extern void i2cBurstWrite(I2C_TypeDef* i2c, uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len){
	uint8_t bytes_sent = 0;

	WAIT_BUSY(i2c);

	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);

	i2c->DR = addr << 1;
	WAIT_ADDR(i2c);

	i2c->SR1;
	i2c->SR2;

	WAIT_TXE(i2c);

	i2c->DR = reg;

	while(bytes_sent < len){
		WAIT_TXE(i2c);
		i2c->DR = *data++;
		bytes_sent++;
	}
	WAIT_TRANS(i2c);
	i2c->CR1 |= I2C_CR1_STOP;
}

/*
  * Desc.: Reades a series of Bytes to a slave device
  * @param: (I2C_TypeDef*)i2c: I2C
  * @param: (uint8_t) addr: address of slave device
  * @param: (uint8_t) reg: address of start register
  * @param: (uint8_t*) data: data
  * @param: (uint8_t) len: number of bytes to send
  * @return: none
  */
extern void i2cBurstRead(I2C_TypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len){
	WAIT_BUSY(i2c);
	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);
	i2c->DR = addr<<1;
	WAIT_ADDR(i2c);
	i2c->SR1;
	i2c->SR2;
	i2c->DR = reg;
	WAIT_RXNE(i2c);
	i2c->CR1 |= I2C_CR1_START;
	WAIT_SB(i2c);
	i2c->DR = i2c->DR = (addr<<1) | 0b00000001;
	WAIT_ADDR(i2c);
	i2c->CR1 |= ~I2C_CR1_ACK;
	i2c->SR1;
	i2c->SR2;

	while(len >0){
		if(len == 1){
			i2c->CR1 &= ~I2C_CR1_ACK_Msk;
			i2c->CR1 |= I2C_CR1_STOP;
			WAIT_RXNE(i2c);
			*data++ = i2c->DR;
			break;
		}
		else{
			WAIT_RXNE(i2c);
			*data++ = i2c->DR;
			len--;
		}
	}
}
