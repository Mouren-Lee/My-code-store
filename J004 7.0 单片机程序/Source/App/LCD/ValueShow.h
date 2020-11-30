#include "interface.h"

#ifndef _VALUESHOW_H_
#define _VALUESHOW_H_

//��ֵ���
typedef struct tag_valueshowscript{
	GUI_RECT rect;				//������ڵ�һ��
	u8 ShowStyle;				//��ʾģʽ,������ڵڶ���
	ST_DrawFrame frame;			//�߿���ͼ
//	ST_Safty safty;				//��ȫ������ǩ
	u16 FontIndex;				//��������
	u8 Flags;					//��־λ
	ST_ValueFormatScript value;	//���ݼ���ʽ
}ST_ValueShowScript;

typedef struct tag_valueshow{
	u8 sign;				//������ڵ�һ��
	u16 value;
}ST_ValueShow;

void ValueShowInit(const ST_ValueShowScript* pScript,ST_ValueShow* pVar);
u16 ValueShowCheck(const ST_ValueShowScript* pScript,ST_ValueShow* pVar,SW_ProcessMsg* pMsg);
void ValueShowDraw(const ST_ValueShowScript* pScript,ST_ValueShow* pVar);

#endif
