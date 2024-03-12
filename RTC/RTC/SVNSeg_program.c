/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Hany      *************************/
/********************  SWC: SVNSeg             *************************/
/********************  LAYER: HAL              *************************/
/********************  VERSION: 1.1          *************************/
/********************  DATE4/3/2024          *************************/
/***********************************************************************/
/***********************************************************************/

#define  F_CPU 16000000
#include <util/delay.h>

/*LIB*/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Error_State.h"

#include "util/delay.h"

/*DIO*/
#include "DIO_interface.h"
#include "DIO_register.h"

/*SevenSegment*/
#include "SVNSeg_interface.h"
#include "SVNSeg_config.h"
#include "SVNSeg_private.h"


u8 arr[]={ 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void SVN_voidINIT()
{
	DIO_u8SetPortDirection(SVN_DATA_PORT,DIO_PORT_OUTPUT);
	DIO_u8SetPortDirection(SVN_ENABLE_PORT,DIO_PORT_OUTPUT);
	
// 	DIO_u8SetPinDirection(SVN_DATA_PORT,SVN_DATA_PIN1,DIO_PIN_OUTPUT);
// 	DIO_u8SetPinDirection(SVN_DATA_PORT,SVN_DATA_PIN2,DIO_PIN_OUTPUT);
// 	DIO_u8SetPinDirection(SVN_DATA_PORT,SVN_DATA_PIN3,DIO_PIN_OUTPUT);
// 	DIO_u8SetPinDirection(SVN_DATA_PORT,SVN_DATA_PIN4,DIO_PIN_OUTPUT);
}

void SVN_enable(u8 pinNumber)
{
	DIO_u8SetPinValue(SVN_ENABLE_PORT,pinNumber,DIO_PIN_LOW);
}
void SVN_disable(u8 pinNumber)
{
	DIO_u8SetPinValue(SVN_ENABLE_PORT,pinNumber,DIO_PIN_HIGH);
}


void SVN_write(u8 number)
{
	DIO_u8SetPortValue(SVN_DATA_PORT,arr[number]);
}
