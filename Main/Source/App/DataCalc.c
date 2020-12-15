//#include "Interface.h"
#include "PIPE.h"
#include "realtimer.h"
#include "PipeData.h"
#include "MainWork.h"
#include "USART1.h"


int f;
 u8 MaiChongDangLiang_flag = 0;
static u8 bInitialed = 0;

static u16 dStartF,dStartF2;
static u16 dTopF,dTopF2;
static u16 dStopF,dStopF2;
static u16 dTopY,dTopH;

static u16 dLastLength;		//前材料长度 
static u16 dLastSpeed;		//前设定速度
static u16 dLastDuty;		//前次的占空比例 
static u16 dLastStyle;
static u16 dAutoD;			//计算得到的自动送料速度
static u16 dAutoTop;
static u16 dLastAutoAccPar;

static u16 dLastRoller;		//前胶辊直径
static u16 dLastCycle;		//前整圈步数
static u16 dLastMark;		//前色标范围
static u16 dLastyutui;		
static u16 dLasthuisuo;	
static u16 dLastpenjiao;	
static u16 dLastDangLiang;	
void DataCalc()
{
	u32 tmp,tmp1,tmp2,tmp3;
	u16 mid;
		u8 bCalcD = 0;
  	u16 midSpeed;		//设定速度
  	u16 midStyle;
	 	u16 midDuty;		//占空比例
    u16 midAutoAccPar;
		u16 seekcnt;
		u16 midLength;		//设定长度
	
	u16 midRoller;		//胶辊直径
	u16 midCycle;		//整圈步数
	u16 midKm;			//主机系数
	u16 midMark;		//色标范围
	u16 midyutui;
	u16 midhuisuo;
  u16 midpenjiao;
	u16 midDangLiang;


//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////	




  dLastStyle = midStyle;
 	dLastSpeed = midSpeed;		
 	dLastDuty = midDuty;
	dLastAutoAccPar=midAutoAccPar;
  dLastLength=midLength;

	dLastRoller = midRoller;
	dLastCycle = midCycle;
	dLastMark = midMark;
	dLastyutui=midyutui;
	dLasthuisuo=midhuisuo;
  dLastpenjiao=midpenjiao;
  dLastDangLiang=midDangLiang;

	bInitialed = 1;
}

void Accredit()
{
	u16 curday;
	u16 daycnt;

  	curday = USART1_GetBuf(RIQITIME);					   //获取目前实际日
  	if(curday!=USART1_GetBuf(LASTDAY)) 			
   	{
		   daycnt = USART1_GetBuf(SYSTEM1_Time); //获取系统1(PIPE_SYSTEM1)
	    if(daycnt!=0)						   //mainwork.c
	   	 {
		     daycnt--;							   //系统1减1
		     USART1_SetBuf(SYSTEM1_Time,daycnt); //放进系统1
		   }
			 
			 USART1_SetBuf(LASTDAY,curday);       //目前实际的日放进上次保存的
   	}
  	
}
