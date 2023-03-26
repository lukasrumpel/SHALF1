/*
 * shalf1Backup.h
 *
 *      Author: lukasrumpel
 */

#ifndef INC_SHALF1BACKUP_H_
#define INC_SHALF1BACKUP_H_

#include <stm32f1xx.h>
#include <stdint.h>
#include <stdbool.h>

#define BKP_BASE_ADR 0x40006C00

typedef enum{
	BKP_OK = 0,
	BKP_INVALID_REG = -1,
	BKP_DATA_OUT_OF_BOUND = -2,
}BKP_ERR_CODE;

typedef enum{
	BKP1 = 0x04,
	BKP2 = 0x08,
	BKP3 = 0x0C,
	BKP4 = 0x10,
	BKP5 = 0x14,
	BKP6 = 0x18,
	BKP7 = 0x1C,
	BKP8 = 0x20,
	BKP9 = 0x24,
	BKP10 = 0x28,
	BKP11 = 0x40,
	BKP12 = 0x44,
	BKP13 = 0x48,
	BKP14 = 0x4C,
	BKP15 = 0x50,
	BKP16 = 0x54,
	BKP17 = 0x58,
	BKP18 = 0x5C,
	BKP19 = 0x60,
	BKP20 = 0x64,
	BKP21 = 0x68,
	BKP22 = 0x6C,
	BKP23 = 0x70,
	BKP24 = 0x74,
	BKP25 = 0x78,
	BKP26 = 0x7C,
	BKP27 = 0x80,
	BKP28 = 0x84,
	BKP29 = 0x88,
	BKP30 = 0x8C,
	BKP31 = 0x90,
	BKP32 = 0x94,
	BKP33 = 0x98,
	BKP34 = 0x9C,
	BKP35 = 0xA0,
	BKP36 = 0xA4,
	BKP37 = 0xA8,
	BKP38 = 0xAC,
	BKP39 = 0xB0,
	BKP40 = 0xB4,
	BKP41 = 0xB8,
	BKP42 = 0xBC
}BKPReg;


extern BKP_ERR_CODE backupWriteByte(uint16_t data, BKPReg BKPRegister);
extern uint16_t backupReadByte(BKPReg BKPRegister);
extern BKP_ERR_CODE backupWriteArray(uint16_t* data, BKPReg BKPRegister, uint8_t numOfBytes);
extern BKP_ERR_CODE backupReadArray(uint16_t* data, BKPReg BKPRegister, uint8_t numOfBytes);

#endif /* INC_SHALF1BACKUP_H_ */
