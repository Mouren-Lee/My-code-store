#include "SWDataType.h"
#include "StaticLabel.h"
#include "StateShow.h"
#include "ValueShow.h"
#include "StateSet.h"
#include "SWWINDOW.h"
#include "FunctionSet.h"
#include "SWManage.h"
#include "WinAction.h"

static const ST_StaticLabelScript staticlabelscript[]={
	{{3,5,800,101},0,{0,0,0,0},5,STR_ZHUCAIDAN4,0},                //主菜单说明4:
	{{3,101,800,197},0,{0,0,0,0},5,STR_ZHUCAIDAN5,0},                //主菜单说明5:
	{{3,197,800,293},0,{0,0,0,0},5,STR_ZHUCAIDAN6,0},                //主菜单说明6:
	{{3,293,800,389},0,{0,0,0,0},5,STR_ZHUCAIDAN7,0},                //主菜单说明7:
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];


static const ST_FunctionSetScript functionsetscript[]={
//	{{620,180,770,250},0,{2,8,0,0},1,0,STR_SETPIYEAR,0,WINDOW02_INDEX,0,OpenSetWindow},//参数设置
	{{0,420,0+160,430+50},0,{2,11,0,0},1,0,STR_SHANGYIYE,0,WINDOW08_INDEX,0,FunOpenWindow},//ZHUYE
//	{{160,420,160+160,430+50},0,{2,11,0,0},1,0,STR_ZHUCAIDAN,0,WINDOW02_INDEX,0,SWOpenWindow},//ZHUYE
	{{320,420,320+160,430+50},0,{2,11,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
//	{{480,420,480+160,430+50},0,{2,11,0,0},1,0,STR_JIANSHICHUANGKOU,0,WINDOW06_INDEX,0,SWOpenWindow},//ZHUYE
	{{640,420,640+160,430+50},0,{2,11,0,0},1,0,STR_XIAYIYE,0,WINDOW10_INDEX,0,FunOpenWindow},//ZHUYE
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={ 
	{STATIC_LABEL,staticlabelscript,staticlabelsign},
	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},


	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
//	{FUNCTION_SET,functionsetscript+3,functionset+3},
//	{FUNCTION_SET,functionsetscript+4,functionset+4},
};

static void drawbackground(SW_SingleWindow* pWin)
{
//	GUI_RECT rect;								
	GUI_SetBkColor(pWin->bkColor);						 
	GUI_Clear();

	GUI_SetColor(GUI_RED);			
	GUI_SetFont(&GUI_FontHZHT_24);
	GUI_GotoXY(540,435);
	GUI_DispString("(2)");
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}

const SW_SingleWindowScript Window09={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	GUI_WHITE,
	DefaultProc0,
	drawbackground0,
};

