/*
 * EEPROM.c
 *
 * Created: 10/23/2023 1:01:43 AM
 *  Author: M Osama
 */ 

#include "EEPROM.h"

void EEPROM_write (unsigned short address , unsigned char data){
	/*set up address register*/
	EEARL = (char)address;
	EEARH = (char)(address >> 8);
	/*set up data register*/
	EEDR = data;
	/*write logical one to EEMWE*/
	SET_BIT(EECR,EEMWE);
	/*start EEPROM write by setting EEWE*/
	SET_BIT(EECR,EEWE);
	/* wait for completion of write operation*/	
	while(READ_BIT(EECR,EEWE) == 1);
	
}
unsigned char EEPROM_read (unsigned short address){
	unsigned char data_val = 0;
	/*set up address register*/
	EEARL = (char)address;
	EEARH = (char)(address >> 8);
	/*start EEPROM read by setting EERE*/
	SET_BIT(EECR,EERE);
	/*return data from data register*/	
	data_val = EEDR;
	return data_val;
}