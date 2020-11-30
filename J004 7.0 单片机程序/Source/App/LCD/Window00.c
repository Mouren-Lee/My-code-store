#include "Interface.h"
#include "PipeData.h"
//#include "RealTime.h"

//static const ST_StaticLabelScript staticlabelscript[]={
//	{{345,319,417,336},0,{0,0,0,0},19,STR_CHANGDUSHEDINGMM,0},  //长度设定
//	{{425,325,461,336},0,{0,0,0,0},14,STR_HAOMI,0},           //(毫米)

//};

//#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
//static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];
/*
static const ST_StateShowScript stateshowscript[]={

	{{473,119,577,162},SW_FLASH|SW_TRUE_FLASH,{1,19,0,0},12,0,STR_STOP,9,30,0,PIPE_WORK_INF},//工作状态

};
#define STATESHOW_COUNT (sizeof(stateshowscript)/sizeof(ST_StateShowScript))
static ST_StateShow stateshow[STATESHOW_COUNT];
*/
//static const ST_ValueShowScript valueshowscript[]={


//	{{146,21,275,75},0,{1,19,0,0},34,0,{0,PIPE_GK1_COUNT,{0,64000,0,64000,0,5,0,0}}},           //计数
//	{{336,281,465,345},0,{2,11,0,0},17,SW_ENABLE_EDIT,{0,PIPE_LENGTH,{0,65000,0,65000,0,4,1,0}}},//长度设定(毫米)
//	{{673,281,719,313},0,{0,0,0,0},16,0,{0,PIPE_SPEED_GK1,{0,999,0,999,0,3,0,0}}},			   //测速
//};

//#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
//static ST_ValueShow valueshow[VALUESHOW_COUNT];

//static const ST_StateSetScript statesetscript[]={
//	{{11,96,165,160},SW_STATIC_HIDE,{17,14,2,0},31,2,STR_COLOR1,2,0,PIPE_SEEK_STYLE,STATE_SET_INCREASE|STATE_CYCLE,1,2,0,0,0},  //颜色
//	{{11,176,165,240},0,{13,11,1,0},18,0,STR_XUNBIAO,0,1,PIPE_SEEK,STATE_SET_REVERT,1,0,0,0,0},				     //寻标	
//	{{641,96,790,160},0,{14,11,1,0},18,0,STR_DIANJIN,0,1,PIPE_JOGF,STATE_SET_REVERT,1,0,0,0,0},				     //点进
//	{{641,176,790,240},SW_TRUE_FLASH|SW_STATIC_HIDE,{15,11,2,0},27,2,STR_DIANTUI,2,0,PIPE_BUSHU,STATE_SET_REVERT,1,2,0,0,0},				     //点退	
//	{{641,16,790,80},0,{12,11,1,0},30,0,STR_FUWEI,0,1,PIPE_STOP_F,STATE_SET_REVERT,1,0,0,0,0},//复位
//	{{491,391,640,475},0,{11,18,0,0},1,0,STR_RUN,0,1,PIPE_START_IN,STATE_SET_CONST|STATE_DELAYDOIT,1,0,0,75,65535},//运行

