#include "interface.h"

#ifndef _STATESHOW_H_
#define _STATESHOW_H_

//静态标签
typedef struct tag_stateshowscript{
	GUI_RECT rect;			//必须放在第一个
	u8 ShowStyle;			//显示模式,必须放在第二个
	ST_DrawFrame frame;		//边框作图
//	ST_Safty safty;			//安全操作标签
	u16 FontIndex;			//字体索引
	u8 FontMax;				//最大字体
	u16 LabelIndex;			//标签索引
	u8 LabelMax;			//最大字库
	u16 ShowDelay;			//闪烁间隔
	u8 ParStyle;			//变量类型
	u16 ParIndex;			//变量索引
}ST_StateShowScript;

typedef struct tag_stateshow{
	u8 sign;				//必须放在第一个
	u16 timer;
	u16 value;
}ST_StateShow;

void StateShowInit(const ST_StateShowScript* pScript,ST_StateShow* pVar);
u16 StateShowCheck(const ST_StateShowScript* pScript,ST_StateShow* pVar,SW_ProcessMsg* pMsg);
void StateShowDraw(const ST_StateShowScript* pScript,ST_StateShow* pVar);


#endif

