#include "SWDataType.h"
#include "StaticLabel.h"
#include "StateShow.h"
#include "ValueShow.h"
#include "StateSet.h"
#include "SWWINDOW.h"
#include "FunctionSet.h"
#include "SWManage.h"
#include "WinAction.h"

const GUI_POINT pPoints[]={{0,14},{-7,0},{7,0}};
#define POINT_COUNT (sizeof(pPoints)/sizeof(pPoints[0]))

static const ST_StaticLabelScript staticlabelscript[]={
	{{324,71,396,89},0,{0,0,0,0},19,STR_KAIGUANDIANYUAN,0},                //���ص�Դ:
	{{133,27,180,45},0,{0,0,0,0},19,STR_SHURU,0},                //����:
	{{315,291,360,309},0,{0,0,0,0},19,STR_START,0},                //����:
	{{415,291,450,309},0,{0,0,0,0},19,STR_STOP,0},                //ֹͣ:
	{{635,98,709,131},0,{0,0,0,0},19,STR_SONGLIAOHUOER,0},                //���ϻ���:
	{{628,198,709,231},0,{0,0,0,0},19,STR_CHAOSUHUOER,0},                //���ٻ���:
	{{590,401,750,419},0,{0,0,0,0},19,STR_GUANGDIANYAN,0},                //�����:
	{{601,94,634,106},0,{0,0,0,0},14,STR_BLUE,0},                //�׵�:
	{{601,109,634,121},0,{0,0,0,0},14,STR_BLACK,0},                //�е�:
	{{601,124,634,136},0,{0,0,0,0},14,STR_BROWN,0},                //�׵�:
	{{601,194,633,206},0,{0,0,0,0},14,STR_BLUE,0},                //ͼ��pic1
	{{601,209,633,221},0,{0,0,0,0},14,STR_BLACK,0},                //ͼ��pic2
	{{601,224,633,236},0,{0,0,0,0},14,STR_BROWN,0},                //ͼ��pic3
	{{641,314,670,326},0,{0,0,0,0},14,STR_RED,0},                //ͼ��pic4
	{{641,328,695,352},0,{0,0,0,0},14,STR_WG,0},          //�ⲿ����ͼ
	{{641,354,675,366},0,{0,0,0,0},14,STR_BLACK,0},         //����˵��
};

#define STATICLABEL_COUNT (sizeof(staticlabelscript)/sizeof(ST_StaticLabelScript))
static ST_StaticLabel staticlabelsign[STATICLABEL_COUNT];

static const ST_FunctionSetScript functionsetscript[]={
	{{0,420,0+160,430+50},0,{2,11,0,0},1,0,STR_SHANGYIYE,0,WINDOW11_INDEX,0,FunOpenWindow},//ZHUYE
	{{320,420,320+160,430+50},0,{2,11,0,0},1,0,STR_RETURN,0,WINDOW00_INDEX,0,FunOpenWindow},//ZHUYE
//	{{640,420,640+160,430+50},0,{2,11,0,0},1,0,STR_XIAYIYE,0,WINDOW13_INDEX,0,SWOpenWindow},//ZHUYE
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
	{STATIC_LABEL,staticlabelscript+10,staticlabelsign+10},
	{STATIC_LABEL,staticlabelscript+11,staticlabelsign+11},
	{STATIC_LABEL,staticlabelscript+12,staticlabelsign+12},
	{STATIC_LABEL,staticlabelscript+13,staticlabelsign+13},
	{STATIC_LABEL,staticlabelscript+14,staticlabelsign+14},
	{STATIC_LABEL,staticlabelscript+15,staticlabelsign+15},
	
	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
//	{FUNCTION_SET,functionsetscript+2,functionset+2},
//	{FUNCTION_SET,functionsetscript+3,functionset+3},
//	{FUNCTION_SET,functionsetscript+4,functionset+4},
};

