/*
 * shalf1.c
 *
 *      Author: lukasrumpel
 */

#include <shalf1.h>

/*
  * Desc.: initializes the SHALF1
  * @param: none
  * @return: (SHALF1_ErrCode) error code
  */
extern SHALF1_ErrCode initSHALF1(void){
#if defined(MED_DENS) || defined(LOW_DENS)
	initClock();
	return noError;
#else
	return densityNotSupported;
#endif
}

/*
  * Desc.: sets the clock settings
  * @param: none
  * @return: none
  */
extern void initClock(void){
	setClock(SHALF1CLKSRC, SHALF1SYSCLOCK, SHALF1APB1CLK, SHALF1APB2CLK);
}
