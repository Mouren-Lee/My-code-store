#include "LCDPLC.h"
#include "Modbus.h"

#ifndef _USART3_H_
#define _USART3_H_

//#define USART2_OVTIME2 200
////#define USART1_FRAME_OVTIME 20
//#define USART2_PAR_SIZE 65

//#define USART1_POWERON 127
//#define TX_DELGY 20

//===============================
//#define READ_COIL     01
//#define READ_DI       02
//#define READ_HLD_REG  03
//#define READ_AI       04
//#define SET_COIL      05
//#define SET_HLD_REG   06
//#define WRITE_COIL    15
//#define WRITE_HLD_REG 16


#define HI(n) ((n)>>8)
#define LOW(n) ((n)&0xff)



//================================
#define SET_RX3() (GPIOB->BRR = GPIO_Pin_12)
#define SET_TX3() (GPIOB->BSRR = GPIO_Pin_12)

//#define SET_RX()  (GPIOC->BRR = GPIO_Pin_5)
//#define SET_RX2() (GPIOC->BRR = GPIO_Pin_4)                

//#define SET_TX()  (GPIOC->BSRR = GPIO_Pin_5)
//#define SET_TX2() (GPIOC->BSRR = GPIO_Pin_4)

//配置异步串口
void USART3_Configuration(void);
//实始化相关变量
//void USART1_Init(void);
//定时调用检查管理通讯接口
//void USART2_Manage(void);
//定时调用检查超时状态
//void USART1_ChkOVtime(void);
////设置MODBUS通讯中开关量
//void USART1_SetIO(u8 index,u8 value);
////取得MODBUS通讯中的开关量状态
//u8 USART1_GetIO(u8 index);
////设置MODBUS通讯中一个变量
//void USART1_SetBuf(u8 index,u16 value);
////取得MOBUS通讯中一个变量
//u16 USART1_GetBuf(u8 index);

////设置16个状态,index为起始号除16
//void USART1_SetIO16(u8 index,u16 value);
////读取16个IO状态,index为起始号除16
//u16 USART1_GetIO16(u8 index);

//void PAR_Initial(void);
//void Modbus_01_Solve(void);
//void Modbus_02_Solve(void);
//void Modbus_03_Solve(void);
//void Modbus_05_Solve(void);
//void Modbus_06_Solve(void);
//void Modbus_15_Solve(void);
//void Modbus_16_Solve(void);


//void Master_01_Slove( u8 board_adr,u16 start_address, u16 lenth );
//void Master_03_Slove( u8 board_adr,u16 start_address,u16 lenth );


//void RS485_TX_Service(void);
//void Master_Service(u8 SlaverAddr,u8 Fuction,u16 StartAddr,u16 ValueOrLenth);
//void RS485_RX_Service(void);
//void modbus_rtu(void);
//void Master_Clear(void);
//void USART2_RecDataTime(void);
//void Master_OVER(void);

#endif

