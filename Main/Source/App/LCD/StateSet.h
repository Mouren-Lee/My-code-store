#include "interface.h"

#ifndef _STATESET_H_
#define _STATESET_H_

#define STATE_SHOW_PRESSED 0x40		//ֻ��ʾ�Ƿ�Ϊ����
#define STATE_CYCLE 0x10			//����ѭ��ģʽ
#define STATE_KEEP 0x20				//���ְ���ʱ��������
#define STATE_DELAY 0x80			//���µ�һ�ζ�����ʱִ��
#define STATE_STYLE_MASK 0x0F		//�ֿ������־λ

#define STATE_DELAYDOIT (STATE_KEEP|STATE_DELAY)

#define STATE_SET_REVERT 0	  //����1���ɿ�0
#define STATE_SET_CONST 1	  //���º�λ����
#define STATE_SET_INCREASE 2  //����
#define STATE_SET_DESCEND 3	  //����

typedef struct tag_statesetscript{
	GUI_RECT rect;			//������ڵ�һ��
	u8 ShowStyle;			//��ʾģʽ,������ڵڶ���
	ST_DrawFrame frame;		//�߿���ͼ
//	ST_Safty safty;			//��ȫ������ǩ
	u16 FontIndex;			//��������
	u8 FontMax;				//�������
	u16 LabelIndex;			//��ǩ����
	u8 LabelMax;			//����ֿ�
	u8 ParStyle;			//��������
	u16 ParIndex;			//��������
	u8 SetStyle;			//��������
	u16 SetValue;			//�ݼ�ֵ���ݼ�ֵ���趨ֵ
	u16 SetMax;				//�趨ֵ����
	u16 SetMin;				//�趨ֵ����
	u16 Delay;				//����ʱ��
	u16 Speed;				//�ݼ��ٶ�
}ST_StateSetScript;

typedef struct tag_stateset{
	u8 sign;
	u16 timer;
	u16 value;
}ST_StateSet;

void StateSetInit(const ST_StateSetScript* pScript,ST_StateSet* pVar);
u16 StateSetCheck(const ST_StateSetScript* pScript,ST_StateSet* pVar,SW_ProcessMsg* pMsg);
void StateSetDraw(const ST_StateSetScript* pScript,ST_StateSet* pVar);

#endif
