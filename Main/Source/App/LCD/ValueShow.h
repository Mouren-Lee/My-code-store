#include "interface.h"

#ifndef _VALUESHOW_H_
#define _VALUESHOW_H_

//数值输出
typedef struct tag_valueshowscript{
	GUI_RECT rect;				//必须放在第一个
	u8 ShowStyle;				//显示模式,必须放在第二个
	ST_DrawFrame frame;			//边框作图
//	ST_Safty safty;				//安全操作标签
	u16 FontIndex;				//字体索引
	u8 Flags;					//标志位
	ST_ValueFormatScript value;	//数据及格式
}ST_ValueShowScript;

typedef struct tag_valueshow{
	u8 sign;				//必须放在第一个
	u16 value;
}ST_ValueShow;

void ValueShowInit(const ST_ValueShowScript* pScript,ST_ValueShow* pVar);
u16 ValueShowCheck(const ST_ValueShowScript* pScript,ST_ValueShow* pVar,SW_ProcessMsg* pMsg);
void ValueShowDraw(const ST_ValueShowScript* pScript,ST_ValueShow* pVar);

#endif
