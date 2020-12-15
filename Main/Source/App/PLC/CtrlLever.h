#include "datatype.h"

#ifndef _CTRL_LEVER_H_
#define _CTRL_LEVER_H_

#define CTRL_SYSTICK 1125		//0.25ms
void Ctrl_Init(void);
void Ctrl_Disable(void);
void Ctrl_Enable(void);
void Ctrl_Configuration(void);
void SysTick_Handler(void);
#endif
