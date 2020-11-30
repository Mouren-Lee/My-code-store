#include "PIPE.h"
#include "flashbase.h"
#include "flashspace.h"
#include "stm32f10x_bkp.h"
#include "ctrllever.h"
#include "PlusOut.h"
#include "USART1.h"
//--------------------------------------------------

//static const u16 BKPDataReg[BKP_DR_NUMBER] =
//{
//    BKP_DR1,BKP_DR2,BKP_DR3,BKP_DR4,BKP_DR5,BKP_DR6,BKP_DR7,BKP_DR8,BKP_DR9,BKP_DR10,   
//	BKP_DR11,BKP_DR12,BKP_DR13,BKP_DR14,BKP_DR15,BKP_DR16,BKP_DR17,BKP_DR18,BKP_DR19,BKP_DR20,
//	BKP_DR21,BKP_DR22,BKP_DR23,BKP_DR24,BKP_DR25,BKP_DR26,BKP_DR27,BKP_DR28,BKP_DR29,BKP_DR30,
//	BKP_DR31,BKP_DR32,BKP_DR33,BKP_DR34,BKP_DR35,BKP_DR36,BKP_DR37,BKP_DR38,BKP_DR39,BKP_DR40,   
//	BKP_DR41,BKP_DR42   
//};

//static u16 DataBuf[PAR_SIZE];

//u16 PAR_GetData(u16 index)
//{	
//	if(index<PAR_SIZE)
//		return DataBuf[index];
//	return 0;
//}

//void PAR_SetData(u16 index,u16 value)
//{
//	if(index<PAR_SIZE)
//	{
//		DataBuf[index] = value;	
//		if(index<BKP_DR_NUMBER)
//			BKP_WriteBackupRegister(BKPDataReg[index],value);
//	}	
//}

//void PAR_Initial(void)
//{
//	u16 i;
//	for(i=0;i<BKP_DR_NUMBER;i++)
//		DataBuf[i] = BKP_ReadBackupRegister(BKPDataReg[i]);	
//	for(;i<PAR_SIZE;i++)
//		DataBuf[i] = 0;	
//}

//void PAR_SetDataBuf(u8 index,const u16* pSrc,u16 count)
//{
//	u16 i;
//	for(i=index;i<BKP_DR_NUMBER&&i<(index+count);i++)
//	{
//		DataBuf[i] = *pSrc++;
//		BKP_WriteBackupRegister(BKPDataReg[i],DataBuf[i]);
//	}
//	for(;i<PAR_SIZE&&i<(index+count);i++)
//		DataBuf[i] = *pSrc++;
//}

//const u16* PAR_GetDataBuf(u8 index)
//{
//	return DataBuf+index;
//}

//----------------------------------------------------
//static u16 FORE_DataBuf[PIPE_DATA_SIZE];
//static u16 BACK_DataBuf[PIPE_DATA_SIZE];
//static u16 FORE_ModifyBit[PIPE_DATA_SIZE];

static u8 bSaveFlash = 0;
static u8 bBackSaveFlash = 0;

static u16 dTimerCnt;
static ST_FlashData flashdata;
extern  u16 Parameter[USART1_PAR_SIZE];
static ST_FlashData factory;
//static const u16 PIPE_MASK[16] = {0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
//																0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};	
//static u8 bSaveFlash = 0;
//static u16 dTimerCnt;
//static ST_FlashData flashdata;

//#define BKP_DR_NUMBER	42

//u16 BKPDataReg[BKP_DR_NUMBER] =
//  {
//    BKP_DR1,BKP_DR2,BKP_DR3,BKP_DR4,BKP_DR5,BKP_DR6,BKP_DR7,BKP_DR8,BKP_DR9,BKP_DR10,   
//	BKP_DR11,BKP_DR12,BKP_DR13,BKP_DR14,BKP_DR15,BKP_DR16,BKP_DR17,BKP_DR18,BKP_DR19,BKP_DR20,
//	BKP_DR21,BKP_DR22,BKP_DR23,BKP_DR24,BKP_DR25,BKP_DR26,BKP_DR27,BKP_DR28,BKP_DR29,BKP_DR30,
//	BKP_DR31,BKP_DR32,BKP_DR33,BKP_DR34,BKP_DR35,BKP_DR36,BKP_DR37,BKP_DR38,BKP_DR39,BKP_DR40,   
//	BKP_DR41,BKP_DR42   
//  };

//void FORE_LoadData(void);
//void FORE_SaveData(void);
////检查前台数据是否被改变
//u8 FORE_isChanged(u8 bBit,u16 index);
////清除前台数据改变标志
//void FORE_ClrChanged(u8 bBit,u16 index);


//void FORE_SetIO(u16 index,u16 value)
//{
//	u16 word;
//	u16 mask;
//	
//	word = index>>4;
//	if(word>=PIPE_DATA_SIZE)
//		return;
//		
//	mask = PIPE_MASK[index&0x000F];
//	if(value)
//		FORE_DataBuf[word] |= mask;
//	else
//		FORE_DataBuf[word] &= (~mask);

