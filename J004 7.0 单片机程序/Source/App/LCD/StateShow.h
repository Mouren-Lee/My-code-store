#include "interface.h"

#ifndef _STATESHOW_H_
#define _STATESHOW_H_

//��̬��ǩ
typedef struct tag_stateshowscript{
	GUI_RECT rect;			//������ڵ�һ��
	u8 ShowStyle;			//��ʾģʽ,������ڵڶ���
	ST_DrawFrame frame;		//�߿���ͼ
//	ST_Safty safty;			//��ȫ������ǩ
	u16 FontIndex;			//��������
	u8 FontMax;				//�������
	u16 LabelIndex;			//��ǩ����
	u8 LabelMax;			//����ֿ�
	u16 ShowDelay;			//��˸���
	u8 ParStyle;			//��������
	u16 ParIndex;			//��������
}ST_StateShowScript;

typedef struct tag_stateshow{
	u8 sign;				//������ڵ�һ��
	u16 timer;
	u16 value;
}ST_StateShow;

void StateShowInit(const ST_StateShowScript* pScript,ST_StateShow* pVar);
u16 StateShowCheck(const ST_StateShowScript* pScript,ST_StateShow* pVar,SW_ProcessMsg* pMsg);
void StateShowDraw(const ST_StateShowScript* pScript,ST_StateShow* pVar);


#endif

