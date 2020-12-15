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
	{{181,81,250,99},0,{0,0,0,0},19,STR_BIANPINQI,0},//变频器：
	{{18,287,90,305},0,{0,0,0,0},19,STR_ZHILIUDIANJI,0},//直流电机：
	{{508,345,562,363},0,{0,0,0,0},19,STR_QUDONGQI,0},//驱动器：
	{{581,310,635,328},0,{0,0,0,0},19,STR_BEEP,0},//蜂鸣器
	{{636,316,668,328},0,{0,0,0,0},14,STR_BLACK,0},//黑:
	{{640,336,668,348},0,{0,0,0,0},14,STR_RED,0},//红:
	{{247,329,305,347},0,{0,0,0,0},19,STR_LICI,0},//励磁:
	{{228,212,283,230},0,{0,0,0,0},19,STR_JIDIANQI,0},//继电器:
	{{560,122,614,140},0,{0,0,0,0},19,STR_JIDIANQI,0},//继电器:
	{{339,242,411,278},0,{0,0,0,0},19,STR_BUJINDIANJI,0},//步进电机:
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

static const ST_FunctionSetScript functionsetscript[]={
//	{{620,180,770,250},0,{2,8,0,0},1,0,STR_SETPIYEAR,0,WINDOW02_INDEX,0,OpenSetWindow},//参数设置
	{{0,420,0+160,430+50},0,{2,11,0,0},1,0,STR_SHANGYIYE,0,WINDOW10_INDEX,0,FunOpenWindow},//ZHUYE
//	{{160,420,160+160,430+50},0,{2,11,0,0},1,0,STR_ZHUCAIDAN,0,WINDOW02_INDEX,0,SWOpenWindow},//ZHUYE
	{{320,420,320+160,430+50},0,{2,11,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
//	{{480,420,480+160,430+50},0,{2,11,0,0},1,0,STR_JIANSHICHUANGKOU,0,WINDOW06_INDEX,0,SWOpenWindow},//ZHUYE
	{{640,420,640+160,430+50},0,{2,11,0,0},1,0,STR_XIAYIYE,0,WINDOW12_INDEX,0,FunOpenWindow},//ZHUYE
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
	
	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
//	{FUNCTION_SET,functionsetscript+3,functionset+3},
//	{FUNCTION_SET,functionsetscript+4,functionset+4},
};

static void drawbackground(SW_SingleWindow* pWin)
{
//	GUI_RECT rect;								
	GUI_SetBkColor(pWin->bkColor);						 
	GUI_Clear();

	GUI_SetColor(GUI_BLUE);			//下面字体和线条为蓝色，直到重新调用该函数

	GUI_DrawHLine(10,670,800);
	GUI_DrawHLine(410,670,800);
	GUI_DrawVLine(670,10,410);      //HLD-800左半边大轮廓

  GUI_DrawHLine(11,671,800);
	GUI_DrawHLine(409,671,800);
	GUI_DrawVLine(671,11,409);      //HLD-800左半边大轮廓内圈

	GUI_DrawHLine(9,669,800);
	GUI_DrawHLine(411,669,800);
	GUI_DrawVLine(669,9,411);      //HLD-800左半边大轮廓外圈

	GUI_GotoXY(775,105);
	GUI_DispString("H");
	GUI_GotoXY(775,135);
	GUI_DispString("L");
	GUI_GotoXY(775,165);
	GUI_DispString("D");
//	GUI_GotoXY(775,195);
//	GUI_DispString("I");
	GUI_DrawVLine(782,203,217);
	GUI_GotoXY(775,225);
	GUI_DispString("8");
	GUI_GotoXY(775,255);
	GUI_DispString("0");
	GUI_GotoXY(775,285);
	GUI_DispString("0");        //HLD-800的名称

  GUI_SetFont(&GUI_FontHZHT_18);  //字体为HT18

	GUI_DrawHLine(310,685,725);
	GUI_DrawHLine(400,685,725);
	GUI_DrawVLine(685,310,400); 
	GUI_DrawVLine(725,310,400);     //最下面的接线柱 Y09~Y16

	GUI_DrawHLine(20,685,725);
	GUI_DrawHLine(140,685,725);
	GUI_DrawVLine(685,20,140); 
	GUI_DrawVLine(725,20,140);      //最上面的接线柱M01~M04

	GUI_DrawHLine(150,685,725);
	GUI_DrawHLine(300,685,725);
	GUI_DrawVLine(685,150,300); 
	GUI_DrawVLine(725,150,300);     //中间的接线柱Y01~Y08

	GUI_DrawHLine(20,180,300);
	GUI_DrawHLine(160,180,300);
	GUI_DrawVLine(180,20,160); 
	GUI_DrawVLine(300,20,160);      //变频器轮廓
    
  GUI_DrawHLine(30,265,715);      //最上面接线柱0V引线
	GUI_DrawHLine(70,265,715);		//最上面接线柱M01引线
	GUI_DrawHLine(90,360,715);		//最上面接线柱M02引线
	GUI_DrawHLine(110,540,715);		//最上面接线柱+24V引线
	GUI_DrawHLine(110,265,510);     //变频器X1引线
	GUI_DrawHLine(150,265,510);     //变频器COM引线
	GUI_DrawVLine(540,110,114);     //上面继电器右竖线上一小段
	GUI_DrawVLine(540,146,150);     //上面继电器右竖线下一小段
 	GUI_DrawVLine(510,110,120);    
	GUI_DrawVLine(510,140,150);     
	GUI_DrawLine(510,120,520,140);  //上面继电器2条左竖线及开关

  GUI_DrawHLine(180,200,715);     //中间接线柱0V引线
	GUI_DrawHLine(240,650,715);		//中间接线柱Y07引线
	GUI_DrawHLine(260,630,715);		//中间接线柱Y08引线
	GUI_DrawHLine(280,610,715);     //中间接线柱+24V引线

	GUI_DrawVLine(650,150,240); 
	GUI_DrawHLine(150,540,650);     //Y07与常开继电器中间连接线

	GUI_DrawVLine(630,210,260); 
	GUI_DrawHLine(210,300,630);   
	GUI_DrawVLine(300,210,240); 
	GUI_DrawHLine(240,270,300);     //Y08与常开继电器中间连接线

	GUI_DrawVLine(610,230,280); 
	GUI_DrawHLine(230,320,610);   
	GUI_DrawVLine(320,230,280); 
	GUI_DrawHLine(280,270,320);     //中间+24V与常开继电器中间连接线

	GUI_DrawVLine(200,180,280); 
	GUI_DrawHLine(280,200,240);     //中间0V与下面一个常开继电器中间连接线
	
	GUI_DrawVLine(270,240,244);     //常开继电器下面一个的右竖线上一小段
	GUI_DrawVLine(270,276,280);     //常开继电器下面一个的右竖线下一小段
 	GUI_DrawVLine(240,240,250);    
	GUI_DrawVLine(240,270,280);     
	GUI_DrawLine(240,250,250,270);  //下面继电器2条左竖线及开关

	GUI_DrawHLine(115,100,150);
	GUI_DrawHLine(400,100,150);
	GUI_DrawVLine(100,115,400); 
	GUI_DrawVLine(150,115,400);      //智能直流调速板轮廓
	
	
	GUI_DrawHLine(350,590,630);
	GUI_DrawHLine(400,590,630);
	GUI_DrawVLine(590,350,400); 
	GUI_DrawVLine(630,350,400);     //蜂鸣器轮廓
    
  GUI_DrawHLine(330,610,715);     //最下面接线柱Y16引线
	GUI_DrawHLine(350,650,715);		//最下面接线柱+24V引线
	GUI_DrawHLine(410,610,650);		//蜂鸣器下面的横线
	GUI_DrawVLine(610,330,355);		//蜂鸣器中间的竖线上一小段
	GUI_DrawVLine(610,395,410);		//蜂鸣器中间的竖线下一小段
	GUI_DrawVLine(650,350,410);		//蜂鸣器右边的竖线

	GUI_DrawHLine(240,440,565);
	GUI_DrawHLine(410,440,565);
	GUI_DrawVLine(440,240,410); 
	GUI_DrawVLine(565,240,410);      //BD-B3C驱动器轮廓
	GUI_DrawHLine(270,565,580);
	GUI_DrawHLine(360,565,580);
	GUI_DrawVLine(580,270,360);      //驱动器右边的小矩形

	GUI_DrawVLine(470,250,320); 
	GUI_DrawVLine(520,265,305);
	GUI_DrawLine(470,250,520,265);
	GUI_DrawLine(470,320,520,305);   //BD-B3C驱动器中间的梯形

	GUI_DrawCircle(485,260,3);
	GUI_DrawCircle(485,270,3);
	GUI_DrawCircle(485,280,3);
	GUI_DrawCircle(485,295,3);
	GUI_DrawCircle(485,310,3);		 //BD-B3C驱动器中间的梯形内左边一排的小圆圈
	GUI_DrawCircle(500,270,3);
	GUI_DrawCircle(500,280,3);
	GUI_DrawCircle(500,290,3);
	GUI_DrawCircle(500,300,3);		 //BD-B3C驱动器中间的梯形内右边一排的小圆圈
	

	GUI_GotoXY(490,354);
	GUI_DispString("C");
	GUI_GotoXY(490,336);
	GUI_DispString("B");
	GUI_GotoXY(490,318);
	GUI_DispString("A");             //BD-B3C驱动器内接线柱的字母
	GUI_GotoXY(508,327);
	GUI_DispString("BD-B3C");        //BD-B3C字母本身


	GUI_DrawHLine(300,340,410);
	GUI_DrawHLine(310,340,410);
	GUI_DrawVLine(340,300,310); 
	GUI_DrawVLine(410,300,310);      //步进电机中间的横矩形
	GUI_DrawHLine(390,350,400);
	GUI_DrawVLine(350,310,390); 
	GUI_DrawVLine(400,310,390);      //步进电机主轮廓
	GUI_DrawHLine(280,370,380);
	GUI_DrawVLine(370,280,300); 
	GUI_DrawVLine(380,280,300);      //步进电机上面的小矩形

	GUI_DrawCircle(375,365,20);		 //步进电机内的大圆
	GUI_DrawCircle(375,365,3);
	GUI_DrawCircle(363,365,3);
	GUI_DrawCircle(387,365,3);
	GUI_DrawCircle(369,353,3);
	GUI_DrawCircle(381,353,3);		 
	GUI_DrawCircle(369,377,3);
	GUI_DrawCircle(381,377,3);		 //步进电机内的小圆

	GUI_DrawHLine(327,369,482);      //步进电机A的引线  
	GUI_DrawHLine(345,387,482);	   	 //步进电机B的引线
	GUI_DrawVLine(369,327,353);		 //步进电机A与小圆连线
	GUI_DrawVLine(387,345,365);		 //步进电机B与小圆连线
	GUI_DrawHLine(363,415,482);		 //步进电机C的引线
	GUI_DrawHLine(400,363,415);		 //步进电机C中间线
	GUI_DrawVLine(415,363,400);		 //步进电机C中间线
	GUI_DrawVLine(363,365,400);		 //步进电机小圆引线（与C相连的）
	GUI_FillCircle(482,327,4);       //步进电机A的引线实心点 
	GUI_FillCircle(482,345,4);       //步进电机B的引线实心点 
	GUI_FillCircle(482,363,4);       //步进电机C的引线实心点 
	GUI_FillCircle(482,376,4);       //步进电机空接线柱实心点 
	GUI_FillCircle(482,389,4);       //AC220V引线实心点 
	GUI_FillCircle(482,402,4);       //步进电机AC220V引线实心点 


	GUI_GotoXY(126,375);
	GUI_DispString("F2");
	GUI_GotoXY(126,357);
	GUI_DispString("C2");
	GUI_GotoXY(108,339);
	GUI_DispString("220V");
	GUI_GotoXY(108,321);
	GUI_DispString("220V");
	GUI_GotoXY(126,303);
	GUI_DispString("H1");
	GUI_GotoXY(126,285);
	GUI_DispString("F1");            //调速板下面6个接线柱
	GUI_GotoXY(126,250);
	GUI_DispString("0V");
	GUI_GotoXY(126,232);
	GUI_DispString("CP");
	GUI_GotoXY(108,214);
	GUI_DispString("+12V");  
	GUI_GotoXY(126,196);
	GUI_DispString("0V");
	GUI_GotoXY(117,178);
	GUI_DispString("INW");	
	GUI_GotoXY(117,160);
	GUI_DispString("ING");
	GUI_GotoXY(126,142);
	GUI_DispString("0V");	
	GUI_GotoXY(108,124);
	GUI_DispString("+12V");  		 //调速板上面8个接线柱的名称

	GUI_DrawHLine(204,150,200);      //调速板0V引线
	
	GUI_DrawHLine(168,150,185);      //调速板ING引线
	GUI_DrawVLine(185,168,240);	
	GUI_DrawHLine(240,185,240);	     //调速板ING与下面的常开继电器的中间连接线

	GUI_DrawHLine(240,150,170);      //调速板CP引线	
	GUI_DrawVLine(170,192,240);	
	GUI_DrawHLine(192,170,360); 
	GUI_DrawVLine(360,90,192);	     //调速板CP与M02中间连接线

	GUI_FillCircle(200,204,4);       //连线的实心点 

	GUI_DrawHLine(329,150,170);      //调速板220V的引线  
	GUI_DrawHLine(347,150,170);	   	 //调速板220V的引线

	GUI_DrawHLine(293,150,240);      //调速板F1的引线  
	GUI_DrawHLine(383,150,240);      //调速板F2的引线  
	GUI_DrawVLine(240,293,318);      //调速板F1的引线下的竖线
	GUI_DrawVLine(240,358,383);      //调速板F2的引线上的竖线	
  GUI_DrawArc(240,323,5,5,-90,+90);	
	GUI_DrawArc(240,333,5,5,-90,+90);
	GUI_DrawArc(240,343,5,5,-90,+90);
	GUI_DrawArc(240,353,5,5,-90,+90);//调速板F1和F2之间的圆弧励磁
  
	GUI_DrawHLine(311,70,100);      //调速板H1的引线  
	GUI_DrawHLine(365,70,100);      //调速板C2的引线  
	GUI_DrawVLine(70,311,316);      //调速板H1的引线下的竖线
	GUI_DrawVLine(70,360,365);      //调速板C2的引线上的竖线
	GUI_DrawCircle(70,338,12);	    //调速板马达的圆
	GUI_DrawHLine(316,62,78);       //调速板马达上的+的横线
	GUI_DrawVLine(62,316,327);      //调速板马达上的+的竖线
	GUI_DrawVLine(78,316,327);      //调速板马达上的+的竖线
	GUI_DrawHLine(360,62,78);       //调速板马达上的-的横线
	GUI_DrawVLine(62,349,360);      //调速板马达上的-的竖线
	GUI_DrawVLine(78,349,360);      //调速板马达上的-的竖线

	GUI_GotoXY(66,313);
	GUI_DispString("+");  		    //调速板马达上的+号
	GUI_GotoXY(66,346);
	GUI_DispString("-");  		    //调速板马达上的-号
	GUI_GotoXY(62,329);
	GUI_DispString("MD");  		    //调速板马达上的-号

	GUI_GotoXY(235,21);
	GUI_DispString("COM");  		//变频器上的COM
	GUI_GotoXY(245,61);
	GUI_DispString("FV");  		    //变频器上的FV
	GUI_GotoXY(245,101);
	GUI_DispString("X1");  		    //变频器上的X1
	GUI_GotoXY(235,141);
	GUI_DispString("COM");  		//变频器上的COM

	GUI_GotoXY(730,21);
	GUI_DispString("0V");
	GUI_GotoXY(730,41);
	GUI_DispString("+5V");
	GUI_GotoXY(730,61);
	GUI_DispString("M01");
	GUI_GotoXY(730,81);
	GUI_DispString("M02");
	GUI_GotoXY(730,101);
	GUI_DispString("+24V");
	GUI_GotoXY(730,171);
	GUI_DispString("0V");            
	GUI_GotoXY(730,191);
	GUI_DispString("Y01");
	GUI_GotoXY(730,211);
	GUI_DispString("Y04");
	GUI_GotoXY(730,231);
	GUI_DispString("Y07");  
	GUI_GotoXY(730,251);
	GUI_DispString("Y08");
	GUI_GotoXY(730,271);
	GUI_DispString("+24V");	
	GUI_GotoXY(730,321);
	GUI_DispString("Y16");	
	GUI_GotoXY(730,341);
	GUI_DispString("+24V");		    //调速板上面8个接线柱的名称

	GUI_GotoXY(449,264);
	GUI_DispString("CW");	
	GUI_GotoXY(441,279);
	GUI_DispString("+5V");	
	GUI_GotoXY(449,294);
	GUI_DispString("CP");		    //BD-B3C驱动器的上面3个接线柱

	GUI_AA_DrawLine(270,244,280,246);
	GUI_AA_DrawLine(280,246,260,250);
	GUI_AA_DrawLine(260,250,280,254);
	GUI_AA_DrawLine(280,254,260,258);
	GUI_AA_DrawLine(260,258,280,262);
	GUI_AA_DrawLine(280,262,260,266);
	GUI_AA_DrawLine(260,266,280,270);
	GUI_AA_DrawLine(280,270,260,274);
	GUI_AA_DrawLine(260,274,270,276);  //下面一个常开继电器的弹簧

	GUI_AA_DrawLine(540,114,550,116);
	GUI_AA_DrawLine(550,116,530,120);
	GUI_AA_DrawLine(530,120,550,124);
	GUI_AA_DrawLine(550,124,530,128);
	GUI_AA_DrawLine(530,128,550,132);
	GUI_AA_DrawLine(550,132,530,136);
	GUI_AA_DrawLine(530,136,550,140);
	GUI_AA_DrawLine(550,140,530,144);
	GUI_AA_DrawLine(530,144,540,146);  //上面一个常开继电器的弹簧

	GUI_AA_DrawLine(610,355,620,357);
	GUI_AA_DrawLine(620,357,600,361);
	GUI_AA_DrawLine(600,361,620,365);
	GUI_AA_DrawLine(620,365,600,369);
	GUI_AA_DrawLine(600,369,620,373);
	GUI_AA_DrawLine(620,373,600,377);
	GUI_AA_DrawLine(600,377,620,381);
	GUI_AA_DrawLine(620,381,600,385);
	GUI_AA_DrawLine(600,385,620,389);  
	GUI_AA_DrawLine(620,389,600,393);
	GUI_AA_DrawLine(600,393,610,395);  //蜂鸣器的弹簧

//	GUI_DrawHLine(230,320,610);   
	GUI_DrawVLine(232,232,246); 
	GUI_DrawVLine(232,252,267); 
	GUI_DrawVLine(232,273,288); 

	GUI_DrawHLine(232,232,246); 
	GUI_DrawHLine(232,252,267); 
	GUI_DrawHLine(232,273,285); 

	GUI_DrawVLine(285,232,246); 
	GUI_DrawVLine(285,252,267); 
	GUI_DrawVLine(285,273,288); 

	GUI_DrawHLine(288,232,246); 
	GUI_DrawHLine(288,252,267); 
	GUI_DrawHLine(288,273,285);      //下面一个弹簧的虚线

	GUI_DrawVLine(502,102,116); 
	GUI_DrawVLine(502,122,137); 
	GUI_DrawVLine(502,143,158); 

	GUI_DrawHLine(102,502,516); 
	GUI_DrawHLine(102,522,537); 
	GUI_DrawHLine(102,543,555); 

	GUI_DrawVLine(555,102,116); 
	GUI_DrawVLine(555,122,137); 
	GUI_DrawVLine(555,143,158); 

	GUI_DrawHLine(158,502,516); 
	GUI_DrawHLine(158,522,537); 
	GUI_DrawHLine(158,543,555);      //上面一个弹簧的虚线

//	GUI_GotoXY(400,240);
//	GUI_DispString("abc");

//	GUI_DrawHLine(412,0,800);	//HLine横线,VLine竖线337+100
//	GUI_DrawHLine(413,0,800);


//	GUI_DrawHLine(150,0,800);	//HLine横线,VLine竖线
//	GUI_DrawHLine(151,0,800);
 
	GUI_SetFont(&GUI_FontHZHT_12);   //字体大小设置为12
	GUI_GotoXY(171,332);
	GUI_DispString("AC220V");  		 //调速板220V之间的AC220V
	GUI_GotoXY(491,383);
	GUI_DispString("AC220V");
	GUI_GotoXY(491,396);
	GUI_DispString("AC220V");       //驱动器的AC220V
	GUI_GotoXY(363,336);
	GUI_DispString("1");  		 //步进电机的1接线柱
	GUI_GotoXY(386,368);
	GUI_DispString("3");        //步进电机的3接线柱
	GUI_GotoXY(353,375);
	GUI_DispString("5");        //步进电机的5接线柱

//	GUI_SetColor(GUI_BLUE);
    
	GUI_SetColor(GUI_RED);
	GUI_DrawHLine(200,418,715);		//中间接线柱Y01引线
	GUI_DrawHLine(220,432,715);		//中间接线柱Y04引线
	GUI_DrawHLine(50,425,715);		//最上面接线柱+5V引线
	GUI_DrawVLine(432,220,280); 
	GUI_DrawHLine(280,432,485);     //Y04与驱动器中间连接线
	GUI_DrawVLine(425,50,295); 
	GUI_DrawHLine(295,425,485);     //+5V与驱动器中间连接线
	GUI_DrawVLine(418,200,310); 
	GUI_DrawHLine(310,418,485);     //Y01与驱动器中间连接线

	GUI_SetColor(GUI_RED);			
	GUI_SetFont(&GUI_FontHZHT_24);
	GUI_GotoXY(540,435);
	GUI_DispString("(4)");
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}

const SW_SingleWindowScript Window11={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	GUI_WHITE,
	DefaultProc0,
	drawbackground0,
};
