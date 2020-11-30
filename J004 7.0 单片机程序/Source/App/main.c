//***********************************************************//
//***************PLC V1**************************************//
//***************2019-1-26***********************************//
//***************测试程序************************************//
//***************昝小舒**************************************//
//***************1.04 2010-6-25**************************************//
//***************4.73 2019-8-20  加密**************************************//
//***********************************************************//


#include "LCDPLC.h"
#include "CtrlLever.h"
#include "USART1.h"
#include "USART2.h"
#include "USART3.h"
#include "USART4.h"
#include "DACCtrl.h"


#include "PIPE.h"
//#include "fsmc_sram.h"
//#include "GUI.h"
//#include "GUIType.h"
//#include "AllFont.h"
#include "RealTimer.h"
//#include "TouchCheck.h"
//#include "SWManage.h"
#include "PipeData.h"
#include "DataCalc.h"
//#include "WinAction.h"
#include "flashbase.h"
#include "MainWork.h"
#include "ADC.h"
#include "iic_smec98sp.h"



void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

//	   GPIO_SetBits(GPIOA,GPIO_Pin_11); //RS485 NDE1
//	   GPIO_SetBits(GPIOA,GPIO_Pin_4); // RS485 NDE2
	
	
	   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);   //禁用JTAG 只用SW   释放PB3 PB4 PA15作为普通端口   增加RCC_APB2Periph_AFIO
	
	
	
//	GPIO_SetBits(GPIOC,GPIO_Pin_5); //RS485 RE	
//	GPIO_SetBits(GPIOC,GPIO_Pin_4); //RS485 DE		
	
//	GPIO_SetBits(GPIOD, GPIO_Pin_12);//LCD LIGHT 
	
	
//	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
//	/* USART3 使用IO端口配置 */    
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);    
//  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
//  GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOA	
	
	 
	//配置PA端口
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_3 |GPIO_Pin_8 | GPIO_Pin_10;  //PA3 -- Rx2  PA8  -- DI2 X11    PA10 -- Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_9;  //PA2  -- Tx2    PA8  -- Tx    
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	
	
	
	
	
	GPIO_InitStructure.GPIO_Pin	=  GPIO_Pin_15;//   PA15 -- NDE2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7  ;
															   //PA6--Y03    PA7--Y04    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 


	/* Configure DAC channe1 and DAC channel2 outputs pins */
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);


	
	// Y03  Y04  Y05  Y06   Y07
//	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure); 

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	#ifdef PLUS_OUT0
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	#else
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //GPIO_Mode_Out_PP  GPIO_Mode_Out_OD
	#endif
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	#ifdef PLUS_OUT1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	#else
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	#endif
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	#ifdef PLUS_OUT2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	#else
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	#endif
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	//配置PB端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14     ;
															//PB0 --Y07    PB1 -- Y08  PB10 -- Y09   PB11 -- Y10  PB12 -- Y11   PB13  -- Y12   PB14  -- Y14      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8| GPIO_Pin_9;
	                             //PB3 --X05   PB4 -- X04   PB5 -- X03   PB8 -- X02    PB8 -- X01 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	//------------------------------------------------------------
//	GPIO_InitStructure.GPIO_Pin	=  GPIO_Pin_11;  //PB11 -- Rx3  
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);	
//	
//	
//	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;  //PB10  -- Tx3      
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//		GPIO_InitStructure.GPIO_Pin	=   GPIO_Pin_12;//PB12  -- NDE3     
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);  
 	//------------------------------------------------------------
	
	

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	//SPI2配置 PB13=SCK PB14=MISO PB15=MOSI
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);	 	
	
	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	#ifdef PLUS_OUT3
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	#else
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	#endif
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	//配置PC端口
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure); 	

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5;
	                             // PC2 --RUN     PC4 --Y05  PC5 --Y06    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11 | GPIO_Pin_12  ;
	                            //PC6--DI1 X12  PC9--X10   PC10--X09    PC11 --X08      PC12 --X07
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	
	
	//------------------------------------------------------------
