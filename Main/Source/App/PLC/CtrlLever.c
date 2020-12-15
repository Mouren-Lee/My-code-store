#include "CtrlLever.h"
#include "USART1.h"
#include "USART2.h"
#include "IOManage.h"
#include "VSPIDAC.h"
//#include "TouchScreen.h"
#include "PIPE.h"
#include "Beeper.h"
#include "RealTimer.h"
#include "MainWork.h"
#include "PlusOut.h"
#include "PlusIn.h"
#include "PipeData.h"
//#include "Flash.h"
#include "IOManage.h"
#include "DACCtrl.h"

extern u8 HBLOW_EN;

void Ctrl_Configuration()
{	
	USART1_Configuration();
	TIM6->PSC = MainFreq_Mhz/1-1;				//分频对应1MHz
	TIM6->ARR = 499;			//对应0.5ms
	TIM6->CR1 = 0x01;
	TIM6->DIER = 0x01;	  		//允许周期中断
//	TScr_Configuration();

	TMR235_Configuration();
	TMR18_Configuration();
}

void Ctrl_Init()
{
	IO_Init();
//	USART1_Init();
//	USART1_SetBuf(0,VERSION);
//	VSPI_Init();
//	TScr_Init();
//	MainWork_InitVar();
}

void Ctrl_Disable()
{
	 TIM6->DIER = 0x00;	//禁止TIM6中断
}

void Ctrl_Enable()
{
	TIM6->DIER = 0x01; //使能TIM6中断
}

u32 TimChg,TimCur;

void TIM6_IRQHandler(void)
{	
	u32 temp1,temp2,tmp;
	
	TIM6->SR = 0;
	TimChg = TimCur++;
	TimChg ^= TimCur;
	//0.5ms	1ms	2ms 4ms 8ms 16ms 32ms 64ms 128ms 256ms 512ms 1024ms	2048ms			

	IO_InCheck();
	IO_OutPut();
	
//	PAR_SetData(INPUT_DATA1,IO_GetDI32());         //alpha
//	PAR_SetData(INPUT_DATA2,IO_GetDO32());         //alpha

//	PAR_SetData(INPUT_DATA1,0xff00);  
//	PAR_SetData(INPUT_DATA2,0x00ff);
	
	
//	temp1=IO_GetDI32();
//	temp2=IO_GetDO32();	
	
			//用于调试
//			tmp = IO_GetDI32();
//			USART1_SetIO16(USART_DI0,tmp&0xFFFF);
//			USART1_SetIO16(USART_DI1,tmp>>16);


    			//tmp = IO_GetDI32();
    			tmp = ~IO_GetDI32();
         USART1_SetBuf(USART_PARA_DI0,tmp&0xFFFF);
				 
				 
	    			//tmp = IO_GetDO32();
    			  tmp = IO_GetDO32();
         USART1_SetBuf(USART_PARA_DO0,tmp&0xFFFF);		



	      temp1=DAC_GetValueAO1()/4;
	      USART1_SetBuf(USART_PARA_DA1,temp1); 
				
	      temp2=DAC_GetValueAO2()/4;
	      USART1_SetBuf(USART_PARA_DA2,temp2); 
//			tmp = IO_GetDO32();
//			USART1_SetIO16(USART_DO0,tmp&0xFFFF);
//			USART1_SetIO16(USART_DO1,tmp>>16);      


//			tmp = USART1_GetIO16(USART_DO1)<<16;
//			tmp += USART1_GetIO16(USART_DO0);
		//	IO_SetDO32(tmp);	
	


								if(TimChg&BIT2)
	        {	

             // Master_03_Slove(01,02,03);
              
						
					}


 // Master_OVER();

	
	
	if(TimChg&BIT7)
	{
		
	 //  modbus_rtu();	
		
//		USART1_ChkOVtime();
//		#ifdef PLUS_OUT0
//			CP0_TMR();
//		#endif
//
//		#ifdef PLUS_OUT1
//			CP1_TMR();
//		#endif
//		
//		#ifdef PLUS_OUT2
//			CP2_TMR();
//		#endif
	}
// 	USART2_Manage();
//	VSPI_Manage();


	
//	RTC_Check();		   //时钟管理


//	BACK_SetBuf(PIPE_YEAR,RTC_GetYear());	
//	BACK_SetBuf(PIPE_MONTH,RTC_GetMonth());
//	BACK_SetBuf(PIPE_DAY,RTC_GetDay());
//	BACK_SetBuf(PIPE_HOUR,RTC_GetHour());
//	BACK_SetBuf(PIPE_MINUTE,RTC_GetMinute());

//	BACK_SetBuf(PIPE_INPUT1,~IO_GetDI16());		//输入状态指示
//	BACK_SetBuf(PIPE_OUTPUT,IO_GetDO16());

// 	if(CP0_GetState())
//	{
//			BACK_SetIO(PIPE_DO0,1);			//并不会真的输出

//	}
//	else
//	{
//		BACK_SetIO(PIPE_DO0,0);

//	}

//	BACK_SetBuf(PIPE_BACK_DA1,VSPI_GetValue(DAC_CH0));
//	BACK_SetBuf(PIPE_BACK_DA2,VSPI_GetValue(DAC_CH1));
//	BACK_SetBuf(PIPE_BACK_DA3,VSPI_GetValue(DAC_CH2));
//	BACK_SetBuf(PIPE_BACK_DA4,VSPI_GetValue(DAC_CH3));

//	USART1_SetBuf(0,PIPE_FlashTimes());
//	USART1_SetBuf(2,BACK_GetBuf(USART1_GetBuf(1)));
//	USART1_SetBuf(4,BACK_GetBuf(USART1_GetBuf(3)));
//	USART1_SetBuf(6,BACK_GetBuf(USART1_GetBuf(5)));

//	if(TimChg&BIT0)
//		TScr_Check();
//	if(TimChg&BIT2)	 	//1ms
//		BEEP_Check();

//	PIN_Check();   //定时器管理计数器   脉冲输入 编码器 横切机不用
	
	//主控制逻辑
	MainWork(TimChg);	


	return;
}
