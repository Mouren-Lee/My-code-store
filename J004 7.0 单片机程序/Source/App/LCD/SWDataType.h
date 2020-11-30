#include "LCDPLC.h"
#include "DataType.h"
#include "GUIType.h"

#ifndef _SW_DATATYPE_H_
#define _SW_DATATYPE_H_



#define TOUCH_CHG BIT1
#define TOUCH_PRESSED BIT0

typedef struct tag_ProcessMsg{
u8 TouchState;
u8 timeup;
int x;
int y;
u16 dMsg;
u32 dParam;
}SW_ProcessMsg;

#define SW_COLOR u32


#define SW_INVALIDATE BIT0		//标志要求重绘
#define SW_HIDE	BIT1			//处于隐藏状态
#define SW_FLASH_HIDE BIT2		//处于闪烁时不显示状态
#define SW_TRANS BIT3			//标志控件为透明的
#define SW_FLASH BIT4			//要求闪烁
#define SW_TRUE_FLASH BIT5		//当值为非0时闪烁
#define SW_TOUCH_PRESSED BIT6	//触摸屏已按下
#define SW_STATIC_HIDE BIT7   //不闪烁时隐藏，且闪烁可以有先后，浅色深色切换图形  2014-11-30翟玉碧改

#define SW_ENABLE_EDIT BIT0		//允许编缉

#define STATIC_LABEL 0x01
#define STATE_SHOW 0x02
#define VALUE_SHOW 0x03
#define STATE_SET 0x04
#define FUNCTION_SET 0x05
#define VALUE_INPUT 0x06

typedef struct tag_ctrlscript{
	u8 style;
	const void* pCtrlScript;		//第一个单元为外形，第二个字节为类型
	void* pVariable;			//第一个字节为标志集
}SW_CtrlScript;

typedef struct tag_drawframe{				     //CtrlFrame.c
	u8 Style;				//绘图函数选择
	u16 ColorIndex;			//颜色列表中的索引   //shareres.c
	u8 ColorMax;			//最大可用颜色		 //0代表1,只有1个颜色,
	u16 ExParam;			//扩展用的参数
}ST_DrawFrame;

typedef struct tag_formatscript{
	u16 ValueMin;			//内部数值最小值
	u16 ValueMax;			//内部数值最大值
	u16 ShowMin;			//显示最小值
	u16 ShowMax;			//显示最大值
	u16 ShowOffset;			//向负值方向偏移量
	u8 integer;				//整数位数
	u8 fraction;			//小数位数
	u8 Flags;				//标志位
}ST_FormatScript;

typedef struct tag_valueformatscript{
	u8 ParStyle;			//变量类型
	u16 ParIndex;			//变量索引
	ST_FormatScript FormatScript;	//数值格式
}ST_ValueFormatScript;

typedef struct tag_labelfont{
	const GUI_FONT* pFont;		//对应字体
	u32 color;				//对应颜色
	u8 sign;				//对齐方式等
}ST_LabelFont;

typedef struct tag_ctrlercolor{
	u32 incolor;		//内部颜色
	u32 outcolor;		//外框颜色
	u32 extend;			//扩展备用
}ST_CtrlColor;

typedef void (*ST_WINCALLBACK)(void* pWin,SW_ProcessMsg* pMsg);
typedef void (*ST_WINBACKDRAW)(void* pWin);


typedef struct tag_singlewindowscript{
	const u16 size;
	const SW_CtrlScript* pScript;
	const u32 bkColor;
	ST_WINCALLBACK pCallback;
	ST_WINBACKDRAW pBackDraw;	//绘背景,如图为0则用bkColor直接填充
}SW_SingleWindowScript;

typedef struct tag_singlewindow{
	s16 Order;					//在显示中的顺序0为不显示越小越在前面
	u32 bkColor;
	u8 sign;
	const SW_SingleWindowScript* pScript;
}SW_SingleWindow;

typedef void (*ST_DrawCtrlFrame)(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state);

#endif
