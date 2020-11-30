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
	
	midSpeed = USART1_GetBuf(SPEED_SET);
	midDuty = USART1_GetBuf(DUTY);
	midAutoAccPar=USART1_GetBuf(AutoAccPar);	
	midLength = USART1_GetBuf(MATERIAL_LENGTH);
	

	midMark = USART1_GetBuf(MARK_WIDTH_LENGTH)*10;
	midyutui = USART1_GetBuf(YUTUI_LENGTH);
	midhuisuo = USART1_GetBuf(HUISUO_LENGTH);
	midpenjiao = USART1_GetBuf(DuanJiao_LENGTH);
	
	midDangLiang = USART1_GetBuf(MaiChongDangLiang1);
	//////////////////////////////////////////////////////////////  ��������
	
	  if(USART1_GetIO(USART_MaiChongJiaoZhun)==1&&MaiChongDangLiang_flag==0)
		{
			tmp = midDangLiang*midLength;
			tmp = tmp/USART1_GetBuf(ShiJi_LENGTH1);
			USART1_SetBuf(MaiChongDangLiang1,tmp);    
      MaiChongDangLiang_flag=1;			
		}
		else if(MaiChongDangLiang_flag==1&&USART1_GetIO(USART_MaiChongJiaoZhun)==0)
		{
			MaiChongDangLiang_flag=0;
		}
		
	////////////////////////////////////////////////////////////////////
		
 if((!bInitialed)||(midDangLiang!=dLastDangLiang)||(dLastLength!=midLength))
	{
			tmp = midLength*midDangLiang;
			tmp = tmp/1000;
			USART1_SetBuf(LENGTH_CNT,tmp);           
			bCalcD = 1;
	
	}
		
		
 if((!bInitialed)||(midDangLiang!=dLastDangLiang)||(dLastMark!=midMark))
	{
			tmp = midMark*midDangLiang;
			tmp = tmp/1000;
			USART1_SetBuf(MARK_WIDTH_CNT,tmp);           
			bCalcD = 1;
	}		

 if((!bInitialed)||(midDangLiang!=dLastDangLiang)||(dLastyutui!=midyutui))
	{
			tmp = midyutui*midDangLiang;
			tmp = tmp/1000;
			USART1_SetBuf(YUTUI_CNT,tmp);           
			bCalcD = 1;
	}

 if((!bInitialed)||(midDangLiang!=dLastDangLiang)||(dLasthuisuo!=midhuisuo))
	{
			tmp = midhuisuo*midDangLiang;
			tmp = tmp/1000;
			USART1_SetBuf(HUISUO_CNT,tmp);           
			bCalcD = 1;
	}
	
 if((!bInitialed)||(midDangLiang!=dLastDangLiang)||(dLastpenjiao!=midpenjiao))
	{
			tmp = midpenjiao*midDangLiang;
			tmp = tmp/1000;
			USART1_SetBuf(DuanJiao_CNT,tmp);           
			bCalcD = 1;
	}

	
