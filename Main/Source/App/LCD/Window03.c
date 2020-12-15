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
	{{32,7,196,31},0,{0,0,0,0},4,STR_DUOGONGNENGSHURU,0},  // 输入
	{{432,7,596,31},0,{0,0,0,0},12,STR_DUOGONGNENGSHUCHU,0},   //输出

  {{4,67,28,85},0,{0,0,0,0},19,STR_X09,0},   //X9
	{{4,147,28,165},0,{0,0,0,0},19,STR_X10,0},   //X10
	{{4,227,28,245},0,{0,0,0,0},19,STR_X11,0},   //X11
	{{4,307,28,325},0,{0,0,0,0},19,STR_X12,0},   //X12
  {{4,387,28,405},0,{0,0,0,0},19,STR_X13,0},   //X13	
	{{204,67,228,85},0,{0,0,0,0},19,STR_X14,0},   //X14
	{{204,147,228,165},0,{0,0,0,0},19,STR_X15,0},   //X15
	{{204,227,228,245},0,{0,0,0,0},19,STR_X16,0},   //X16
	
  {{404,67,428,85},0,{0,0,0,0},20,STR_Y12,0},   //Y12
	{{404,147,428,165},0,{0,0,0,0},20,STR_Y13,0},   //Y13
	{{404,227,428,245},0,{0,0,0,0},20,STR_Y14,0},   //Y14
	{{404,307,428,325},0,{0,0,0,0},20,STR_Y15,0},   //Y15
	{{404,387,428,405},0,{0,0,0,0},20,STR_Y16,0},   //Y16	
	
	{{602,38,798,62},0,{0,0,0,0},4,STR_DAKONGYANSHI2,0},        //打孔延时二
	{{756,84,798,102},0,{0,0,0,0},19,STR_MIAO,0},    //秒		
  {{602,118,798,142},0,{0,0,0,0},4,STR_DAKONGSHIJIAN2,0},   //打孔时间二
	{{756,164,798,182},0,{0,0,0,0},19,STR_MIAO,0},    //秒	
	
  {{602,198,798,222},0,{0,0,0,0},4,STR_LALIAOCHANGDU,0},  //拉料长度
  {{756,251,792,262},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)		
	
	{{602,278,798,302},0,{0,0,0,0},4,STR_DULIAOSHIJIAN,0},      //堵料时间	
	{{756,324,798,342},0,{0,0,0,0},19,STR_MIAO,0},    //秒		
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

static const ST_ValueShowScript valueshowscript[]={	

	{{602,38,798,114},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_HOLE_DELAY2,{0,10000,0,500,0,1,2,0}}},	     //打孔延时二
	{{602,118,798,194},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_HOLE_KEEP2,{0,19980,0,999,0,1,2,0}}},	     //打孔时间二


  {{602,198,798,274},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_PULL_MATERIAL,{0,9990,0,9990,0,3,1,0}}},         //后拉长度
	{{602,278,798,354},0,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_BLOCKING_TIME,{0,999,0,999,0,1,2,0}}},                  //堵料时间
};

#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
static ST_ValueShow valueshow[VALUESHOW_COUNT];


