/*
 * shalf1I2C.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1I2C_H_
#define INC_SHALF1I2C_H_

typedef enum{
	I2C_CLK_100 = 0,
	I2C_CLK_400
}I2C_CLOCKSPEED;

typedef enum{
	I2C_DUTY_CYCLE_2 = 0,
	IC2_DUTY_CYCLE_16_9
}I2C_DUTYCYCLE;

typedef enum{
	I2C_2MHZ = 0b000010,
	I2C_5MHZ = 0b000101,
	I2C_10MHZ = 0b001010,
	I2C_20MHZ = 0b010100,
	I2C_25MHZ = 0b011001,
	I2C_50MHZ = 0b110010
}I2C_PCLK;

extern void i2cInit(I2C_TypeDef* i2c, I2C_PCLK pclk, I2C_DUTYCYCLE dutycycle, I2C_CLOCKSPEED clkspeed);
extern void i2cWriteByte(I2C_TypeDef* i2c, uint8_t addr, uint8_t data);
extern uint8_t i2cReadByte(I2C_TypeDef* i2c, uint8_t addr);
extern void i2cWriteReg(I2C_TypeDef* i2c, uint8_t addr, uint8_t reg, uint8_t data);
extern uint8_t i2cReadReg(I2C_TypeDef* i2c, uint8_t addr, uint8_t reg);
extern void i2cBurstWrite(I2C_TypeDef* i2c, uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);
extern void i2cBurstRead(I2C_TypeDef *i2c, uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);


#endif /* INC_SHALF1I2C_H_ */
