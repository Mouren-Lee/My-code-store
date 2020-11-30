#include "IOManage.h"
#include "PIPE.h"
#include "PipeData.h"
#include "MainWork.h"

static u32 DIBuf[4];
static u8 BufIndex;
static u32 InDataLast,InData,InEdge,InRevLast,InRevEdge;
static u32 OutData;
 

void IO_Init()
{
   InData = 0xFFFFFFFF;
	 InDataLast = InData;
 
}

void IO_InCheck()
{
	u32 dPortIn;
	u32 tmp,tmp88;
	
//-------------------------------------------------------------------			
	tmp = GPIOC->IDR;
	dPortIn =   ((tmp&GPIO_Pin_6)<<5)|((tmp&GPIO_Pin_12)>>6)|((tmp&GPIO_Pin_10)>>2)|((tmp&GPIO_Pin_9))|((tmp&GPIO_Pin_11)>>4);	   	
                  //PC6--DI1 X12        PC12--X07               PC10--X09                PC9 --X10        PC11 --X08
 //-------------------------------------------------------------------		
 	
	tmp = GPIOD->IDR;		
	dPortIn =  dPortIn | ((tmp&(GPIO_Pin_2))<<3);	   
		                    //PD2  -- DI2  X06 	
 
//-------------------------------------------------------------------			
	
	tmp = GPIOB->IDR;			
	dPortIn =  dPortIn | ((tmp&GPIO_Pin_3)<<1)|((tmp&GPIO_Pin_4)>>1)|((tmp&GPIO_Pin_5)>>3)|((tmp&GPIO_Pin_8)>>7)|((tmp&GPIO_Pin_9)>>9);	   	
                             //PB3 --X05           PB4 -- X04       PB5 -- X03                PB8 -- X02        PB9 -- X01
	
 //-------------------------------------------------------------------		
 	
	tmp = GPIOA->IDR;		
	dPortIn =  dPortIn | ((tmp&(GPIO_Pin_8))<<2);	   
		                    //PA8  -- DI2  X11
//-------------------------------------------------------------------		
	if(++BufIndex>=4)BufIndex = 0;
	DIBuf[BufIndex] = dPortIn;
	dPortIn = (DIBuf[0]|DIBuf[1]|DIBuf[2]|DIBuf[3])
				^(DIBuf[0]&DIBuf[1]&DIBuf[2]&DIBuf[3]);
	InDataLast = InData;
	InData = InData&dPortIn;				
	InData |=(DIBuf[0]&(~dPortIn));
	InEdge =(InData^InDataLast);		 //2012-9-1改
	//DI采集   包括按钮
	
//	Rev_Inconf();  //2015-5-5
}

void IO_OutPut()
{
	u32 tmp;
	
	#define DO_PA_MASK (BIT0|BIT1|BIT6|BIT7)          //PA0 --Y01   PA1--Y02     PA6--Y03    PA7--Y04    
	#define DO_PB_MASK (BIT0|BIT1|BIT10|BIT11|BIT12|BIT13|BIT14)  //PB0 --Y07   PB1 -- Y08   PB13 -- Y09  PB14 -- Y10  PB15 -- Y11    
	#define DO_PC_MASK (BIT4|BIT5)                    //PC4 --Y05   PC5 --Y06 
//	#define DO_PD_MASK (BIT2)                         //PD2 --X05 
//	#define DO_PE_MASK (BIT7|BIT8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15)    // 置3位 4位 5位 6位 7位 8位 9位 10位 11位

//-------------------------------------------------------------------		
	tmp = (OutData&(BIT0))|(OutData&(BIT1))|(OutData&(BIT2))<<4|(OutData&(BIT3))<<4;  //  
          //PA0 --Y01       PA1--Y02         PA6--Y03              PA7--Y04    
	GPIOA->BSRR = (~tmp)&DO_PA_MASK;
	GPIOA->BRR = tmp&DO_PA_MASK;		
	
//-------------------------------------------------------------------		
	tmp = (OutData&(BIT6))>>6|(OutData&(BIT7))>>6|(OutData&(BIT8))<<2|(OutData&(BIT9))<<2|(OutData&(BIT10))<<2|(OutData&(BIT11))<<2|(OutData&(BIT12))<<2;  // 置1位 2位
        //PB0 --Y07            PB1 -- Y08         PB10 -- Y09         PB11 -- Y10           PB12 -- Y11       PB13 -- Y12         PB14 -- Y13
	GPIOB->BSRR = (~tmp)&DO_PB_MASK;
	GPIOB->BRR = tmp&DO_PB_MASK;		
	
//-------------------------------------------------------------------	
	tmp = (OutData&(BIT4))|(OutData&(BIT5));    // 置0位
	        //PC4 --Y05           PC5 --Y06 
	GPIOC->BSRR = (~tmp)&DO_PC_MASK;
	GPIOC->BRR = tmp&DO_PC_MASK;	

 
//-------------------------------------------------------------------	
//	tmp = (OutData&(BIT4))>>2;  // 置1位 2位
//	           // PD2--X05 
//	GPIOD->BSRR = (~tmp)&DO_PD_MASK;
//	GPIOD->BRR = tmp&DO_PD_MASK;	
	
	
	

}

u32 IO_GetDI32(void)
{
	return (InData&0xFFFFFFFF);
}

u8 IO_GetDI(u32 Mask)
{
	return ((InData&Mask)?1:0);		
}

u8 IO_GetDIChange(u32 Mask)
{
	return ((InEdge&Mask)?1:0);
}

void IO_SetDO32(u32 value)
{
	OutData = value;
}

u32 IO_GetDO32()
{
	return OutData;
}

u8 IO_GetDO(u32 Mask)
{
	return ((OutData&Mask)?1:0);
}

void IO_SetDO(u32 mask)
{
	OutData|=mask;		
}

void IO_ResetDO(u32 mask)
{
	OutData&=(~mask);
}

void IO_SetDOValue(u32 mask,u8 bSet)
{
	if(bSet)
	  	OutData|=mask;
	else
		OutData&=(~mask);	
}


