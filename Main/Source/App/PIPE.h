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
////����SIZE���԰���Ϊ��λ2���ֽ�
//#define PIPE_FLASH_HEAD 0
//#define PIPE_FLASH_SIZE 87			//���ɴ���127
//#define PIPE_BKP_HEAD PIPE_FLASH_SIZE
//#define PIPE_BKP_SIZE 25			//���ݲ�ͬоƬ��С��ͬ��Ҳ����RAM����ʹ��
//#define PIPE_RAM_HEAD	(PIPE_BKP_HEAD+PIPE_BKP_SIZE)
//#define PIPE_RAM_SIZE 40		//ԭΪ30	
//#define PIPE_DATA_SIZE (PIPE_BKP_SIZE+PIPE_FLASH_SIZE+PIPE_RAM_SIZE)
////bBitΪ0ʱ��Ӧ16λ��,�����Ӧλ

#define FLASH_SAVE_SPACE 24000          //12���ӱ���һ��flash����
////ǰ̨��������
//void FORE_SetIO(u16 index,u16 value);
//void FORE_SetBuf(u16 index,u16 value);
////ǰ̨��ȡ����
//u16 FORE_GetIO(u16 index);
//u16 FORE_GetBuf(u16 index);

////��̨��������
//void BACK_SetIO(u16 index,u16 value);
//void BACK_SetBuf(u16 index,u16 value);
////��̨ȡ������
//u16 BACK_GetIO(u16 index);
//u16 BACK_GetBuf(u16 index);
////�ܵ���ʼ����ر���
void PIPE_Init(void);
////ǿ��FLASH����
void PIPE_SaveFlash(void);

void PIPE_BackSaveFlash(void);
////��ʱ������ܵ�����
void PIPE_Check(void);
void BackSaveParameters(void);
void BackLoadParameters(void);

//u16 PIPE_FlashTimes(void);

#endif
