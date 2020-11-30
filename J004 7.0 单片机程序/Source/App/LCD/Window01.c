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
#include "WinAction.h"

static const ST_StaticLabelScript staticlabelscript[]={
	{{20,45,140,105},0,{0,0,0,0},2,STR_DIANHUA,0},//µÁª∞£∫
//	{{410,140,720,200},0,{3,2,0,0},2,STR_QUXIAN,0},//«˙œﬂ£∫
    {{20,135,140,195},0,{0,0,0,0},2,STR_CHUCHANG,0},//≥ˆ≥ß∫
	{{400,220,710,270},0,{3,2,0,0},2,STR_MIMA1,0},//–ﬁ∏ƒ√‹¬Î1£∫
	{{20,220,180,270},0,{0,0,0,0},2,STR_TOPIC_SYSTEM1,0},//œµÕ≥1£∫
	{{20,310,179,360},0,{0,0,0,0},2,STR_SETCOLOK,0},//–£◊º ±º‰
//	{{20,55,330,115},0,{3,2,0,0},2,STR_FANGLIAOJIASUKUAIMAN,0},//∑≈¡œº”ÀŸøÏ¬˝:
//   {{241,390,390,460},0,{0,0,0,0},2,STR_RUANJIANBANBEN,0},
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

static const ST_ValueShowScript valueshowscript[]={
//	{{150,55,300-5,115},0,{1,0,0,0},0,SW_ENABLE_EDIT,{0,PIPE_FLASH0,{0,9999,0,9999,0,4,0,1}}},//µÁª∞
//	{{300,55,450-5,115},0,{1,0,0,0},0,SW_ENABLE_EDIT,{0,PIPE_FLASH1,{0,9999,0,9999,0,4,0,1}}},//µÁª∞
//	{{450,55,600-5,115},0,{1,0,0,0},0,SW_ENABLE_EDIT,{0,PIPE_FLASH2,{0,9999,0,9999,0,4,0,1}}},//µÁª∞

//	{{410,140,710,200},0,{0,0,0,0},3,SW_ENABLE_EDIT,{0,PIPE_CURVE,{0,15,0,15,0,2,0,0}}},//«˙œﬂ—°‘Ò 2014-05-18º”
	{{400,220,700,270},0,{0,0,0,0},3,SW_ENABLE_EDIT,{0,PIPE_MIMA1,{0,65535,0,65535,0,5,0,0}}},//√‹¬Î1£∫
//	{{410,140,710,200},0,{0,0,0,0},3,SW_ENABLE_EDIT,{0,PIPE_APART_KEEP,{0,20000,0,500,0,1,2,0}}},//Õ—¥¸ ±º‰£∫
	{{180,220,320,270},0,{3,2,0,0},3,SW_ENABLE_EDIT,{0,PIPE_SYSTEM1,{0,65535,0,65535,0,5,0,0}}},	//œµÕ≥1
	{{180,310,270,360},0,{3,2,0,0},1,SW_ENABLE_EDIT,{0,PIPE_YEAR_SET,{0,250,2012,2262,0,4,0,0}}},       
	{{290,310,340,360},0,{3,2,0,0},1,SW_ENABLE_EDIT,{0,PIPE_MONTH_SET,{0,11,1,12,0,2,0,0}}},            
	{{360,310,410,360},0,{3,2,0,0},1,SW_ENABLE_EDIT,{0,PIPE_DAY_SET,{0,30,1,31,0,2,0,0}}},                             
	{{450,310,500,360},0,{3,2,0,0},1,SW_ENABLE_EDIT,{0,PIPE_HOUR_SET,{0,23,0,23,0,2,0,0}}},
	{{520,310,570,360},0,{3,2,0,0},1,SW_ENABLE_EDIT,{0,PIPE_MINUTE_SET,{0,59,0,59,0,2,0,0}}},
};

#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
static ST_ValueShow valueshow[VALUESHOW_COUNT];

static const ST_StateSetScript statesetscript[]={
	//{{40,40,40+200,40+80},0,{2,2,0,0},1,0,STR_CHINESE,1,1,PIPE_LANGRAGE,STATE_SET_INCREASE|STATE_CYCLE,1,1,0,0,0},	//english
	{{110,35,110+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH12,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},// ÷∂Ø◊‘∂Ø//∏ƒ±‰”Ô—‘
	{{160,35,160+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH1,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{210,35,210+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH2,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{260,35,260+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH3,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},

	{{350,35,350+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH4,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{400,35,400+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH5,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{450,35,450+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH6,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{500,35,500+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH7,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},

	{{550,35,550+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH8,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{600,35,600+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH9,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{650,35,650+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH10,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{700,35,700+45,35+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH11,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},


	{{150,130,150+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH13,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},//…Ë÷√2
	{{200,130,200+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH14,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{250,130,250+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH15,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{300,130,300+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH16,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},

	{{350,130,350+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH17,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{400,130,400+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH18,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{450,130,450+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH19,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{500,130,500+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH20,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},

	{{550,130,550+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH21,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{600,130,600+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH22,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{650,130,650+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH23,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},
	{{700,130,700+45,130+70},0,{1,0,0,0},24,0,STR_NUMM0,10,0,PIPE_FLASH24,STATE_SET_INCREASE|STATE_CYCLE|STATE_KEEP,1,10,0,270,25},

//	{{400,390,550,460},0,{2,11,1,0},1,0,STR_HENGQIEJI,1,1,PIPE_MACHINE,STATE_SET_INCREASE|STATE_CYCLE,1,1,0,0,0},	   //∫·«–ª˙÷∆¥¸ª˙«–ªª
};

#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
static ST_StateSet stateset[STATESET_COUNT];

static void AdjustClock(u16 CmdID,const ST_PARAM* pParam)
{
	u32 tmp;
	tmp = RTC_Adjust(FORE_GetBuf(PIPE_YEAR_SET),FORE_GetBuf(PIPE_MONTH_SET),
		FORE_GetBuf(PIPE_DAY_SET),FORE_GetBuf(PIPE_HOUR_SET)
		,FORE_GetBuf(PIPE_MINUTE_SET),0);
	FORE_SetBuf(PIPE_TIME_H,tmp>>16);
	FORE_SetBuf(PIPE_TIME_L,tmp&0xFFFF);
}

static const ST_FunctionSetScript functionsetscript[]={
	{{20,390,170,460},0,{2,7,0,0},1,0,STR_BAOCUNSHUJU,0,1,0,Win_SaveParameters},//±£¥Ê ˝æ›
	{{600,310,750,360},0,{2,2,0,0},1,0,STR_CLOCKSET,0,1,0,AdjustClock},         //–£◊º ±º‰
	{{600,390,750,460},0,{2,2,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,OpenSaveWindow},//∑µªÿ–¬ª˙–Õ
};
	  
#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={
	{STATIC_LABEL,staticlabelscript,staticlabelsign},
	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},
	{STATIC_LABEL,staticlabelscript+4,staticlabelsign+4},
//	{STATIC_LABEL,staticlabelscript+5,staticlabelsign+5},
//	{STATIC_LABEL,staticlabelscript+6,staticlabelsign+6},
//	{STATIC_LABEL,staticlabelscript+7,staticlabelsign+7},

//	{STATE_SHOW,stateshowscript,stateshow},		

	{VALUE_SHOW,valueshowscript,valueshow},
	{VALUE_SHOW,valueshowscript+1,valueshow+1},
	{VALUE_SHOW,valueshowscript+2,valueshow+2},
	{VALUE_SHOW,valueshowscript+3,valueshow+3},
	{VALUE_SHOW,valueshowscript+4,valueshow+4},
	{VALUE_SHOW,valueshowscript+5,valueshow+5},
	{VALUE_SHOW,valueshowscript+6,valueshow+6},
//	{VALUE_SHOW,valueshowscript+7,valueshow+7},
//	{VALUE_SHOW,valueshowscript+8,valueshow+8},
//	{VALUE_SHOW,valueshowscript+9,valueshow+9},

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
	{STATE_SET,statesetscript+13,stateset+13},
	{STATE_SET,statesetscript+14,stateset+14},
	{STATE_SET,statesetscript+15,stateset+15},
	{STATE_SET,statesetscript+16,stateset+16},
	{STATE_SET,statesetscript+17,stateset+17},
	{STATE_SET,statesetscript+18,stateset+18},
	{STATE_SET,statesetscript+19,stateset+19},
	{STATE_SET,statesetscript+20,stateset+20},
	{STATE_SET,statesetscript+21,stateset+21},
	{STATE_SET,statesetscript+22,stateset+22},
	{STATE_SET,statesetscript+23,stateset+23},
//	{STATE_SET,statesetscript+24,stateset+24},


	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
//	{FUNCTION_SET,functionsetscript+3,functionset+3},
};

static void drawbackground(SW_SingleWindow* pWin)
{
	GUI_RECT rect;
	GUI_SetBkColor(pWin->bkColor);
	GUI_Clear();

	GUI_SetColor(GUI_BLACK);
	rect.x0=270;rect.x1=290;
	rect.y0 = 310;rect.y1=360;
	GUI_SetFont(&GUI_FontHZHT_32);
	GUI_DispStringInRect("-",&rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
	rect.x0 = 340;rect.x1=360;
	GUI_DispStringInRect("-",&rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
	rect.x0 = 500;rect.x1=520;
	GUI_DispStringInRect(":",&rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
    
	GUI_SetColor(GUI_BLUE);
	GUI_DrawHLine(70,310,345);	//HLine∫·œﬂ,VLine ˙œﬂ
	GUI_DrawHLine(69,310,345);
	
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window01={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
