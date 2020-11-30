#include "stm32f10x.h"
#include "absacc.h"							//���ڶ�λflash������ַ
#include "flashbase.h"

//������0��ʼ
u16 FlashGetData(ST_FlashData* pFlash,u16 index)
{
	if(index>=FLASH_SLOT_SIZE-1)return 0;
	return pFlash->pAddress[pFlash->CurSlot+index+1];
}

u16 FlashGetTimes(ST_FlashData* pFlash)
{
	return pFlash->pAddress[pFlash->CurSlot];
}

void FlashInit(ST_FlashData* pFlash,u32 address)
{  
	u16 i;
	pFlash->pAddress = (u16*)address;
	for(i=FLASH_SLOT_SIZE;i<FLASH_SIZE;i+=FLASH_SLOT_SIZE)
	{
		if(pFlash->pAddress[i] == 0xFFFF)
			break;
	}

	pFlash->CurSlot = i-FLASH_SLOT_SIZE;
	pFlash->Index = 1;						//������
}

void FlashEraseSlot(ST_FlashData* pFlash)
{
	u16 times;
	times = pFlash->pAddress[pFlash->CurSlot];
	
	if(times==0xFFFF)					//��ֹ������û�б���ʼ����
		times = 0;
	else if(times<0xFFFE)
		times++;
	
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	if((pFlash->CurSlot+FLASH_SLOT_SIZE)>=FLASH_SIZE)
	{
		FLASH_ErasePage((u32)pFlash->pAddress);
		pFlash->CurSlot = 0;	
	}
	else
	{	
		pFlash->CurSlot+=FLASH_SLOT_SIZE;	
	}
	pFlash->Index = 1;	
	
	FLASH_ProgramHalfWord((u32)pFlash->pAddress+pFlash->CurSlot*2,times);
}

//����������˳��д�룬��֮ǰҪ����FlashEraseSlot
void FlashWriteData(ST_FlashData* pFlash,u16 data)
{
	if(pFlash->Index>=FLASH_SLOT_SIZE-1)return;
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ProgramHalfWord((u32)pFlash->pAddress+(pFlash->CurSlot+pFlash->Index)*2,data);
	pFlash->Index++;
}
