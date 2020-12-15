#include "Interface.h"

//参数名称字体索引

#define INPUTFONT 0
#define KEYFONT 0

#define DESCRIBELABEL 0
#define MAXLABEL 1
#define MINLABEL 2

#define KEY_NONE 0
#define KEY_ESC 1
#define KEY_CLR 2
#define KEY_BACK 3
#define KEY_ENTER 4

#define BUFSIZE 20
//工作变量指针
static ST_ValueFormatScript const* pVariable = 0;
static u8 ShowBuf[BUFSIZE];
static u8 ShowPassword[BUFSIZE];
static u8 bufpt=0;
static u8 bflash=0;
static u8 m_bPassword = 0;
static u16 m_CmdID;
static ST_PARAM m_Param;
static FUNCTIONSETCALL* pEnterCallback=0;

void DrawNumerShow(u8 bErase)
{
	u8 i;
	GUI_RECT rect;
	const ST_LabelFont *pFont;

	rect.x0 = 160;rect.x1 = 500;
	rect.y0 = 80;rect.y1 = 140;

	if(bErase)
		GUI_SetColor(GUI_WHITE);
	else
		GUI_SetColor(GUI_BLACK);

	pFont = GetShareLabelFont(INPUTFONT);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(pFont->pFont);

	if(m_bPassword)
	{
		for(i=0;i<bufpt;i++)
		{
			ShowPassword[i]='*';
		}
		ShowPassword[i] = 0;
		GUI_DispStringInRect((const char*)ShowPassword,&rect,GUI_TA_RIGHT|GUI_TA_VCENTER);
	}
	else
		GUI_DispStringInRect((const char*)ShowBuf,&rect,GUI_TA_RIGHT|GUI_TA_VCENTER);

}

static void callback(u16 CmdID,const ST_PARAM* pParam)
{
	u16 tmp;
	if(pVariable == 0)
		return;

	DrawNumerShow(1);
	switch(CmdID)
	{
	case KEY_BACK:
		if(bufpt>0)
			ShowBuf[--bufpt] = 0;
		break;				
	case KEY_CLR:
		bufpt = 0;
		break;
	case KEY_ESC:
		SWCloseCurrentWin();
		break;
	case KEY_ENTER:
		if(Str2Value(ShowBuf,&tmp,&(pVariable->FormatScript)))
		{
			if(pVariable->ParStyle)
				FORE_SetIO(pVariable->ParIndex,Show2Value(tmp,&(pVariable->FormatScript)));
			else
				FORE_SetBuf(pVariable->ParIndex,Show2Value(tmp,&(pVariable->FormatScript)));
			
			SWCloseCurrentWin();
			if(pEnterCallback!=0)
			{
				pEnterCallback(m_CmdID,&m_Param);
			}
		}
		else
		{
			bufpt =Value2Str(ShowBuf,tmp,&(pVariable->FormatScript));
			bflash = 1;
		}
		break;
	default:
		if(bflash)
		{
			ShowBuf[0] = '0';
			ShowBuf[1] = 0;
			bufpt = 1;
			bflash = 0;
		}	
		 bufpt = AddCharValue(ShowBuf,CmdID,&(pVariable->FormatScript));
		break;

	}
	if(bufpt==0)
	{
		ShowBuf[0] = '0';
		ShowBuf[1] = 0;
		bufpt = 1;
	}
	DrawNumerShow(0);
}

static const ST_FunctionSetScript functionsetscript[]={
	{{160,370,270,430},0,{2,1,1,0},KEYFONT,0,STR_NUMM0,0,'0',0,callback,0},			//'0'
	{{285,370,395,430},0,{2,1,1,0},KEYFONT,0,STR_NUMPT,0,'.',0,callback,0},			//'.'
	{{410,370,520,430},0,{2,1,1,0},KEYFONT,0,STR_NUMNEG,0,'-',0,callback,0},		//'.'
	{{160,300,270,360},0,{2,1,1,0},KEYFONT,0,STR_NUMM1,0,'1',0,callback,0},			//'1'
	{{285,300,395,360},0,{2,1,1,0},KEYFONT,0,STR_NUMM2,0,'2',0,callback,0},			//'2'
	{{410,300,520,360},0,{2,1,1,0},KEYFONT,0,STR_NUMM3,0,'3',0,callback,0},			//'3'
	{{160,230,270,290},0,{2,1,1,0},KEYFONT,0,STR_NUMM4,0,'4',0,callback,0},			//'4'
	{{285,230,395,290},0,{2,1,1,0},KEYFONT,0,STR_NUMM5,0,'5',0,callback,0},			//'5'
	{{410,230,520,290},0,{2,1,1,0},KEYFONT,0,STR_NUMM6,0,'6',0,callback,0},			//'6'
	{{160,160,270,220},0,{2,1,1,0},KEYFONT,0,STR_NUMM7,0,'7',0,callback,0},			//'7'
	{{285,160,395,220},0,{2,1,1,0},KEYFONT,0,STR_NUMM8,0,'8',0,callback,0},			//'8'
	{{410,160,520,220},0,{2,1,1,0},KEYFONT,0,STR_NUMM9,0,'9',0,callback,0},			//'9'
	{{535,300,645,430},0,{2,1,1,0},KEYFONT,0,STR_ENTER,0,KEY_ENTER,0,callback,0},	//'Enter'
	{{535,230,645,290},0,{2,1,1,0},KEYFONT,0,STR_CLR,0,KEY_CLR,0,callback,0},		//'clr'
	{{535,160,645,220},0,{2,1,1,0},KEYFONT,0,STR_BACK,0,KEY_BACK,0,callback,0},		//'back'
	{{535,80,645,140},0,{2,1,1,0},KEYFONT,0,STR_ESC,0,KEY_ESC,0,callback,0},		//'ESC'
};