//	{{641,391,790,475},0,{12,18,1,0},1,0,STR_STOP,0,1,PIPE_STOP_IN,STATE_SET_CONST,1,0,0,0,0},				     //停止
//	{{11,21,130,75},0,{2,17,0,0},35,0,STR_JISHU,0,1,PIPE_CNT_CLR,STATE_SET_CONST,1,0,0,0,0},					     //计数清零
//	{{276,21,395,75},0,{2,17,0,0},35,0,STR_PISHU,0,1,PIPE_BATCH_CLR,STATE_SET_CONST,1,0,0,0,0},				     //批数清零
//	{{276,21,395,75},0,{2,17,0,0},35,0,STR_TOTAL_CNT,0,1,PIPE_TOTAL_CNT_CLR,STATE_SET_CONST,1,0,0,0,0},		         //总计数清零
//	{{731,281,790,345},0,{2,11,0,0},21,0,STR_SPEEDUP,0,0,PIPE_SPEED_SET,STATE_SET_INCREASE|STATE_KEEP|STATE_SHOW_PRESSED,1,999,0,25,5},//主机速度加速 25对应1秒，50对应2秒，5对应0.2秒
//	{{541,281,600,345},0,{2,11,0,0},21,0,STR_SPEEDDN,0,0,PIPE_SPEED_SET,STATE_SET_DESCEND|STATE_KEEP|STATE_SHOW_PRESSED,1,999,0,25,5},//主机速度减速
//	{{466,281,525,345},0,{2,11,0,0},21,0,STR_SPEEDUP,0,0,PIPE_LENGTH,STATE_SET_INCREASE|STATE_KEEP|STATE_SHOW_PRESSED,1,30000,0,25,5},//长度设定增加
//	{{276,281,335,345},0,{2,11,0,0},21,0,STR_SPEEDDN,0,0,PIPE_LENGTH,STATE_SET_DESCEND|STATE_KEEP|STATE_SHOW_PRESSED,1,30000,0,25,5},//长度设定减少

//};

//#define STATESET_COUNT (sizeof(statesetscript)/sizeof(ST_StateSetScript))
//static ST_StateSet stateset[STATESET_COUNT];