static const ST_StateSetScript statesetscript[]={
	{{32,38,196,114},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN1,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入1
	{{32,118,196,194},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN2,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入2
	{{32,198,196,274},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN3,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入3
	{{32,278,196,354},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN4,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入4
	{{32,358,196,434},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN5,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入5
	{{232,38,396,114},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN6,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入6
	{{232,118,396,194},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN7,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入7
	{{232,198,396,274},0,{2,11,0,0},4,0,STR_REVIN0,17,0,PIPE_REV_IN8,STATE_SET_INCREASE|STATE_CYCLE,1,17,0,0,0},	 //备用输入8
	
	
	{{432,38,596,114},0,{2,11,0,0},12,0,STR_REVOUT0,11,0,PIPE_REV_OUT1,STATE_SET_INCREASE|STATE_CYCLE,1,11,0,0,0},	 //备用输出1
	{{432,118,596,194},0,{2,11,0,0},12,0,STR_REVOUT0,11,0,PIPE_REV_OUT2,STATE_SET_INCREASE|STATE_CYCLE,1,11,0,0,0},	 //备用输出2
	{{432,198,596,274},0,{2,11,0,0},12,0,STR_REVOUT0,11,0,PIPE_REV_OUT3,STATE_SET_INCREASE|STATE_CYCLE,1,11,0,0,0},	 //备用输出3
	{{432,278,596,354},0,{2,11,0,0},12,0,STR_REVOUT0,11,0,PIPE_REV_OUT4,STATE_SET_INCREASE|STATE_CYCLE,1,11,0,0,0},	 //备用输出4
	{{432,358,596,434},0,{2,11,0,0},12,0,STR_REVOUT0,11,0,PIPE_REV_OUT5,STATE_SET_INCREASE|STATE_CYCLE,1,11,0,0,0},	 //备用输出5	
//	{{202,264,398,340},0,{2,11,2,0},16,0,STR_SHOUDONGZIDONG,1,1,PIPE_SPEED_AUTO,STATE_SET_INCREASE|STATE_CYCLE|STATE_DELAYDOIT,1,1,0,75,65535},//手动自动	
};

#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
static ST_StateSet stateset[STATESET_COUNT];


static const ST_FunctionSetScript functionsetscript[]={
//	{{2,264,198,340},0,{2,11,0,0},16,0,STR_PINGMUJIAOZHUN,0,WINCALIBRATE_INDEX,0,FunOpenWindow,75},//屏幕校准
	{{620,380,770,450},0,{2,2,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,OpenSaveWindow},//返回
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];


static const SW_CtrlScript SW_Ctrls[]={

//	{STATE_SHOW,stateshowscript,stateshow},		

	{STATE_SET,statesetscript,stateset},
	{STATE_SET,statesetscript+1,stateset+1},
	{STATE_SET,statesetscript+2,stateset+2},
	{STATE_SET,statesetscript+3,stateset+3},
	{STATE_SET,statesetscript+4,stateset+4},
	{STATE_SET,statesetscript+5,stateset+5},
	{STATE_SET,statesetscript+6,stateset+6},
	{STATE_SET,statesetscript+7,stateset+7},
	{STATE_SET,statesetscript+8,stateset+8},	
	{STATE_SET,statesetscript+9,stateset+9},
	{STATE_SET,statesetscript+10,stateset+10},
	{STATE_SET,statesetscript+11,stateset+11},
	{STATE_SET,statesetscript+12,stateset+12},		
	
	{VALUE_SHOW,valueshowscript,valueshow},
	{VALUE_SHOW,valueshowscript+1,valueshow+1},
	{VALUE_SHOW,valueshowscript+2,valueshow+2},
	{VALUE_SHOW,valueshowscript+3,valueshow+3},
//	{VALUE_SHOW,valueshowscript+4,valueshow+4},
//	{VALUE_SHOW,valueshowscript+5,valueshow+5},
//	{VALUE_SHOW,valueshowscript+6,valueshow+6},
//	{VALUE_SHOW,valueshowscript+7,valueshow+7},
//	{VALUE_SHOW,valueshowscript+8,valueshow+8},
//	{VALUE_SHOW,valueshowscript+9,valueshow+9},

	
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
	{STATIC_LABEL,staticlabelscript+19,staticlabelsign+19},	
	{STATIC_LABEL,staticlabelscript+20,staticlabelsign+20},		
	{STATIC_LABEL,staticlabelscript+21,staticlabelsign+21},	
	{STATIC_LABEL,staticlabelscript+22,staticlabelsign+22},	
	
	{FUNCTION_SET,functionsetscript,functionset},
//	{FUNCTION_SET,functionsetscript+1,functionset+1},
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


const SW_SingleWindowScript Window03={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
