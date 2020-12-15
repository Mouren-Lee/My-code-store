#include "ValueShow.h"
#include "SWManage.h"
#include "Beeper.h"


void ValueShowInit(const ST_ValueShowScript* pScript,ST_ValueShow* pVar)
{
	pVar->sign=pScript->ShowStyle|SW_INVALIDATE;
	pVar->value = 0;
}


u16 ValueShowCheck(const ST_ValueShowScript* pScript,ST_ValueShow* pVar,SW_ProcessMsg* pMsg)
{
	u16 tmp;
	u8 isInRect;

	if(pScript->value.ParStyle)
		tmp = FORE_GetIO(pScript->value.ParIndex);
	else
		tmp = FORE_GetBuf(pScript->value.ParIndex);

	if(pVar->value!=tmp)
	{
		pVar->sign|=SW_INVALIDATE;
		pVar->value = tmp;
	}
	if(pScript->Flags&SW_ENABLE_EDIT)
	{
		if(pMsg->x>=pScript->rect.x0&&pMsg->x<=pScript->rect.x1&&pMsg->y>=pScript->rect.y0&&pMsg->y<=pScript->rect.y1)
			isInRect = 1;
		else
			isInRect = 0;

		if(isInRect&&(pMsg->TouchState&TOUCH_CHG)&&(pMsg->TouchState&TOUCH_PRESSED))
		{
			BEEP_SetBeeper(REMIND_BEEP);
			SWOpenWindow(WININPUT_INDEX);
			SetInputValue(&(pScript->value),0);
		}
	}
	return 0;
}

void ValueShowDraw(const ST_ValueShowScript* pScript,ST_ValueShow* pVar)
{
	#define MAXCHARSIZE 16
	u8 Str[MAXCHARSIZE];
	GUI_RECT rect;
	const ST_FormatScript* pFormat;

	pFormat = &(pScript->value.FormatScript);

	if((pVar->sign&SW_INVALIDATE)&&(!(pVar->sign&(SW_HIDE|SW_FLASH_HIDE))))
	{
		rect.x0 = pScript->rect.x0;
		rect.y0 = pScript->rect.y0;
		rect.x1 = pScript->rect.x1;
		rect.y1 = pScript->rect.y1;

		CtrlDrawFrame(pScript->frame.Style,&rect,GetShareColor(pScript->frame.ColorIndex),0);
		Value2Str(Str,Value2Show(pVar->value,pFormat),pFormat);
		Str[MAXCHARSIZE-1]=0;	//保护一下
		CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex),Str);	
	}
	pVar->sign&=(~SW_INVALIDATE);
}
