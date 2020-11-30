#ifndef _VALUETRANS_H_
#define _VALUETRANS_H_


#include "Interface.h"
#include "SWDataType.h"

//数据格式前面填0
#define VFM_FILL BIT0

//将数值按格式缩放
u16 Value2Show(u16 value,const ST_FormatScript* pFormat);
//将显示的值按格式缩放到内部数值
u16 Show2Value(u16 value,const ST_FormatScript* pFormat);
//将数据转化为字符串
u8 Value2Str(u8* str,u16 value,const ST_FormatScript* pFormat);
//将字符串按格式转化为数据
u8 Str2Value(u8* str,u16* pValue,const ST_FormatScript* pFormat);

u8 AddCharValue(u8* str,u8 num,const ST_FormatScript* pFormat);

#endif
