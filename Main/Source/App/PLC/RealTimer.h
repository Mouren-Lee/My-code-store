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
u32 mid;				//用于中间变量,防止重入
const u8* pMonthday;	//用于中间变量,防止重入
}ST_Time;

//根据总秒数计算日期时间
void RTC_CalcCalendar(u32 TotalCnt,ST_Time* time);
//取得距2012-1-1 0:0:0的总秒数
u32 RTC_GetTotalCnt(void);
//初台化实时时钟相关变量
void RTC_Init(u16 TimH,u16 TimL);
//配置实时时钟
u8 RTC_Configuration(void);
//定时检查管理实时时钟模块
void RTC_Check(void);
//对实时时钟进行校时
u32 RTC_Adjust(u8 year,u8 month,u8 day,u8 hour,u8 min,u8 sec);
//取得当前年
u8 RTC_GetYear(void);
//取得当前月
u8 RTC_GetMonth(void);
//取得当前日
u8 RTC_GetDay(void);
//取得当前时
u8 RTC_GetHour(void);
//取得当前分
u8 RTC_GetMinute(void);
//取得当前秒
u8 RTC_GetSecond(void);
#endif
