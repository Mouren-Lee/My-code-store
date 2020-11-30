#include "TouchCheck.h"
#include "Beeper.h"

static u8 LastState = 0;


void TouchCheck(SW_ProcessMsg* pMsg)
{
	GUI_PID_STATE State;	
	u8 CurState;

    GUI_TOUCH_GetState(&State);

	pMsg->TouchState = 0;
	if(State.Pressed)
	{
		CurState = TOUCH_PRESSED;
		pMsg->TouchState|=TOUCH_PRESSED;
	}
	else
	{
		CurState = 0;
		pMsg->TouchState&=(~TOUCH_PRESSED);
	}

	if(CurState^LastState)
		pMsg->TouchState|=TOUCH_CHG;
	
	LastState = CurState;


	pMsg->x = State.x;
	pMsg->y = State.y;
}