//	GPIO_InitStructure.GPIO_Pin	=  GPIO_Pin_11;  //PC12 -- Rx4  
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);	
//	
//	
//	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;  //PC10  -- Tx4      
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	
//		GPIO_InitStructure.GPIO_Pin	=   GPIO_Pin_12;//PA12  -- NDE4     
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);  
 	//------------------------------------------------------------
 	//配置PD端口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2  ;
	                             // PD2--X06 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 	
	
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	                             //PD8--Y13  PD9--Y14  PD10--Y15  PD11--Y16  PD12--Y17  PD13--Y18  PD14--Y19  PD15--Y20 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);		
	
 
 	
	//配置PE端口
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//	                             //PE7--Y04   PE8--Y05   PE9--Y06   PE10--Y07  PE11--Y08  PE12--Y09  PE13--Y10  PE14--Y11  PE15--Y12
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);	

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
//	                             //PD0--X18  
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOE, &GPIO_InitStructure); 


}

//系统中断管理
void NVIC_Configuration(void)
{ 
	NVIC_InitTypeDef NVIC_InitStructure;
  	/* Configure the NVIC Preemption Priority Bits */  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	#ifdef  VECT_TAB_RAM  
	  /* Set the Vector Table base location at 0x20000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
	  /* Set the Vector Table base location at 0x08000000 */ 
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif

	/* Enable the TIM6 global Interrupt as Systick*/
  	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	  NVIC_Init(&NVIC_InitStructure);

	/* Enable the TIM1 global Interrupt OV*/
  	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);


	/* Enable the TIM1 CAP1 global Interrupt OV*/
  	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);


	#ifdef PLUS_OUT1
	/* Enable the TIM2 global Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);
	#endif

	#ifdef PLUS_OUT2
	/* Enable the TIM3 global Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);
	#endif

	#ifdef PLUS_OUT0
	/* Enable the TIM5 global Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);
	#endif
	
	#ifdef PLUS_OUT3
	/* Enable the TIM5 global Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);
	#endif
}

//配置系统时钟,使能各外设时钟
void RCC_Configuration(void)
{
	SystemInit();	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA 
                           |RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
                           |RCC_APB2Periph_GPIOD 
	                         |RCC_APB2Periph_TIM1	 | RCC_APB2Periph_TIM8| RCC_APB2Periph_AFIO
                            , ENABLE );

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_DAC  
							| RCC_APB1Periph_TIM5| RCC_APB1Periph_TIM6
							| RCC_APB1Periph_SPI2|RCC_APB1Periph_PWR
							| RCC_APB1Periph_BKP| RCC_APB1Periph_USART2|RCC_APB1Periph_USART3|RCC_APB1Periph_UART4
							,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
}


//配置所有外设
void Init_All_Periph(void)
{  
	RCC_Configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	Ctrl_Configuration();
  DAC_Configuration();	
	USART2_Configuration();
//	USART3_Configuration();	
//	USART4_Configuration();	
	 STMADC_Init();
	 SMEC_I2cInit();	
//	FSMC_LCD_Init();
	RTC_Configuration();
	SysTick->LOAD = 90000&SysTick_LOAD_RELOAD;//对应10ms
	SysTick->CTRL = SysTick_CTRL_ENABLE ;
}

void Init_Ctrl_Par(void)
{


//	
//	FORE_SetBuf(PIPE_MIMA1,11111);		//密码1初始化
//	FORE_SetBuf(PIPE_MIMA2,22222);		//密码2初始化
//	
//	FORE_SetIO(PIPE_LANGRAGE,0);


//	
//	FORE_SetBuf(PIPE_FLASH12,0);		//电话
//	FORE_SetBuf(PIPE_FLASH1,5);		//电话
//	FORE_SetBuf(PIPE_FLASH2,1);		//电话
//	FORE_SetBuf(PIPE_FLASH3,0);	
//	
//	FORE_SetBuf(PIPE_FLASH4,8);		//电话
//	FORE_SetBuf(PIPE_FLASH5,5);		//电话
//	FORE_SetBuf(PIPE_FLASH6,5);		//电话
//	FORE_SetBuf(PIPE_FLASH7,0);		 //电话
//	
//	FORE_SetBuf(PIPE_FLASH8,0);		 //电话
//	FORE_SetBuf(PIPE_FLASH9,2);		//电话
//	FORE_SetBuf(PIPE_FLASH10,1);		//电话
//	FORE_SetBuf(PIPE_FLASH11,8);		//电话

   
//   USART1_SetBuf(USART_PARA_ShaoZhong, 100);	

    USART1_SetBuf(BATCH_MODE, 0);	
    USART1_SetBuf(BATCH_COUNT, 0);		
    USART1_SetBuf(TOTAL_COUNT, 0);	
    USART1_SetBuf(TOTAL_COUNT2, 0);	
    USART1_SetBuf(GK1_COUNT, 0);	
    USART1_SetBuf(WORK_INF, 0);	
    USART1_SetBuf(AMOUNT_BATCH, 10);	
    USART1_SetBuf(SPEED_GK1, 0);			
    USART1_SetBuf(PAUSE_TIME, 200);				
    USART1_SetBuf(MATERIAL_LENGTH, 2000);	
    USART1_SetBuf(ALARM_CNT, 3);		
    USART1_SetBuf(MARK_WIDTH_LENGTH, 10);	
    USART1_SetBuf(YUTUI_LENGTH, 0);	
    USART1_SetBuf(HUISUO_LENGTH, 0);	
    USART1_SetBuf(SPEED_YUTUI,300);	
    USART1_SetBuf(SPEED_HUISUO, 300);	
    USART1_SetBuf(JOG_Frequency, 300);	
    USART1_SetBuf(XunBiao_Frequency, 300);	
    USART1_SetBuf(TOP_FrequencyCP1, 5000);	
    USART1_SetBuf(TOP_YUTUI, 5000);	
    USART1_SetBuf(TOP_HUISUO, 5000);	
    USART1_SetBuf(ShuChui_Time, 10);			
    USART1_SetBuf(HengChuiBFB, 70);			
    USART1_SetBuf(JingDian_Dealy, 0);			
    USART1_SetBuf(HeDao_Dealy, 0);			
    USART1_SetBuf(FangLiaoTiQian_Time, 0);			
    USART1_SetBuf(APART1_Dealy, 10);			
    USART1_SetBuf(APART1_Time, 10);
    USART1_SetBuf(BanZheng_Dealy, 10);
    USART1_SetBuf(BanZheng_Time, 10);
    USART1_SetBuf(TangYa_Dealy, 10);
    USART1_SetBuf(QiDong_Dealy, 100);
    USART1_SetBuf(Blocking_Time, 100);
    USART1_SetBuf(GaoWei_Dealy, 0);
    USART1_SetBuf(HOLE1_DELAY, 0);						
    USART1_SetBuf(HOLE1_KEEP, 20);		
    USART1_SetBuf(ShiJi_LENGTH1, 2000);		
    USART1_SetBuf(MarkWait_CNT, 0);
    USART1_SetBuf(SPEED_CP1JianSu, 20);		
    USART1_SetBuf(Clear_Time, 6);		
    USART1_SetBuf(LOSE_MARK, 3);			
    USART1_SetBuf(SPEED_SET, 50);					
    USART1_SetBuf(SPEED_STEPCP1, 400);			
    USART1_SetBuf(SEEK_STYLE, 0);	
    USART1_SetBuf(MaiChongDangLiang1, 600);	
    USART1_SetBuf(STWOSPEEDFRE, 6);	
    USART1_SetBuf(ZhuJiDianDongSpeed, 6);	
    USART1_SetBuf(MAIN_REGULATOR, 50);	
	  USART1_SetBuf(SYSTEM1_Time, 3000);	
    USART1_SetBuf(RIQITIME, 20);	
	  USART1_SetBuf(LASTDAY, 0);	
 
    

    USART1_SetIO(USART_SUOZHOU, 0);		
    USART1_SetIO(USART_LongOrShort, 0);		
    USART1_SetIO(USART_FEED_CUT, 0);		
    USART1_SetIO(USART_MaiChongJiaoZhun, 0);	
    USART1_SetIO(USART_BuShu, 0);	
    USART1_SetIO(USART_TOTAL_CLR, 0);	
    USART1_SetIO(USART_CNT_CLR, 0);	
    USART1_SetIO(USART_BATCH_CLR, 0);			
    USART1_SetIO(USART_TuoDaiPuTongOrBuJin, 0);			
	  USART1_SetIO(USART_DaKong, 0);			
    USART1_SetIO(USART_BreakSwitch, 0);			
    USART1_SetIO(USART_ZhuJiAdjust,1);
	  USART1_SetIO(USART_MaiChongCW,0);
		
}




int main(void)
{  
	u8 TimChg,TimLast,TimCur;

//	SW_ProcessMsg Msg;
//	u16 tmp;
//  u8 ScreenCheck();
	
// 	Ctrl_Init();
//	Win_InitParameters();
//	Init_All_Periph();
	PIPE_Init();

	if(USART1_GetIO(USART_PB_SavePara))
	{
		//BKP_DeInit();            //2015-6-5   BKP初始化
		//初始化参数
		Init_Ctrl_Par();
		
  	USART1_SetIO(USART_PB_SavePara,0);
//		if(Win_isParaEmpty())		//取得Flash使用次数
//			Win_SaveParameters(1,0);//保存默认数据
	}
	
	Ctrl_Init();
	Init_All_Periph();	

//	RTC_Init(FORE_GetBuf(PIPE_TIME_H),FORE_GetBuf(PIPE_TIME_L));


	//用于调试
//	GUI_Init();
	__enable_irq();

//	SWManageInit();

//	if((FORE_GetBuf(PIPE_CALIBRATE_X1)!=0)&&(FORE_GetBuf(PIPE_CALIBRATE_Y1)!=0))
//	{
//		GUI_TOUCH_Calibrate(GUI_COORD_X,0,LCD_XSIZE,FORE_GetBuf(PIPE_CALIBRATE_X0),FORE_GetBuf(PIPE_CALIBRATE_X1));
//		GUI_TOUCH_Calibrate(GUI_COORD_Y,0,LCD_YSIZE,FORE_GetBuf(PIPE_CALIBRATE_Y0),FORE_GetBuf(PIPE_CALIBRATE_Y1));		
//	}

 	while(1)
  	{
		if(SysTick->CTRL&SysTick_CTRL_COUNTFLAG)		
			TimCur++;
		 
		TimChg = TimLast^TimCur;
		TimLast = TimCur;	

//		if(TimChg&BIT0)
//			Msg.timeup = 1;

//		TouchCheck(&Msg);
//		SWManageCheck(&Msg);

		DataCalc();
		Accredit();

 RS485_Service();		
		
//		if(TimChg&BIT0)
//			GUI_TOUCH_Exec();
		if(TimChg&BIT0)
			PIPE_Check();
		

//		if(TimChg&BIT5)
//		ADCTEMP= Get_Adc(0) ; 


		
//  		if(ScreenCheck())//SSD1963.c最后的函数检测屏是否已经花掉
//				SWRedraw();//重画当前窗口
/*		if(TimChg&BIT5)  //1024ms
		   {
		  
		    if((SWReturnWin()==WINDOW07_INDEX)||(SWReturnWin()==WINDOW02_INDEX)||(SWReturnWin()==WINDOW06_INDEX))
				{
				TimWin++;
			   	if(TimWin>=80)
			    {
			      	SWReMachine();
				    TimWin=0;
					}
				}
		   }
*/
	}
}

