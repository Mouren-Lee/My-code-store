#include "LCDPLC.h"

#ifndef _PIPE_H_
#define _PIPE_H_

//-------------------------------------------
#define PAR_SIZE 150
#define BKP_DR_NUMBER	42

u16 PAR_GetData(u16 index);
void PAR_SetData(u16 index,u16 value);
void PAR_Initial(void);
void PAR_SetDataBuf(u8 index,const u16* pSrc,u16 count);
const u16* PAR_GetDataBuf(u8 index);


//------------------------------------------
////所有SIZE都以半字为单位2个字节
//#define PIPE_FLASH_HEAD 0
//#define PIPE_FLASH_SIZE 87			//不可大于127
//#define PIPE_BKP_HEAD PIPE_FLASH_SIZE
//#define PIPE_BKP_SIZE 25			//根据不同芯片大小不同，也可作RAM类型使用
//#define PIPE_RAM_HEAD	(PIPE_BKP_HEAD+PIPE_BKP_SIZE)
//#define PIPE_RAM_SIZE 40		//原为30	
//#define PIPE_DATA_SIZE (PIPE_BKP_SIZE+PIPE_FLASH_SIZE+PIPE_RAM_SIZE)
////bBit为0时对应16位数,否则对应位

#define FLASH_SAVE_SPACE 24000          //12分钟保存一次flash数据
////前台设置数据
//void FORE_SetIO(u16 index,u16 value);
//void FORE_SetBuf(u16 index,u16 value);
////前台读取数据
//u16 FORE_GetIO(u16 index);
//u16 FORE_GetBuf(u16 index);

////后台设置数据
//void BACK_SetIO(u16 index,u16 value);
//void BACK_SetBuf(u16 index,u16 value);
////后台取得数据
//u16 BACK_GetIO(u16 index);
//u16 BACK_GetBuf(u16 index);
////管道初始化相关变量
void PIPE_Init(void);
////强制FLASH存贮
void PIPE_SaveFlash(void);

void PIPE_BackSaveFlash(void);
////定时检查管理管道数据
void PIPE_Check(void);
void BackSaveParameters(void);
void BackLoadParameters(void);

//u16 PIPE_FlashTimes(void);

#endif
