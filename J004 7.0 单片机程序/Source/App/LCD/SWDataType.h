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


#define SW_INVALIDATE BIT0		//��־Ҫ���ػ�
#define SW_HIDE	BIT1			//��������״̬
#define SW_FLASH_HIDE BIT2		//������˸ʱ����ʾ״̬
#define SW_TRANS BIT3			//��־�ؼ�Ϊ͸����
#define SW_FLASH BIT4			//Ҫ����˸
#define SW_TRUE_FLASH BIT5		//��ֵΪ��0ʱ��˸
#define SW_TOUCH_PRESSED BIT6	//�������Ѱ���
#define SW_STATIC_HIDE BIT7   //����˸ʱ���أ�����˸�������Ⱥ�ǳɫ��ɫ�л�ͼ��  2014-11-30����̸�

#define SW_ENABLE_EDIT BIT0		//����༩

#define STATIC_LABEL 0x01
#define STATE_SHOW 0x02
#define VALUE_SHOW 0x03
#define STATE_SET 0x04
#define FUNCTION_SET 0x05
#define VALUE_INPUT 0x06

typedef struct tag_ctrlscript{
	u8 style;
	const void* pCtrlScript;		//��һ����ԪΪ���Σ��ڶ����ֽ�Ϊ����
	void* pVariable;			//��һ���ֽ�Ϊ��־��
}SW_CtrlScript;

typedef struct tag_drawframe{				     //CtrlFrame.c
	u8 Style;				//��ͼ����ѡ��
	u16 ColorIndex;			//��ɫ�б��е�����   //shareres.c
	u8 ColorMax;			//��������ɫ		 //0����1,ֻ��1����ɫ,
	u16 ExParam;			//��չ�õĲ���
}ST_DrawFrame;

typedef struct tag_formatscript{
	u16 ValueMin;			//�ڲ���ֵ��Сֵ
	u16 ValueMax;			//�ڲ���ֵ���ֵ
	u16 ShowMin;			//��ʾ��Сֵ
	u16 ShowMax;			//��ʾ���ֵ
	u16 ShowOffset;			//��ֵ����ƫ����
	u8 integer;				//����λ��
	u8 fraction;			//С��λ��
	u8 Flags;				//��־λ
}ST_FormatScript;

typedef struct tag_valueformatscript{
	u8 ParStyle;			//��������
	u16 ParIndex;			//��������
	ST_FormatScript FormatScript;	//��ֵ��ʽ
}ST_ValueFormatScript;

typedef struct tag_labelfont{
	const GUI_FONT* pFont;		//��Ӧ����
	u32 color;				//��Ӧ��ɫ
	u8 sign;				//���뷽ʽ��
}ST_LabelFont;

typedef struct tag_ctrlercolor{
	u32 incolor;		//�ڲ���ɫ
	u32 outcolor;		//�����ɫ
	u32 extend;			//��չ����
}ST_CtrlColor;

typedef void (*ST_WINCALLBACK)(void* pWin,SW_ProcessMsg* pMsg);
typedef void (*ST_WINBACKDRAW)(void* pWin);


typedef struct tag_singlewindowscript{
	const u16 size;
	const SW_CtrlScript* pScript;
	const u32 bkColor;
	ST_WINCALLBACK pCallback;
	ST_WINBACKDRAW pBackDraw;	//�汳��,��ͼΪ0����bkColorֱ�����
}SW_SingleWindowScript;

typedef struct tag_singlewindow{
	s16 Order;					//����ʾ�е�˳��0Ϊ����ʾԽСԽ��ǰ��
	u32 bkColor;
	u8 sign;
	const SW_SingleWindowScript* pScript;
}SW_SingleWindow;

typedef void (*ST_DrawCtrlFrame)(GUI_RECT* pRect,const ST_CtrlColor* pColor,u16 state);

#endif
