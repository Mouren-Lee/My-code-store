#include "interface.h"
#include "FunctionSet.h"
#include "PipeData.h"

#ifndef _WININPUT_H_
#define _WININPUT_H_

static const ST_ValueFormatScript PasswordScript={0,PIPE_PASSWORD,{0,65535,0,65535,0,5,0,0}};			  //������λ��
/*
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
*/
void SetInputValue(const ST_ValueFormatScript* pValue,u8 bPass);
void SetEnterCallback(FUNCTIONSETCALL* pCallback,u16 CmdID,const ST_PARAM* pParam);

#endif
