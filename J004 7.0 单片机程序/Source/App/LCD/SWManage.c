#include "SWManage.h"
#include "SWDatatype.h"
#include "SWWindow.h"

#define WINDOWCNT (sizeof(pWinScript)/sizeof(SW_SingleWindowScript*))

static u16 dCurWindow;
static SW_SingleWindow windows[WINDOWCNT];

void SWManageInit(void)
{
	s16 i;
	
	for(i=0;i<WINDOWCNT;i++)
	{
		DefaultInit(&(windows[i]),pWinScript[i]);
		windows[i].Order = 0;
	}

	dCurWindow = WINMAIN;
	windows[WINMAIN].Order = 1;
}

void SWManageCheck(SW_ProcessMsg* pMsg)
{
	if(dCurWindow<WINDOWCNT)
	(windows[dCurWindow].pScript->pCallback)(windows+dCurWindow,pMsg);
}

void SWOpenWindow(u16 index)
{
	s16 i;
	s16 tmp;
	if(index>=WINDOWCNT)return;
	//查找对应窗口是否在已队列中
	if(windows[index].Order!=0)	//已显示
		tmp = windows[index].Order;
	else
		tmp = WINDOWCNT;	//所有都加1

	for(i=0;i<WINDOWCNT;i++)
	{
		if(windows[i].Order!=0&&windows[i].Order<tmp)
			windows[i].Order++;
	}
	windows[index].Order = 1;
	windows[index].sign|=SW_INVALIDATE;
	dCurWindow = index;
}

void SWRedraw()
{
	windows[dCurWindow].sign|=SW_INVALIDATE;
}

void SWCloseCurrentWin()
{
	s16 i;
	for(i=0;i<WINDOWCNT;i++)
	{
		if(windows[i].Order!=0)
			windows[i].Order--;
		if(windows[i].Order==1)
			dCurWindow = i;
	}
	windows[dCurWindow].sign|=SW_INVALIDATE;
}

u16 SWReturnWin(void)
{
	if(dCurWindow<=WINDOWCNT)
		return dCurWindow;
	else
		return WINDOW00_INDEX;
}


