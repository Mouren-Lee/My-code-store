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
/*
static const ST_StaticLabelScript staticlabelscript[]={
 {{2,144,198,168},SW_CM,{0,0,0,0},4,STR_DINGLIAOGESHU,0},  //顶料个数
 {{202,144,398,168},SW_TRANS,{0,0,0,0},4,STR_TUODAIPISHU,0},  //脱袋批数
 {{402,144,598,168},SW_TRANS,{0,0,0,0},4,STR_DUOZOUCHANGDU,0},  //多走长度
 {{556,197,592,208},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)
};
  
#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

*/
/*
static const ST_ValueShowScript valueshowscript[]={
	{{146,21,275,75},0,{1,19,0,0},34,0,{0,PIPE_BATCH_COUNT,{0,64000,0,64000,0,5,0,0}}},       //批数
	
	{{2,144,198,220},SW_TRANS,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_PRESS_CNT,{0,9,0,9,0,1,0,0}}},            //顶料个数
	{{202,144,398,220},SW_TRANS,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_DRAG_BATCH,{1,19,1,19,0,2,0,0}}},            //脱袋批数
  {{402,144,598,220},SW_TRANS,{1,0,0,0},36,SW_ENABLE_EDIT,{0,PIPE_MORE_LENGTH,{0,50000,0,50000,0,4,1,0}}},         //多走长度

};

#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
static ST_ValueShow valueshow[VALUESHOW_COUNT];
*/
/*
static const ST_StateSetScript statesetscript[]={
  {{11,21,130,75},0,{2,17,0,0},35,0,STR_PISHU,0,1,PIPE_BATCH_CLR,STATE_SET_CONST,1,0,0,0,0},				     //批数清零
};

#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
static ST_StateSet stateset[STATESET_COUNT];
*/

static const ST_FunctionSetScript functionsetscript[]={
	{{620,400,770,470},0,{2,2,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,OpenSaveWindow},//返回
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];


static const SW_CtrlScript SW_Ctrls[]={

//	{STATE_SHOW,stateshowscript,stateshow},		

//	{STATE_SET,statesetscript,stateset},
//	{STATE_SET,statesetscript+1,stateset+1},
//	{STATE_SET,statesetscript+2,stateset+2},
//	{STATE_SET,statesetscript+3,stateset+3},
//	{STATE_SET,statesetscript+4,stateset+4},
//	{STATE_SET,statesetscript+5,stateset+5},
//	{STATE_SET,statesetscript+6,stateset+6},
//	{STATE_SET,statesetscript+7,stateset+7},
//	{STATE_SET,statesetscript+8,stateset+8},	
	
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

	
//	{STATIC_LABEL,staticlabelscript,staticlabelsign},
//	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
//	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
//	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},
//	{STATIC_LABEL,staticlabelscript+4,staticlabelsign+4},
//	{STATIC_LABEL,staticlabelscript+5,staticlabelsign+5},
//	{STATIC_LABEL,staticlabelscript+6,staticlabelsign+6},
//	{STATIC_LABEL,staticlabelscript+7,staticlabelsign+7},	
	
	{FUNCTION_SET,functionsetscript,functionset},
//	{FUNCTION_SET,functionsetscript+1,functionset+1},
};

static void drawbackground(SW_SingleWindow* pWin)		 
{
//	GUI_RECT rect;										 
	GUI_SetBkColor(pWin->bkColor);
	GUI_Clear();



	GUI_DrawBitmap(&bm96hailida,20,20);

    GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontHZHT_32);
	GUI_GotoXY(150,20);
	GUI_DispString("无 锡 市 海 利 达 自 动 化 仪 器 厂");	

    GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontHZHT_32);
	GUI_GotoXY(200,100);
	GUI_DispString("0 5 1 0 - 8 5 5 0 0 2 1 8");	

    GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontHZHT_32);
	GUI_GotoXY(200,200);
	GUI_DispString("www.wuxihailida.com");	
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window14={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
