#ifndef _IOMANAGE_H_
#define _IOMANAGE_H_

#include "LCDPLC.h"

#define X01 GPIO_Pin_0
#define X02 GPIO_Pin_1
#define X03 GPIO_Pin_2
#define X04 GPIO_Pin_3
#define X05 GPIO_Pin_4
#define X06 GPIO_Pin_5
#define X07 GPIO_Pin_6
#define X08 GPIO_Pin_7
#define X09 GPIO_Pin_8
#define X10 GPIO_Pin_9
#define X11 GPIO_Pin_10
#define X12 GPIO_Pin_11
#define X13 GPIO_Pin_12
#define X14 GPIO_Pin_13
#define X15 GPIO_Pin_14
#define X16 GPIO_Pin_15
#define X17 GPIO_Pin_16
#define X18 GPIO_Pin_17
#define X19 GPIO_Pin_18
#define X20 GPIO_Pin_19
#define X21 GPIO_Pin_20
#define X22 GPIO_Pin_21






#define Y01 GPIO_Pin_0
#define Y02 GPIO_Pin_1
#define Y03 GPIO_Pin_2
#define Y04 GPIO_Pin_3
#define Y05 GPIO_Pin_4
#define Y06 GPIO_Pin_5
#define Y07 GPIO_Pin_6
#define Y08 GPIO_Pin_7
#define Y09 GPIO_Pin_8
#define Y10 GPIO_Pin_9
#define Y11 GPIO_Pin_10
#define Y12 GPIO_Pin_11
#define Y13 GPIO_Pin_12
#define Y14 GPIO_Pin_13
#define Y15 GPIO_Pin_14
#define Y16 GPIO_Pin_15
#define Y17 GPIO_Pin_16
#define Y18 GPIO_Pin_17
#define Y19 GPIO_Pin_18
#define Y20 GPIO_Pin_19
#define Y21 GPIO_Pin_20
#define Y22 GPIO_Pin_21
#define Y23 GPIO_Pin_22
#define Y24 GPIO_Pin_23
#define Y25 GPIO_Pin_24
#define Y26 GPIO_Pin_25
#define Y27 GPIO_Pin_26
#define Y28 GPIO_Pin_27
#define Y29 GPIO_Pin_28
#define Y30 GPIO_Pin_29
#define Y31 GPIO_Pin_30
#define Y32 GPIO_Pin_31


#define SW1 BIT19
#define SW2	BIT18
#define SW3 BIT17
#define SW4 BIT16

//��ʼ����ر���
void IO_Init(void);
//��ʱ����DIģ��
void IO_InCheck(void);
//ȡ��16��DI״̬
u32 IO_GetDI32(void);
//ȡ��ָ��DI״̬
u8 IO_GetDI(u32 mask);
//���DI״̬�Ƿ����仯
u8 IO_GetDIChange(u32 Mask);   //�����������ޱ仯
//��ʱ����DOģ��
void IO_OutPut(void);
//�趨16��DO״̬
void IO_SetDO32(u32 value);
//ȡ�õ�ǰDO���״̬
u32 IO_GetDO32(void);
//����ָ��λDO״̬ΪON
u8 IO_GetDO(u32 Mask);

void IO_SetDO(u32 mask);
//��λָ��λDO״̬ΪOFF
void IO_ResetDO(u32 mask);
//����ָ��λDOΪ����ֵ
void IO_SetDOValue(u32 mask,u8 bSet);


void IO_SetDO32(u32 value);

//u8 Rev_GetDI(u32 Mask);
//u8 Rev_GetDIChange(u32 Mask);

//u8 Rev_GetDO(u16 Mask);
//void Rev_SetDO(u16 mask);
//void Rev_ResetDO(u16 mask);
//void Rev_SetDOValue(u16 mask,u8 bSet);
//void Rev_Outconf(void);

//void Rev_Inconf(void);

//void IO_SetRO(void);
//void IO_ResetRO(void);

#endif