//	FORE_ModifyBit[word] |= mask;
//}

//void FORE_SetBuf(u16 index,u16 value)
//{
//	if(index>=PIPE_DATA_SIZE)
//		return;
//	FORE_DataBuf[index] = value;
//	FORE_ModifyBit[index] = 0xFFFF;	
//}


//u8 FORE_isChanged(u8 bBit,u16 index)
//{
//	u16 word;
//	u16 mask;

//	if(bBit)
//	{
//		word = index>>4;
//		if(word>=PIPE_DATA_SIZE)
//			return 0;
//		
//		mask = PIPE_MASK[index&0x000F];
//		
//		if(FORE_ModifyBit[word]&mask)
//			return 1;		
//	}
//	else
//	{
//		if(index>=PIPE_DATA_SIZE)
//			return 0;
//		if(FORE_ModifyBit[index])
//			return 1;	
//	}
//	return 0;
//}

//void FORE_ClrChanged(u8 bBit,u16 index)
//{
//	u16 word;
//	u16 mask;

//	if(bBit)
//	{
//		word = index>>4;
//		if(word>=PIPE_DATA_SIZE)
//			return;
//		
//		mask = PIPE_MASK[index&0x000F];
//		FORE_ModifyBit[word]&=(~mask);		
//	}
//	else
//	{
//		if(index>=PIPE_DATA_SIZE)
//			return;
//		FORE_ModifyBit[index] = 0;	
//	}
//}

//u16 FORE_GetIO(u16 index)
//{
//	u16 word;
//	u16 mask;
//	
//	word = index>>4;
//	if(word>=PIPE_DATA_SIZE)
//		return 0;
//	mask = PIPE_MASK[index&0x000F];
//	if(FORE_DataBuf[word]&mask)
//		return 1;
//	return 0;
//}

//u16 FORE_GetBuf(u16 index)
//{
//	if(index>=PIPE_DATA_SIZE)
//		return 0;
//	return 	FORE_DataBuf[index];
//}


//void BACK_SetIO(u16 index,u16 value)
//{
//	u16 word,mask;

//	word = index>>4;
//	if(word>=PIPE_DATA_SIZE)
//		return;
//		
//	mask = PIPE_MASK[index&0x000F];
//	if(value)
//		BACK_DataBuf[word] |= mask;
//	else
//		BACK_DataBuf[word] &= (~mask);
//}

//void BACK_SetBuf(u16 index,u16 value)
//{
//	if(index>=PIPE_DATA_SIZE)
//		return;
//	BACK_DataBuf[index] = value;
//}


//u16 BACK_GetIO(u16 index)
//{
//	u16 word;
//	u16 mask;
//	word = index>>4;
//	if(word>=PIPE_DATA_SIZE)
//		return 0;
//	mask = PIPE_MASK[index&0x000F];
//	if(BACK_DataBuf[word]&mask)
//		return 1;
//	return 0;
//}

//u16 BACK_GetBuf(u16 index)
//{
//	if(index>=PIPE_DATA_SIZE)
//			return 0;
//	return 	BACK_DataBuf[index];
//}

//u16 BACK_GetData(u8 bBit,u16 index)
//{
//	if(bBit)
//		return BACK_GetIO(index);
//	return BACK_GetBuf(index);
//}


////防止重入，界面侧与PLC侧使用不同的函数调用
//void FORE_LoadData(void)
//{
//	u8 i;
//	for(i=0;i<PIPE_DATA_SIZE;i++)
//	{
//		FORE_DataBuf[i] = BACK_DataBuf[i];
//		FORE_ModifyBit[i] = 0;
//	}
//}

////需要关闭中断
//void FORE_SaveData(void)
//{
//	u8 i;
//	for(i=0;i<PIPE_DATA_SIZE;i++)
//		BACK_DataBuf[i] = (BACK_DataBuf[i]&(~FORE_ModifyBit[i]))|(FORE_DataBuf[i]&FORE_ModifyBit[i]);	
//}


void PIPE_SaveFlash()
{

	bSaveFlash = 1;
}

void PIPE_BackSaveFlash()
{
	if(bBackSaveFlash==0)	
	bBackSaveFlash = 1;
}



void PIPE_Init()
{
	u16 i;
	FlashInit(&flashdata,DATA_FLASH_ADDRES);
	FlashInit(&factory,FACTORY_FLASH_ADDRES);	
	
	
	#if (USART1_PAR_SIZE>0)
	for(i=3;i<USART1_PAR_SIZE;i++)
		Parameter[i]=FlashGetData(&flashdata,i);
// Parameter[0]=0;
// Parameter[1]=0;	
// Parameter[2]=0;	
// Parameter[3]=0;	
	#endif
	
//		#if (USART1_PAR_SIZE>0)
//	for(i=3;i<USART1_PAR_SIZE;i++)
//		Parameter[i]=FlashGetData(&factory,i);
//	#endif
	
	
//	for(i=0;i<PIPE_BKP_SIZE;i++)
//		BACK_DataBuf[i+PIPE_BKP_HEAD]=BKP_ReadBackupRegister(BKPDataReg[i]);

//	FORE_LoadData();
}

