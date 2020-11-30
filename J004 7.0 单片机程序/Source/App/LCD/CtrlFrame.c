#include "CtrlFrame.h"
#include "SWDataType.h"

#define pai 3.141592653
GUI_POINT pPoints0[4];

const GUI_POINT pPoints5[]={{0,0},{0,-6},{13,0}};
#define POINT_COUNT5 (sizeof(pPoints5)/sizeof(pPoints5[0]))         //上箭头

const GUI_POINT pPoints6[]={{0,0},{0,6},{13,0}};
#define POINT_COUNT6 (sizeof(pPoints6)/sizeof(pPoints6[0]))         //下箭头

const GUI_POINT pPoints7[]={{0,-30},{-30,0},{-20,0},{-20,25},{20,25},{20,0},{30,0}};
#define POINT_COUNT7 (sizeof(pPoints7)/sizeof(pPoints7[0]))

const GUI_POINT pPoints8[]={{-4,-5},{4,-5},{5,1},{-5,1}};
#define POINT_COUNT8 (sizeof(pPoints8)/sizeof(pPoints8[0]))

const GUI_POINT pPoints9[]={{-30,0},{-33,-3},{0,-36},{8,-28},{8,-35},{15,-35},{15,-21},{33,-3},{30,0},{0,-30}};
#define POINT_COUNT9 (sizeof(pPoints9)/sizeof(pPoints9[0]))


const GUI_POINT pPoints10[]={{-30,0},{0,30},{14,30},{21,23},{14,16},{7,23},{-23,-7},{-16,-14},{-23,-21},{-30,-14}};
#define POINT_COUNT10 (sizeof(pPoints10)/sizeof(pPoints10[0]))

//const GUI_POINT pPoints11[]={{0,-8},{9,1},{13,-3},{4,-12}};
//#define POINT_COUNT11 (sizeof(pPoints11)/sizeof(pPoints11[0]))

const GUI_POINT pPoints11[]={{0,-8},{11,3},{18,-4},{7,-15}};
#define POINT_COUNT11 (sizeof(pPoints11)/sizeof(pPoints11[0]))

const GUI_POINT pPoints12[]={{0,-5},{0,4},{10,0}};
#define POINT_COUNT12 (sizeof(pPoints12)/sizeof(pPoints12[0]))        //箭头

const GUI_POINT pPoints13[]={{-9,-24},{10,-24},{10,6},{-9,25}};
#define POINT_COUNT13 (sizeof(pPoints13)/sizeof(pPoints13[0]))      //切刀

const GUI_POINT pPoints14[]={{12,12},{14,10},{28,24},{26,26}};
#define POINT_COUNT14 (sizeof(pPoints14)/sizeof(pPoints14[0]))      //放大镜手柄

//空画
void CtrlDrawFrame_0000(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
//	GUI_SetColor(GUI_GetBkColor());
//	GUI_FillRect(pRect->x0,pRect->y0,pRect->x1,pRect->y1);
	return;
}


void CtrlDrawText(GUI_RECT* pRect,const ST_LabelFont* pFont,const u8* pStr)
{
	GUI_SetFont(pFont->pFont);
	GUI_SetColor(pFont->color);
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	GUI_DispStringInRect((const char*)pStr,pRect,pFont->sign);
}

//画方框
void CtrlDrawFrame_0001(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN001 5
	GUI_SetColor(pColor->outcolor);
	GUI_DrawRectEx(pRect);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	pRect->x0+=MARGIN001;
	pRect->x1-=MARGIN001;

}

