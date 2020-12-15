#include "VSPIDAC.h"

#ifdef TLC5604
	#define RESET_FS() (GPIOC->BSRR = GPIO_Pin_1)
	#define SET_FS() (GPIOC->BRR = GPIO_Pin_1)
	#define RESET_SCK() (GPIOC->BSRR = GPIO_Pin_2)
	#define SET_SCK() (GPIOC->BRR = GPIO_Pin_2)
	#define RESET_SDA() (GPIOC->BSRR = GPIO_Pin_3)
	#define SET_SDA() (GPIOC->BRR = GPIO_Pin_3)
#else
	#define RESET_LOAD() (GPIOC->BRR = GPIO_Pin_1)
	#define SET_LOAD() (GPIOC->BSRR = GPIO_Pin_1)
	#define RESET_SCK() (GPIOC->BRR = GPIO_Pin_2)
	#define SET_SCK() (GPIOC->BSRR = GPIO_Pin_2)
	#define RESET_SDA() (GPIOC->BRR = GPIO_Pin_3)
	#define SET_SDA() (GPIOC->BSRR = GPIO_Pin_3)
#endif

u8 dOffset[4];
u16 dValue[4];
u8 SPIStep;
u16 SPIAdr;

u16 SPISendBuf;

static const u8 ChannelMap[4]={3,0,1,2};

void VSPI_Init()
{
	for(SPIAdr=0;SPIAdr<4;SPIAdr++)
	{
		dOffset[SPIAdr]=128;		 //128¶ÔÓ¦0
		dValue[SPIAdr]=0;
	}
	SPIStep=0;
	SPIAdr=0;
	#ifdef TLC5604
		SET_SCK();
		SET_FS();
	#else
		RESET_SCK();
		SET_LOAD();
	#endif
}

void VSPI_Manage()
{
	#ifdef TLC5604
		if(SPIStep<32)
		{
			if(SPIStep&0x0001)		
				RESET_SCK();
			else
			{
				if(SPIStep==0)
				{
					SPISendBuf = dOffset[SPIAdr]+dValue[SPIAdr];
					if(SPISendBuf>128)
						SPISendBuf-=128;
					else
						SPISendBuf = 0;
			
					if(SPISendBuf>0x3FF)
						SPISendBuf = 0x3FF;	
		
					SPISendBuf = (ChannelMap[SPIAdr++]<<14)|(SPISendBuf<<2);
					SPIAdr&=0x03;					
				
					RESET_FS();
				}
	
				if(SPISendBuf&0x8000)
					SET_SDA();
				else
					RESET_SDA();
				SPISendBuf=SPISendBuf<<1; 

			 	SET_SCK();
			}
			SPIStep++;
		}
		else
		{	
			SET_FS();
			SET_SCK();
			SPIStep = 0;
		}
	#else
		if(SPIStep<22)
		{
			if(SPIStep&0x0001)		
				RESET_SCK();
			else
			{
				if(SPIStep==0)
				{
					SPISendBuf = dOffset[SPIAdr]+dValue[SPIAdr];
					if(SPISendBuf>128)
						SPISendBuf-=128;
					else
						SPISendBuf = 0;
				
					if(SPISendBuf>0xFF)
						SPISendBuf = 0xFF;	
		
					SPISendBuf = (ChannelMap[SPIAdr++]<<9)|(SPISendBuf);
					SPIAdr&=0x03;					
				
					SET_LOAD();
				}
	
				if(SPISendBuf&0x0400)
					SET_SDA();
				else
					RESET_SDA();

				SPISendBuf=SPISendBuf<<1; 
			
			 	SET_SCK();
			}
			SPIStep++;
		}
		else
		{	
			RESET_LOAD();
			RESET_SCK();
			SPIStep = 0;
		}
	#endif
}

u16 VSPI_GetValue(u8 index)
{
	if(index>=4)return 0;
	#ifdef TLC5604
   		return dValue[index];
	#else
		return dValue[index]<<2;
	#endif
}

void VSPI_SetValue(u8 index,u16 value)
{
   	if(index>=4)return;
	#ifdef TLC5604
   		dValue[index] = value;
	#else
		dValue[index] = value>>2;
	#endif
}

void VSPI_SetOffset(u8 index,u8 offset)
{
	dOffset[index] = offset;		
}
