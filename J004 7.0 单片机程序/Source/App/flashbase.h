#ifndef _FLASH_BASE_H_
#define _FLASH_BASE_H_

#include "stm32f10x.h"

typedef struct tag_flash
{
	u16* pAddress;
	u16 CurSlot;		 	//��ǰSLOT�ĵ�һ��������
	u16 Index;				//��ǰSLOT��д��ָ��
}ST_FlashData;

#define FLASH_SLOT_SIZE 256			  		//��������Ϊ2���ֽ���
#define FLASH_SIZE 1024
#define FLASH_SLOT_NUM (FLASH_SIZE/FLASH_SLOT_SIZE)

//������0��ʼ
u16 FlashGetData(ST_FlashData* pFlash,u16 index);
u16 FlashGetTimes(ST_FlashData* pFlash);
void FlashInit(ST_FlashData* pFlash,u32 address);
void FlashEraseSlot(ST_FlashData* pFlash);
//����������˳��д�룬��֮ǰҪ����FlashEraseSlot
void FlashWriteData(ST_FlashData* pFlash,u16 data);

#endif

