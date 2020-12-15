#include "FunctionSet.h"
#include "SWManage.h"
#include "Beeper.h"


void FunOpenWindow(u16 CmdID,const ST_PARAM* pParam)
{
	SWOpenWindow(CmdID);
}

void OpenSaveWindow(u16 CmdID,const ST_PARAM* pParam)
{
	SWOpenWindow(CmdID);
	PIPE_SaveFlash();
}

void FunCloseCurWindow(u16 CmdID,const ST_PARAM* pParam)
{
	SWCloseCurrentWin();
}



void FunctionSetInit(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar)
{
	pVar->sign=pScript->ShowStyle|SW_INVALIDATE;
}

u16 FunctionSetCheck(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar,SW_ProcessMsg* pMsg)
{
	u8 isInRect;
	if(pMsg->x>=pScript->rect.x0&&pMsg->x<=pScript->rect.x1&&pMsg->y>=pScript->rect.y0&&pMsg->y<=pScript->rect.y1)
		isInRect = 1;
	else
		isInRect = 0;
	
	if(isInRect&&(!(pVar->sign&SW_HIDE)))
	{
		if(pVar->sign&SW_TOUCH_PRESSED)
		{
			if(pVar->timer!=0)
			{
				if(pMsg->timeup)
				{
					pVar->timer--;
					if(pVar->timer==0)
					{
						if(pScript->pCallBack!=NULL)
						{
							pScript->pCallBack(pScript->CmdID,&(pScript->Param));
							BEEP_SetBeeper(REMIND_BEEP);							//ÌáÊ¾Òô
						}
					}
				}
			}
			if(!(pMsg->TouchState&TOUCH_PRESSED))
			{
				pVar->sign&=(~SW_TOUCH_PRESSED);
				pVar->sign|=SW_INVALIDATE;
				
			}
		}
		else if((pMsg->TouchState&TOUCH_CHG)&&(pMsg->TouchState&TOUCH_PRESSED))
		{
			pVar->sign|=SW_TOUCH_PRESSED;
			pVar->sign|=SW_INVALIDATE;
			BEEP_SetBeeper(REMIND_BEEP);
			pVar->timer = pScript->Delay;
			if((!pScript->Delay)&&(pScript->pCallBack!=NULL))
				pScript->pCallBack(pScript->CmdID,&(pScript->Param));
		}
	}
	else
	{
		if(pVar->sign&SW_TOUCH_PRESSED)
			pVar->sign|=SW_INVALIDATE;
		pVar->sign&=(~SW_TOUCH_PRESSED);
	}
	return 0;
}

void FunctionSetDraw(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar)
{
	
	GUI_RECT rect;
	u8 pressed = 0;
	if((pVar->sign&SW_INVALIDATE)&&(!(pVar->sign&(SW_HIDE|SW_FLASH_HIDE))))
	{
		rect.x0 = pScript->rect.x0;
		rect.y0 = pScript->rect.y0;
		rect.x1 = pScript->rect.x1;
		rect.y1 = pScript->rect.y1;

		if(pVar->sign&SW_TOUCH_PRESSED)
			pressed = 1;
		CtrlDrawFrame(pScript->frame.Style,&rect,
				GetShareColor(pScript->frame.ColorIndex+MyMin(pressed,pScript->frame.ColorMax)),pressed);
		CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex+MyMin(pressed,pScript->FontMax)),
				GetShareString(pScript->LabelIndex+MyMin(pressed,pScript->LabelMax)));
	}
	pVar->sign&=(~SW_INVALIDATE);
}
