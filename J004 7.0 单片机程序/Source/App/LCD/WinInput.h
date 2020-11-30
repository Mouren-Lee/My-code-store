#include "interface.h"
#include "FunctionSet.h"
#include "PipeData.h"

#ifndef _WININPUT_H_
#define _WININPUT_H_

static const ST_ValueFormatScript PasswordScript={0,PIPE_PASSWORD,{0,65535,0,65535,0,5,0,0}};			  //改密码位数
/*
typedef struct tag_formatscript{
	u16 ValueMin;			//内部数值最小值
	u16 ValueMax;			//内部数值最大值
	u16 ShowMin;			//显示最小值
	u16 ShowMax;			//显示最大值
	u16 ShowOffset;			//向负值方向偏移量
	u8 integer;				//整数位数
	u8 fraction;			//小数位数
	u8 Flags;				//标志位
}ST_FormatScript;

typedef struct tag_valueformatscript{
	u8 ParStyle;			//变量类型
	u16 ParIndex;			//变量索引
	ST_FormatScript FormatScript;	//数值格式
}ST_ValueFormatScript;
*/
void SetInputValue(const ST_ValueFormatScript* pValue,u8 bPass);
void SetEnterCallback(FUNCTIONSETCALL* pCallback,u16 CmdID,const ST_PARAM* pParam);

#endif
