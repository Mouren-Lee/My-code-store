/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_X.h"
#include "ili9320.h"
#include "TouchScreen.h"

unsigned short int X,Y;

void GUI_TOUCH_X_ActivateX(void) {
}

void GUI_TOUCH_X_ActivateY(void) {
}

/*
 
int  GUI_TOUCH_X_MeasureX(void) {
  unsigned short i;
  unsigned short sum=0;
  for(i=0;i<8;i++)
   	sum+=TPReadX();
  return sum>>3;
}

int  GUI_TOUCH_X_MeasureY(void) {
  unsigned short i;
  unsigned short sum=0;
  for(i=0;i<8;i++)
   	sum+=TPReadY();
  return sum>>3;
}
*/ 

int  GUI_TOUCH_X_MeasureX(void) 
{
	return(TScr_GetX());  
}

int  GUI_TOUCH_X_MeasureY(void)
{
	return(TScr_GetY()); 
}
