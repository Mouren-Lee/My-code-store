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

static const ST_StaticLabelScript staticlabelscript[]={
	{{20,120,180,170},0,{0,0,0,0},2,STR_TOPIC_SYSTEM2,0},//系统2
	{{20,40,330,100},0,{3,2,0,0},2,STR_MIMA2,0},  //修改密码2：

};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

static const ST_ValueShowScript valueshowscript[]={
  {{20,40,320,100},SW_TRANS,{0,0,0,0},3,SW_ENABLE_EDIT,{0,PIPE_MIMA2,{0,65535,0,65535,0,5,0,0}}},//密码2：
	{{191,120,330,170},0,{3,2,0,0},3,SW_ENABLE_EDIT,{0,PIPE_SYSTEM2,{0,65535,0,65535,0,5,0,0}}},//系统2
		


};

#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
static ST_ValueShow valueshow[VALUESHOW_COUNT];

//static const ST_StateSetScript statesetscript[]={
//	{{620,30,770,100},0,{2,2,1,0},1,0,STR_FUWEI,0,1,PIPE_STOP_F,STATE_SET_CONST,1,0,0,0,0},//复位
//};

//#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
//static ST_StateSet stateset[STATESET_COUNT];

static const ST_FunctionSetScript functionsetscript[]={
	{{600,380,750,450},0,{2,2,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,OpenSaveWindow},//返回
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={
	
	
//	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
//	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
//	{STATE_SHOW,stateshowscript,stateshow},		


//	{VALUE_SHOW,valueshowscript+5,valueshow+5},
//	{VALUE_SHOW,valueshowscript+6,valueshow+6},
//	{VALUE_SHOW,valueshowscript+7,valueshow+7},
//	{VALUE_SHOW,valueshowscript+8,valueshow+8},
//	{VALUE_SHOW,valueshowscript+9,valueshow+9},

//	{STATIC_LABEL,staticlabelscript+5,staticlabelsign+5},
//	{STATIC_LABEL,staticlabelscript+6,staticlabelsign+6},
//	{STATIC_LABEL,staticlabelscript+7,staticlabelsign+7},

//	{STATE_SET,statesetscript,stateset},

	{FUNCTION_SET,functionsetscript,functionset},
//	{FUNCTION_SET,functionsetscript+1,functionset+1},

   	
	{VALUE_SHOW,valueshowscript+1,valueshow+1},
	{VALUE_SHOW,valueshowscript+2,valueshow+2},
//	{VALUE_SHOW,valueshowscript+3,valueshow+3},
//	{VALUE_SHOW,valueshowscript+4,valueshow+4},


	{STATIC_LABEL,staticlabelscript,staticlabelsign},
	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
//	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
//	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},
//	{STATIC_LABEL,staticlabelscript+4,staticlabelsign+4},

   {VALUE_SHOW,valueshowscript,valueshow},
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


const SW_SingleWindowScript Window05={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
