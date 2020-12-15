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
   return (!FlashGetTimes(&factory));		//ȡ��Flashʹ�ô���
}

void Win_SaveParameters(u16 CmdID,const ST_PARAM* pParam)//��������
{
	u16 i;
	FLASH_Unlock();
	FlashEraseSlot(&factory);
	for(i=PIPE_FLASH_HEAD;i<PIPE_FLASH_SIZE;i++)
	{
		__disable_irq();
		FlashWriteData(&factory,FORE_GetBuf(i));			  //��PIPE_BKP_MID��ʼ��������BKP
		__enable_irq();
	}
	PIPE_SaveFlash();
	FLASH_Lock();
}

void Win_LoadParameters(u16 CmdID,const ST_PARAM* pParam)//�ָ�����
{
	u16 i;
	u16 index;
	for(i=4;i<PIPE_FLASH_SIZE;i++)//�ӵ�6����ʼ�Żָ����ݣ������PipeData.h����û������֮ǰ
	{
		index = i+PIPE_FLASH_HEAD;
		FORE_SetBuf(index,FlashGetData(&factory,i));
	}
}