////主程序中调用所以只针对FOREBUF
void PIPE_Check()
{	
	u8 bModified = 0;
	u16 i;

	Ctrl_Disable();
//	FORE_SaveData();
	Ctrl_Enable();

//	if(bSaveFlash&&CP0_GetState()==CP_WAIT&&CP1_GetState()==CP_WAIT)
//	{
//		dTimerCnt=0;
//		bSaveFlash = 0;
//	}

//	if((bBackSaveFlash==1)&&CP0_GetState()==CP_WAIT&&CP1_GetState()==CP_WAIT)
//	{
//		dTimerCnt=0;
//		bBackSaveFlash = 2;
//	}
		if(bSaveFlash)
	{
		dTimerCnt=0;
		bSaveFlash = 0;
	}

	if(bBackSaveFlash==1)
	{
		dTimerCnt=0;
		bBackSaveFlash = 2;
	}
	
	if(dTimerCnt==0&&CP0_GetState()==CP_WAIT&&CP1_GetState()==CP_WAIT)
	{
		dTimerCnt = FLASH_SAVE_SPACE;
	   #if (USART1_PAR_SIZE>0)
		//检查FLASH数据是否改变
		for(i=3;i<USART1_PAR_SIZE;i++)
		{
			if(Parameter[i]!=FlashGetData(&flashdata,i))
			{
				bModified = 1;
				break;
			}	
		}

		if(bModified)
		{
			FLASH_Unlock();
			FlashEraseSlot(&flashdata);
			__disable_irq();
			for(i=0;i<USART1_PAR_SIZE;i++)
			{
				FlashWriteData(&flashdata,Parameter[i]);
			}
			__enable_irq();
			FLASH_Lock();
		}		//写入至FLASH中
		
		
//			if(bBackSaveFlash==2)
//		{
//			
//			FLASH_Unlock();
//			FlashEraseSlot(&factory);
//			__disable_irq();
//			for(i=3;i<USART1_PAR_SIZE;i++)
//			{
//				FlashWriteData(&factory,Parameter[i]);
//			}
//			__enable_irq();
//			FLASH_Lock();
//			
//			bBackSaveFlash=0;
//		}		//写入至FLASH中	
		
		
		
		
		#endif
	}
	else
		dTimerCnt--;

	//保存到备份区
//	for(i=0;i<PIPE_BKP_SIZE;i++)
//		BKP_WriteBackupRegister(BKPDataReg[i],BACK_DataBuf[i+PIPE_FLASH_SIZE]);
					
	Ctrl_Disable();
//	for(i=0;i<USART1_PAR_SIZE;i++)
//		FORE_DataBuf[i] = BACK_DataBuf[i];				
	Ctrl_Enable();

//	for(i=0;i<PIPE_DATA_SIZE;i++)
//		FORE_ModifyBit[i] = 0;
}

//u16 PIPE_FlashTimes(void)
//{
//	return FlashGetTimes(&flashdata);
//}

void BackSaveParameters()//保存备份数据
{
	u16 i;
//	FLASH_Unlock();
//	FlashEraseSlot(&factory);
//	for(i=3;i<USART1_PAR_SIZE;i++)
//	{
//		__disable_irq();
//		FlashWriteData(&factory,Parameter[i]);			  //从PIPE_BKP_MID开始保存整个BKP
//		__enable_irq();
//	}

//	FLASH_Lock();
	
			FLASH_Unlock();
			FlashEraseSlot(&factory);
			__disable_irq();
			for(i=0;i<USART1_PAR_SIZE;i++)
			{
				FlashWriteData(&factory,Parameter[i]);
			}
			__enable_irq();
			FLASH_Lock();
	
	
}

void BackLoadParameters()//恢复出厂
{
	u16 i;
	u16 index;
//	for(i=3;i<USART1_PAR_SIZE;i++)//从第6个开始才恢复数据，这个是PipeData.h数据没有整理之前
//	{
//		
//		Parameter[i]=FlashGetData(&factory,i);
//		

//	}
//	Ctrl_Disable();
	for(i=0;i<USART1_PAR_SIZE;i++)
		Parameter[i]=FlashGetData(&factory,i);	
	 Parameter[0]=0;
	 Parameter[1]=0;	
	 Parameter[2]=0;	
	 Parameter[3]=0;	
//	Ctrl_Enable();	

	
//	for(i=3;i<USART1_PAR_SIZE;i++)
//		Parameter[i]=FlashGetData(&flashdata,i);	
	
}

