#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f10x.h"


//索引从0开始
u16 FlashGetData(u16 index);
void FlashInit(void);
void FlashEraseSlot(void);
//必须连续按顺序写入，且之前要调用FlashEraseSlot
void FlashWriteData(u16 data);
//取得Flash写入的次数
u16 FlashGetTimes(void);

#endif

