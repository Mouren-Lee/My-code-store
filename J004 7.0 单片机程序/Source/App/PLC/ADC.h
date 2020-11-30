/*----------------------------------------------------------------------------/
/  Tension_Control  	 								 						            (C)Wuning, 2018
/-----------------------------------------------------------------------------/
/ 						Copyright (C) 2018, Wuning, all right reserved.
/
/	 * @file    VSPIDAC.h
/  * @author  wuningcumt
/  * @version V1.0.0
/  * @date    10-May-2018
/  * @brief   this file config TLC5620 gpio and TLC5620 setvalue function
/
/-----------------------------------------------------------------------------/
change records:
/
/----------------------------------------------------------------------------*/
#ifndef __VSPIDAC_H_
#define __VSPIDAC_H_

//#include "main.h"
#include "MainWork.h"
 

void  STMADC_Init(void);
u16 Get_Adc(u8 ch);

void   ADC_START(u8 ch);
u16 Get_AdcData(void) ;
#endif
