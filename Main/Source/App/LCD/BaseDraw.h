#ifndef _BASEDRAW_H_
#define _BASEDRAW_H_

#include "Interface.h"

//ɫ�ʱ��u32
#if (LCD_SWAP_RB==0)
	#define MRGB(b,g,r) ((u32)(((u8)(r)|((u16)((u8)(g))<<8))|(((u32)(u8)(b))<<16)))
#else
	#define MRGB(r,g,b) ((u32)(((u8)(r)|((u16)((u8)(g))<<8))|(((u32)(u8)(b))<<16)))
#endif
//������ɫ��ǳ
u32 BrightColor(u32 color,s16 step);
u32 BrightRed(u32 color,s16 step);
u32 BrightGreen(u32 color,s16 step);
u32 BrightBlue(u32 color,s16 step);

//��3D�߿�
void Draw3DRect(const GUI_RECT *rect,u32 leftup,u32 rightdn,u8 height);

void DrawXPFrame(const GUI_RECT *rect);

#endif


