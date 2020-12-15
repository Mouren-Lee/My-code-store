#ifndef _VALUETRANS_H_
#define _VALUETRANS_H_


#include "Interface.h"
#include "SWDataType.h"

//���ݸ�ʽǰ����0
#define VFM_FILL BIT0

//����ֵ����ʽ����
u16 Value2Show(u16 value,const ST_FormatScript* pFormat);
//����ʾ��ֵ����ʽ���ŵ��ڲ���ֵ
u16 Show2Value(u16 value,const ST_FormatScript* pFormat);
//������ת��Ϊ�ַ���
u8 Value2Str(u8* str,u16 value,const ST_FormatScript* pFormat);
//���ַ�������ʽת��Ϊ����
u8 Str2Value(u8* str,u16* pValue,const ST_FormatScript* pFormat);

u8 AddCharValue(u8* str,u8 num,const ST_FormatScript* pFormat);

#endif
