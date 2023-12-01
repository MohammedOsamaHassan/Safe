/*
 * LED.h
 *
 * Created: 10/9/2023 2:59:30 PM
 *  Author: M Osama
 */ 


#ifndef LED_H_
#define LED_H_
#include "DIO.h"

void LED_vInit (ports port ,pins pin);
void LED_vTurnOn (ports port ,pins pin);
void LED_vTurnOff (ports port ,pins pin);
void LED_vTurnToggle (ports port ,pins pin);



#endif /* LED_H_ */