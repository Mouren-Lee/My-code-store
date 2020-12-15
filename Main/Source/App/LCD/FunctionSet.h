#include "interface.h"

#ifndef _FUNCTIONSET_H_
#define _FUNCTIONSET_H_

typedef union tag_param{
	u32 dData;
	void* pData;
}ST_PARAM;

typedef void FUNCTIONSETCALL(u16 CmdID,const ST_PARAM* pParam);
#define NULL 0
typedef struct tag_functionsetscript{
	GUI_RECT rect;			//������ڵ�һ��
	u8 ShowStyle;			//��ʾģʽ,������ڵڶ���
	ST_DrawFrame frame;		//�߿���ͼ
//	ST_Safty safty;			//��ȫ������ǩ
	U16 FontIndex;			//��������
	u8 FontMax;				//�������
	u16 LabelIndex;			//��ǩ����
	u8 LabelMax;			//����ֿ�
	u16 CmdID;				//���ò���
	ST_PARAM Param;				//���ò���
	FUNCTIONSETCALL* pCallBack;	//��Ӧ�Ļص�����	
	u16 Delay;				//��ʱ����ʱ��
}ST_FunctionSetScript;

typedef struct tag_functionset{
	u8 sign;
	u16 timer;
}ST_FunctionSet;

void FunCloseCurWindow(u16 CmdID,const ST_PARAM* pParam);
void FunOpenWindow(u16 CmdID,const ST_PARAM* pParam);
void OpenSaveWindow(u16 CmdID,const ST_PARAM* pParam);
void FunctionSetInit(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar);
u16 FunctionSetCheck(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar,SW_ProcessMsg* pMsg);
void FunctionSetDraw(const ST_FunctionSetScript* pScript,ST_FunctionSet* pVar);


#endif
