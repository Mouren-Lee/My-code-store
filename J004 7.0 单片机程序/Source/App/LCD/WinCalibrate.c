#include "Interface.h"
#include "Beeper.h"

#define AIM_WIDTH 25
#define  AIM_CENTER (AIM_WIDTH>>1)

#define CHECK_MISTAK_MAX 80

static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1) {
  return p0+ ((p1 - p0) * (l - l0)) / (l1 - l0);
} 

#define CHECK_SIZE 4

static const u16 ObjectPosX[CHECK_SIZE] = {
100,LCD_XSIZE-100,100,LCD_XSIZE-100,
};

static const u16 ObjectPosY[CHECK_SIZE] = {
LCD_YSIZE-100,100,100,LCD_YSIZE-100,
};

static u8 CaliStep = 0;

static void DrawAim(u16 x,u16 y)
{
	GUI_SetColor(MRGB(255,0,0));
	GUI_DrawRect(x-AIM_WIDTH,y-1,x+AIM_WIDTH,y+1);
	GUI_DrawRect(x-1,y-AIM_WIDTH,x+1,y+AIM_WIDTH);
	
	GUI_DrawRect(x-AIM_CENTER-1,y-AIM_CENTER-1,x+AIM_CENTER+1,y+AIM_CENTER+1);
	GUI_DrawRect(x-AIM_CENTER+1,y-AIM_CENTER+1,x+AIM_CENTER-1,y+AIM_CENTER-1);
	GUI_SetColor(MRGB(255,255,255));
	GUI_DrawLine(x-AIM_WIDTH+1,y,x+AIM_WIDTH-1,y);
	GUI_DrawLine(x,y-AIM_WIDTH+1,x,y+AIM_WIDTH-1);
}

#define ARRAY 4
#define BUFSIZE (1<<ARRAY)
#define PTMASK ((1<<ARRAY)-1)
#define MISTAKEMAX 60

static u16 PressX[BUFSIZE];
static u16 PressY[BUFSIZE];
static u16 PressPt=0;
static u8 Pressed;
static u8 AimDrawed;

#define CHECK_PRESSED BIT0
#define CHECK_DONE BIT1

static u16 CheckPosX;
static u16 CheckPosY;

static u16 RealPosX[CHECK_SIZE];
static u16 RealPosY[CHECK_SIZE];



#define CHECKDELAY 5
static u8 Touch_WaitPress(SW_ProcessMsg* pMsg)
{
	u32 tmpX;
	u32 tmpY; 
	u32 Mistake;
	u16 i;
	GUI_PID_STATE State;

	if(!(pMsg->timeup))
		return 0;

	pMsg->timeup = 0;


	GUI_TOUCH_GetState(&State);
	if(State.Pressed)
	{
		if(!(Pressed&CHECK_PRESSED))
		{
			PressPt = 0;
		}
		Pressed |= CHECK_PRESSED;		

		PressX[PressPt&PTMASK] = GUI_TOUCH_GetyPhys();			   //XY有个交换
	   	PressY[PressPt&PTMASK] = GUI_TOUCH_GetxPhys(); 
	
		if(PressPt==0xFFFF)
			PressPt = BUFSIZE;
		else
			PressPt++;					

		if((PressPt>=BUFSIZE)&&(!(Pressed&CHECK_DONE)))
		{
			tmpX = ((1<<ARRAY)>>1);
	   		tmpY = ((1<<ARRAY)>>1);
			for(i=0;i<BUFSIZE;i++)
			{
				tmpX+=PressX[i];
				tmpY+=PressY[i];
			}
			CheckPosX=tmpX>>ARRAY;
			CheckPosY=tmpY>>ARRAY;
			Mistake = 0;
		   	for(i=0;i<BUFSIZE;i++)
			{
				if(CheckPosX>PressX[i])
					Mistake+=(CheckPosX-PressX[i]);
				else
					Mistake+=(PressX[i]-CheckPosX);
				
				if(CheckPosY>PressY[i])
					Mistake+=(CheckPosY-PressY[i]);
				else
					Mistake+=(PressY[i]-CheckPosY);				
			}
	
			if(Mistake<MISTAKEMAX)
			{
				BEEP_SetBeeper(REMIND_BEEP);
				Pressed|=CHECK_DONE;				
			}
		}	
	}
	else
	{
		if(Pressed&CHECK_PRESSED)
		{
			Pressed &= (~CHECK_PRESSED); 
			if(Pressed&CHECK_DONE)
			{	
				Pressed = 0;
				return 1;
			}
		}
		Pressed=0;
	}
	return 0;
}

static void drawbackground(SW_SingleWindow* pWin)
{
	GUI_RECT rect;

	GUI_SetBkColor(MRGB(250,250,250));  
  	GUI_Clear();
	GUI_SetFont(&GUI_FontHZAIM_24);
	GUI_SetColor(MRGB(0,0,0));
	rect.x0 = 0;
	rect.y0 = 200;
	rect.x1 = LCD_XSIZE-1;
	rect.y1 = 300;
	GUI_DispStringInRect("请按住十字中心\n直到嘀的一声",&rect,GUI_TA_CENTER|GUI_TA_TOP);
}


