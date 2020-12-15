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
	{{2,38,198,62},0,{0,0,0,0},4,STR_BUPIANCHANGDU,0},  //长度设定二
	{{156,91,192,102},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)
	{{202,38,398,62},0,{0,0,0,0},4,STR_JIAOGUNZHOUCHANG2,0},   //胶辊周长二 补片周长
  {{356,91,392,102},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)		
	
	{{402,38,598,62},0,{0,0,0,0},12,STR_SONGLIAOSUDU2,0},      //	送料速度二
	{{602,38,798,62},0,{0,0,0,0},4,STR_ZUIGAOPINLV2,0},       //伺服转速二
	{{756,84,798,102},0,{0,0,0,0},19,STR_HEZI,0},     //HZ
	{{2,118,198,142},0,{0,0,0,0},4,STR_LADUANCHANGDU,0},  //拉断长度
	{{156,171,192,182},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)	
	
 {{2,278,198,302},0,{0,0,0,0},4,STR_DINGLIAOGESHU,0},  //顶料个数
  	{{156,331,192,355},0,{0,0,0,0},19,STR_GE,0},             //个
 {{202,278,398,302},0,{0,0,0,0},4,STR_TUODAIPISHU,0},  //脱袋批数
  	{{340,324,392,342},0,{0,0,0,0},19,STR_GEMEIPI,0},             //批
 {{402,278,598,302},0,{0,0,0,0},4,STR_DUOZOUCHANGDU,0},  //多走长度
 {{556,331,592,342},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)	
 ////////////ZXS
  {{2,358,198,382},0,{0,0,0,0},4,STR_TuiLiaoChangDu,0},  //退料长度
 {{156,411,192,435},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)
 {{202,358,398,382},0,{0,0,0,0},4,STR_TuoDaiZhiHou,0},  //脱袋滞后
 {{356,411,392,435},0,{0,0,0,0},19,STR_MIAO,0},           //(秒)  {{356,312,398,330},0,{0,0,0,0},19,STR_MIAO,0},    //秒
//////////////ZXS

};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

static const ST_ValueShowScript valueshowscript[]={
	{{2,38,198,114},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_LENGTH2,{0,65000,0,65000,0,4,1,0}}},//长度设定(毫米)二   补片长度
	{{202,38,398,114},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_ROLLER2,{0,31416,0,31416,0,4,1,0}}},	   //胶辊周长:二
	{{402,38,598,114},0,{24,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_SPEED_STEP2,{40,4000,40,4000,0,4,0,0}}},  //送料速度二
  {{602,38,798,114},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_TOP_SPEED2,{300,40000,300,40000,0,5,0,0}}},   //伺服转速二
		
	{{2,118,198,194},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_SNAP_LENGTH,{0,990,0,990,0,2,1,0}}},         //拉断长度	
		
	{{146,216,275,270},0,{1,19,0,0},34,0,{0,PIPE_BATCH_COUNT,{0,64000,0,64000,0,5,0,0}}},       //批数		
		
	{{2,278,198,354},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_PRESS_CNT,{0,9,0,9,0,1,0,0}}},            //顶料个数
	{{202,278,398,354},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_DRAG_BATCH,{1,19,1,19,0,2,0,0}}},            //脱袋批数
  {{402,278,598,354},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_MORE_LENGTH,{0,50000,0,50000,0,4,1,0}}},         //多走长度	
  ////////////zxs
   	{{2,358,198,434},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_TLCD,{0,999,0,999,0,2,1,0}}},            //退料长度*0.1mm
	{{202,358,398,434},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_TDZH,{0,10000,0,500,0,1,2,0}}},            //脱袋滞后*0.01s
  ////////////zxs
  	
};

#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
static ST_ValueShow valueshow[VALUESHOW_COUNT];