static const ST_FunctionSetScript functionsetscript[]={
	{{1,375,120,475},0,{5,10,0,0},29,0,STR_ZHUYE,0,0,0,0},//ZHUYE
	{{121,375,240,475},0,{6,11,0,0},29,0,STR_ZHUCAIDAN,0,WINDOW02_INDEX,0,FunOpenWindow},//ZHUCAIDAN
	{{241,375,360,475},0,{7,11,0,0},29,0,STR_JIANSHICHUANGKOU,0,WINDOW06_INDEX,0,FunOpenWindow},//JIANSHICHUANGKOU
	{{361,375,480,475},0,{8,11,0,0},29,0,STR_XITONGJIANJIE,0,WINDOW07_INDEX,0,FunOpenWindow},//JIANJIE
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={


//	{STATE_SHOW,stateshowscript,stateshow},	
//	{STATE_SHOW,stateshowscript+1,stateshow+1},	
//	{STATE_SHOW,stateshowscript+2,stateshow+2},	
//	{STATE_SHOW,stateshowscript+3,stateshow+3},	
//	{STATE_SHOW,stateshowscript+4,stateshow+4},	
//	{STATE_SHOW,stateshowscript+5,stateshow+5},	
//	{STATE_SHOW,stateshowscript+6,stateshow+6},	
//	{STATE_SHOW,stateshowscript+7,stateshow+7},	
//	{STATE_SHOW,stateshowscript+8,stateshow+8},	
//	{STATE_SHOW,stateshowscript+9,stateshow+9},		
//	{STATE_SHOW,stateshowscript+10,stateshow+10},	
//	{STATE_SHOW,stateshowscript+11,stateshow+11},	
//	{STATE_SHOW,stateshowscript+12,stateshow+12},	
//	{STATE_SHOW,stateshowscript+13,stateshow+13},


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


//	{STATE_SET,statesetscript,stateset},
//	{STATE_SET,statesetscript+1,stateset+1},
//	{STATE_SET,statesetscript+2,stateset+2},
//	{STATE_SET,statesetscript+3,stateset+3},
//	{STATE_SET,statesetscript+4,stateset+4},
//	{STATE_SET,statesetscript+5,stateset+5},
//	{STATE_SET,statesetscript+6,stateset+6},
//	{STATE_SET,statesetscript+7,stateset+7},
//	{STATE_SET,statesetscript+8,stateset+8},
//	{STATE_SET,statesetscript+9,stateset+9},
//	{STATE_SET,statesetscript+10,stateset+10},
//	{STATE_SET,statesetscript+11,stateset+11},
//	{STATE_SET,statesetscript+12,stateset+12},
//	{STATE_SET,statesetscript+13,stateset+13},
//	{STATE_SET,statesetscript+14,stateset+14},
	//{STATE_SET,statesetscript+15,stateset+15},

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
	
	{FUNCTION_SET,functionsetscript,functionset},	
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
	{FUNCTION_SET,functionsetscript+3,functionset+3},
//	{FUNCTION_SET,functionsetscript+4,functionset+4},
};

static void drawbackground(SW_SingleWindow* pWin)		  
{
//	GUI_RECT rect;										 
	GUI_SetBkColor(pWin->bkColor);
	GUI_Clear();
	
	GUI_SetColor(GUI_BLUE);
/*
	rect.x0 = 656;
	rect.y0 = 12;
	rect.x1 = 661;										 //日期中间的横线   
	rect.y1 = 32;
	GUI_SetColor(GUI_BLUE);
	GUI_SetFont(&GUI_FontHZHT_18);
	GUI_DispStringInRect("/",&rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
	rect.x0 = 685;
	rect.y0 = 16;
	rect.x1 = 694;										 //日期中间的横线   
	rect.y1 = 34;
	GUI_DispStringInRect("/",&rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
*/	
//  GUI_DrawHLine(368,0,800);	//HLine横线,VLine竖线
//	GUI_DrawHLine(367,0,800);

//	GUI_SetColor(GUI_GREEN);
//	GUI_AA_FillCircle(282,212,15);
//	GUI_AA_FillCircle(282,179,15);   //左放料胶辊
//	GUI_AA_FillCircle(500,179,15);
//	GUI_AA_FillCircle(500,212,15);   //右送料胶辊	

//	GUI_SetColor(GUI_WHITE);
//	GUI_DrawHLine(196,239,345);
//	GUI_DrawHLine(195,234,349);     //放料胶辊中间的水平线
//   
//	GUI_DrawCircle(349,204,8);        
//  GUI_DrawCircle(349,204,1);  
//	GUI_DrawPoint(349,204);			//第一个小轴承

//	GUI_DrawLine(358,204,366,232);
//	GUI_DrawLine(358,203,366,231);  //第一个轴承与摆臂之间的线


//	
//	GUI_DrawCircle(375,232,8);        
//    GUI_DrawCircle(375,232,1);
//	GUI_DrawPoint(375,232);			//第二个轴承(摆臂)
//	
//  	GUI_DrawLine(384,232,396,183);
//	GUI_DrawLine(384,231,396,182);	//第二个与第三个轴承之间的连线

//    GUI_DrawCircle(405,184,8);        
//    GUI_DrawCircle(405,184,1);  
//	GUI_DrawPoint(405,184);			//第三个轴承

//	GUI_DrawLine(414,183,426,232);
//	GUI_DrawLine(414,182,426,231);   //第三个与第四个轴承之间的连线

//	GUI_DrawCircle(435,232,8);        
//    GUI_DrawCircle(435,232,1);
//	GUI_DrawPoint(435,232);			//第四个轴承

//	GUI_DrawLine(444,232,454,196);
//	GUI_DrawLine(444,231,454,195);
//	
//	GUI_DrawHLine(196,454,577);
//	GUI_DrawHLine(195,454,577);         //右边的料连线

//	GUI_DrawCircle(500,179,1);
//	GUI_DrawPoint(500,179);			//右送料胶辊中间的白点
//  GUI_DrawCircle(500,212,1);
//	GUI_DrawPoint(500,212);			//右送料胶辊中间的白点

//	GUI_DrawCircle(234,220,25);     
//	GUI_FillCircle(234,220,3);  //后放卷
//	
//	GUI_SetColor(GUI_BLACK);
//	GUI_FillRect(558,197,577,246);        //底刀

}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window00={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