//画按钮
void CtrlDrawFrame_0002(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画反向按钮
void CtrlDrawFrame_0003(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN003 8
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,-64);
	rightdn = BrightColor(pColor->outcolor,64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	pRect->x0+=MARGIN003;	
	pRect->x1-=MARGIN003;

}

//画指示灯
void CtrlDrawFrame_0004(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	u32 color;
	int x,y;
	int len;
	x = pRect->x1-pRect->x0;
	y = pRect->y1-pRect->y0;
	if(y>x)
	{
		len = x;
		x = pRect->x0+x/2;
		y = pRect->y0+len/2;
		pRect->y0+=(len+1);
		
	}
	else
	{
		len = y;
		x = pRect->x0+len/2;
		y = pRect->y0+y/2;
		pRect->x0+=(len+1);

	}
	len>>=1;
	color = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(color);
	GUI_FillCircle(x,y,len);
	
	GUI_SetColor(pColor->outcolor);
	x--;
	y--;
	len-=((len>>4)+1);
	GUI_FillCircle(x,y,len);

	color = BrightColor(pColor->incolor,-64);
	GUI_SetColor(color);
	len = len-((len>>3)+1);
	GUI_FillCircle(x,y,len);
	GUI_SetColor(pColor->incolor);
	x--,y--,len--;
	GUI_FillCircle(x,y,len);
	GUI_SetColor(GUI_WHITE);
	len-=(len>>2);
	GUI_DrawArc(x,y,len,len,100,170);
}

/*
void CtrlDrawFrame_0005(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	u16 y=0;
	s16 deep;
	u32 color;
	u8 bit = 0;
	color = pColor->incolor;
	
	for(y=pRect->y0,deep =0;y<pRect->y1;y++,deep++)
	{
		GUI_SetColor(color);
		GUI_DrawHLine(y,pRect->x0,pRect->x1);
		color = BrightColor(color,8);
	}
}*/

//画主页home
void CtrlDrawFrame_0005(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
    GUI_SetColor(GUI_MAGENTA);
	GUI_FillPolygon(pPoints7,POINT_COUNT7,(pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2);//画房子
	GUI_DrawHLine((pRect->y0+pRect->y1)/2+5,(pRect->x0+pRect->x1)/2-10,(pRect->x0+pRect->x1)/2+10);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-5,(pRect->y0+pRect->y1)/2+15);
	GUI_SetColor(GUI_WHITE);
	GUI_FillRect((pRect->x0+pRect->x1)/2-10,(pRect->y0+pRect->y1)/2-5,(pRect->x0+pRect->x1)/2+10,(pRect->y0+pRect->y1)/2+15);
	GUI_SetColor(GUI_MAGENTA);
	GUI_DrawHLine((pRect->y0+pRect->y1)/2+5,(pRect->x0+pRect->x1)/2-10,(pRect->x0+pRect->x1)/2+10);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-5,(pRect->y0+pRect->y1)/2+15);
	GUI_SetColor(GUI_YELLOW);
	GUI_FillPolygon(pPoints9,POINT_COUNT9,(pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2);//画房顶
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画主菜单设置
void CtrlDrawFrame_0006(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
	GUI_SetColor(GUI_DARKGREEN);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-5,24);
	GUI_FillPolygon(pPoints8,POINT_COUNT8,(pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-29);
	GUI_RotatePolygon(pPoints0,pPoints8,POINT_COUNT8,pai);
	GUI_FillPolygon(pPoints0,POINT_COUNT8,(pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2+19);
	GUI_RotatePolygon(pPoints0,pPoints8,POINT_COUNT8,-pai/2);
	GUI_FillPolygon(pPoints0,POINT_COUNT8,(pRect->x0+pRect->x1)/2+24,(pRect->y0+pRect->y1)/2-5);
	GUI_RotatePolygon(pPoints0,pPoints8,POINT_COUNT8,pai/2);
	GUI_FillPolygon(pPoints0,POINT_COUNT8,(pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2-5);
	GUI_RotatePolygon(pPoints0,pPoints8,POINT_COUNT8,-pai/4);
	GUI_FillPolygon(pPoints0,POINT_COUNT8,(pRect->x0+pRect->x1)/2+17,(pRect->y0+pRect->y1)/2-22);
	GUI_RotatePolygon(pPoints0,pPoints8,POINT_COUNT8,+pai/4);
	GUI_FillPolygon(pPoints0,POINT_COUNT8,(pRect->x0+pRect->x1)/2-17,(pRect->y0+pRect->y1)/2-22);
	GUI_RotatePolygon(pPoints0,pPoints8,POINT_COUNT8,-pai/4*3);
	GUI_FillPolygon(pPoints0,POINT_COUNT8,(pRect->x0+pRect->x1)/2+17,(pRect->y0+pRect->y1)/2+12);
	GUI_RotatePolygon(pPoints0,pPoints8,POINT_COUNT8,+pai/4*3);
	GUI_FillPolygon(pPoints0,POINT_COUNT8,(pRect->x0+pRect->x1)/2-17,(pRect->y0+pRect->y1)/2+12);
	GUI_SetColor(GUI_GREEN);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-5,16);
	GUI_SetColor(GUI_WHITE);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-5,8);
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画监视窗口
void CtrlDrawFrame_0007(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
    GUI_SetColor(MRGB(0,128,255));
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-10,25);
	GUI_FillRect((pRect->x0+pRect->x1)/2-6,(pRect->y0+pRect->y1)/2+14,(pRect->x0+pRect->x1)/2+6,(pRect->y0+pRect->y1)/2+19);
	GUI_FillRect((pRect->x0+pRect->x1)/2-20,(pRect->y0+pRect->y1)/2+19,(pRect->x0+pRect->x1)/2+20,(pRect->y0+pRect->y1)/2+25);	
	GUI_SetColor(GUI_WHITE);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-10,15);
	GUI_SetColor(GUI_BLACK);
	GUI_FillCircle((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-10,10);
	GUI_SetColor(GUI_WHITE);
	GUI_FillCircle((pRect->x0+pRect->x1)/2-2,(pRect->y0+pRect->y1)/2-12,5);
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画电话简介
void CtrlDrawFrame_0008(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
    GUI_SetColor(MRGB(155,29,158));
/*
	GUI_FillPolygon(pPoints10,POINT_COUNT10,(pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-10);//画电话
	GUI_FillPolygon(pPoints11,POINT_COUNT11,(pRect->x0+pRect->x1)/2-23,(pRect->y0+pRect->y1)/2-25);
	GUI_FillPolygon(pPoints11,POINT_COUNT11,(pRect->x0+pRect->x1)/2+14,(pRect->y0+pRect->y1)/2+12);
*/
	GUI_SetPenSize(7);
	GUI_AA_DrawArc((pRect->x0+pRect->x1)/2+50,(pRect->y0+pRect->y1)/2-53,80,80,200,250);
	GUI_SetPenSize(1);
	GUI_FillPolygon(pPoints11,POINT_COUNT11,(pRect->x0+pRect->x1)/2-28,(pRect->y0+pRect->y1)/2-17);
	GUI_FillPolygon(pPoints11,POINT_COUNT11,(pRect->x0+pRect->x1)/2+11,(pRect->y0+pRect->y1)/2+22);
	
	
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画点进点退箭头
void CtrlDrawFrame_0009(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	GUI_SetColor(GUI_WHITE);
	GUI_FillPolygon(pPoints12,POINT_COUNT12,pRect->x0,(pRect->y0+pRect->y1)/2);
}

//切刀
void CtrlDrawFrame_0010(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillPolygon(pPoints13,POINT_COUNT13,(pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2);
}

//绿色椭圆运行
void CtrlDrawFrame_0011(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
	GUI_SetColor(GUI_GREEN);
	GUI_FillEllipse((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2,48,26);	
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//红色椭圆运行
void CtrlDrawFrame_0012(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
	GUI_SetColor(GUI_RED);
	GUI_FillEllipse((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2,48,26);	
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画放大镜
void CtrlDrawFrame_0013(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}

	GUI_SetColor(GUI_BLACK);
    GUI_AA_FillCircle((pRect->x0+pRect->x1)/2-25,(pRect->y0+pRect->y1)/2-7,15);	
	GUI_FillPolygon(pPoints14,POINT_COUNT14,(pRect->x0+pRect->x1)/2-25,(pRect->y0+pRect->y1)/2-7);
   	
	GUI_SetColor(pColor->incolor);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2-25,(pRect->y0+pRect->y1)/2-7,12);	

	GUI_SetColor(GUI_BLACK);
    GUI_AA_FillCircle((pRect->x0+pRect->x1)/2-25,(pRect->y0+pRect->y1)/2-7,1);	

	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画点进
void CtrlDrawFrame_0014(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}

	GUI_SetColor(GUI_BLACK);
	GUI_DrawCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2-14,13);	
	GUI_DrawCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2+14,13);	
    GUI_DrawHLine((pRect->y0+pRect->y1)/2,(pRect->x0+pRect->x1)/2-56,(pRect->x0+pRect->x1)/2);
	GUI_FillPolygon(pPoints12,POINT_COUNT12,(pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2-14,1);	
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2+14,1);

	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//画点退
void CtrlDrawFrame_0015(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}

	GUI_SetColor(GUI_BLACK);
	GUI_DrawCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2-14,13);	
	GUI_DrawCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2+14,13);	
    GUI_DrawHLine((pRect->y0+pRect->y1)/2,(pRect->x0+pRect->x1)/2-46,(pRect->x0+pRect->x1)/2+10);
	GUI_RotatePolygon(pPoints0,pPoints12,POINT_COUNT12,pai);
	GUI_FillPolygon(pPoints0,POINT_COUNT12,(pRect->x0+pRect->x1)/2-46,(pRect->y0+pRect->y1)/2);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2-14,1);	
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2-24,(pRect->y0+pRect->y1)/2+14,1);	

	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//按钮补数
void CtrlDrawFrame_0016(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//按钮空白
void CtrlDrawFrame_0017(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
	GUI_SetColor(GUI_WHITE);
	GUI_FillEllipse((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2,48,24);	
	
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//按钮追浅色标
void CtrlDrawFrame_0018(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}

	GUI_SetColor(GUI_WHITE);
	GUI_FillRect((pRect->x0+pRect->x1)/2+50,(pRect->y0+pRect->y1)/2-25,(pRect->x0+pRect->x1)/2+60,(pRect->y0+pRect->y1)/2+5);	

	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}

//按钮追深色标
void CtrlDrawFrame_0019(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}

	GUI_SetColor(GUI_BLACK);
	GUI_FillRect((pRect->x0+pRect->x1)/2+50,(pRect->y0+pRect->y1)/2-25,(pRect->x0+pRect->x1)/2+60,(pRect->y0+pRect->y1)/2+5);
	
	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}
/*
//画说明书
void CtrlDrawFrame_0020(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN002 5
	u32 leftup,rightdn;
	leftup = BrightColor(pColor->outcolor,64);
	rightdn = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);
	if(state==0)
		Draw3DRect(pRect,leftup,rightdn,pColor->extend);
	else if(state==1)
	{		
		Draw3DRect(pRect,rightdn,leftup,pColor->extend);
		pRect->x0+=pColor->extend;
		pRect->y0+=pColor->extend;
	}
	else
	{
		Draw3DRect(pRect,pColor->outcolor,pColor->outcolor,pColor->extend);
	}
	
	GUI_SetColor(GUI_WHITE);
	GUI_SetPenSize(5);
	GUI_AA_DrawArc(375,155,50,50,60,120);
	GUI_AA_DrawArc(425,155,50,50,60,120);
	GUI_SetPenSize(1);

	GUI_DrawVLine((pRect->x0+pRect->x1)/2+50,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2-50,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);

	GUI_DrawVLine((pRect->x0+pRect->x1)/2+51,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2-51,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);

	GUI_DrawVLine((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);

	GUI_AA_DrawArc(375,95,50,50,60,120);
	GUI_AA_DrawArc(425,95,50,50,60,120);

	pRect->x0+=MARGIN002;
	pRect->x1-=MARGIN002;
}
*/

void CtrlDrawFrame_0020(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	GUI_SetColor(GUI_WHITE);
	GUI_SetPenSize(5);
	GUI_AA_DrawArc(375,155,50,50,60,120);
	GUI_AA_DrawArc(425,155,50,50,60,120);
	GUI_SetPenSize(1);

	GUI_DrawVLine((pRect->x0+pRect->x1)/2+50,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2-50,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);

	GUI_DrawVLine((pRect->x0+pRect->x1)/2+51,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2-51,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);

	GUI_DrawVLine((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);
	GUI_DrawVLine((pRect->x0+pRect->x1)/2,(pRect->y0+pRect->y1)/2-28,(pRect->y0+pRect->y1)/2+32);

	GUI_AA_DrawArc(375,95,50,50,60,120);
	GUI_AA_DrawArc(425,95,50,50,60,120);

}

//画上半个箭头
void CtrlDrawFrame_0021(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	GUI_SetColor(GUI_WHITE);
	GUI_FillPolygon(pPoints5,POINT_COUNT5,pRect->x0,pRect->y1);
}

//画下半个箭头
void CtrlDrawFrame_0022(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	GUI_SetColor(GUI_WHITE);
	GUI_FillPolygon(pPoints6,POINT_COUNT6,pRect->x0,pRect->y0);
}

//画指示灯背景绿色
void CtrlDrawFrame_0023(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	u32 color;
	int x,y;
	int len;

	GUI_SetColor(GUI_GREEN);
	GUI_FillRectEx(pRect);

	x = pRect->x1-pRect->x0;
	y = pRect->y1-pRect->y0;
	if(y>x)
	{
		len = x;
		x = pRect->x0+x/2;
		y = pRect->y0+len/2;
		pRect->y0+=(len+1);
		
	}
	else
	{
		len = y;
		x = pRect->x0+len/2;
		y = pRect->y0+y/2;
		pRect->x0+=(len+1);

	}
	len>>=1;
	color = BrightColor(pColor->outcolor,-64);
	GUI_SetColor(color);
	GUI_FillCircle(x,y,len);
	
	GUI_SetColor(pColor->outcolor);
	x--;
	y--;
	len-=((len>>4)+1);
	GUI_FillCircle(x,y,len);

	color = BrightColor(pColor->incolor,-64);
	GUI_SetColor(color);
	len = len-((len>>3)+1);
	GUI_FillCircle(x,y,len);
	GUI_SetColor(pColor->incolor);
	x--,y--,len--;
	GUI_FillCircle(x,y,len);
	GUI_SetColor(GUI_WHITE);
	len-=(len>>2);
	GUI_DrawArc(x,y,len,len,100,170);
}

//画送料速度
void CtrlDrawFrame_0024(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	#define MARGIN001 5
	GUI_SetColor(pColor->outcolor);
	GUI_DrawRectEx(pRect);
	GUI_SetColor(pColor->incolor);
	GUI_FillRectEx(pRect);

	GUI_SetColor(GUI_BLACK);
	GUI_DrawCircle((pRect->x0+pRect->x1)/2+66,(pRect->y0+pRect->y1)/2+2,9);	
	GUI_DrawCircle((pRect->x0+pRect->x1)/2+66,(pRect->y0+pRect->y1)/2+22,9);	
  GUI_DrawHLine((pRect->y0+pRect->y1)/2+12,(pRect->x0+pRect->x1)/2+44,(pRect->x0+pRect->x1)/2+85);
	GUI_FillPolygon(pPoints12,POINT_COUNT12,(pRect->x0+pRect->x1)/2+85,(pRect->y0+pRect->y1)/2+12);
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2+66,(pRect->y0+pRect->y1)/2+2,1);	
	GUI_AA_FillCircle((pRect->x0+pRect->x1)/2+66,(pRect->y0+pRect->y1)/2+22,1);

	pRect->x0+=MARGIN001;
	pRect->x1-=MARGIN001;
}


ST_DrawCtrlFrame DrawCtrlFrame[]={
	CtrlDrawFrame_0000,
	CtrlDrawFrame_0001,
	CtrlDrawFrame_0002,
	CtrlDrawFrame_0003,
	CtrlDrawFrame_0004,
	CtrlDrawFrame_0005,
	CtrlDrawFrame_0006,
	CtrlDrawFrame_0007,
	CtrlDrawFrame_0008,
	CtrlDrawFrame_0009,
	CtrlDrawFrame_0010,
	CtrlDrawFrame_0011,
	CtrlDrawFrame_0012,
	CtrlDrawFrame_0013,
	CtrlDrawFrame_0014,
	CtrlDrawFrame_0015,
	CtrlDrawFrame_0016,
	CtrlDrawFrame_0017,
	CtrlDrawFrame_0018,
	CtrlDrawFrame_0019,
	CtrlDrawFrame_0020,
	CtrlDrawFrame_0021,
	CtrlDrawFrame_0022,
	CtrlDrawFrame_0023,
	CtrlDrawFrame_0024,
};

#define FRAMEKIND (sizeof(DrawCtrlFrame)/sizeof(ST_DrawCtrlFrame))

void CtrlDrawFrame(u16 DrawStyle,GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state)
{
	if(DrawStyle>=FRAMEKIND)return;
	DrawCtrlFrame[DrawStyle](pRect,pColor,state);
}
