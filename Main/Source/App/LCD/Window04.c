#include "SWDataType.h"
#include "StaticLabel.h"
#include "StateShow.h"
#include "ValueShow.h"
#include "StateSet.h"
#include "SWWINDOW.h"
#include "FunctionSet.h"
#include "SWManage.h"
#include "PipeData.h"
#include "RealTimer.h"

//static const ST_StaticLabelScript staticlabelscript[]={

//	
//};

//#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
//static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

//static const ST_ValueShowScript valueshowscript[]={

//};

//#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
//static ST_ValueShow valueshow[VALUESHOW_COUNT];


//static const ST_StateSetScript statesetscript[]={
//	{{602,198,798,274},0,{2,11,0,0},1,0,STR_BUJINKUAISU,3,0,PIPE_CURVELINE,STATE_SET_INCREASE|STATE_CYCLE|STATE_DELAYDOIT,1,3,0,75,65535},    //曲线选择
//};

//#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
//static ST_StateSet stateset[STATESET_COUNT];


static void SystemAdjust(u16 CmdID,const ST_PARAM* pParam)  
{
	if(BACK_GetBuf(PIPE_SYSTEM1)>30&&BACK_GetBuf(PIPE_SYSTEM2)>30)
	{
		BACK_SetBuf(PIPE_SYSTEM1,25);	 //1
		BACK_SetBuf(PIPE_SYSTEM2,10);	 //2
  }
}

static const ST_FunctionSetScript functionsetscript[]={
	{{602,278,798,354},0,{2,11,0,0},16,0,STR_XITONGJIAOZHENG,0,0,0,SystemAdjust,150},   //系统校正
	{{620,390,770,460},0,{2,2,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,OpenSaveWindow},         //返回

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
//	{VALUE_SHOW,valueshowscript+12,valueshow+12},
//	{VALUE_SHOW,valueshowscript+13,valueshow+13},
//	{VALUE_SHOW,valueshowscript+14,valueshow+14},
//  {VALUE_SHOW,valueshowscript+15,valueshow+15},
	
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
//	{STATIC_LABEL,staticlabelscript+22,staticlabelsign+22},
//	{STATIC_LABEL,staticlabelscript+23,staticlabelsign+23},
//	{STATIC_LABEL,staticlabelscript+24,staticlabelsign+24},		
//	{STATIC_LABEL,staticlabelscript+25,staticlabelsign+25},
//	{STATIC_LABEL,staticlabelscript+26,staticlabelsign+26},
	
//	{STATE_SET,statesetscript,stateset},

	{FUNCTION_SET,functionsetscript,functionset},	
	{FUNCTION_SET,functionsetscript+1,functionset+1},
//	{FUNCTION_SET,functionsetscript+2,functionset+2},
//	{FUNCTION_SET,functionsetscript+3,functionset+3},
//	{FUNCTION_SET,functionsetscript+4,functionset+4},
//	{FUNCTION_SET,functionsetscript+5,functionset+5},
};

static void drawbackground(SW_SingleWindow* pWin)		  
{
//	GUI_RECT rect;										 
	GUI_SetBkColor(pWin->bkColor);
	GUI_Clear();
	
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window04={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
