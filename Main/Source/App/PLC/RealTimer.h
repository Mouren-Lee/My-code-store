#ifndef _REALTIMER_H_
#define _REALTIMER_H_

#include "LCDPLC.h"

typedef struct tag_time{
u8 year;
u8 month;
u8 day;
u8 hour;
u8 minute;
u8 second;
u32 mid;				//�����м����,��ֹ����
const u8* pMonthday;	//�����м����,��ֹ����
}ST_Time;

//������������������ʱ��
void RTC_CalcCalendar(u32 TotalCnt,ST_Time* time);
//ȡ�þ�2012-1-1 0:0:0��������
u32 RTC_GetTotalCnt(void);
//��̨��ʵʱʱ����ر���
void RTC_Init(u16 TimH,u16 TimL);
//����ʵʱʱ��
u8 RTC_Configuration(void);
//��ʱ������ʵʱʱ��ģ��
void RTC_Check(void);
//��ʵʱʱ�ӽ���Уʱ
u32 RTC_Adjust(u8 year,u8 month,u8 day,u8 hour,u8 min,u8 sec);
//ȡ�õ�ǰ��
u8 RTC_GetYear(void);
//ȡ�õ�ǰ��
u8 RTC_GetMonth(void);
//ȡ�õ�ǰ��
u8 RTC_GetDay(void);
//ȡ�õ�ǰʱ
u8 RTC_GetHour(void);
//ȡ�õ�ǰ��
u8 RTC_GetMinute(void);
//ȡ�õ�ǰ��
u8 RTC_GetSecond(void);
#endif
