#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f10x.h"


//������0��ʼ
u16 FlashGetData(u16 index);
void FlashInit(void);
void FlashEraseSlot(void);
//����������˳��д�룬��֮ǰҪ����FlashEraseSlot
void FlashWriteData(u16 data);
//ȡ��Flashд��Ĵ���
u16 FlashGetTimes(void);

#endif

