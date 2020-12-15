#include "PlusOut.h"
#include "Curve.h"
#include "CPArray.h"
#include "USART1.h"
#include "MainWork.h"
#include "IOManage.h"
#include "PipeData.h"
#define PLUS_HIGH_WIDTH 40

#define PLUS_BUF_SIZE 1024
#define PLUS_BUF_SIZE2 1024
//#define PLUS_BUF_SIZE 8192
static ST_CPArray CP0Array;
static ST_CPArray CP0Array2;
static u16 CP0Plus[PLUS_BUF_SIZE];
static ST_CPSend CP0Send;

static ST_CPArray CP1Array;
static u16 CP1Plus[PLUS_BUF_SIZE];
static ST_CPSend CP1Send;

static ST_CPArray CP2Array;
static u16 CP2Plus[PLUS_BUF_SIZE];
static ST_CPSend CP2Send;

static ST_CPArray CP3Array;
static u16 CP3Plus[PLUS_BUF_SIZE];
static ST_CPSend CP3Send;

void TMR235_Configuration()
 { 
//	//CP0 
// 	TIM5->CR1 = 0x0008;	 //单脉冲模式，向上计数
//	TIM5->CCMR1 = 0x0060;//CH1
//	TIM5->CCER = 0x0003;
//	TIM5->PSC = MainFreq_Mhz/TIMFreq_Mhz-1; //分频对应1MHz
//	TIM5->ARR = 1000;
//	TIM5->CCR1 = 500;
//	TIM5->DIER = 0x01;	 //允许周期中断	 
//	 
//	//CP1 
// 	TIM2->CR1 = 0x0008;	 //单脉冲模式，向上计数
//	TIM2->CCMR1 = 0x6000;//CH2
//	TIM2->CCER = 0x0030;
//	TIM2->PSC = MainFreq_Mhz/TIMFreq_Mhz-1; //分频对应1MHz
//	TIM2->ARR = 1000;
//	TIM2->CCR2 = 500;
//	TIM2->DIER = 0x01;	 //允许周期中断
	 
 	TIM5->CR1 = 0x0008;	 //单脉冲模式，向上计数
	TIM5->CCMR1 = 0x0070;//CH1
	TIM5->CCER = 0x0003;
	TIM5->PSC = MainFreq_Mhz/TIMFreq_Mhz-1; //分频对应1MHz  35
	
	TIM5->ARR = 1000;
	TIM5->CCR1 = 500;
	TIM5->DIER = 0x01;	 //允许周期中断	 
	 
	 
	 
 	TIM2->CR1 = 0x0008;	 //单脉冲模式，向上计数
	TIM2->CCMR1 = 0x7000;//CH2
	TIM2->CCER = 0x0030;
	TIM2->PSC = MainFreq_Mhz/TIMFreq_Mhz-1; //分频对应1MHz
	TIM2->ARR = 1000;
	TIM2->CCR2 = 500;
	TIM2->DIER = 0x01;	 //允许周期中断	 
	 
	 
	 
	 
	 
//	//CP2
// 	TIM3->CR1 = 0x0008;	 //单脉冲模式，向上计数
//	TIM3->CCMR1 = 0x0060;//CH1
//	TIM3->CCER = 0x0003;
//	TIM3->PSC = MainFreq_Mhz/TIMFreq_Mhz-1; //分频对应1MHz
//	TIM3->ARR = 1000;
//	TIM3->CCR1 = 500;
//	TIM3->DIER = 0x01;	 //允许周期中断



//	//CP3
//	TIM4->CR1 = 0x0008;	 //单脉冲模式，向上计数
//	TIM4->CCMR2 = 0x7000;//CH4
//	TIM4->CCER = 0x3000;
//	TIM4->PSC = MainFreq_Mhz/TIMFreq_Mhz-1; //分频对应1MHz
//	TIM4->ARR = 1000;
//	TIM4->CCR4 = 500;
//	TIM4->DIER = 0x01;	 //允许周期中断
	

	


	SetArrayMemory(&CP0Array,CP0Plus,PLUS_BUF_SIZE);  
	SetArrayMemory(&CP0Array2,CP0Plus,PLUS_BUF_SIZE2);  
	CP0Send.pArray = &CP0Array;
	CP0Send.pArray2= &CP0Array2;	
	CP0Send.State = CP_WAIT;

	SetArrayMemory(&CP1Array,CP1Plus,PLUS_BUF_SIZE);  
	CP1Send.pArray = &CP1Array;
	CP1Send.State = CP_WAIT;
	
//	SetArrayMemory(&CP2Array,CP2Plus,PLUS_BUF_SIZE);  
//	CP2Send.pArray = &CP2Array;
//	CP2Send.State = CP_WAIT;	
//	
//	SetArrayMemory(&CP3Array,CP3Plus,PLUS_BUF_SIZE);  
//	CP3Send.pArray = &CP3Array;
//	CP3Send.State = CP_WAIT;	

}
//-------------------------------------------------------------------------------------------------------------
//CP0操作程序
bool CP0_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT)
{
	if(CP0Send.State!=CP_WAIT)
   		return FALSE;	
	
	TIM5->CR1&=(~BIT0);

	if(PlusCnt>SeekCnt)			   	 //2015-12-29改 先走长度  再走一个色标范围
		PlusCnt-=SeekCnt;
	else
		PlusCnt = 0; 
	
	if(PlusCnt==0)return TRUE;
		
	if(SetArrayParam(&CP0Array,PlusCnt,curve,StartT,StopT,MinT,TimeScale))	 
	//	SetArrayParam(&CP0Array,PlusCnt,curve,StartT,StopT,MinT,TimeScale);
		ArrayInit(&CP0Array);

	
	while(!ArrayRun(&CP0Array));

	CP0Send.SeekCnt = SeekCnt*2;	   //2015-12-29改 先走长度  再走一个色标范围

	//CP0Send.SeekCnt = SeekCnt;
	CP0Send.DingChangCnt=0;
	CP0Send.SeekT = StopT;
	CP0Send.KeepCnt = KeepCnt;
	CP0Send.State = CP_START;
	CPArraySend(&CP0Send);		  //产生第一个脉冲的周期

	TIM5->ARR = PLUS_HIGH_WIDTH*2;
	TIM5->CCR1 = PLUS_HIGH_WIDTH;
	TIM5->CCR4 = PLUS_HIGH_WIDTH;

	TIM5->CNT = 0;	
 	TIM5->CR1|=BIT0;			//启动TIM5
	TIM5->SR = 0;
	return TRUE;
}

