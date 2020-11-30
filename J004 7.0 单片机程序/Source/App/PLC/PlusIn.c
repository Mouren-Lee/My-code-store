#include "PlusIn.h"

#define BUFSIZE 20
#define TIMSPACE 200		//0.25msʱ��Ӧ50ms
u16 BufPt;
u16 TIMBase;

u16 TIM8Last;
u16 TIM8Buf[BUFSIZE];
u16 TIM8Freq;
u32 TIM8Sum;

u16 TIM1Last;
u16 TIM1Buf[BUFSIZE];
u16 TIM1Freq;
u32 TIM1Sum;

void TMR18_Configuration()
{	 
	//TIM8��ʼ��	F0		TIM8_CH1
	TIM8->CCMR1 = 0x0021;		//�˲�����N=4 �޷�Ƶ IC1ӳ����TI1FP1Ϊ����
	TIM8->SMCR = 0x0057;
	TIM8->CR1 = 0x0001;			//����TIM8
	TIM8->EGR |= BIT0;			//�������
	TIM8->SR = 0;
	//TIM1��ʼ��	F1	  TIM1_CH1
	TIM1->CCMR1 = 0x0021;		//�˲�����N=4 �޷�Ƶ IC1ӳ����TI1FP1Ϊ����
	TIM1->SMCR = 0x0057;
	TIM1->CR1 = 0x0001;			//����TIM1
	TIM1->EGR |= BIT0;			//�������
	TIM1->SR = 0;
}	

void PIN_Init()
{
	for(BufPt=0;BufPt<BUFSIZE;BufPt++)
	{
		TIM8Buf[BufPt] = 0;
		TIM1Buf[BufPt] = 0;
	}
	TIMBase = 0;
	TIM8Last = 0;TIM1Last = 0;
	TIM8Freq = 0;TIM1Freq = 0;
	TIM8Sum = 0;TIM1Sum = 0;
}

void PIN_Check()
{
	u16 TIMCur;	
	u16 TIMBufCur;

	TIMBase++;
	if(TIMBase>=TIMSPACE)
	{
		TIMBase = 0;  

	  	BufPt++;
		if(BufPt>=BUFSIZE)
			BufPt = 0;

	  	TIMCur = TIM8->CNT;
		if(TIMCur<TIM8Last)
			TIMBufCur = 0xFFFF-TIM8Last+TIMCur+1;
		else
			TIMBufCur = TIMCur-TIM8Last;
	
		TIM8Last = TIMCur;
		TIM8Sum += TIMBufCur;
		TIM8Sum -= TIM8Buf[BufPt];
		TIM8Buf[BufPt] = TIMBufCur;

		if(TIM8Sum>0xFFFF)
			TIM8Freq = 0xFFFF;
		else
			TIM8Freq = TIM8Sum&0xFFFF;
			
		TIMCur = TIM1->CNT;
		if(TIMCur<TIM1Last)
			TIMBufCur = 0xFFFF-TIM1Last+TIMCur+1;
		else
			TIMBufCur = TIMCur-TIM1Last;

		TIM1Last = TIMCur;
		TIM1Sum += TIMBufCur;
		TIM1Sum -= TIM1Buf[BufPt];
		TIM1Buf[BufPt] = TIMBufCur;

		if(TIM1Sum>0xFFFF)
			TIM1Freq = 0xFFFF;
		else
			TIM1Freq = TIM1Sum&0xFFFF;	
	}
}

u16 PIN_GetF0()
{
	return TIM8Freq;
}

u16 PIN_GetF1()
{
	return TIM1Freq;
}
