#include "LCDPLC.h"

#ifndef _VSPI_DAC_H_
#define _VSPI_DAC_H_

#define DAC_M4   0
#define DAC_M1	 1
#define DAC_M2	 2
#define DAC_M3	 3

//初始化DAC模块相关变量
void VSPI_Init(void);
//定时管理DAC模块
void VSPI_Manage(void);
//读取当前通道输出值0~1023对应0~10V
u16 VSPI_GetValue(u8 index);
//设置某通道输出0~1023对应0~10V
void VSPI_SetValue(u8 index,u16 value);
//设置通道偏移0对应-128，128对应0，255对应127
void VSPI_SetOffset(u8 index,u8 offset);

#endif