bool CP0_isLostMark()
{
	return (CP0Send.LostMark?TRUE:FALSE);
}

bool CP0_ClearLostMark()
{
	CP0Send.LostMark=0;
	CP0Send.State=CP_WAIT;
}

void CP0_SetMark(u8 mark)
{
	CP0Send.Mark = mark;
}

bool CP0_Keep(u32 PlusCnt,u16 MaxT)
{
	if(CP0Send.State!=CP_WAIT)
		return FALSE;

	CP0Send.SendCnt = 0;
	CP0Send.KeepCnt = PlusCnt;
	CP0Send.NextT = MaxT;

   	TIM5->CR1&=(~BIT0);
 	TIM5->ARR = MaxT;
	TIM5->CCR1 = TIM5->ARR>>1;
	CP0Send.State = CP_KEEP_LEN;
	TIM5->CNT = 0;	
 	TIM5->CR1|=BIT0;			//启动TIM5
	TIM5->SR = 0;

	return TRUE;
}

void CP0_Stop()
{
	TIM5->CR1 &= (~BIT0);	//停止TIM1
	TIM5->SR = 0;			//清除中断标志
	CP0Send.State = CP_WAIT;
}

u8 CP0_GetState()
{
	return CP0Send.State;
}


u32 Get_CP0()
{
   return CP0Send.DingChangCnt;
}
void CP0_ClearDingChang()
{
	CP0Send.DingChangCnt = 0;
}


//TIM5中断服务程序
void TIM5_IRQHandler(void)
{
	TIM5->SR = 0;

	if(CP0Send.State != CP_WAIT)
	{
		TIM5->ARR = CP0Send.NextT-1;

		if(CP0Send.NextT>(2*PLUS_HIGH_WIDTH))
			TIM5->CCR1 = CP0Send.NextT-PLUS_HIGH_WIDTH;
		else
			TIM5->CCR1 = CP0Send.NextT/2;

		TIM5->CR1 |= BIT0;
	}
	ArrayRun(&CP0Array);
	CPArraySend(&CP0Send);	
  CP0Send.DingChangCnt++;		
}


//-------------------------------------------------------------------------------------------------------------
//CP1操作程序
bool CP1_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT)
{
	if(CP1Send.State!=CP_WAIT)
   		return FALSE;	
	
	TIM2->CR1&=(~BIT0);

//	if(PlusCnt>SeekCnt)			  //2015-12-29改 先走长度  再走一个色标范围
//		PlusCnt-=SeekCnt;
//	else
//		PlusCnt = 0; 

	if(PlusCnt==0)return TRUE;

	if(SetArrayParam(&CP1Array,PlusCnt,curve,StartT,StopT,MinT,TimeScale))
	 	ArrayInit(&CP1Array);

	while(!ArrayRun(&CP1Array));

//	CP1Send.SeekCnt = SeekCnt*2;	//2015-12-29改 先走长度  再走一个色标范围
	 	CP1Send.SeekCnt = SeekCnt;
	CP1Send.SeekT = StopT;
	CP1Send.KeepCnt = KeepCnt;
	CP1Send.State = CP_START;
	CPArraySend2(&CP1Send);		  //产生第一个脉冲的周期

	TIM2->ARR = PLUS_HIGH_WIDTH*2;
	TIM2->CCR2 = PLUS_HIGH_WIDTH;

	TIM2->CNT = 0;	
 	TIM2->CR1|=BIT0;			//启动TIM2
	TIM2->SR = 0;
	return TRUE;
}

