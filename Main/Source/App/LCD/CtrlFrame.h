#ifndef _CTRLFRAME_H_
#define _CTRLFRAME_H_

#include "Interface.h"

void CtrlDrawFrame(u16 DrawStyle,GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state);
void CtrlDrawText(GUI_RECT* pRect,const ST_LabelFont* pFont,const u8* pStr);

#endif
