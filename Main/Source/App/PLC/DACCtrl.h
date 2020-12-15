#include "datatype.h"
#include "stm32f10x.h"

#ifndef _DAC_CTRL_H_
#define _DAC_CTRL_H_

//配置DAC相关设置寄存器
void DAC_Configuration(void);
//设置DAC1的输出电压
void DAC_SetValueAO1(u16 volt);
//设置DAC2的输出电压
void DAC_SetValueAO2(u16 volt);
//取得DAC1当前电压
u16 DAC_GetValueAO1(void);
//取得DAC2当前电压		
u16 DAC_GetValueAO2(void);

void DAC_SetOffset(u8 index,u16 offset);
#endif
