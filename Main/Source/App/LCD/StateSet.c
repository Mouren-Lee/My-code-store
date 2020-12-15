#include "StateSet.h"
#include "Beeper.h"

static u8  bushu;
	
void StateSetInit(const ST_StateSetScript* pScript,ST_StateSet* pVar)
{
	pVar->sign=pScript->ShowStyle|SW_INVALIDATE;
	pVar->value = 0;
	pVar->timer = 0;
}

void StateSetValue(const ST_StateSetScript* pScript,ST_StateSet* pVar)
{
	switch(pScript->SetStyle&STATE_STYLE_MASK)
	{
		case STATE_SET_REVERT:
			pVar->timer = pScript->Speed;
			pVar->value = 1;
			break;
		case STATE_SET_CONST:
			pVar->value = pScript->SetValue;
			break;
		case STATE_SET_INCREASE:
			pVar->timer = pScript->Speed;
			if((pScript->SetStyle&STATE_CYCLE)&&(pVar->value>=pScript->SetMax))
				pVar->value=pScript->SetMin;
			else
			{
				if((pScript->SetMax-pScript->SetValue)>pVar->value)
					pVar->value+=pScript->SetValue;
				else
					pVar->value=pScript->SetMax;
			}
			break;
		case STATE_SET_DESCEND:
			pVar->timer = pScript->Speed;
			if((pScript->SetStyle&STATE_CYCLE)&&(pVar->value<=pScript->SetMin))
				pVar->value=pScript->SetMax;
			else
			{
				if((pScript->SetMin+pScript->SetValue)<pVar->value)
					pVar->value-=pScript->SetValue;
				else
					pVar->value = pScript->SetMin;
			}
	}
}

u16 StateSetCheck(const ST_StateSetScript* pScript,ST_StateSet* pVar,SW_ProcessMsg* pMsg)
{
	u16 tmp;
	u8 isInRect;
	if(pScript->ParStyle)
		tmp = FORE_GetIO(pScript->ParIndex);
	else
		tmp = FORE_GetBuf(pScript->ParIndex);
	if(pVar->value!=tmp)
	{
		if(!(pScript->SetStyle&STATE_SHOW_PRESSED))
			pVar->sign|=SW_INVALIDATE;
		pVar->value = tmp;
	}
	
	if((pVar->sign&SW_TRUE_FLASH)&&(pVar->sign&SW_STATIC_HIDE))
	{
			if(pVar->value==2)
			{
				bushu=0;
			}	
			else	if(pVar->value==0)
							bushu=1;
	}
	
	if(pMsg->x>=pScript->rect.x0&&pMsg->x<=pScript->rect.x1&&pMsg->y>=pScript->rect.y0&&pMsg->y<=pScript->rect.y1)
		isInRect = 1;
	else
		isInRect = 0;

	if(isInRect&&(!(pVar->sign&SW_HIDE)))
	{
		if(pVar->sign&SW_TOUCH_PRESSED)		//已经按下
		{
			if(!(pMsg->TouchState&TOUCH_PRESSED))
			{
				pVar->sign&=(~SW_TOUCH_PRESSED);
				pVar->sign|=SW_INVALIDATE;
				if((pVar->sign&SW_TRUE_FLASH)&&(pVar->sign&SW_STATIC_HIDE)&&bushu==0)
					pVar->value = 2;                     //点退补数专用
				else if((pScript->SetStyle&STATE_STYLE_MASK)==STATE_SET_REVERT)
					pVar->value = 0;
			}
			else
			{
				if(pMsg->timeup)
				{
					if((pScript->SetStyle&STATE_KEEP)&&(pVar->timer!=65535))
					{
						if(pVar->timer)
							pVar->timer--;
						else
						{
							pVar->timer = pScript->Speed;
							StateSetValue(pScript,pVar);
							if(!(pScript->SetStyle&STATE_SHOW_PRESSED))
								pVar->sign|=SW_INVALIDATE;
						}
					}
				}
			}
		} 
		else if((pMsg->TouchState&TOUCH_CHG)&&(pMsg->TouchState&TOUCH_PRESSED))
		{//新按下的
			pVar->sign|=SW_TOUCH_PRESSED;
			pVar->sign|=SW_INVALIDATE;
			BEEP_SetBeeper(REMIND_BEEP);
			pVar->timer = pScript->Delay;
				if(!(pScript->SetStyle&STATE_DELAY))
					StateSetValue(pScript,pVar);
		}	
	}
	else
	{
		if(pVar->sign&SW_TOUCH_PRESSED)
		{
			pVar->sign|=SW_INVALIDATE;
			if((pVar->sign&SW_TRUE_FLASH)&&(pVar->sign&SW_STATIC_HIDE)&&bushu==0)
				pVar->value = 2;                              //点退补数专用
				else if((pScript->SetStyle&STATE_STYLE_MASK)==STATE_SET_REVERT)
				        pVar->value = 0;
		}
		pVar->sign&=(~SW_TOUCH_PRESSED);		
	}

	if(pVar->value!=(pScript->ParStyle?FORE_GetIO(pScript->ParIndex):FORE_GetBuf(pScript->ParIndex)))
	{
		if(pScript->ParStyle)
			FORE_SetIO(pScript->ParIndex,pVar->value);	
		else
			FORE_SetBuf(pScript->ParIndex,pVar->value);	
		
		if(!(pScript->SetStyle&STATE_SHOW_PRESSED))
			pVar->sign|=SW_INVALIDATE;
	}
	return 0;
}

