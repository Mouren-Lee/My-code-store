#include "datatype.h"
#include "stm32f10x.h"

#ifndef _DAC_CTRL_H_
#define _DAC_CTRL_H_

//����DAC������üĴ���
void DAC_Configuration(void);
//����DAC1�������ѹ
void DAC_SetValueAO1(u16 volt);
//����DAC2�������ѹ
void DAC_SetValueAO2(u16 volt);
//ȡ��DAC1��ǰ��ѹ
u16 DAC_GetValueAO1(void);
//ȡ��DAC2��ǰ��ѹ		
u16 DAC_GetValueAO2(void);

void DAC_SetOffset(u8 index,u16 offset);
#endif
