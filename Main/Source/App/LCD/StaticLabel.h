#include "interface.h"

#ifndef _STATICLABEL_H_
#define _STATICLABEL_H_

//��̬��ǩ
typedef struct tag_staticlabelscript{
	GUI_RECT rect;			//������ڵ�һ��
	u8 ShowStyle;			//��ʾģʽ,������ڵڶ���
	ST_DrawFrame frame;		//�߿���ͼ
//	ST_Safty safty;			//��ȫ������ǩ
	u16 FontIndex;				//��������
	u16 LabelIndex;				//�ֿ�����
	u16 ShowDelay;				//ʱ����
}ST_StaticLabelScript;

typedef struct tag_staticlabel{
	u8 sign;				//������ڵ�һ��
	u16 timer;
}ST_StaticLabel;

void StaticLabelInit(const ST_StaticLabelScript* pScript,ST_StaticLabel *pVar);
u16 StaticLabelCheck(const ST_StaticLabelScript* pScript,ST_StaticLabel *pVar,SW_ProcessMsg *pMsg);
void StaticLabelDraw(const ST_StaticLabelScript* pScript,ST_StaticLabel *PVar);

#endif

