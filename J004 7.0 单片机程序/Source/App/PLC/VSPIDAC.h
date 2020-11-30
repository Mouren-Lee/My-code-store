#include "LCDPLC.h"

#ifndef _VSPI_DAC_H_
#define _VSPI_DAC_H_

#define DAC_M4   0
#define DAC_M1	 1
#define DAC_M2	 2
#define DAC_M3	 3

//��ʼ��DACģ����ر���
void VSPI_Init(void);
//��ʱ����DACģ��
void VSPI_Manage(void);
//��ȡ��ǰͨ�����ֵ0~1023��Ӧ0~10V
u16 VSPI_GetValue(u8 index);
//����ĳͨ�����0~1023��Ӧ0~10V
void VSPI_SetValue(u8 index,u16 value);
//����ͨ��ƫ��0��Ӧ-128��128��Ӧ0��255��Ӧ127
void VSPI_SetOffset(u8 index,u8 offset);

#endif