bool CP1_isLostMark()
{
	return (CP1Send.LostMark?TRUE:FALSE);
}

void CP1_SetMark(u8 mark)
{
	CP1Send.Mark = mark;
}

bool CP1_Keep(u32 PlusCnt,u16 MaxT)
{
	if(CP1Send.State!=CP_WAIT)
		return FALSE;

	CP1Send.SendCnt = 0;
	CP1Send.KeepCnt = PlusCnt;
	CP1Send.NextT = MaxT;

   	TIM2->CR1&=(~BIT0);
 	TIM2->ARR = MaxT;
	TIM2->CCR2 = TIM2->ARR>>1;
	CP1Send.State = CP_KEEP_LEN;
	TIM2->CNT = 0;	
 	TIM2->CR1|=BIT0;			//启动TIM2
	TIM2->SR = 0;

	return TRUE;
}

void CP1_Stop()
{
	TIM2->CR1 &= (~BIT0);	//停止TIM1
	TIM2->SR = 0;			//清除中断标志
	CP1Send.State = CP_WAIT;
}

u8 CP1_GetState()
{
	return CP1Send.State;
}

//TIM2中断服务程序
void TIM2_IRQHandler(void)
{
	TIM2->SR = 0;

	if(CP1Send.State != CP_WAIT)
	{
		TIM2->ARR = CP1Send.NextT-1;

		if(CP1Send.NextT>(2*PLUS_HIGH_WIDTH))
			TIM2->CCR2 = CP1Send.NextT-PLUS_HIGH_WIDTH;
		else
			TIM2->CCR2 = CP1Send.NextT/2;

		TIM2->CR1 |= BIT0;
	}
	ArrayRun(&CP1Array);
	CPArraySend2(&CP1Send);		
}


//-------------------------------------------------------------------------------------------------------------
////CP2操作程序
//bool CP2_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT)
//{
//	if(CP2Send.State!=CP_WAIT)
//   		return FALSE;	
//	
//	TIM3->CR1&=(~BIT0);

//	if(PlusCnt>SeekCnt)
//		PlusCnt-=SeekCnt;
//	else
//		PlusCnt = 0; 

//	if(PlusCnt==0)return TRUE;

//	if(SetArrayParam(&CP2Array,PlusCnt,curve,StartT,StopT,MinT,TimeScale))
//	 	ArrayInit(&CP2Array);

//	while(!ArrayRun(&CP2Array));

////	CP4Send.SeekCnt = SeekCnt*2;
//	CP2Send.SeekCnt = SeekCnt;	
//	CP2Send.SeekT = StopT;
//	CP2Send.KeepCnt = KeepCnt;
//	CP2Send.State = CP_START;
//	CPArraySend2(&CP2Send);		  //产生第一个脉冲的周期

//	TIM3->ARR = PLUS_HIGH_WIDTH*2;
//	TIM3->CCR1 = PLUS_HIGH_WIDTH;

//	TIM3->CNT = 0;	
// 	TIM3->CR1|=BIT0;			//启动TIM3
//	TIM3->SR = 0;
//	return TRUE;
//}

//bool CP2_isLostMark()
//{
//	return (CP2Send.LostMark?TRUE:FALSE);
//}

//void CP2_SetMark(u8 mark)
//{
//	CP2Send.Mark = mark;
//}

//bool CP2_Keep(u32 PlusCnt,u16 MaxT)
//{
//	if(CP2Send.State!=CP_WAIT)
//		return FALSE;

//	CP2Send.SendCnt = 0;
//	CP2Send.KeepCnt = PlusCnt;
//	CP2Send.NextT = MaxT;

//   	TIM3->CR1&=(~BIT0);
// 	TIM3->ARR = MaxT;
//	TIM3->CCR1 = TIM3->ARR>>1;
//	CP2Send.State = CP_KEEP_LEN;
//	TIM3->CNT = 0;	
// 	TIM3->CR1|=BIT0;			//启动TIM3
//	TIM3->SR = 0;

//	return TRUE;
//}

