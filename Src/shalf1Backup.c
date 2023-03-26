/*
 * shalf1Backup.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1Backup.h>
#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * defines
 */

#define ENABLE_BKP() {RCC->APB1ENR |= RCC_APB1ENR_BKPEN; \
					PWR->CR |= PWR_CR_DBP;}
#define DISABLE_BKP() {RCC->APB1ENR &= ~RCC_APB1ENR_BKPEN_Msk;\
					PWR->CR &= ~PWR_CR_DBP_Msk;}
#define GET_BKP_ADR(REG) {(uint32_t*)((BKP_BASE_ADR) + (uint32_t)(REG))}

uint8_t BKPRegLookup[] = {0x04,0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28, 0x40, 0x44, 0x48, 0x4C, 0x50, 0x54, 0x58, 0x5C, 0x60, 0x64, 0x68, 0x6C, 0x70, 0x74, 0x78, 0x7C, 0x80, 0x84, 0x88, 0x8C, 0x90, 0x94, 0x98, 0x9C,  0xA0, 0xA4, 0xA8, 0xAC, 0xB0, 0xB4, 0xB8, 0xBC};

static uint8_t getIDX(BKPReg BKPRegister);

/*
  * Desc.: writes single byte in one of the backup registers
  * @param: (uint16_t) data: Byte which is to be written in the backup register
  * @param: (BKPReg) BKPRegister: register in which to the data has to be written
  * @return: (BKP_ERR_CODE) error code
  */
BKP_ERR_CODE backupWriteByte(uint16_t data, BKPReg BKPRegister){
	if((BKPRegister > 0) && (BKPRegister <= 42)){
		ENABLE_BKP();
		uint32_t* regAdr = GET_BKP_ADR(BKPRegister);
		*regAdr = data;
		DISABLE_BKP();
		return BKP_OK;
	}
	else{
		return BKP_INVALID_REG;
	}
}

/*
  * Desc.: reads single byte from a given backup register
  * @param: (BKPReg) BKPRegister: register to read
  * @return: (uint16_t) value of BKP register
  */
uint16_t backupReadByte(BKPReg BKPRegister){
	if((BKPRegister > 0) && (BKPRegister <= 42)){
		uint16_t dataBuff = 0;
		ENABLE_BKP();
		uint32_t* regAdr = GET_BKP_ADR(BKPRegister);
		dataBuff = *regAdr;
		return dataBuff;
	}
	else{
		return 0;
	}
}

/*
  * Desc.: writes a sequence of bytes in the backup registers, the registers indices are incremented from the index of the start register
  * @param: (uint16_t*) data: bytes to be written
  * @param: (BKPReg) BKPRegister: start register
  * @param: (uint8_t) numOfBytes: number of bytes / registers
  * @return: (BKP_ERR_CODE) error code
  */
extern BKP_ERR_CODE backupWriteArray(uint16_t* data, BKPReg BKPRegister, uint8_t numOfBytes){
	if((getIDX(BKPRegister) >= 0) && (getIDX(BKPRegister) + numOfBytes <= 42)){
		ENABLE_BKP();
		uint8_t i;
		uint32_t *regAdr = 0;
		for(i = getIDX(BKPRegister); i < getIDX(BKPRegister)+numOfBytes; i++){
			regAdr = (uint32_t*)((BKP_BASE_ADR) + (uint32_t)(BKPRegLookup[getIDX(BKPRegister)+i]));
			*regAdr = *data++;
		}
		DISABLE_BKP();
		return BKP_OK;
	}
	else{
		return BKP_DATA_OUT_OF_BOUND;
	}
}

/*
  * Desc.: reads a sequence of bytes from the backup registers, the registers indices are incremented from the index of the start register
  * @param: (uint16_t*) data: read buffer
  * @param: (BKPReg) BKPRegister: start register
  * @param: (uint8_t) numOfBytes: number of bytes / registers
  * @return: (BKP_ERR_CODE) error code
  */
extern BKP_ERR_CODE backupReadArray(uint16_t* data, BKPReg BKPRegister, uint8_t numOfBytes){
	if((getIDX(BKPRegister) >= 0) && (getIDX(BKPRegister) + numOfBytes <= 42)){
		ENABLE_BKP();
		uint8_t i;
		uint32_t *regAdr = 0;
		for(i = getIDX(BKPRegister); i < getIDX(BKPRegister)+numOfBytes; i++){
			regAdr = (uint32_t*)((BKP_BASE_ADR) + (uint32_t)(BKPRegLookup[getIDX(BKPRegister)+i]));
			*data++ = *regAdr;
		}
		DISABLE_BKP();
		return BKP_OK;
	}
	else{
		return BKP_DATA_OUT_OF_BOUND;
	}
}

/*
  * Desc.: function for converting BKPReg to a numeric value for iteration
  * @param: (BKPReg) BKPRegister: start register
  * @return: (uint8_t) position in lookup table
  */
static uint8_t getIDX(BKPReg BKPRegister){
	int i = 0;
	while((BKPRegister != BKPRegLookup[i])){
		i++;
	}
	return i;
}
