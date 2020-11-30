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
	  {{718,179,725,201},0,{0,0,0,0},4,STR_COLON,25},   //秒闪显示
	  {{38,280,293,320},0,{0,0,0,0},26,STR_SHENGCHANSHANG,0},  //制造商
	  {{227,220,369,244},0,{0,0,0,0},4,STR_CHUCHANGBIANHAO,0},  //出厂编号
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];


static const ST_ValueShowScript valueshowscript[]={
	{{565,182,610,202},SW_TRANS,{0,0,0,0},4,0,{0,PIPE_YEAR,{0,250,2012,2262,0,4,0,VFM_FILL}}},   //年
	{{618,182,644,202},SW_TRANS,{0,0,0,0},4,0,{0,PIPE_MONTH,{0,11,1,12,0,2,0,VFM_FILL}}},		   //月
	{{652,182,678,202},SW_TRANS,{0,0,0,0},4,0,{0,PIPE_DAY,{0,30,1,31,0,2,0,VFM_FILL}}},		   //日
	{{688,179,718,204},SW_TRANS,{0,0,0,0},4,0,{0,PIPE_HOUR,{0,23,0,23,0,2,0,VFM_FILL}}},		   //时
	{{725,179,755,204},SW_TRANS,{0,0,0,0},4,0,{0,PIPE_MINUTE,{0,59,0,59,0,2,0,VFM_FILL}}},	   //分
};

#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
static ST_ValueShow valueshow[VALUESHOW_COUNT];

