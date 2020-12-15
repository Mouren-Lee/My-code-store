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
	{{0,0,800,50},0,{0,0,0,0},1,STR_ZHUCAIDAN,0},                //主页:
	{{3,50,800,194},0,{0,0,0,0},5,STR_ZHUCAIDAN1,0},                //主菜单说明1:
	{{3,194,800,290},0,{0,0,0,0},5,STR_ZHUCAIDAN2,0},                //主菜单说明2:
	{{3,290,800,410},0,{0,0,0,0},5,STR_ZHUCAIDAN3,0},                //主菜单说明3:
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];


static const ST_FunctionSetScript functionsetscript[]={
//	{{620,180,770,250},0,{2,8,0,0},1,0,STR_SETPIYEAR,0,WINDOW02_INDEX,0,OpenSetWindow},//参数设置
//	{{0,420,0+160,430+50},0,{2,11,0,0},1,0,STR_SHANGYIYE,0,WINDOW09_INDEX,0,SWOpenWindow},//ZHUYE
//	{{160,420,160+160,430+50},0,{2,11,0,0},1,0,STR_ZHUCAIDAN,0,WINDOW02_INDEX,0,SWOpenWindow},//ZHUYE
	{{320,420,320+160,430+50},0,{2,11,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
//	{{480,420,480+160,430+50},0,{2,11,0,0},1,0,STR_JIANSHICHUANGKOU,0,WINDOW06_INDEX,0,SWOpenWindow},//ZHUYE
	{{640,420,640+160,430+50},0,{2,11,0,0},1,0,STR_XIAYIYE,0,WINDOW09_INDEX,0,FunOpenWindow},//ZHUYE
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={ 
	{STATIC_LABEL,staticlabelscript,staticlabelsign},
	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},
//	{STATIC_LABEL,staticlabelscript+4,staticlabelsign+4},
//	{STATIC_LABEL,staticlabelscript+5,staticlabelsign+5},
//	{STATIC_LABEL,staticlabelscript+6,staticlabelsign+6},
//	{STATIC_LABEL,staticlabelscript+7,staticlabelsign+7},
//	{STATIC_LABEL,staticlabelscript+8,staticlabelsign+8},
//	{STATIC_LABEL,staticlabelscript+9,staticlabelsign+9},
//	{STATIC_LABEL,staticlabelscript+10,staticlabelsign+10},
//	{STATIC_LABEL,staticlabelscript+11,staticlabelsign+11},
//	{STATIC_LABEL,staticlabelscript+12,staticlabelsign+12},
	
	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
//	{FUNCTION_SET,functionsetscript+2,functionset+2},
//	{FUNCTION_SET,functionsetscript+3,functionset+3},
//	{FUNCTION_SET,functionsetscript+4,functionset+4},
};

static void drawbackground(SW_SingleWindow* pWin)
{
//	static u16 i;

//	GUI_RECT rect;								
	GUI_SetBkColor(pWin->bkColor);						 
	GUI_Clear();

	GUI_SetColor(GUI_RED);			
	GUI_SetFont(&GUI_FontHZHT_24);
	GUI_GotoXY(540,435);
	GUI_DispString("(1)");
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window08={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	GUI_WHITE,
	DefaultProc0,
	drawbackground0,
};
