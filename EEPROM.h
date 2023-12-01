/*
 * EEPROM.h
 *
 * Created: 10/23/2023 1:01:58 AM
 *  Author: M Osama
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "BIT_Math.h"
#include <avr/io.h>

void EEPROM_write (unsigned short address , unsigned char data);
unsigned char EEPROM_read (unsigned short address);




#endif /* EEPROM_H_ */