//	
//	 	if((!bInitialed)||(midRoller!=dLastRoller)
//		||(midCycle!=dLastCycle)||(dLastLength!=midLength))
//	{
//		if(midRoller!=0)
//		{
//			tmp = midLength*midCycle+(midRoller>>1);
//			tmp = tmp/midRoller;
//			if(tmp>65535)
//				tmp = 65535;
//			USART1_SetBuf(LENGTH_CNT,tmp);           
//			bCalcD = 1;
//		}
//	}
// 
//	//---------------------------------------------------	
//	if((!bInitialed)||(midRoller!=dLastRoller)
//		||(midCycle!=dLastCycle)||(dLastMark!=midMark))
//	{
//		if(midRoller!=0)
//		{
//			tmp = midMark*midCycle+(midRoller>>1);
//			tmp = tmp/midRoller;
//			if(tmp>65535)
//				tmp = 65535;
//			USART1_SetBuf(MARK_WIDTH_CNT,tmp);
//			bCalcD = 1;
//		}
//	}	
//	
//	
//		if((!bInitialed)||(midRoller!=dLastRoller)  //Ԥ��
//		||(midCycle!=dLastCycle)||(dLastyutui!=midyutui))
//	{
//		if(midRoller!=0)
//		{
//			tmp = midyutui*midCycle+(midRoller>>1);
//			tmp = tmp/midRoller;
//			if(tmp>65535)
//				tmp = 65535;
//			USART1_SetBuf(YUTUI_CNT,tmp);           
//			bCalcD = 1;
//			
//	
//			
//			
//			
//		}
//	}
//	
//		if((!bInitialed)||(midRoller!=dLastRoller)//����
//		||(midCycle!=dLastCycle)||(dLasthuisuo!=midhuisuo))
//	{
//		if(midRoller!=0)
//		{
//			tmp = midhuisuo*midCycle+(midRoller>>1);
//			tmp = tmp/midRoller;
//			if(tmp>65535)
//				tmp = 65535;
//			USART1_SetBuf(HUISUO_CNT,tmp);           
//			bCalcD = 1;
//		}
//	}
//	
//	if((!bInitialed)||(midRoller!=dLastRoller)//�罺
//		||(midCycle!=dLastCycle)||(dLastpenjiao!=midpenjiao))
//	{
//		if(midRoller!=0)
//		{
//			tmp = midpenjiao*midCycle+(midRoller>>1);
//			tmp = tmp/midRoller;
//			if(tmp>65535)
//				tmp = 65535;
//			USART1_SetBuf(DuanJiao_CNT,tmp);           
//			bCalcD = 1;
//		}
//	}
//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////	
	mid = USART1_GetBuf(TOP_FrequencyCP1);	
	if((!bInitialed)||dTopF!=mid)	
	{	
		dTopF = mid;							   //�ֶ��ٶȼ���  Ƶ������
		if(mid==0)mid = 1;
    	tmp = TIMFreq_Mhz*1000000/mid;
		if(tmp>0xFFFF)
			mid = 0xFFFF;
		else
			mid = tmp;
		USART1_SetBuf(TOP_FrequencyCP1_T,mid);		
	}
	
	
		
	mid = USART1_GetBuf(JOG_Frequency);				//��õ㶯Ƶ��
	if((!bInitialed)||dStartF!=mid)
	{
		dStartF = mid;									 //��Ƶ�����ڼ���
		if(mid==0)mid = 1;
		tmp = TIMFreq_Mhz*1000000/mid;
		if(tmp>0xFFFF)
			mid = 0xFFFF;
		else
			mid = tmp;
		USART1_SetBuf(JOG_Frequency_T,mid);
	}
	mid = USART1_GetBuf(XunBiao_Frequency);				//�������Ƶ��	 Ѱ��Ƶ��
	if((!bInitialed)||dStartF2!=mid)
	{
		dStartF2 = mid;									 //��Ƶ�����ڼ���
		if(mid==0)mid = 1;
		tmp = TIMFreq_Mhz*1000000/mid;
		if(tmp>0xFFFF)
			mid = 0xFFFF;
		else
			mid = tmp;
		USART1_SetBuf(XunBiao_Frequency_T,mid);
	}


	mid = USART1_GetBuf(TOP_YUTUI);	
	if((!bInitialed)||dTopY!=mid)	
	{	
		dTopY = mid;							   //�ֶ��ٶȼ���  Ƶ������ Ԥ��
		if(mid==0)mid = 1;
    	tmp = TIMFreq_Mhz*1000000/mid;
		if(tmp>0xFFFF)
			mid = 0xFFFF;
		else
			mid = tmp;
		USART1_SetBuf(TOP_YUTUI_T,mid);		
	}	


	mid = USART1_GetBuf(TOP_HUISUO);	
	if((!bInitialed)||dTopH!=mid)	
	{	
		dTopH = mid;							   //�ֶ��ٶȼ���  Ƶ������ ����
		if(mid==0)mid = 1;
    	tmp = TIMFreq_Mhz*1000000/mid;
		if(tmp>0xFFFF)
			mid = 0xFFFF;
		else
			mid = tmp;
		USART1_SetBuf(TOP_HUISUO_T,mid);		
	}	


	
//if(USART1_GetIO(USART_SPEED_AUTO))	   //&& USART1_GetIO(USART_AutoAccPar)==0
//{
//  if(dLastSpeed!=midSpeed||dLastDuty!=midDuty||dLastStyle!=midStyle||dLastAutoAccPar!=midAutoAccPar||dLastLength!=midLength)
//	{	
//     

//		//------------------------------------------------------------
//			seekcnt = 0;
//			tmp = 1000*midDuty/midSpeed;
//		
//		        tmp1 = USART1_GetBuf(LENGTH_CNT)* 450/tmp;     
//		

//								
//            tmp3=tmp1*USART1_GetBuf(AutoAccPar)/1000;
//							
//			      dAutoD = tmp3;
//							
//							
//			//---------------------------------------------------------------------				
//		 
//		  if(4000*USART1_GetBuf(LENGTH_CNT)/tmp>1000000/USART1_GetBuf(JOG_SPEED))////////////////////////
//			{				
//							
//		    tmp1=4000*USART1_GetBuf(LENGTH_CNT)/tmp-1000000/USART1_GetBuf(JOG_SPEED);////////////////////////////////
//			}
//			else  tmp1=0;
//			
//			
////			 tmp1=2700*FORE_GetBuf(PIPE_LENGTH_CNT)/tmp;
//			
//		  if(tmp1>60000) tmp1=60000;
//		  if(tmp1<400) tmp1=400;			


//						
//						 //tmp3=tmp1*USART1_GetBuf(AutoAccPar)/1000;
//							tmp3=tmp1;
//							
//							
//							
//						  if(tmp3>60000) tmp3=60000;		
//							
//		  dAutoTop=tmp3;	
//		
//		
//		

//			if(dAutoTop<300) dAutoTop=300;	

//      
//			USART1_SetBuf(SPEED_STEPCP1,dAutoD);	
//   		USART1_SetBuf(TOP_SPEEDCP1,dAutoTop);
//				
//      USART1_SetIO(USART_AutoAccPar,1);
//       
//	}
//}

//	
//	if(USART1_GetIO(USART_SPEED_AUTO))
//	{
//		USART1_SetBuf(SPEED_STEPCP1,dAutoD);	
//		USART1_SetBuf(TOP_SPEEDCP1,dAutoTop);
//	}

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
