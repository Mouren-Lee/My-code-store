#include "SWDataType.h"
#include "StaticLabel.h"
#include "StateShow.h"
#include "ValueShow.h"
#include "StateSet.h"
#include "SWWINDOW.h"
#include "FunctionSet.h"
#include "SWManage.h"
#include "WinAction.h"

const GUI_POINT pPoints1[]={{30,220},{50,220},{50,270},{30,270}};
#define POINT_COUNT1 (sizeof(pPoints1)/sizeof(pPoints1[0]))

const GUI_POINT pPoints2[]={{50,150},{50,200},{70,180},{70,150}};
#define POINT_COUNT2 (sizeof(pPoints2)/sizeof(pPoints2[0]))

const GUI_POINT pPoints3[]={{0,10},{-5,0},{5,0}};
#define POINT_COUNT3 (sizeof(pPoints3)/sizeof(pPoints3[0]))

const GUI_POINT pPoints4[]={{0,-10},{-5,0},{5,0}};
#define POINT_COUNT4 (sizeof(pPoints4)/sizeof(pPoints4[0]))

static const ST_StaticLabelScript staticlabelscript[]={
	{{0,0,800,50},0,{0,0,0,0},1,STR_CHUANGANLUOJITU,0},                //输入传感器逻辑关系图:
	{{3,50,800,146},0,{0,0,0,0},5,STR_LUOJIGUANXI,0},                //逻辑关系详情:
	{{80,160,165,208},0,{0,0,0,0},5,STR_QIEDAO,0},                //切刀:
	{{70,240,145,288},0,{0,0,0,0},5,STR_DIDAO,0},                //底刀:
	{{480,170,565,218},0,{0,0,0,0},5,STR_QIEDAO,0},                //切刀:
	{{470,240,545,288},0,{0,0,0,0},5,STR_DIDAO,0},                //底刀:
	{{40,297,75,321},0,{0,0,0,0},5,STR_PICTURE,0},                //图、pic1
	{{440,297,475,321},0,{0,0,0,0},5,STR_PICTURE,0},                //图、pic3
	{{0,322,800,372},0,{0,0,0,0},1,STR_WAIBUJIEXIANTU,0},          //外部接线图
	{{3,372,800,420},0,{0,0,0,0},5,STR_JIEXIANSHUOMING,0},         //接线说明
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];


static const ST_FunctionSetScript functionsetscript[]={
//	{{620,180,770,250},0,{2,8,0,0},1,0,STR_SETPIYEAR,0,WINDOW02_INDEX,0,OpenSetWindow},//参数设置
	{{0,420,0+160,430+50},0,{2,11,0,0},1,0,STR_SHANGYIYE,0,WINDOW09_INDEX,0,FunOpenWindow},//ZHUYE
//	{{160,420,160+160,430+50},0,{2,11,0,0},1,0,STR_ZHUCAIDAN,0,WINDOW02_INDEX,0,SWOpenWindow},//ZHUYE
	{{320,420,320+160,430+50},0,{2,11,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
//	{{480,420,480+160,430+50},0,{2,11,0,0},1,0,STR_JIANSHICHUANGKOU,0,WINDOW06_INDEX,0,SWOpenWindow},//ZHUYE
	{{640,420,640+160,430+50},0,{2,11,0,0},1,0,STR_XIAYIYE,0,WINDOW11_INDEX,0,FunOpenWindow},//ZHUYE
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={ 
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
//	{STATIC_LABEL,staticlabelscript+10,staticlabelsign+10},
//	{STATIC_LABEL,staticlabelscript+11,staticlabelsign+11},
//	{STATIC_LABEL,staticlabelscript+12,staticlabelsign+12},
//	{STATIC_LABEL,staticlabelscript+13,staticlabelsign+13},
//	{STATIC_LABEL,staticlabelscript+14,staticlabelsign+14},
//	{STATIC_LABEL,staticlabelscript+15,staticlabelsign+15},
	
	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
//	{FUNCTION_SET,functionsetscript+3,functionset+3},
//	{FUNCTION_SET,functionsetscript+4,functionset+4},
};


static void drawbackground(SW_SingleWindow* pWin)
{
//	static u16 i;

//	GUI_RECT rect;								
	GUI_SetBkColor(pWin->bkColor);						 
	GUI_Clear();

	GUI_SetColor(GUI_BLACK);                             //设置下面几句的颜色

	GUI_FillPolygon(pPoints1,POINT_COUNT1,0,0);
	GUI_FillPolygon(pPoints1,POINT_COUNT1,400,0);

	GUI_FillPolygon(pPoints2,POINT_COUNT2,0,10);
	GUI_FillPolygon(pPoints2,POINT_COUNT2,400,20);	
	
	GUI_DrawVLine(40,175,195);
	GUI_FillPolygon(pPoints4,POINT_COUNT4,40,175);
	GUI_DrawVLine(440,185,205);
	GUI_FillPolygon(pPoints3,POINT_COUNT3,440,205);

	GUI_SetFont(&GUI_FontHZHT_24);                            //设置字体

	GUI_GotoXY(79,297);
	GUI_DispString("1");
	GUI_GotoXY(479,297);
	GUI_DispString("2");

	GUI_SetColor(GUI_RED);			
	GUI_SetFont(&GUI_FontHZHT_24);
	GUI_GotoXY(540,435);
	GUI_DispString("(3)");
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window10={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	GUI_WHITE,
	DefaultProc0,
	drawbackground0,
};
