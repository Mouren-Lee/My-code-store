#include "TouchScreen.h"

#define POSBUF_BIT 3				  //4096最多对应这个数
#define POSBUF_SIZE (1<<POSBUF_BIT)	  
u8 bGetX;
#define SRC_CHECK_X 0x0090
#define SRC_CHECK_Y 0x00D0
u16 dScrX;
u16 dScrY;

u16 dXBuf[POSBUF_SIZE];
u16 dYBuf[POSBUF_SIZE];
u32 dXBufSum;
u32 dYBufSum;
u16 dXAverage;
u16 dYAverage;
u8 dXBufPt;
u8 dYBufPt;
u16 dXMistake;
u16 dYMistake;

#define MAX_MISTAKE 6

void TScr_Configuration()
{
	SPI_InitTypeDef   SPI_InitStructure; 
  	// SPI2 Config  
  	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b; 
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; 
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
  	SPI_InitStructure.SPI_CRCPolynomial = 7; 
  	SPI_Init(SPI2,&SPI_InitStructure); 

  	// SPI2 enable  
  	SPI_Cmd(SPI2,ENABLE);  
}

void TScr_Init()
{
	for(dXBufPt=0;dXBufPt<POSBUF_SIZE;dXBufPt++)
		dXBuf[dXBufPt] = 0;
   	dXBufPt=0;

	for(dYBufPt=0;dYBufPt<POSBUF_SIZE;dYBufPt++)
		dYBuf[dXBufPt] = 0;
	dYBufPt=0;

	dXBufSum=0;
	dYBufSum=0;
	bGetX = 0;
	dScrX = 0;
	dScrY = 0;

}

void TScr_Check()
{
	u16 value;
	u16* pSrc;
	u16 *pDis;
	u8 i,p;

	if(!(SPI2->SR&BIT7))	//发送结束	BSY
	{
		if(bGetX)
		{			
			if(SPI2->SR&BIT1)
				value = SPI2->DR>>3;
			else
				return;		 

			//插入	 升序
			//找到第一个比value大的数
			for(i=0;i<dXBufPt&&dXBuf[i]<=value;i++);
			p = i;
			pDis = dXBuf+dXBufPt;
			pSrc = pDis-1;
			for(;i<dXBufPt;i++)
				*pDis-- = *pSrc--;
			dXBuf[p]=value;
			dXBufPt++;
  			
			SPI2->DR = SRC_CHECK_X;
			bGetX = FALSE;
		}
		else
		{
			if(SPI2->SR&BIT1)
				value = SPI2->DR>>3;
			else
				return;   

			dScrY = value;

			//插入	 升序
			//找到第一个比value大的数
			for(i=0;i<dYBufPt&&dYBuf[i]<=value;i++);
			p = i;
			pDis = dYBuf+dYBufPt;
			pSrc = pDis-1;
			for(;i<dYBufPt;i++)
				*pDis-- = *pSrc--;
			dYBuf[p]=value;
			dYBufPt++;
 	   
			SPI2->DR = SRC_CHECK_Y;
			bGetX = TRUE;
		}
		 
		if((dXBufPt>=POSBUF_SIZE)&&(dYBufPt>=POSBUF_SIZE))
		{
			dYBufPt = 0;
			dXBufPt = 0;
			if((dXBuf[POSBUF_SIZE/2]-dXBuf[POSBUF_SIZE/2-1]<MAX_MISTAKE)
			&&(dYBuf[POSBUF_SIZE/2]-dYBuf[POSBUF_SIZE/2-1]<MAX_MISTAKE))
			{
				dScrX =  (dXBuf[POSBUF_SIZE/2-1]+dXBuf[POSBUF_SIZE/2])/2;
				dScrY =  (dYBuf[POSBUF_SIZE/2-1]+dYBuf[POSBUF_SIZE/2])/2;
			}
		}
	}
}

u16 TScr_GetX()
{
	return dScrX;
}

u16 TScr_GetY()
{
	return dScrY;
}
