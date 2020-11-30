#include "Interface.h"
#include "PipeData.h"
//#include "RealTime.h"

static const ST_StaticLabelScript staticlabelscript[]={
	
//	{{51,90,109,110},0,{0,0,0,0},8,STR_X09,0},       //X9	
//	{{151,90,209,110},0,{0,0,0,0},8,STR_X10,0},       //X10		
//	{{251,90,309,110},0,{0,0,0,0},8,STR_X11,0},       //X11	
//	{{351,90,400,110},0,{0,0,0,0},8,STR_X12,0},       //X12			

//	{{451,90,509,110},0,{0,0,0,0},8,STR_X13,0},       //X13	
//	{{551,90,609,110},0,{0,0,0,0},8,STR_X14,0},       //X14		
//	{{651,90,709,110},0,{0,0,0,0},8,STR_X15,0},       //X15	
//	{{751,90,800,110},0,{0,0,0,0},8,STR_X16,0},       //X16		
//	
//	{{351,210,409,230},0,{0,0,0,0},8,STR_Y12,0},    	 //Y12
//	{{451,210,509,230},0,{0,0,0,0},8,STR_Y13,0},    	 //Y13
//	{{551,210,609,230},0,{0,0,0,0},8,STR_Y14,0},    	 //Y14
//	{{651,210,709,230},0,{0,0,0,0},8,STR_Y15,0},    	 //Y15	
//	{{751,210,800,230},0,{0,0,0,0},8,STR_Y16,0},    	 //Y16		
	
	{{10,270,110,310},0,{0,0,0,0},5,STR_ZHUJIMONI,0},    //主机模拟
	{{210,270,310,310},0,{0,0,0,0},5,STR_FANGLIAOMONI,0},//放料模拟
	{{400,270,520,310},0,{0,0,0,0},5,STR_FANGLIAOMONI2,0}, //放料模拟2
	{{620,270,720,310},0,{0,0,0,0},5,STR_CHULIAOMONI,0}, //出料模拟
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

static const ST_StateShowScript stateshowscript[]={
	{{10,30,100,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X01,0,25,1,PIPE_DI15},
	{{110,30,200,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X02,0,25,1,PIPE_DI14},
	{{210,30,300,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X03,0,25,1,PIPE_DI13},
	{{310,30,400,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X04,0,25,1,PIPE_DI12},
	{{410,30,500,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X05,0,25,1,PIPE_DI11},
	{{510,30,600,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X06,0,25,1,PIPE_DI10},
	{{610,30,700,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X07,0,25,1,PIPE_DI9},
	{{710,30,800,70},0,{4,COLOR_REDLED,1,0},8,0,STR_X08,0,25,1,PIPE_DI8},
	{{10,90,100,130},0,{4,COLOR_REDLED,1,0},8,0,STR_X09,0,25,1,PIPE_DI7},
	{{110,90,200,130},0,{4,COLOR_REDLED,1,0},8,0,STR_X10,0,25,1,PIPE_DI6},
	{{210,90,305,130},0,{4,COLOR_REDLED,1,0},8,0,STR_X11,0,25,1,PIPE_DI5},
	{{310,90,400,130},0,{4,COLOR_REDLED,1,0},8,0,STR_X12,0,25,1,PIPE_DI4},
	{{410,90,500,130},0,{4,COLOR_REDLED,1,0},23,0,STR_X13,0,25,1,PIPE_DI3},
	{{510,90,600,130},0,{4,COLOR_REDLED,1,0},23,0,STR_X14,0,25,1,PIPE_DI2},
	{{610,90,700,130},0,{4,COLOR_REDLED,1,0},23,0,STR_X15,0,25,1,PIPE_DI1},
	{{710,90,800,130},0,{4,COLOR_REDLED,1,0},23,0,STR_X16,0,25,1,PIPE_DI0},	


//	{{10,90,100,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI7},    //2015
//	{{110,90,200,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI6},
//	{{210,90,300,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI5},
//	{{310,90,400,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI4},		
//	{{410,90,500,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI3},    //2015
//	{{510,90,600,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI2},
//	{{610,90,700,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI1},
//	{{710,90,800,130},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DI0},	
//	
//	{{51,110,109,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN1},   //2015
//	{{151,110,209,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN2},  
//	{{251,110,309,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN3},  
//	{{351,110,400,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN4},  
//	{{451,110,509,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN5},   //2015
//	{{551,110,609,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN6},  
//	{{651,110,709,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN7},  
//	{{751,110,800,130},0,{0,0,0,0},8,0,STR_XS0,17,25,0,PIPE_REV_IN8},  
	
	{{10,150,100,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y01,0,25,1,PIPE_DO0},
	{{110,150,200,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y02,0,25,1,PIPE_DO1},
	{{210,150,300,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y03,0,25,1,PIPE_DO2},
	{{310,150,400,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y04,0,25,1,PIPE_DO3},
	{{410,150,500,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y05,0,25,1,PIPE_DO4},
	{{510,150,600,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y06,0,25,1,PIPE_DO5},
	{{610,150,700,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y07,0,25,1,PIPE_DO6},
	{{710,150,800,190},0,{4,COLOR_REDLED,1,0},8,0,STR_Y08,0,25,1,PIPE_DO7},
	{{10,210,100,250},0,{4,COLOR_REDLED,1,0},8,0,STR_Y09,0,25,1,PIPE_DO8},
	{{110,210,200,250},0,{4,COLOR_REDLED,1,0},8,0,STR_Y10,0,25,1,PIPE_DO9},
	{{210,210,300,250},0,{4,COLOR_REDLED,1,0},8,0,STR_Y11,0,25,1,PIPE_DO10},
	{{310,210,400,250},0,{4,COLOR_REDLED,1,0},23,0,STR_Y12,0,25,1,PIPE_DO11},
	{{410,210,500,250},0,{4,COLOR_REDLED,1,0},23,0,STR_Y13,0,25,1,PIPE_DO12},
	{{510,210,600,250},0,{4,COLOR_REDLED,1,0},23,0,STR_Y14,0,25,1,PIPE_DO13},
	{{610,210,700,250},0,{4,COLOR_REDLED,1,0},23,0,STR_Y15,0,25,1,PIPE_DO14},
	{{710,210,800,250},0,{4,COLOR_REDLED,1,0},8,0,STR_Y16,0,25,1,PIPE_DO15},
	
//	{{310,210,400,250},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DO11},   //2015
//	{{410,210,500,250},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DO12},
//	{{510,210,600,250},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DO13},
//	{{610,210,700,250},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DO14},
//	{{710,210,800,250},0,{4,COLOR_REDLED,1,0},0,0,0,0,25,1,PIPE_DO15},	
//	
//	{{351,230,409,250},0,{0,0,0,0},8,0,STR_YS0,11,25,0,PIPE_REV_OUT1},    //2015
//	{{451,230,509,250},0,{0,0,0,0},8,0,STR_YS0,11,25,0,PIPE_REV_OUT2},  
//	{{551,230,609,250},0,{0,0,0,0},8,0,STR_YS0,11,25,0,PIPE_REV_OUT3},  
//	{{651,230,709,250},0,{0,0,0,0},8,0,STR_YS0,11,25,0,PIPE_REV_OUT4},  
//	{{751,230,800,250},0,{0,0,0,0},8,0,STR_YS0,11,25,0,PIPE_REV_OUT5},  	
};
#define STATESHOW_COUNT (sizeof(stateshowscript)/sizeof(ST_StateShowScript))
static ST_StateShow stateshow[STATESHOW_COUNT];

static const ST_ValueShowScript valueshowscript[]={
	{{721,270,786,310},0,{1,19,0,0},3,0,{0,PIPE_BACK_DA1,{0,1023,0,100,0,2,1,0}}},//备用模拟	
	{{521,270,590,310},0,{1,19,0,0},3,0,{0,PIPE_BACK_DA2,{0,1023,0,100,0,2,1,0}}},//出料模拟	
	{{311,270,380,310},0,{1,19,0,0},3,0,{0,PIPE_BACK_DA3,{0,1023,0,100,0,2,1,0}}},//放料模拟			
	{{111,270,180,310},0,{1,19,0,0},3,0,{0,PIPE_BACK_DA4,{0,1023,0,100,0,2,1,0}}},//主机模拟	
};
	
#define VALUESHOW_COUNT (sizeof(valueshowscript)/sizeof(ST_ValueShowScript))
static ST_ValueShow valueshow[VALUESHOW_COUNT];

static const ST_FunctionSetScript functionsetscript[]={
	{{1,375,120,475},0,{5,11,0,0},29,0,STR_ZHUYE,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
	{{121,375,240,475},0,{6,11,0,0},29,0,STR_ZHUCAIDAN,0,WINDOW02_INDEX,0,FunOpenWindow},//ZHUCAIDAN
	{{241,375,360,475},0,{7,10,0,0},29,0,STR_JIANSHICHUANGKOU,0,0,0,0},//JIANSHICHUANGKOU
	{{361,375,480,475},0,{8,11,0,0},29,0,STR_XITONGJIANJIE,0,WINDOW07_INDEX,0,FunOpenWindow},//JIANJIE
};

#define FUNCTIONSET_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTIONSET_COUNT];

static const SW_CtrlScript SW_Ctrls[]={

	
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
	{STATE_SHOW,stateshowscript+24,stateshow+24},	
	{STATE_SHOW,stateshowscript+25,stateshow+25},	
	{STATE_SHOW,stateshowscript+26,stateshow+26},	
	{STATE_SHOW,stateshowscript+27,stateshow+27},	
	{STATE_SHOW,stateshowscript+28,stateshow+28},	
	{STATE_SHOW,stateshowscript+29,stateshow+29},	
	{STATE_SHOW,stateshowscript+30,stateshow+30},	
	{STATE_SHOW,stateshowscript+31,stateshow+31},
//	{STATE_SHOW,stateshowscript+32,stateshow+32},
//	{STATE_SHOW,stateshowscript+33,stateshow+33},	
//	{STATE_SHOW,stateshowscript+34,stateshow+34},
//	{STATE_SHOW,stateshowscript+35,stateshow+35},	
//	{STATE_SHOW,stateshowscript+36,stateshow+36},
//	{STATE_SHOW,stateshowscript+37,stateshow+37},	
//	{STATE_SHOW,stateshowscript+38,stateshow+38},
//	{STATE_SHOW,stateshowscript+39,stateshow+39},		
//	{STATE_SHOW,stateshowscript+40,stateshow+40},	
//	{STATE_SHOW,stateshowscript+41,stateshow+41},	
//	{STATE_SHOW,stateshowscript+42,stateshow+42},
//	{STATE_SHOW,stateshowscript+43,stateshow+43},		
//	{STATE_SHOW,stateshowscript+44,stateshow+44},	

	
	{VALUE_SHOW,valueshowscript,valueshow},
	{VALUE_SHOW,valueshowscript+1,valueshow+1},
	{VALUE_SHOW,valueshowscript+2,valueshow+2},
	{VALUE_SHOW,valueshowscript+3,valueshow+3},

	{STATIC_LABEL,staticlabelscript,staticlabelsign},
	{STATIC_LABEL,staticlabelscript+1,staticlabelsign+1},
	{STATIC_LABEL,staticlabelscript+2,staticlabelsign+2},
	{STATIC_LABEL,staticlabelscript+3,staticlabelsign+3},
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

	GUI_SetColor(GUI_BLACK);
	GUI_DrawHLine(135,0,800);	//HLine横线,VLine竖线
	GUI_SetColor(GUI_WHITE);
	GUI_DrawHLine(136,0,800);

	GUI_SetColor(GUI_BLACK);
	GUI_DrawHLine(257,0,800);	//HLine横线,VLine竖线
	GUI_SetColor(GUI_WHITE);
	GUI_DrawHLine(258,0,800);

//  GUI_SetColor(GUI_BLUE);
//	GUI_DrawHLine(368,0,800);	 
//	GUI_DrawHLine(367,0,800);

}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}


const SW_SingleWindowScript Window06={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	0xE6B23E,
	DefaultProc0,
	drawbackground0,
};
