#include "StateShow.h"

void StateShowInit(const ST_StateShowScript* pScript,ST_StateShow* pVar)
{
	pVar->sign=pScript->ShowStyle|SW_INVALIDATE;
	pVar->value = 0;
	pVar->timer = 0;
}

u16 StateShowCheck(const ST_StateShowScript* pScript,ST_StateShow* pVar,SW_ProcessMsg* pMsg)
{
	u16 tmp;
	if(pScript->ParStyle)
		tmp = FORE_GetIO(pScript->ParIndex);
	else
		tmp = FORE_GetBuf(pScript->ParIndex);
	if(pVar->value!=tmp)
	{
		pVar->sign|=SW_INVALIDATE;
		pVar->value = tmp;
	}

	if(pScript->ShowStyle&SW_FLASH)
	{
		if(!pVar->value&&(pScript->ShowStyle&SW_TRUE_FLASH))
		{
	    if(pScript->ShowStyle&SW_STATIC_HIDE)
			{	
				pVar->sign|=SW_FLASH_HIDE;
			}
			else
			{
				pVar->sign&=(~SW_FLASH_HIDE);
			}
		}
		else if(pMsg->timeup)
				 {
						if(pVar->timer==0)
						{
							pVar->timer = pScript->ShowDelay;	//重置闪烁延时
							pVar->sign|=SW_INVALIDATE;			//要求重画
							pVar->sign^=SW_FLASH_HIDE;			//取反向显示
						}
						else
						pVar->timer--;
				 }
	}
	return 0;
}

void StateShowDraw(const ST_StateShowScript* pScript,ST_StateShow* pVar)
{
	GUI_RECT rect;
	if((pVar->sign&SW_INVALIDATE)&&(!(pVar->sign&(SW_HIDE|SW_FLASH_HIDE))))
	{
		rect.x0 = pScript->rect.x0;
		rect.y0 = pScript->rect.y0;
		rect.x1 = pScript->rect.x1;
		rect.y1 = pScript->rect.y1;

		CtrlDrawFrame(pScript->frame.Style,&rect,
			GetShareColor(pScript->frame.ColorIndex+MyMin(pVar->value,pScript->frame.ColorMax)),pVar->value);
		CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex+MyMin(pVar->value,pScript->FontMax)),
			GetShareString(pScript->LabelIndex+MyMin(pVar->value,pScript->LabelMax)));
	}
	pVar->sign&=(~SW_INVALIDATE);
}

