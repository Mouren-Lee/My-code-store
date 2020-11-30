#include "SWDataType.h"
#include "StaticLabel.h"
#include "StateShow.h"
#include "ValueShow.h"
#include "StateSet.h"
#include "SWWINDOW.h"
#include "FunctionSet.h"
#include "SWManage.h"
#include "WinAction.h"

//static const ST_StaticLabelScript staticlabelscript[]={

//};

//#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
//static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];


//static const ST_ValueShowScript valueshowscript[]={
//};

//#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
//static ST_ValueShow valueshow[VALUESHOW_COUNT];

//static const ST_StateSetScript statesetscript[]={
//		{{2,20,198,100},0,{2,11,3,0},1,0,STR_JIXING1,4,0,PIPE_BATCH_MODE,STATE_SET_INCREASE|STATE_CYCLE,1,4,0,0,0},	 //机型选择
//	{{202,20,398,100},0,{2,11,2,0},1,0,STR_XIANQIEHOUSONG,1,1,PIPE_FEED_CUT,STATE_SET_INCREASE|STATE_CYCLE,1,1,0,0,0},//先送后切
//};

//#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
//static ST_StateSet stateset[STATESET_COUNT];

static const ST_FunctionSetScript functionsetscript[]={
	{{402,20,598,100},0,{2,11,0,0},1,0,STR_HUIFUCHUCHANG,0,1,0,Win_LoadParameters,150},//恢复出厂
	{{1,375,120,475},0,{5,11,0,0},29,0,STR_ZHUYE,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
	{{121,375,240,475},0,{6,10,0,0},29,0,STR_ZHUCAIDAN,0,0,0,0},//ZHUCAIDAN
	{{602,20,798,100},0,{2,11,0,0},33,0,STR_FUCAIDAN,0,WINDOW04_INDEX,0,FunOpenWindow,40},//FUCAIDAN
	{{241,375,360,475},0,{7,11,0,0},29,0,STR_JIANSHICHUANGKOU,0,WINDOW06_INDEX,0,FunOpenWindow},//JIANSHICHUANGKOU
	{{361,375,480,475},0,{8,11,0,0},29,0,STR_XITONGJIANJIE,0,WINDOW07_INDEX,0,FunOpenWindow},//JIANJIE

};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={

//	{STATE_SHOW,stateshowscript,stateshow},	
	
//	{VALUE_SHOW,valueshowscript,valueshow},
//	{VALUE_SHOW,valueshowscript+1,valueshow+1},
//	{VALUE_SHOW,valueshowscript+2,valueshow+2},
//	{VALUE_SHOW,valueshowscript+3,valueshow+3},
//	{VALUE_SHOW,valueshowscript+4,valueshow+4},
//	{VALUE_SHOW,valueshowscript+5,valueshow+5},
//	{VALUE_SHOW,valueshowscript+6,valueshow+6},
//	{VALUE_SHOW,valueshowscript+7,valueshow+7},
//	{VALUE_SHOW,valueshowscript+8,valueshow+8},
//	{VALUE_SHOW,valueshowscript+9,valueshow+9},
//	{VALUE_SHOW,valueshowscript+10,valueshow+10},
//	{VALUE_SHOW,valueshowscript+11,valueshow+11},
////	{VALUE_SHOW,valueshowscript+12,valueshow+12},
//	
//	{STATIC_LABEL,staticlabelscript,staticlabelsign},
//	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
//	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
//	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},
//	{STATIC_LABEL,staticlabelscript+4,staticlabelsign+4},
//	{STATIC_LABEL,staticlabelscript+5,staticlabelsign+5},
//	{STATIC_LABEL,staticlabelscript+6,staticlabelsign+6},
//	{STATIC_LABEL,staticlabelscript+7,staticlabelsign+7},
//	{STATIC_LABEL,staticlabelscript+8,staticlabelsign+8},
//	{STATIC_LABEL,staticlabelscript+9,staticlabelsign+9},
//	{STATIC_LABEL,staticlabelscript+10,staticlabelsign+10},
//	{STATIC_LABEL,staticlabelscript+11,staticlabelsign+11},
//	{STATIC_LABEL,staticlabelscript+12,staticlabelsign+12},
//	{STATIC_LABEL,staticlabelscript+13,staticlabelsign+13},
//	{STATIC_LABEL,staticlabelscript+14,staticlabelsign+14},
//	{STATIC_LABEL,staticlabelscript+15,staticlabelsign+15},
//	{STATIC_LABEL,staticlabelscript+16,staticlabelsign+16},
//	{STATIC_LABEL,staticlabelscript+17,staticlabelsign+17},
//	{STATIC_LABEL,staticlabelscript+18,staticlabelsign+18},
//	{STATIC_LABEL,staticlabelscript+19,staticlabelsign+19},
//	{STATIC_LABEL,staticlabelscript+20,staticlabelsign+20},	
//	{STATIC_LABEL,staticlabelscript+21,staticlabelsign+21},
//	
//	{STATE_SET,statesetscript,stateset},
//	{STATE_SET,statesetscript+1,stateset+1},
//	{STATE_SET,statesetscript+2,stateset+2},
	
	{FUNCTION_SET,functionsetscript,functionset},	
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
	{FUNCTION_SET,functionsetscript+3,functionset+3},
	{FUNCTION_SET,functionsetscript+4,functionset+4},
	{FUNCTION_SET,functionsetscript+5,functionset+5},
//	{FUNCTION_SET,functionsetscript+6,functionset+6},
};

static void drawbackground(SW_SingleWindow* pWin)
{
//	GUI_RECT rect;								
	GUI_SetBkColor(pWin->bkColor);						 
	GUI_Clear();					

/*	rect.x0 = 0;										   //计数
	rect.y0 = 150;
	rect.x1 = 200+0;
	rect.y1 = 150+80;
	GUI_SetColor(GUI_WHITE);
	GUI_FillRectEx(&rect);
	Draw3DRect(&rect,GUI_DARKGRAY,GUI_LIGHTGRAY,2);
*/

//	GUI_SetColor(GUI_BLUE);
//  GUI_DrawHLine(368,0,800);	//HLine??,VLine??
//	GUI_DrawHLine(367,0,800);

}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window02={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
