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
	
	midSpeed = USART1_GetBuf(SPEED_SET);
	midDuty = USART1_GetBuf(DUTY);
	midAutoAccPar=USART1_GetBuf(AutoAccPar);	
	midLength = USART1_GetBuf(MATERIAL_LENGTH);
	

	midMark = USART1_GetBuf(MARK_WIDTH_LENGTH)*10;
	midyutui = USART1_GetBuf(YUTUI_LENGTH);
	midhuisuo = USART1_GetBuf(HUISUO_LENGTH);
	midpenjiao = USART1_GetBuf(DuanJiao_LENGTH);
	
	midDangLiang = USART1_GetBuf(MaiChongDangLiang1);
	//////////////////////////////////////////////////////////////  当量计算
	
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
//		if((!bInitialed)||(midRoller!=dLastRoller)  //预退
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
//		if((!bInitialed)||(midRoller!=dLastRoller)//回缩
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
//	if((!bInitialed)||(midRoller!=dLastRoller)//喷胶
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
		dTopF = mid;							   //手动速度计算  频率上限
		if(mid==0)mid = 1;
    	tmp = TIMFreq_Mhz*1000000/mid;
		if(tmp>0xFFFF)
			mid = 0xFFFF;
		else
			mid = tmp;
		USART1_SetBuf(TOP_FrequencyCP1_T,mid);		
	}
	
	
		
	mid = USART1_GetBuf(JOG_Frequency);				//获得点动频率
	if((!bInitialed)||dStartF!=mid)
	{
		dStartF = mid;									 //起动频率周期计算
		if(mid==0)mid = 1;
		tmp = TIMFreq_Mhz*1000000/mid;
		if(tmp>0xFFFF)
			mid = 0xFFFF;
		else
			mid = tmp;
		USART1_SetBuf(JOG_Frequency_T,mid);
	}
	mid = USART1_GetBuf(XunBiao_Frequency);				//获得启动频率	 寻标频率
	if((!bInitialed)||dStartF2!=mid)
	{
		dStartF2 = mid;									 //起动频率周期计算
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
		dTopY = mid;							   //手动速度计算  频率上限 预退
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
		dTopH = mid;							   //手动速度计算  频率上限 回缩
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
