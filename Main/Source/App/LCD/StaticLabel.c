#include "StaticLabel.h"
#include "SWDataType.h"

void StaticLabelInit(const ST_StaticLabelScript* pScript,ST_StaticLabel *pVar)
{
	pVar->sign=pScript->ShowStyle|SW_INVALIDATE;
	pVar->timer = 0;
}

u16 StaticLabelCheck(const ST_StaticLabelScript* pScript,ST_StaticLabel *pVar,SW_ProcessMsg *pMsg)
{
	if(pScript->ShowStyle&SW_FLASH)
	{
		if(pMsg->timeup)
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

void StaticLabelDraw(const ST_StaticLabelScript* pScript,ST_StaticLabel *pVar)
{
	GUI_RECT rect;
	if((pVar->sign&SW_INVALIDATE)&&(!(pVar->sign&(SW_HIDE|SW_FLASH_HIDE))))
	{	
		rect.x0 = pScript->rect.x0;
		rect.y0 = pScript->rect.y0;
		rect.x1 = pScript->rect.x1;
		rect.y1 = pScript->rect.y1;

		CtrlDrawFrame(pScript->frame.Style,&rect,GetShareColor(pScript->frame.ColorIndex),0);
		CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex),GetShareString(pScript->LabelIndex));
		
	}
	pVar->sign&=(~SW_INVALIDATE);
}