static void drawbackground(SW_SingleWindow* pWin)
{
//	GUI_RECT rect;								
	GUI_SetBkColor(pWin->bkColor);						 
	GUI_Clear();

	GUI_DrawBitmap(&bm96hailida,5,185);
	
	GUI_SetColor(GUI_BLUE);
	
	GUI_DrawHLine(10,0,200);
	GUI_DrawHLine(410,0,200);
	GUI_DrawVLine(200,10,410);    //HLD-800�Ұ�ߴ�������Ȧ

	GUI_DrawHLine(11,0,199);
	GUI_DrawHLine(409,0,199);
	GUI_DrawVLine(199,11,409);    //HLD-800�Ұ�ߴ�������Ȧ

	GUI_DrawHLine(9,0,201);
	GUI_DrawHLine(411,0,201);
	GUI_DrawVLine(201,9,411);    //HLD-800�Ұ�ߴ�������Ȧ

/*
  GUI_GotoXY(60,105);
	GUI_DispString("H");
	GUI_GotoXY(60,135);
	GUI_DispString("L");
	GUI_GotoXY(60,165);
	GUI_DispString("D");
	GUI_GotoXY(60,195);
//	GUI_DispString("I");
	GUI_DrawVLine(67,203,217);
	GUI_GotoXY(60,225);
	GUI_DispString("8");
	GUI_GotoXY(60,255);
	GUI_DispString("0");
	GUI_GotoXY(60,285);
	GUI_DispString("0");        //HLD-800������
*/


	GUI_DrawHLine(350,140,180);
	GUI_DrawHLine(400,140,180);
	GUI_DrawVLine(140,350,400); 
	GUI_DrawVLine(180,350,400);   //������Ľ����� X09~X16

	GUI_DrawHLine(80,140,180);
	GUI_DrawHLine(140,140,180);
	GUI_DrawVLine(140,80,140); 
	GUI_DrawVLine(180,80,140);   //������Ľ�����UART����Դ

	GUI_DrawHLine(150,140,180);
	GUI_DrawHLine(340,140,180);
	GUI_DrawVLine(140,150,340); 
	GUI_DrawVLine(180,150,340);   //�м�Ľ�����X01~X08

	GUI_DrawHLine(20,300,420);
	GUI_DrawHLine(140,300,420);
	GUI_DrawVLine(300,20,140); 
	GUI_DrawVLine(420,20,140);    //���ص�Դ����
    
	GUI_DrawHLine(40,260,300);
	GUI_DrawVLine(260,10,40); 
	GUI_SetFont(&GUI_FontHZHT_18);
	GUI_GotoXY(265,15);
	GUI_DispString("N");
	GUI_DrawHLine(60,240,300);
	GUI_DrawVLine(240,10,60);    //���ص�Դ������������L N ��������
	GUI_GotoXY(245,15);
	GUI_DispString("L");

	GUI_GotoXY(85,27);
	GUI_DispString("DC24V");            //DC24V����

	GUI_DrawHLine(90,150,300);
	GUI_GotoXY(270,72);
	GUI_DispString("+V");
	GUI_DrawHLine(110,150,300);    //���ص�Դ��������Ľ�����������
	GUI_GotoXY(270,92);
	GUI_DispString("-V");

	GUI_GotoXY(120,82);
	GUI_DispString("+");
	GUI_GotoXY(120,102);
	GUI_DispString("-");
	GUI_GotoXY(100,162);
	GUI_DispString("+24V");
	GUI_GotoXY(110,182);
	GUI_DispString("X01");
	GUI_GotoXY(110,202);
	GUI_DispString("X02");
	GUI_GotoXY(110,222);
	GUI_DispString("X03");
	GUI_GotoXY(110,252);
	GUI_DispString("X07");
	GUI_GotoXY(110,272);
	GUI_DispString("X08");
	GUI_GotoXY(115,312);
	GUI_DispString("0V");        //��������������

	GUI_DrawHLine(90,600,750);
	GUI_DrawHLine(140,600,750);
	GUI_DrawVLine(600,90,140); 
	GUI_DrawVLine(750,90,140);    //���ϻ������� ����һ��

	GUI_DrawHLine(80,710,720);
	GUI_DrawHLine(150,710,720);
	GUI_DrawVLine(710,80,150); 
	GUI_DrawVLine(720,80,150);    //���ϻ�����������

	GUI_DrawHLine(80,730,740);
	GUI_DrawHLine(150,730,740);
	GUI_DrawVLine(730,80,150); 
	GUI_DrawVLine(740,80,150);     //���ϻ�����������


	GUI_DrawHLine(190,600,750);
	GUI_DrawHLine(240,600,750);
	GUI_DrawVLine(600,190,240); 
	GUI_DrawVLine(750,190,240);    //���ٻ������� ����һ��

	GUI_DrawHLine(180,710,720);
	GUI_DrawHLine(250,710,720);
	GUI_DrawVLine(710,180,250); 
	GUI_DrawVLine(720,180,250);    //���ٻ�����������

	GUI_DrawHLine(180,730,740);
	GUI_DrawHLine(250,730,740);
	GUI_DrawVLine(730,180,250); 
	GUI_DrawVLine(740,180,250);     //���ٻ�����������

	GUI_DrawHLine(300,640,700);
	GUI_DrawHLine(380,640,700);
	GUI_DrawVLine(640,300,380); 
	GUI_DrawVLine(700,300,380);    //�����
  
	GUI_DrawHLine(400,655,685);
	GUI_DrawVLine(655,380,400); 
	GUI_DrawVLine(685,380,400);     //���������һ��С����

	GUI_DrawHLine(130,580,600);
	GUI_DrawHLine(115,560,600);
	GUI_DrawHLine(100,540,600);     //���ϻ�����3��ֱ�ӽ���
	
	GUI_DrawHLine(230,580,600);
	GUI_DrawHLine(215,560,600);
	GUI_DrawHLine(200,540,600);     //���ٻ�����3��ֱ�ӽ���

	GUI_DrawHLine(320,580,640);
	GUI_DrawHLine(340,520,640);
	GUI_DrawHLine(360,540,640);     //����۵�3��ֱ�ӽ���

	GUI_DrawVLine(580,130,320);   //����һ������������
	GUI_DrawVLine(560,115,190);   //X01�����ϻ����м���
	GUI_DrawVLine(560,210,215);	  //X02�볬�ٻ����м���
	GUI_DrawVLine(520,230,340);	  //X03�������м���
	GUI_DrawVLine(540,100,360);	  //X03�������м���

	GUI_DrawHLine(170,150,580);    //+24V���ߣ��м��������
	GUI_DrawHLine(190,150,560);    //X01����
	GUI_DrawHLine(210,150,560);    //X02����
	GUI_DrawHLine(230,150,520);    //X03����

	GUI_DrawHLine(260,150,300);    //X07����
	GUI_DrawHLine(280,150,400);    //X08����
	GUI_DrawHLine(320,150,540);    //0V���� ���м��������

	GUI_DrawVLine(300,260,290);   //��������
	GUI_DrawVLine(300,310,320);
	GUI_DrawLine(300,290,310,310);

	GUI_DrawVLine(400,280,290);   //ֹͣ����
	GUI_DrawVLine(400,310,320);
	GUI_DrawLine(400,290,410,310);
 
	GUI_FillCircle(300,320,4);
	GUI_FillCircle(400,320,4);
	GUI_FillCircle(580,170,4);
	GUI_FillCircle(540,320,4);
	GUI_FillCircle(540,200,4);
	GUI_FillCircle(580,230,4);    //���ߵ�ʵ�ĵ�

	GUI_DrawVLine(123,48,65);   
	GUI_DrawVLine(124,48,65);
	GUI_DrawVLine(125,48,65);
  GUI_FillPolygon(pPoints,POINT_COUNT,124,65);   //��ͷ

	GUI_SetColor(GUI_RED);			
	GUI_SetFont(&GUI_FontHZHT_24);
	GUI_GotoXY(540,435);
	GUI_DispString("(5)");
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}

const SW_SingleWindowScript Window12={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	GUI_WHITE,
	DefaultProc0,
	drawbackground0,
};
