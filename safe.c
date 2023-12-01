/*
 * safe.c
 *
 * Created: 11/5/2023 3:10:53 PM
 *  Author: M Osama
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "KEYPAD.h"
#include "EEPROM.h"

#define EEPROM_STATUS_LOCATION     0x20
#define EEPROM_PASSWORD_LOCATION1  0x21
#define EEPROM_PASSWORD_LOCATION2  0x22
#define EEPROM_PASSWORD_LOCATION3  0x23
#define EEPROM_PASSWORD_LOCATION4  0x24
#define EEPROM_BLOCK_MODE_STATUS   0x30
#define MAX_TRIS  3
#define BLOCK_TIME 20

char password[4];
char flag = 0;
char updateflag = 0;

void SetPassword (void);
void CheckPassword (void);
void EditPassword (void);
void BlockMode (void);

int main(void)
{
	char mode = NOTPRESSED;
	LCD_vInit();
	keypad_vInit();
	LED_vInit(DIO_PORTA,DIO_PIN0);
	if (EEPROM_read(EEPROM_BLOCK_MODE_STATUS) == 0x00)
	{
		BlockMode();
		goto label;
	}
	else if (EEPROM_read(EEPROM_BLOCK_MODE_STATUS) == 0xFF)
	{
		SetPassword();
		label :
		LCD_clearscreen();
		LCD_vSend_string("1:Check Password");
		LCD_movecursor(2,1);
		LCD_vSend_string("2:Edit Password");
		do
		{
			mode = keypad_u8check_press();
		} while (mode == NOTPRESSED);
		if (mode == '1')
		{
			mode = NOTPRESSED;
			CheckPassword();
		}
		else if (mode == '2')
		{
			mode = NOTPRESSED;
			EditPassword();
			if (updateflag == 1)
			{
				updateflag = 0;
				goto label;
			}
			
		}
		else
		{
			LCD_clearscreen();
			LCD_vSend_string("Wrong choice");
			_delay_ms(1000);
			goto label;
		}
	}
}

void SetPassword (void){
	char val = NOTPRESSED;
	char i = 0;
	if (EEPROM_read(EEPROM_STATUS_LOCATION) == 0xFF)
	{
		LCD_vSend_string("Set Password:");
		for (i = 0 ; i < 4 ; i++)
		{
			do 
			{
				val = keypad_u8check_press();
			} while (val == NOTPRESSED);
			LCD_movecursor(2,6+i);
			LCD_vSend_char(val);
			_delay_ms(500);
			LCD_movecursor(2,6+i);
			LCD_vSend_char('*');
			_delay_ms(500);
			EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,val);
		}
		EEPROM_write(EEPROM_STATUS_LOCATION,0x00);		
	}
		
}

void CheckPassword (void){
	char i = 0;
	char trais = MAX_TRIS;
	while (flag == 0)
	{
		password[0]=password[1]=password[2]=password[3] = NOTPRESSED;
		LCD_clearscreen();
		LCD_vSend_string("Enter Password:");
		for (i = 0 ; i < 4 ; i++)
		{
			do
			{
				password[i] = keypad_u8check_press();
			} while (password[i] == NOTPRESSED);
			LCD_movecursor(2,6+i);
			LCD_vSend_char(password[i]);
			_delay_ms(500);
			LCD_movecursor(2,6+i);
			LCD_vSend_char('*');
			_delay_ms(500);	
		}
		if (password[0] == EEPROM_read(EEPROM_PASSWORD_LOCATION1) &&
		    password[1] == EEPROM_read(EEPROM_PASSWORD_LOCATION2) &&
		    password[2] == EEPROM_read(EEPROM_PASSWORD_LOCATION3) &&
		    password[3] == EEPROM_read(EEPROM_PASSWORD_LOCATION4))
		{
			LCD_clearscreen();
			LCD_vSend_string("Correct Password");
			LCD_movecursor(2,1);
			LCD_vSend_string("Safe Open");
			LED_vTurnOn(DIO_PORTA,DIO_PIN0);
			flag = 1;	
		}
		else{
			trais -= 1;
			if (trais > 0)
			{
				LCD_clearscreen();
				LCD_vSend_string("Wrong Password");
				_delay_ms(1000);
				LCD_clearscreen();
				LCD_vSend_string("Left Tries : ");
				LCD_vSend_int(trais);
				_delay_ms(1000);
			}
			else
			{
				LCD_clearscreen();
				LCD_vSend_string("Wrong Password");
				LCD_movecursor(2,1);
				LCD_vSend_string("Safe closed");
				_delay_ms(1000);	
				BlockMode();
				flag = 0;
				trais = MAX_TRIS;	
			}
		}		
	}	
}

void EditPassword (void){
	char oldpass[4];
	char i = 0;
	char checkflag = 0;
	char trais = MAX_TRIS;
	char val = NOTPRESSED;
	while (updateflag == 0){
		while (checkflag == 0)
		{
			oldpass[0]=oldpass[1]=oldpass[2]=oldpass[3] = NOTPRESSED;
			LCD_clearscreen();
			LCD_vSend_string("Old Password:");
			for (i = 0 ; i < 4 ; i++)
			{
				do
				{
					oldpass[i] = keypad_u8check_press();
				} while (oldpass[i] == NOTPRESSED);
				LCD_movecursor(2,6+i);
				LCD_vSend_char(oldpass[i]);
				_delay_ms(500);
				LCD_movecursor(2,6+i);
				LCD_vSend_char('*');
				_delay_ms(500);	
			}
			if (oldpass[0] == EEPROM_read(EEPROM_PASSWORD_LOCATION1) &&
				oldpass[1] == EEPROM_read(EEPROM_PASSWORD_LOCATION2) &&
				oldpass[2] == EEPROM_read(EEPROM_PASSWORD_LOCATION3) &&
				oldpass[3] == EEPROM_read(EEPROM_PASSWORD_LOCATION4))
			{	
				EEPROM_write(EEPROM_STATUS_LOCATION,0xFF);
				if (EEPROM_read(EEPROM_STATUS_LOCATION) == 0xFF)
				{
					LCD_clearscreen();
					LCD_vSend_string("New Password:");
					for (i = 0 ; i < 4 ; i++)
					{
						do
						{
							val = keypad_u8check_press();
						} while (val == NOTPRESSED);
						LCD_movecursor(2,6+i);
						LCD_vSend_char(val);
						_delay_ms(500);
						LCD_movecursor(2,6+i);
						LCD_vSend_char('*');
						_delay_ms(500);
						EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,val);
					}
					EEPROM_write(EEPROM_STATUS_LOCATION,0x00);
					LCD_clearscreen();
					LCD_vSend_string("Update Success");
					_delay_ms(1000);
					updateflag = 1;
					checkflag = 1;
				}		
			}
			else
			{
				trais -= 1;
				if (trais > 0)
				{
					LCD_clearscreen();
					LCD_vSend_string("Wrong Password");
					_delay_ms(1000);
					LCD_clearscreen();
					LCD_vSend_string("Left Tries : ");
					LCD_vSend_int(trais);
					_delay_ms(1000);
				}
				else
				{
					LCD_clearscreen();
					LCD_vSend_string("Wrong Password");
					LCD_movecursor(2,1);
					LCD_vSend_string("Safe closed");
					_delay_ms(1000);
					BlockMode();
					checkflag = 0;
					trais = MAX_TRIS;
				}	
			}		
		}
	}			
}


void BlockMode (void){
	EEPROM_write(EEPROM_BLOCK_MODE_STATUS,0x00);
	char BlockTime = BLOCK_TIME;	
	while (BlockTime > 0){
		LCD_clearscreen();
		LCD_vSend_string("BLock Time:");
		LCD_vSend_int(BlockTime);
		_delay_ms(1000);
		BlockTime--;
	}	
	EEPROM_write(EEPROM_BLOCK_MODE_STATUS,0xFF);
}