static const ST_StateShowScript stateshowscript[]={
	{{294,273,294+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH12},
	{{322,273,322+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH1},
	{{350,273,350+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH2},
	{{378,273,378+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH3},

	{{439,273,439+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH4},
	{{467,273,467+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH5},
	{{495,273,495+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH6},
	{{523,273,523+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH7},

	{{551,273,551+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH8},
	{{579,273,579+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH9},
	{{607,273,607+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH10},
	{{635,273,635+28,333},SW_TRANS,{0,0,0,0},26,0,STR_NUMM0,10,25,0,PIPE_FLASH11},


	{{370,220,370+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH13},
	{{385,220,385+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH14},
	{{400,220,400+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH15},
	{{415,220,415+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH16},

	{{430,220,430+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH17},
	{{445,220,445+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH18},
	{{460,220,460+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH19},
	{{475,220,475+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH20},

	{{490,220,490+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH21},
	{{505,220,505+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH22},
	{{520,220,520+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH23},
	{{535,220,535+15,220+24},SW_TRANS,{0,0,0,0},4,0,STR_NUMM0,10,25,0,PIPE_FLASH24},
};
#define STATESHOW_COUNT (sizeof(stateshowscript)/sizeof(ST_StateShowScript))
static ST_StateShow stateshow[STATESHOW_COUNT];

static const ST_StateSetScript statesetscript[]={
	{{40,40,40+200,40+80},0,{2,2,0,0},1,0,STR_CHINESE,1,1,PIPE_LANGRAGE,STATE_SET_INCREASE|STATE_CYCLE,1,1,0,0,0},	//english									//改变语言
};

#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
static ST_StateSet stateset[STATESET_COUNT];

static void EnterPassword(u16 CmdID,ST_PARAM* pParam)				//核对密码程序
{																	//SWManage.c和LCDPLC.h
	if(FORE_GetBuf(PIPE_PASSWORD)==FORE_GetBuf(PIPE_MIMA1))	    //31107
	{
		FORE_SetBuf(PIPE_YEAR_SET,FORE_GetBuf(PIPE_YEAR));
		FORE_SetBuf(PIPE_MONTH_SET,FORE_GetBuf(PIPE_MONTH));
		FORE_SetBuf(PIPE_DAY_SET,FORE_GetBuf(PIPE_DAY));
		FORE_SetBuf(PIPE_HOUR_SET,FORE_GetBuf(PIPE_HOUR));
		FORE_SetBuf(PIPE_MINUTE_SET,FORE_GetBuf(PIPE_MINUTE));
		SWOpenWindow(WINDOW01_INDEX);								//window01.c系统1界面
	}
	else if(FORE_GetBuf(PIPE_PASSWORD)==FORE_GetBuf(PIPE_MIMA2))	    //60609
	{
		SWOpenWindow(WINDOW05_INDEX);								//window05.c系统2界面
	}


	return;						 									//window00.c运行界面
}								 									//window03.c初始界面

static void OpenSetWindow(u16 CmdID,const ST_PARAM* pParam)  //输数据界面
{
	SWOpenWindow(WININPUT_INDEX);					   //开输入窗口
	FORE_SetBuf(PIPE_PASSWORD,0);				       //清除上次的密码
	SetInputValue(&PasswordScript,1);				   //输进来的数据去哪里
	SetEnterCallback(EnterPassword,CmdID,pParam);	   //核对密码enterpassword函数,
}

static void Changelangrage(u16 CmdID,const ST_PARAM* pParam)
{
	SWRedraw();
}



static const ST_FunctionSetScript functionsetscript[]={
//	{{370,30,520,100},0,{2,2,0,0},1,0,STR_PINGMUJIAOZHUN,0,WINCALIBRATE_INDEX,0,FunOpenWindow,75},//屏幕校准
//	{{410,30,560,100},0,{2,2,0,0},1,0,STR_PINGMUJIAOZHUN,0,WINCALIBRATE_INDEX,0,FunOpenWindow,75},//屏幕校准
	{{560,40,560+200,40+80},0,{2,8,0,0},1,0,STR_XITONGSHEZHI,0,WINDOW02_INDEX,0,OpenSetWindow},//系统设置
	{{1,375,120,475},0,{5,11,0,0},29,0,STR_ZHUYE,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
	{{121,375,240,475},0,{6,11,0,0},29,0,STR_ZHUCAIDAN,0,WINDOW02_INDEX,0,FunOpenWindow},//ZHUCAIDAN
	{{241,375,360,475},0,{7,11,0,0},29,0,STR_JIANSHICHUANGKOU,0,WINDOW06_INDEX,0,FunOpenWindow},//JIANSHICHUANGKOU
	{{361,375,480,475},0,{8,10,0,0},29,0,STR_XITONGJIANJIE,0,0,0,0},//JIANJIE
	{{40,40,40+200,40+80},0,{0,0,0,0},1,0,0,0,0,0,Changelangrage},//english

};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={
	  {STATIC_LABEL,staticlabelscript,staticlabelsign},
	  {STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
    {STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
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

	{STATE_SHOW,stateshowscript,stateshow},	
	{STATE_SHOW,stateshowscript+1,stateshow+1},
	{STATE_SHOW,stateshowscript+2,stateshow+2},	
	{STATE_SHOW,stateshowscript+3,stateshow+3},	
	{STATE_SHOW,stateshowscript+4,stateshow+4},	
	{STATE_SHOW,stateshowscript+5,stateshow+5},	
	{STATE_SHOW,stateshowscript+6,stateshow+6},	
	{STATE_SHOW,stateshowscript+7,stateshow+7},	
	{STATE_SHOW,stateshowscript+8,stateshow+8},	
	{STATE_SHOW,stateshowscript+9,stateshow+9},	
	{STATE_SHOW,stateshowscript+10,stateshow+10},	
	{STATE_SHOW,stateshowscript+11,stateshow+11},	
	{STATE_SHOW,stateshowscript+12,stateshow+12},	
	{STATE_SHOW,stateshowscript+13,stateshow+13},
	{STATE_SHOW,stateshowscript+14,stateshow+14},	
	{STATE_SHOW,stateshowscript+15,stateshow+15},	
	{STATE_SHOW,stateshowscript+16,stateshow+16},	
	{STATE_SHOW,stateshowscript+17,stateshow+17},	
	{STATE_SHOW,stateshowscript+18,stateshow+18},	
	{STATE_SHOW,stateshowscript+19,stateshow+19},	
	{STATE_SHOW,stateshowscript+20,stateshow+20},	
	{STATE_SHOW,stateshowscript+21,stateshow+21},	
	{STATE_SHOW,stateshowscript+22,stateshow+22},	
	{STATE_SHOW,stateshowscript+23,stateshow+23},
	
	{VALUE_SHOW,valueshowscript,valueshow},
	{VALUE_SHOW,valueshowscript+1,valueshow+1},
	{VALUE_SHOW,valueshowscript+2,valueshow+2},
	{VALUE_SHOW,valueshowscript+3,valueshow+3},
	{VALUE_SHOW,valueshowscript+4,valueshow+4},
//	{VALUE_SHOW,valueshowscript+5,valueshow+5},
//	{VALUE_SHOW,valueshowscript+6,valueshow+6},
//	{VALUE_SHOW,valueshowscript+7,valueshow+7},

	{STATE_SET,statesetscript,stateset},
//	{STATE_SET,statesetscript+1,stateset+1},
//	{STATE_SET,statesetscript+2,stateset+2},

	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
	{FUNCTION_SET,functionsetscript+3,functionset+3},
	{FUNCTION_SET,functionsetscript+4,functionset+4},
	{FUNCTION_SET,functionsetscript+5,functionset+5},
//	{FUNCTION_SET,functionsetscript+6,functionset+6},
//	{FUNCTION_SET,functionsetscript+7,functionset+7},
};

static void drawbackground(SW_SingleWindow* pWin)
{ 
  
	GUI_RECT rect;								
	GUI_SetBkColor(pWin->bkColor);						 
	GUI_Clear();
	
	GUI_SetColor(GUI_BLUE);
	rect.x0 = 611;
	rect.y0 = 182;
	rect.x1 = 617;										 //日期中间的横线 
	rect.y1 = 202;
	GUI_SetFont(&GUI_FontHZHT_18);
	GUI_DispStringInRect("/",&rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
	rect.x0 = 645;
	rect.y0 = 182;
	rect.x1 = 651;										 //日期中间的横线   
	rect.y1 = 202;
	GUI_DispStringInRect("/",&rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
	
	

	GUI_DrawHLine(150,0,800);	//HLine横线,VLine竖线
	GUI_DrawHLine(151,0,800);

	GUI_DrawHLine(368,0,800);	//HLine,VLine
	GUI_DrawHLine(367,0,800);

  GUI_SetColor(GUI_RED);
	GUI_DrawHLine(301,414,431);	//HLine横线,VLine竖线
	GUI_DrawHLine(300,414,431);
//版本号
	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontHZHT_24);
	GUI_GotoXY(625,220);
	GUI_DispString("（V：2.31RA）");	
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window07={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};

