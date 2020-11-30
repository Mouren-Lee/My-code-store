#ifndef _FLASH_BASE_H_
#define _FLASH_BASE_H_

#include "stm32f10x.h"

typedef struct tag_flash
{
	u16* pAddress;
	u16 CurSlot;		 	//当前SLOT的第一个数索引
	u16 Index;				//当前SLOT的写入指针
}ST_FlashData;

#define FLASH_SLOT_SIZE 256			  		//半字数，为2倍字节数
#define FLASH_SIZE 1024
#define FLASH_SLOT_NUM (FLASH_SIZE/FLASH_SLOT_SIZE)

//索引从0开始
u16 FlashGetData(ST_FlashData* pFlash,u16 index);
u16 FlashGetTimes(ST_FlashData* pFlash);
void FlashInit(ST_FlashData* pFlash,u32 address);
void FlashEraseSlot(ST_FlashData* pFlash);
//必须连续按顺序写入，且之前要调用FlashEraseSlot
void FlashWriteData(ST_FlashData* pFlash,u16 data);

#endif

