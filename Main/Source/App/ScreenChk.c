#include "ScreenChk.h"
#include "ili9320.h"
#include "SWManage.h"

static u16 ChkPixel = 0;
static u16 LastChk = 0;
static u16 ErroCnt = 0;

void ScreenCheck()
{
	ili9320_SetPoint(0,0,ChkPixel);
	if(ili9320_GetPoint(0,0)!=LastChk)
		ErroCnt++;
	else
		ErroCnt = 0;

	if(ErroCnt>=10)
	{
		ErroCnt = 0;
		ili9320_Initializtion();
		SWRedraw();
	}
			
	LastChk = ChkPixel;
	ChkPixel++;
}
