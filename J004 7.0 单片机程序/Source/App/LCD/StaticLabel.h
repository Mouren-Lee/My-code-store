#include "interface.h"

#ifndef _STATICLABEL_H_
#define _STATICLABEL_H_

//静态标签
typedef struct tag_staticlabelscript{
	GUI_RECT rect;			//必须放在第一个
	u8 ShowStyle;			//显示模式,必须放在第二个
	ST_DrawFrame frame;		//边框作图
//	ST_Safty safty;			//安全操作标签
	u16 FontIndex;				//文字字体
	u16 LabelIndex;				//字库索引
	u16 ShowDelay;				//时间间隔
}ST_StaticLabelScript;

typedef struct tag_staticlabel{
	u8 sign;				//必须放在第一个
	u16 timer;
}ST_StaticLabel;

void StaticLabelInit(const ST_StaticLabelScript* pScript,ST_StaticLabel *pVar);
u16 StaticLabelCheck(const ST_StaticLabelScript* pScript,ST_StaticLabel *pVar,SW_ProcessMsg *pMsg);
void StaticLabelDraw(const ST_StaticLabelScript* pScript,ST_StaticLabel *PVar);

#endif

