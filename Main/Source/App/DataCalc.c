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

static u16 dLastLength;		//ǰ���ϳ��� 
static u16 dLastSpeed;		//ǰ�趨�ٶ�
static u16 dLastDuty;		//ǰ�ε�ռ�ձ��� 
static u16 dLastStyle;
static u16 dAutoD;			//����õ����Զ������ٶ�
static u16 dAutoTop;
static u16 dLastAutoAccPar;

static u16 dLastRoller;		//ǰ����ֱ��
static u16 dLastCycle;		//ǰ��Ȧ����
static u16 dLastMark;		//ǰɫ�귶Χ
static u16 dLastyutui;		
static u16 dLasthuisuo;	
static u16 dLastpenjiao;	
static u16 dLastDangLiang;	
void DataCalc()
{
	u32 tmp,tmp1,tmp2,tmp3;
	u16 mid;
		u8 bCalcD = 0;
  	u16 midSpeed;		//�趨�ٶ�
  	u16 midStyle;
	 	u16 midDuty;		//ռ�ձ���
    u16 midAutoAccPar;
		u16 seekcnt;
		u16 midLength;		//�趨����
	
	u16 midRoller;		//����ֱ��
	u16 midCycle;		//��Ȧ����
	u16 midKm;			//����ϵ��
	u16 midMark;		//ɫ�귶Χ
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

  	curday = USART1_GetBuf(RIQITIME);					   //��ȡĿǰʵ����
  	if(curday!=USART1_GetBuf(LASTDAY)) 			
   	{
		   daycnt = USART1_GetBuf(SYSTEM1_Time); //��ȡϵͳ1(PIPE_SYSTEM1)
	    if(daycnt!=0)						   //mainwork.c
	   	 {
		     daycnt--;							   //ϵͳ1��1
		     USART1_SetBuf(SYSTEM1_Time,daycnt); //�Ž�ϵͳ1
		   }
			 
			 USART1_SetBuf(LASTDAY,curday);       //Ŀǰʵ�ʵ��շŽ��ϴα����
   	}
  	
}
