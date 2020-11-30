#include "interface.h"

#ifndef _STATESET_H_
#define _STATESET_H_

#define STATE_SHOW_PRESSED 0x40		//只显示是否为按下
#define STATE_CYCLE 0x10			//采用循环模式
#define STATE_KEEP 0x20				//保持按下时连续工作
#define STATE_DELAY 0x80			//按下第一次动作延时执行
#define STATE_STYLE_MASK 0x0F		//分开特殊标志位

#define STATE_DELAYDOIT (STATE_KEEP|STATE_DELAY)

#define STATE_SET_REVERT 0	  //按下1，松开0
#define STATE_SET_CONST 1	  //按下后复位常数
#define STATE_SET_INCREASE 2  //增加
#define STATE_SET_DESCEND 3	  //减少

typedef struct tag_statesetscript{
	GUI_RECT rect;			//必须放在第一个
	u8 ShowStyle;			//显示模式,必须放在第二个
	ST_DrawFrame frame;		//边框作图
//	ST_Safty safty;			//安全操作标签
	u16 FontIndex;			//字体索引
	u8 FontMax;				//最大字体
	u16 LabelIndex;			//标签索引
	u8 LabelMax;			//最大字库
	u8 ParStyle;			//变量类型
	u16 ParIndex;			//变量索引
	u8 SetStyle;			//设置类型
	u16 SetValue;			//递加值、递减值或设定值
	u16 SetMax;				//设定值上限
	u16 SetMin;				//设定值下限
	u16 Delay;				//迟滞时间
	u16 Speed;				//递加速度
}ST_StateSetScript;

typedef struct tag_stateset{
	u8 sign;
	u16 timer;
	u16 value;
}ST_StateSet;

void StateSetInit(const ST_StateSetScript* pScript,ST_StateSet* pVar);
u16 StateSetCheck(const ST_StateSetScript* pScript,ST_StateSet* pVar,SW_ProcessMsg* pMsg);
void StateSetDraw(const ST_StateSetScript* pScript,ST_StateSet* pVar);

#endif
