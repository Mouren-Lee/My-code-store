#include "WinAction.h"
#include "Flashbase.h"
#include "FlashSpace.h"

static ST_FlashData factory;

void Win_InitParameters()
{
	FlashInit(&factory,FACTORY_FLASH_ADDRES);
}

u32 Win_isParaEmpty()
{
   return (!FlashGetTimes(&factory));		//取得Flash使用次数
}

void Win_SaveParameters(u16 CmdID,const ST_PARAM* pParam)//保存数据
{
	u16 i;
	FLASH_Unlock();
	FlashEraseSlot(&factory);
	for(i=PIPE_FLASH_HEAD;i<PIPE_FLASH_SIZE;i++)
	{
		__disable_irq();
		FlashWriteData(&factory,FORE_GetBuf(i));			  //从PIPE_BKP_MID开始保存整个BKP
		__enable_irq();
	}
	PIPE_SaveFlash();
	FLASH_Lock();
}

void Win_LoadParameters(u16 CmdID,const ST_PARAM* pParam)//恢复出厂
{
	u16 i;
	u16 index;
	for(i=4;i<PIPE_FLASH_SIZE;i++)//从第6个开始才恢复数据，这个是PipeData.h数据没有整理之前
	{
		index = i+PIPE_FLASH_HEAD;
		FORE_SetBuf(index,FlashGetData(&factory,i));
	}
}


