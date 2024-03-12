/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Hany      *************************/
/********************  SWC: SVNSeg             *************************/
/********************  LAYER: HAL              *************************/
/********************  VERSION: 1.1          *************************/
/********************  DATE4/3/2024          *************************/
/***********************************************************************/
/***********************************************************************/


#ifndef SVNSEG_INTEFACE_H_
#define SVNSEG_INTEFACE_H_

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Error_State.h"


void SVN_voidINIT();
void SVN_write(u8 number);

void SVN_enable(u8 pinNumber);
void SVN_disable(u8 pinNumber);
#endif