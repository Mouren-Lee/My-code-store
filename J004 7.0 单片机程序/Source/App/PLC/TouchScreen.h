#include "LCDPLC.h"

#ifndef _TOUCH_SCREEN_H_
#define _TOUCH_SCREEN_H_

//�����봥��оƬͨѶ��SPI�ӿ�
void TScr_Configuration(void);
//ʵʼ������������ر���
void TScr_Init(void);
//��ʱ��鴥��״̬
void TScr_Check(void);
//ȡ��X����
u16 TScr_GetX(void);
//ȡ��Y����
u16 TScr_GetY(void);

#endif
