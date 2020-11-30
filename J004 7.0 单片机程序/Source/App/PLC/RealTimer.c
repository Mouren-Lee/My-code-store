#include "RealTimer.h"
#include "PIPE.h"

#define SECINMIN (60)
#define SECINHOUR (60*60)
#define SECINDAY  (60*60*24)
#define SECINYEAR (SECINDAY*365)
#define SECINLEAP (SECINDAY*366)
#define SECIN4YEAR (4*SECINYEAR+SECINDAY)
	
static const u8 Monthday[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static const u8 MonthLeapday[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
static u32 rtc_erro=0;
static u32 RTC_AdjustCnt;		//修正时间
static u32 RTC_LastSec;
//static u8 RTC_Year;	 //以2012年为基础，为闰年
//static u8 RTC_Month;		 //以0为基础，0~11月
//static u8 RTC_Day;		 //以0为基础,0~30天代表1号~31号
//static u8 RTC_Hour;	 //0~23
//static u8 RTC_Minute;		 //0~59
//static u8 RTC_Second;		 //0~59

static ST_Time RTC_Time;

u8 RTC_Configuration()
{
	/* Enable PWR and BKP clocks */

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  //BKP_DeInit();				/* Reset Backup Domain */

  RCC_LSEConfig(RCC_LSE_ON);	 /* Enable LSE */
  
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	  /* Wait till LSE is ready */
  {
		rtc_erro++;
		if(rtc_erro>=700000)
			return 1;
  }

  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		/* Select LSE as RTC Clock Source */
 
  RCC_RTCCLKCmd(ENABLE);					   /* Enable RTC Clock */
 
  RTC_WaitForSynchro();						 /* Wait for RTC registers synchronization */

  RTC_WaitForLastTask();					 /* Wait until last write operation on RTC registers has finished */
 
 // RTC_ITConfig(RTC_IT_SEC, ENABLE);			/* Enable the RTC Second */

  RTC_WaitForLastTask();				   /* Wait until last write operation on RTC registers has finished */

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
								  
  RTC_WaitForLastTask();			 /* Wait until last write operation on RTC registers has finished */
	return 0;
}


//写两个完全一样的函数,防止重入	,用于界面程序
void RTC_CalcCalendar(u32 TotalCnt,ST_Time* time)
{
	time->year = 0;
	time->pMonthday = MonthLeapday;
	while(TotalCnt>=SECIN4YEAR)
	{
		TotalCnt-=SECIN4YEAR;
		time->year+=4;
	}
	if(TotalCnt>SECINLEAP)
	{
	 	TotalCnt-=SECINLEAP;
		time->year++;
		time->pMonthday = Monthday;
		while(TotalCnt>SECINYEAR)
		{
			TotalCnt-=SECINYEAR;
			time->year++;	
		}
	}//得到年
	for(time->month=0;time->month<12;time->month++)
	 {
	 	time->mid = *(time->pMonthday)++ * SECINDAY ;
	 	if(TotalCnt>=time->mid)
			TotalCnt-=time->mid;
		else
			break;
	}//得到月
	time->day = TotalCnt/SECINDAY;
	TotalCnt%=SECINDAY;
	time->hour = TotalCnt/SECINHOUR;
	TotalCnt%=SECINHOUR;
	time->minute = TotalCnt/60;
	time->second = TotalCnt%60;
}

//常用于中断程序
void RTC_LoadCalendar()
{
	 u32 TotalCnt;	 
	 TotalCnt = RTC_AdjustCnt+RTC_LastSec;
	 RTC_CalcCalendar(TotalCnt,&RTC_Time);
}

u8 GetDaysinMonth(u8 year,u8 month)
{
	const u8* pMonthday;
	if(month>12)
		return 30;
	
	pMonthday = Monthday;
	if(year&0x03==0)	//为闰年 2月
		pMonthday = MonthLeapday;

	return pMonthday[month];
}

void RTC_Load()
{
	RTC_LastSec =  RTC_GetCounter();
	RTC_LoadCalendar();
}

void RTC_AddMin(void)
{
	RTC_Time.minute++;
	if(RTC_Time.minute>=60)
	{
		RTC_Time.minute-=60;
		RTC_Time.hour++;
		if(RTC_Time.hour>=24)
		{
			RTC_Time.hour=0;
			RTC_Time.day++;
			if(RTC_Time.day>=GetDaysinMonth(RTC_Time.year,RTC_Time.month))
			{
				RTC_Time.day = 0;
				RTC_Time.month++;
				if(RTC_Time.month>=12)
				{
					RTC_Time.month=0;
					RTC_Time.year++;
				}
			}
		}
	}
}

void RTC_Check()
{
	u32 RTC_Cur;
	u32 dDiff;
	RTC_Cur = RTC_GetCounter();
	if(RTC_Cur!=RTC_LastSec)
	{
	   	dDiff = RTC_Cur-RTC_LastSec;
		RTC_LastSec = RTC_Cur;
		if(dDiff>180)
			RTC_LoadCalendar();	
		else
		{
			RTC_Time.second+=dDiff;

			while(RTC_Time.second>=60)
			{
				RTC_Time.second-=60;
				RTC_AddMin();
			} 		
		}
	}
}

u32 RTC_CalcSecond(u8 year,u8 month,u8 day,u8 hour,u8 min,u8 sec)
{
	u32 TotalCnt;
	u8 i;
	const u8* pMonthday;
	for(TotalCnt = 0;year>=4;year-=4)
		TotalCnt+=SECIN4YEAR;
	pMonthday = MonthLeapday;
	if(year>0)
	{
		TotalCnt+=SECINLEAP;
		pMonthday = Monthday;

		for(year--;year>0;year--)
			TotalCnt+=SECINYEAR;
	}
	for(i=0;i<month;i++)
		TotalCnt+= *pMonthday++ * SECINDAY;
	if(day>=*pMonthday)
		day = *pMonthday;
	TotalCnt+=day*SECINDAY;
	TotalCnt+=hour*SECINHOUR;
	TotalCnt+=min*SECINMIN;
	TotalCnt+=sec;
	return TotalCnt;
}

u32 RTC_Adjust(u8 year,u8 month,u8 day,u8 hour,u8 min,u8 sec)
{
	RTC_AdjustCnt = RTC_CalcSecond(year,month,day,hour,min,sec);
	RTC_SetCounter(0);
	RTC_LastSec = 0;
	RTC_LoadCalendar();
	return RTC_AdjustCnt;
}

u32 RTC_GetTotalCnt()
{
	return (RTC_AdjustCnt+RTC_LastSec);
}

u8 RTC_GetYear(void)
{
	return RTC_Time.year;
}

u8 RTC_GetMonth(void)
{
	return RTC_Time.month;
}
u8 RTC_GetDay(void)
{
	return RTC_Time.day;
}
u8 RTC_GetHour(void)
{
	return RTC_Time.hour;
}
u8 RTC_GetMinute(void)
{
	return RTC_Time.minute;
}
u8 RTC_GetSecond(void)
{
	return RTC_Time.second;
}

void RTC_Init(u16 TimeH,u16 TimeL)
{
	RTC_AdjustCnt = TimeH;
	RTC_AdjustCnt<<=16;
	RTC_AdjustCnt+=TimeL;
	RTC_LoadCalendar();
}