static const ST_StateSetScript statesetscript[]={
	{{300,126,450,190},0,{14,11,1,0},18,0,STR_DIANJIN,0,1,PIPE_JOGF2,STATE_SET_REVERT,1,0,0,0,0},				     //点进2
	{{550,126,700,190},0,{15,11,1,0},18,0,STR_DIANTUI,0,1,PIPE_JOGB2,STATE_SET_REVERT,1,0,0,0,0},				     //点退2
  {{11,216,130,270},0,{2,17,0,0},35,0,STR_PISHU,0,1,PIPE_BATCH_CLR,STATE_SET_CONST,1,0,0,0,0},				     //批数清零	
};

#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
static ST_StateSet stateset[STATESET_COUNT];

static const ST_FunctionSetScript functionsetscript[]={
	{{620,380,770,450},0,{2,2,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,OpenSaveWindow},//返回
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];


static const SW_CtrlScript SW_Ctrls[]={

//	{STATE_SHOW,stateshowscript,stateshow},		

	{STATE_SET,statesetscript,stateset},
	{STATE_SET,statesetscript+1,stateset+1},
	{STATE_SET,statesetscript+2,stateset+2},
//	{STATE_SET,statesetscript+3,stateset+3},
//	{STATE_SET,statesetscript+4,stateset+4},
//	{STATE_SET,statesetscript+5,stateset+5},
//	{STATE_SET,statesetscript+6,stateset+6},
//	{STATE_SET,statesetscript+7,stateset+7},
//	{STATE_SET,statesetscript+8,stateset+8},	
	
	{VALUE_SHOW,valueshowscript,valueshow},
	{VALUE_SHOW,valueshowscript+1,valueshow+1},
	{VALUE_SHOW,valueshowscript+2,valueshow+2},
	{VALUE_SHOW,valueshowscript+3,valueshow+3},
	{VALUE_SHOW,valueshowscript+4,valueshow+4},
	{VALUE_SHOW,valueshowscript+5,valueshow+5},
	{VALUE_SHOW,valueshowscript+6,valueshow+6},
	{VALUE_SHOW,valueshowscript+7,valueshow+7},
	{VALUE_SHOW,valueshowscript+8,valueshow+8},
	{VALUE_SHOW,valueshowscript+9,valueshow+9},
   {VALUE_SHOW,valueshowscript+10,valueshow+10},
	
	{STATIC_LABEL,staticlabelscript,staticlabelsign},
	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},
	{STATIC_LABEL,staticlabelscript+4,staticlabelsign+4},
	{STATIC_LABEL,staticlabelscript+5,staticlabelsign+5},
	{STATIC_LABEL,staticlabelscript+6,staticlabelsign+6},
	{STATIC_LABEL,staticlabelscript+7,staticlabelsign+7},	
	{STATIC_LABEL,staticlabelscript+8,staticlabelsign+8},
	{STATIC_LABEL,staticlabelscript+9,staticlabelsign+9},
	{STATIC_LABEL,staticlabelscript+10,staticlabelsign+10},	
	{STATIC_LABEL,staticlabelscript+11,staticlabelsign+11},	
	{STATIC_LABEL,staticlabelscript+12,staticlabelsign+12},	
	{STATIC_LABEL,staticlabelscript+13,staticlabelsign+13},	
	{STATIC_LABEL,staticlabelscript+14,staticlabelsign+14},	
	{STATIC_LABEL,staticlabelscript+15,staticlabelsign+15},
	{STATIC_LABEL,staticlabelscript+16,staticlabelsign+16},	
	{STATIC_LABEL,staticlabelscript+17,staticlabelsign+17},	
	{STATIC_LABEL,staticlabelscript+18,staticlabelsign+18},	
		
	{FUNCTION_SET,functionsetscript,functionset},
//	{FUNCTION_SET,functionsetscript+1,functionset+1},
};

static void drawbackground(SW_SingleWindow* pWin)		 
{
//	GUI_RECT rect;										 
	GUI_SetBkColor(pWin->bkColor);
	GUI_Clear();
	
	GUI_SetColor(GUI_BLUE);
  GUI_DrawHLine(205,0,800);	//HLine??,VLine??
	GUI_DrawHLine(206,0,800);		
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window13={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
