#include "LCDPLC.h"

#ifndef _TOUCH_SCREEN_H_
#define _TOUCH_SCREEN_H_

//配置与触摸芯片通讯的SPI接口
void TScr_Configuration(void);
//实始化触摸管理相关变量
void TScr_Init(void);
//定时检查触摸状态
void TScr_Check(void);
//取得X坐标
u16 TScr_GetX(void);
//取得Y坐标
u16 TScr_GetY(void);

#endif