#define FUNCTION_COUNT (sizeof(functionsetscript)/sizeof(ST_FunctionSetScript))
static ST_FunctionSet functionset[FUNCTION_COUNT];

static SW_CtrlScript SW_Ctrls[]={
	{FUNCTION_SET,functionsetscript,functionset},
	{FUNCTION_SET,functionsetscript+1,functionset+1},
	{FUNCTION_SET,functionsetscript+2,functionset+2},
	{FUNCTION_SET,functionsetscript+3,functionset+3},
	{FUNCTION_SET,functionsetscript+4,functionset+4},
	{FUNCTION_SET,functionsetscript+5,functionset+5},
	{FUNCTION_SET,functionsetscript+6,functionset+6},
	{FUNCTION_SET,functionsetscript+7,functionset+7},
	{FUNCTION_SET,functionsetscript+8,functionset+8},
	{FUNCTION_SET,functionsetscript+9,functionset+9},
	{FUNCTION_SET,functionsetscript+10,functionset+10},
	{FUNCTION_SET,functionsetscript+11,functionset+11},
	{FUNCTION_SET,functionsetscript+12,functionset+12},
	{FUNCTION_SET,functionsetscript+13,functionset+13},
	{FUNCTION_SET,functionsetscript+14,functionset+14},
	{FUNCTION_SET,functionsetscript+15,functionset+15},
};

static void drawbackground(SW_SingleWindow* pWin)
{
	GUI_RECT rect;
	u16 tmp;

	rect.x0 = 140;rect.x1 = 660;
	rect.y0 = 50;rect.y1 = 450;
	GUI_SetColor(pWin->bkColor);
	GUI_FillRectEx(&rect);
	Draw3DRect(&rect,GUI_WHITE,GUI_DARKGRAY,3);

		
	//画方框
	rect.x0 = 160;rect.x1 = 520;
	rect.y0 = 80;rect.y1 = 140;
	GUI_SetColor(GUI_WHITE);
	GUI_FillRectEx(&rect);
	Draw3DRect(&rect,GUI_DARKGRAY,GUI_LIGHTGRAY,2);
	//画装饰
	GUI_SetColor(GUI_DARKGRAY);
	GUI_DrawLine(160,150,640,150);
	GUI_SetColor(GUI_WHITE);
	GUI_DrawLine(161,151,641,151);
		
	if(pVariable->ParStyle)
		tmp = FORE_GetIO(pVariable->ParIndex);
	else
		tmp = FORE_GetBuf(pVariable->ParIndex);

	tmp = Value2Show(tmp,&(pVariable->FormatScript));	
	bufpt = Value2Str(ShowBuf,tmp,&(pVariable->FormatScript));
	DrawNumerShow(0);
}

static void WinInputProc(SW_SingleWindow* pWin,SW_ProcessMsg* pMsg)
{

	if(pWin->sign&SW_INVALIDATE)
		bflash = 1;
	
	DefaultProc(pWin,pMsg);	
}

void SetInputValue(const ST_ValueFormatScript* pValue,u8 bPass)
{
	pVariable = pValue;
	m_bPassword = bPass;
	pEnterCallback = 0;
}

void SetEnterCallback(FUNCTIONSETCALL* pCallback,u16 CmdID,const ST_PARAM* pParam)
{
	pEnterCallback = pCallback;
	m_CmdID = CmdID;
	if(sizeof(void*)>sizeof(u32))
		m_Param.pData=pParam->pData;
	else
		m_Param.dData = pParam->dData;	
}

static void drawbackground0(void* pWin)
{
	drawbackground(pWin);	
}

static void WinInputProc0(void* pWin,SW_ProcessMsg* pMsg)
{
	WinInputProc(pWin,pMsg);
}
const SW_SingleWindowScript WinInput={
	sizeof(SW_Ctrls)/sizeof(SW_CtrlScript),
	SW_Ctrls,
	GUI_LIGHTGRAY,
	WinInputProc0,
	drawbackground0,
};
