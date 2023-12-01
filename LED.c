/*
 * LED.c
 *
 * Created: 10/9/2023 2:59:19 PM
 *  Author: M Osama
 */ 



#include "LED.h"


void LED_vInit (ports port ,pins pin){	
	DIO_pin_dierction(port,pin,DIO_OUTPUT);	
}

void LED_vTurnOn (ports port ,pins pin){
	DIO_pin_write(port,pin,1);		
}

void LED_vTurnOff (ports port ,pins pin){
	DIO_pin_write(port,pin,0);	
}

void LED_vTurnToggle (ports port ,pins pin){
	DIO_pin_toggle(port,pin);		
}