static void WinCaliProc(SW_SingleWindow* pWin,SW_ProcessMsg* pMsg)
{ 
	int Phs0,Phs1;
	u16 pos,i;
	u16 mistake;
	u16 tmp0,tmp1;
	GUI_RECT rect;

	if(pWin->sign&SW_INVALIDATE)
	{
		CaliStep = 0;
		AimDrawed = 0;		
	}	
	switch(CaliStep)
	{
		case 0:
			if(!(pMsg->TouchState&TOUCH_PRESSED))
			{		
				CaliStep = 1;
				drawbackground(pWin);								
			}
			break;
		case 1:
		case 2:	
			pos = CaliStep-1;		
			if(!AimDrawed)
			{
				AimDrawed = 1;
				if(pos<CHECK_SIZE)
					DrawAim(ObjectPosX[pos],ObjectPosY[pos]);	
			}
			if(Touch_WaitPress(pMsg))
			{
			
				RealPosX[pos] = CheckPosX;
				RealPosY[pos] = CheckPosY;
				if(pos<CHECK_SIZE)
					GUI_ClearRect(ObjectPosX[pos]-AIM_WIDTH,ObjectPosY[pos]-AIM_WIDTH,ObjectPosX[pos]+AIM_WIDTH,ObjectPosY[pos]+AIM_WIDTH);
				
				AimDrawed = 0;

				if(CaliStep==2)
				{
					GUI_TOUCH_Calibrate(GUI_COORD_X, ObjectPosX[0], ObjectPosX[1],RealPosX[0],RealPosX[1]);
					GUI_TOUCH_Calibrate(GUI_COORD_Y, ObjectPosY[0], ObjectPosY[1],RealPosY[0],RealPosY[1]);
				}								
				CaliStep++;
			}			
			break;
		case 3:
		case 4:
			pos = CaliStep-1;		
			if(!AimDrawed)
			{
				AimDrawed = 1;
				if(pos<CHECK_SIZE)
					DrawAim(ObjectPosX[pos],ObjectPosY[pos]);	
			}
			if(Touch_WaitPress(pMsg))
			{
				RealPosX[pos] = CheckPosX;
				RealPosY[pos] = CheckPosY;				
				if(pos<CHECK_SIZE)
					GUI_ClearRect(ObjectPosX[pos]-AIM_WIDTH,ObjectPosY[pos]-AIM_WIDTH,ObjectPosX[pos]+AIM_WIDTH,ObjectPosY[pos]+AIM_WIDTH);
				AimDrawed = 0;
				
				if(CaliStep == 4)
				{
					mistake = 0;
					GUI_TOUCH_GetCalData(0,&Phs0,&Phs1);
					for(i=2;i<4;i++)
					{
						tmp0 = _Log2Phys(ObjectPosX[i],0,LCD_XSIZE,Phs0,Phs1);
						if(tmp0>RealPosX[i])
							pos =(tmp0-RealPosX[i]);
						else
							pos =(RealPosX[i]-tmp0);
						if(pos>mistake)
							mistake = pos;
					}

					GUI_TOUCH_GetCalData(1,&Phs0,&Phs1);
					for(i=2;i<4;i++)
					{
						tmp1 = _Log2Phys(ObjectPosY[i],0,LCD_YSIZE,Phs0,Phs1);
						if(tmp1>RealPosY[i])
							pos =(tmp1-RealPosY[i]);
						else
							pos =(RealPosY[i]-tmp1);
						if(pos>mistake)
							mistake = pos;
					}

					if(pos>CHECK_MISTAK_MAX)
					{									
						//恢复数据
						GUI_TOUCH_SetDefaultCalibration();
						GUI_SetBkColor(MRGB(250,250,250));  
					  	GUI_Clear();
						
						GUI_SetFont(&GUI_FontHZAIM_24);
						GUI_SetColor(MRGB(255,64,64));
						rect.x0 = 0;
						rect.y0 = 200;
						rect.x1 = LCD_XSIZE-1;
						rect.y1 = 300;
						GUI_DispStringInRect("未能正确校准\n请点屏幕重试",&rect,GUI_TA_CENTER|GUI_TA_TOP);					
					}
					else
					{
						//保存数据到BKP
						GUI_TOUCH_GetCalData(0,&Phs0,&Phs1);
						FORE_SetBuf(PIPE_CALIBRATE_X0,Phs0);
						FORE_SetBuf(PIPE_CALIBRATE_X1,Phs1);

						GUI_TOUCH_GetCalData(1,&Phs0,&Phs1);
						FORE_SetBuf(PIPE_CALIBRATE_Y0,Phs0);
						FORE_SetBuf(PIPE_CALIBRATE_Y1,Phs1);
						
						SWCloseCurrentWin();	
					}
				}
				CaliStep++;
			}
			break;
		case 5:
			if((pMsg->TouchState&TOUCH_CHG)&&(pMsg->TouchState&TOUCH_PRESSED))
					CaliStep = 0;		
			
			break;
		default:
			CaliStep = 0;   					
	}

	pWin->sign&=(~SW_INVALIDATE);
}

static void WinCaliProc0(void* pWin,SW_ProcessMsg* pMsg)
{
	WinCaliProc(pWin,pMsg);
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}

const SW_SingleWindowScript WinCalibrate={
	0,
	0,
	GUI_LIGHTGRAY,
	WinCaliProc0,
	drawbackground0,
};
