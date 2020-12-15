#include "interface.h"

#ifndef _FUNCTIONSET_H_
#define _FUNCTIONSET_H_

typedef union tag_param{
	u32 dData;
	void* pData;
}ST_PARAM;

typedef void FUNCTIONSETCALL(u16 CmdID,const ST_PARAM* pParam);
#define NULL 0
typedef struct tag_functionsetscript{
	GUI_RECT rect;			//必须放在第一个
	u8 ShowStyle;			//显示模式,必须放在第二个
	ST_DrawFrame frame;		//边框作图
//	ST_Safty safty;			//安全操作标签
	U16 FontIndex;			//字体索引
	u8 FontMax;				//最大字体
	u16 LabelIndex;			//标签索引
	u8 LabelMax;			//最大字库
	u16 CmdID;				//调用参数
	ST_PARAM Param;				//调用参数
	FUNCTIONSETCALL* pCallBack;	//对应的回调函数	
	u16 Delay;				//延时动作时间
}ST_FunctionSetScript;

typedef struct tag_functionset{
	u8 sign;
	u16 timer;
}ST_FunctionSet;

void FunCloseCurWindow(u16 CmdID,const ST_PARAM* pParam);
void FunOpenWindow(u16 CmdID,const ST_PARAM* pParam);
void OpenSaveWindow(u16 CmdID,const ST_PARAM* pParam);
void FunctionSetInit(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar);
u16 FunctionSetCheck(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar,SW_ProcessMsg* pMsg);
void FunctionSetDraw(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar);


#endif
