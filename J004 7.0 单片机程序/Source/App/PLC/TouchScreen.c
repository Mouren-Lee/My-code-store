#include "TouchScreen.h"

#define POSBUF_BIT 3				  //4096最多对应这个数
#define POSBUF_SIZE (1<<POSBUF_BIT)	  
u8 CurCheck;
#define SRC_CHECK_X 0x0093
#define SRC_CHECK_IN3 0x00A3
#define SRC_CHECK_Y 0x00D3
#define SRC_CHECK_IN4 0x00E3
u16 dScrX;
u16 dScrY;

typedef struct tag_dataelement{
u16 value;
s8 previous;
s8 next;
}ST_DataElement;
//previous为-1时,为头
//next为-1时为尾

typedef struct tag_datalink{
ST_DataElement data[POSBUF_SIZE];
u8 head;
u8 trail;
u8 pos;
}ST_DataLink;

ST_DataLink XBuf;
ST_DataLink YBuf;

#define MAX_MISTAKE 8

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

void TScr_LinkInit(ST_DataLink* pLink)
{
	u8 i;
	for(i=0;i<POSBUF_SIZE;i++)
	{
		pLink->data[i].value = 0;
		pLink->data[i].previous = i-1;
		pLink->data[i].next = i+1;
	}
	pLink->data[0].previous = POSBUF_SIZE-1;
	pLink->data[POSBUF_SIZE-1].next = 0;
	pLink->pos = 0;
	pLink->head = 0;
}

void TScr_LinkAddValue(ST_DataLink* pLink,u16 value)
{
	ST_DataElement* pCur;
	u8 seek,i;

	//调整当前值
	if(++(pLink->pos)>= POSBUF_SIZE)
		pLink->pos-=POSBUF_SIZE;
	//删除当前项值
	pCur = pLink->data+pLink->pos;
	//始终保证队列是满的,循环队列
	pLink->data[pCur->previous].next = pCur->next;
	pLink->data[pCur->next].previous = pCur->previous;	

	if(pLink->head == pLink->pos)//在头上
		pLink->head = pCur->next;

	pCur->value = value;
	seek = pLink->head;

	for(i=0;i<(POSBUF_SIZE-1);i++)
	{	
		if(value<=pLink->data[seek].value)
			break;
		seek = pLink->data[seek].next;
	}	

	if(i==0)
		pLink->head = pLink->pos;

	pCur->previous = pLink->data[seek].previous;
	pCur->next = seek;
	pLink->data[seek].previous = pLink->pos;
	pLink->data[pCur->previous].next = pLink->pos;
}	

void TScr_GetMidValue(u16* pValue,ST_DataLink* pLink)
{
	u16 value[4];
	u8 seek,i;
	for(seek=pLink->head,i=0;i<((POSBUF_SIZE>>1)-2);i++)
		seek = pLink->data[seek].next;
	for(i=0;i<4;i++)
	{
		value[i] = pLink->data[seek].value;
		seek = pLink->data[seek].next;
	}
	if(((value[0]>value[3])?(value[0]-value[3]):(value[3]-value[0]))<= MAX_MISTAKE)
		*pValue = (value[0]+value[1]+value[2]+value[3])/4;
}

void TScr_Init()
{
	TScr_LinkInit(&XBuf);
	TScr_LinkInit(&YBuf);

	CurCheck = 0;

	dScrX = 0;
	dScrY = 0;
}

void TScr_Check()
{
	u16 value;

	if(!(SPI2->SR&BIT7))	//发送结束	BSY
	{
		if(SPI2->SR&BIT1)
			value = SPI2->DR>>3;
		else
			return;
		switch(CurCheck)
		{
			case 0:
				SPI2->DR = SRC_CHECK_Y;
				TScr_LinkAddValue(&XBuf,value);
				TScr_GetMidValue(&dScrX,&XBuf);
				break;
			case 1:
				SPI2->DR = SRC_CHECK_IN4;
			
				break;
			case 2:
				SPI2->DR = SRC_CHECK_X;
				TScr_LinkAddValue(&YBuf,value);
				TScr_GetMidValue(&dScrY,&YBuf);
				break;
			case 3:
				SPI2->DR = SRC_CHECK_IN4;
			
				break;			
		}
		CurCheck++;
		if(CurCheck>=4)
			CurCheck = 0;		
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
