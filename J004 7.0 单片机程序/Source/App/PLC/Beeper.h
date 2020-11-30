#ifndef _BEEPER_H_
#define _BEEPER_H_

#include "LCDPLC.h"

#define REMIND_BEEP 100
//设置鸣叫时间长度
void BEEP_SetBeeper(u16 count);
//定时管理蜂鸣器
void BEEP_Check(void);
#define BEEP_ON() (GPIOC->BSRR = GPIO_Pin_0)
#define BEEP_OFF() (GPIOC->BRR = GPIO_Pin_0)

#endif