//void CP2_Stop()
//{
//	TIM3->CR1 &= (~BIT0);	//停止TIM1
//	TIM3->SR = 0;			//清除中断标志
//	CP2Send.State = CP_WAIT;
//}

//u8 CP2_GetState()
//{
//	return CP2Send.State;
//}

////TIM3中断服务程序
//void TIM3_IRQHandler(void)
//{
//	TIM3->SR = 0;

//	if(CP2Send.State != CP_WAIT)
//	{
//		TIM3->ARR = CP2Send.NextT-1;

//		if(CP2Send.NextT>(2*PLUS_HIGH_WIDTH))
//			TIM3->CCR1 = CP2Send.NextT-PLUS_HIGH_WIDTH;
//		else
//			TIM3->CCR1 = CP2Send.NextT/2;

//		TIM3->CR1 |= BIT0;
//	}
//	ArrayRun(&CP2Array);
//	CPArraySend2(&CP2Send);		
//}
////--------------------------------------------------------------------------------------------------------
////CP3操作程序




//u32 Get_CP3()
//{
// 
//   return CP3Send.DingChangCnt;
//}
//void CP3_ClearDingChang()
//{
// 
//  CP3Send.DingChangCnt=0;
//}

//u16 CP3_GetHavenplus()
//{
//	return CP3Send.Havencnt;
//}



//void CP3_StartHaven()
//{
//	CP3Send.Havencnt=0;	
//}

//bool CP3_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT)
//{
//	if(CP3Send.State!=CP_WAIT)
//   		return FALSE;	
//	
//	TIM4->CR1&=(~BIT0);

//	//if(PlusCnt>SeekCnt)
//	//	PlusCnt-=SeekCnt;
//	//else
//	//	PlusCnt = 0; 
//	
//	if(PlusCnt==0)return TRUE;
//		
//	if(SetArrayParam(&CP3Array,PlusCnt,curve,StartT,StopT,MinT,TimeScale))
//		ArrayInit(&CP3Array);

//	while(!ArrayRun(&CP3Array));
//	
//	CP3Send.DingChangCnt=0; 
////	CP1Send.SeekCnt = SeekCnt*2;
//	CP3Send.SeekCnt = SeekCnt;	
//	
//	CP3Send.SeekT = StopT;
//	CP3Send.KeepCnt = KeepCnt;
//	CP3Send.State = CP_START;
//	CPArraySend2(&CP3Send);		  //产生第一个脉冲的周期

//	TIM4->ARR = PLUS_HIGH_WIDTH*2;
//	TIM4->CCR4 = PLUS_HIGH_WIDTH;

//	TIM4->CNT = 0;	
// 	TIM4->CR1|=BIT0;			//启动TIM4
//	TIM4->SR = 0;
//	return TRUE;
//}

//bool CP3_isLostMark()
//{
//	return (CP3Send.LostMark?TRUE:FALSE);
//}

//void CP3_SetMark(u8 mark)
//{
//	CP3Send.Mark = mark;
//}

//bool CP3_Keep(u32 PlusCnt,u16 MaxT)
//{
//	if(CP3Send.State!=CP_WAIT)
//		return FALSE;

//	if(PlusCnt==0)
//		return TRUE;
//	CP3Send.SendCnt = 1;
//	CP3Send.KeepCnt = PlusCnt;
//	CP3Send.NextT = MaxT;

//   	TIM4->CR1&=(~BIT0);
// 	TIM4->ARR = MaxT;
//	TIM4->CCR4 = TIM4->ARR>>1;
//	CP3Send.State = CP_KEEP_LEN;
//	TIM4->CNT = 0;	
// 	TIM4->CR1|=BIT0;			//启动TIM4
//	TIM4->SR = 0;

//	return TRUE;
//}

//void CP3_Stop()
//{
//	TIM4->CR1 &= (~BIT0);	//停止TIM1		   
//	TIM4->SR = 0;			//清除中断标志
//	CP3Send.State = CP_WAIT;
//}

//u8 CP3_GetState()
//{
//	return CP3Send.State;
//}

////TIM4中断服务程序
//void TIM4_IRQHandler(void)
//{
//	TIM4->SR = 0;


//	if(CP3Send.State != CP_WAIT)
//	{
//		TIM4->ARR = CP3Send.NextT-1;

//		if(CP3Send.NextT>(2*PLUS_HIGH_WIDTH))
//			TIM4->CCR4 = CP3Send.NextT-PLUS_HIGH_WIDTH;
//		else
//			TIM4->CCR4 = CP3Send.NextT/2;
//		CP3Send.Havencnt++;
//		TIM4->CR1 |= BIT0;
//	}
//	ArrayRun(&CP3Array);
//	CPArraySend2(&CP3Send);	
//  CP3Send.DingChangCnt++;			
//}
