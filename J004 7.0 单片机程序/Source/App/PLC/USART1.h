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

//配置异步串口
void USART1_Configuration(void);
//实始化相关变量
//void USART1_Init(void);
//定时调用检查管理通讯接口
//void USART1_Manage(void);
//定时调用检查超时状态
//void USART1_ChkOVtime(void);
//设置MODBUS通讯中开关量
void USART1_SetIO(u8 index,u8 value);
//取得MODBUS通讯中的开关量状态
u8 USART1_GetIO(u8 index);
//设置MODBUS通讯中一个变量
void USART1_SetBuf(u16 index,u16 value);
//取得MOBUS通讯中一个变量
u16 USART1_GetBuf(u16 index);

//设置16个状态,index为起始号除16
//void USART1_SetIO16(u8 index,u16 value);
//读取16个IO状态,index为起始号除16
//u16 USART1_GetIO16(u8 index);
void RS485_Service(void);
void RS485_SendData(u8 *buff,u8 len);

//void PAR_Initial(void);










#endif

