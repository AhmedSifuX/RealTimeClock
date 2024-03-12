/*
 * RTC.c
 *
 * Created: 11/03/2024 09:15:10 ص
 * Author : user
 */ 

#define F_CPU 16000000
#include "util/delay.h"

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Error_State.h"

#include "DIO_interface.h"

#include "SVNSeg_interface.h"
#include "SVNSeg_config.h"

#include "KPD_interface.h"

#include "LCD_interface.h"


u8 sec=0,minutes=0, hours=0;
u8 firstNumber=0,secondNumber=0;
u8 option = 0;

void clockStart(void);
void inputTaking(void);


int main(void)
{
	
	LCD_voidINIT();
	KPD_voidINIT();
	SVN_voidINIT();
	
	
	inputTaking();
	
	
    /* Replace with your application code */
    while (1) 
    {
		inputTaking();
	}
}

void inputTaking(void)
{
	LCD_u8SendString("Press 1 to set");
	LCD_u8SetPosXY(1,0);
	LCD_u8SendString("clock");
	do 
	{
		clockStart();
		option = KPD_GetPressedKey();
	} while (option == KPD_NOT_PRESSED_KEY);
	if((option-48) == 1)
{
	/*HOURS*/
	/*---------------------------------------------------*/
	retryHours:
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	LCD_u8SendString("Enter");
	LCD_u8SetPosXY(1,0);
	LCD_u8SendString("Hours : ");

	_delay_ms(500);
	do
	{
		firstNumber = KPD_GetPressedKey();
	} while (firstNumber==KPD_NOT_PRESSED_KEY);
	LCD_voidSendData(firstNumber);
	_delay_ms(250);
	
	do
	{
		secondNumber = KPD_GetPressedKey();
	} while (secondNumber==KPD_NOT_PRESSED_KEY);
	LCD_voidSendData(secondNumber);
	_delay_ms(250);
	hours = (secondNumber-48)+10*(firstNumber-48);
	if(hours>12 || hours<0)
	{
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	LCD_u8SendString("Error Wrong");
	LCD_u8SetPosXY(1,0);
	LCD_u8SendString("Input");
	_delay_ms(1000);
	goto retryHours;
	}
	else
	{
	/*---------------------------------------------------*/
	/*Minutes*/
	/*---------------------------------------------------*/
	retryMinutes:
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	LCD_u8SendString("Enter");
	LCD_u8SetPosXY(1,0);
	LCD_u8SendString("Minutes : ");

	_delay_ms(500);
	do
	{
		firstNumber = KPD_GetPressedKey();
	} while (firstNumber==KPD_NOT_PRESSED_KEY);
	LCD_voidSendData(firstNumber);
	_delay_ms(250);
	
	do
	{
		secondNumber = KPD_GetPressedKey();
	} while (secondNumber==KPD_NOT_PRESSED_KEY);
	LCD_voidSendData(secondNumber);
	_delay_ms(250);
	minutes = (secondNumber-48)+10*(firstNumber-48);
	if(minutes>60 || minutes < 0)
	{
		LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
		LCD_u8SendString("Error Wrong");
		LCD_u8SetPosXY(1,0);
		LCD_u8SendString("Input");
		_delay_ms(1000);
		goto retryMinutes;
	}
	else
		{
	/*---------------------------------------------------*/
	/*Seconds*/
	/*---------------------------------------------------*/
	retrySeconds:
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	LCD_u8SendString("Enter");
	LCD_u8SetPosXY(1,0);
	LCD_u8SendString("Seconds : ");

	_delay_ms(500);
	do
	{
		firstNumber = KPD_GetPressedKey();
	} while (firstNumber==KPD_NOT_PRESSED_KEY);
	LCD_voidSendData(firstNumber);
	_delay_ms(250);
	
	do
	{
		secondNumber = KPD_GetPressedKey();
	} while (secondNumber==KPD_NOT_PRESSED_KEY);
	LCD_voidSendData(secondNumber);
	_delay_ms(250);
	sec = (secondNumber-48)+10*(firstNumber-48);
	if(sec>60 || sec < 0)
	{
		LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
		LCD_u8SendString("Error Wrong");
		LCD_u8SetPosXY(1,0);
		LCD_u8SendString("Input");
		_delay_ms(1000);
		goto retrySeconds;
	}
	else
	{
		LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
		/*---------------------------------------------------*/
	
	LCD_u8SendString("Clock is");
	LCD_u8SetPosXY(1,0);
	LCD_u8SendString("working...");
	_delay_ms(500);
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	
			
			}
		}
			
	}
}
else
clockStart();
}

void clockStart(void)
{
	/*CLOCK CODE*/
				u8 right_sec = sec % 10; // en1
				u8 left_sec =  sec  / 10; // en2
				u8 right_hours = hours % 10; // en5
				u8 left_hours =  hours  / 10; // en6
				u8 right_minutes = minutes % 10; // en3
				u8 left_minutes =  minutes  / 10; // en4
				
				for(u8 i = 0; i < 25 ; i++)
				{
					SVN_disable(SVN_EN1);
					SVN_disable(SVN_EN2);
					SVN_disable(SVN_EN3);
					SVN_disable(SVN_EN4);
					SVN_disable(SVN_EN5);
					SVN_disable(SVN_EN6);
					/*--------------------*/
					/*Seconds*/
					SVN_write(left_sec);
					SVN_enable(SVN_EN2);
					_delay_ms(5);
					SVN_disable(SVN_EN2);
					SVN_write(right_sec);
					SVN_enable(SVN_EN1);
					_delay_ms(5);
					/*--------------------*/
					/*Minutes*/
					SVN_disable(SVN_EN1);
					SVN_write(right_minutes);
					SVN_enable(SVN_EN3);
					_delay_ms(5);
					SVN_disable(SVN_EN3);
					SVN_write(left_minutes);
					SVN_enable(SVN_EN4);
					_delay_ms(5);
					/*--------------------*/
					/*Hours*/
					SVN_disable(SVN_EN4);
					SVN_write(right_hours);
					SVN_enable(SVN_EN5);
					_delay_ms(10);
					SVN_disable(SVN_EN5);
					SVN_write(left_hours);
					SVN_enable(SVN_EN6);
					_delay_ms(10);
					
	}
	sec++;
	if(sec >= 60)
	{
		sec = 0;
		minutes++;
	}
	if(minutes >=  60)
	{
		minutes=0;
		hours++;
	}
	if(hours>12)
	{
		hours=0;
	}
	/*END OF CLOCK CODE*/
}