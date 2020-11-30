#include "LCDPLC.h"

#ifndef _TOUCH_SCREEN_H_
#define _TOUCH_SCREEN_H_

void TScr_Configuration(void);
void TScr_Init(void);
void TScr_Check(void);
u16 TScr_GetX(void);
u16 TScr_GetY(void);

#endif
