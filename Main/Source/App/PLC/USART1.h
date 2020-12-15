#include "LCDPLC.h"
#include "Modbus.h"

#ifndef _USART1_H_
#define _USART1_H_

#define USART1_OVTIME 200
#define USART1_FRAME_OVTIME 20
#define USART1_PAR_SIZE 256

#define USART1_POWERON 127
#define TX_DELGY 20

#define SET_RX() (GPIOA->BRR = GPIO_Pin_11)
#define SET_TX() (GPIOA->BSRR = GPIO_Pin_11)

//�����첽����
void USART1_Configuration(void);
//ʵʼ����ر���
//void USART1_Init(void);
//��ʱ���ü�����ͨѶ�ӿ�
//void USART1_Manage(void);
//��ʱ���ü�鳬ʱ״̬
//void USART1_ChkOVtime(void);
//����MODBUSͨѶ�п�����
void USART1_SetIO(u8 index,u8 value);
//ȡ��MODBUSͨѶ�еĿ�����״̬
u8 USART1_GetIO(u8 index);
//����MODBUSͨѶ��һ������
void USART1_SetBuf(u16 index,u16 value);
//ȡ��MOBUSͨѶ��һ������
u16 USART1_GetBuf(u16 index);

//����16��״̬,indexΪ��ʼ�ų�16
//void USART1_SetIO16(u8 index,u16 value);
//��ȡ16��IO״̬,indexΪ��ʼ�ų�16
//u16 USART1_GetIO16(u8 index);
void RS485_Service(void);
void RS485_SendData(u8 *buff,u8 len);

//void PAR_Initial(void);










#endif

