#ifndef _BEEPER_H_
#define _BEEPER_H_

#include "LCDPLC.h"

#define REMIND_BEEP 100
//��������ʱ�䳤��
void BEEP_SetBeeper(u16 count);
//��ʱ���������
void BEEP_Check(void);
#define BEEP_ON() (GPIOC->BSRR = GPIO_Pin_0)
#define BEEP_OFF() (GPIOC->BRR = GPIO_Pin_0)

#endif