void StateSetDraw(const ST_StateSetScript* pScript,ST_StateSet* pVar)
{
	GUI_RECT rect;
	u8 pressed = 0;
	if((pVar->sign&SW_INVALIDATE)&&(!(pVar->sign&(SW_HIDE|SW_FLASH_HIDE))))
	{
		rect.x0 = pScript->rect.x0;
		rect.y0 = pScript->rect.y0;
		rect.x1 = pScript->rect.x1;
		rect.y1 = pScript->rect.y1;

		if(pScript->SetStyle&STATE_SHOW_PRESSED)
		{
			if(pVar->sign&SW_TOUCH_PRESSED)
				pressed = 1;
			CtrlDrawFrame(pScript->frame.Style,&rect,
				GetShareColor(pScript->frame.ColorIndex+MyMin(pressed,pScript->frame.ColorMax)),pressed);
			CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex+MyMin(pressed,pScript->FontMax)),
				GetShareString(pScript->LabelIndex+MyMin(pressed,pScript->LabelMax)));
		}
		else
		{
			if((pVar->sign&SW_TRUE_FLASH)&&(pVar->sign&SW_STATIC_HIDE)&&(pVar->value==1)&&bushu)   //点退补数
			{
				CtrlDrawFrame(pScript->frame.Style,&rect,
					GetShareColor(pScript->frame.ColorIndex+MyMin(pVar->value,pScript->frame.ColorMax)),pVar->value);
				CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex),
			    GetShareString(pScript->LabelIndex));
			
			}
			else if((pVar->sign&SW_TRUE_FLASH)&&(pVar->sign&SW_STATIC_HIDE)&&(pVar->value==1)&&bushu==0)   //点退补数
			{
				CtrlDrawFrame(pScript->frame.Style+1,&rect,
					GetShareColor(pScript->frame.ColorIndex+MyMin(pVar->value,pScript->frame.ColorMax)),pVar->value);
				CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex+1),
			    GetShareString(pScript->LabelIndex+1));
			
			}
			else if((pVar->sign&SW_TRUE_FLASH)&&(pVar->sign&SW_STATIC_HIDE)&&(pVar->value==2))
			{	
				CtrlDrawFrame(pScript->frame.Style+1,&rect,
					GetShareColor(pScript->frame.ColorIndex),0);
				CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex+1),
			    GetShareString(pScript->LabelIndex+1));
			}
		  else if(pVar->sign&SW_STATIC_HIDE)            //追浅追深
			{
				CtrlDrawFrame(pScript->frame.Style+pVar->value,&rect,
					GetShareColor(pScript->frame.ColorIndex+MyMin(pVar->value,pScript->frame.ColorMax)),pVar->value);
				CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex+MyMin(pVar->value,pScript->FontMax)),
			    GetShareString(pScript->LabelIndex+MyMin(pVar->value,pScript->LabelMax)));
			}
			else  //大多数
			{
				CtrlDrawFrame(pScript->frame.Style,&rect,
					GetShareColor(pScript->frame.ColorIndex+MyMin(pVar->value,pScript->frame.ColorMax)),pVar->value);
				CtrlDrawText(&rect,GetShareLabelFont(pScript->FontIndex+MyMin(pVar->value,pScript->FontMax)),
					GetShareString(pScript->LabelIndex+MyMin(pVar->value,pScript->LabelMax)));
      }		

		}
	}


	pVar->sign&=(~SW_INVALIDATE);
}
