#include "datatype.h"
#include "stm32f10x.h"

#ifndef _LCDPLC_H_
#define _LCDPLC_H_

#define PASSWORD_SET 1
#define PASSWORD_SYSTEM1_SET 31107
#define PASSWORD_HIDE_SET 2
#define PASSWORD_SYSTEM2_SET 60609

#define VERSION 1000

#define PLUS_OUT0
//#define PLUS_OUT1					   //定义则为肪冲输邮否则为DO输出
//#define PLUS_OUT2					   //定义则为肪冲输邮否则为DO输出
//#define PLUS_OUT3	


//#define TLC5604
//如果使用TLC5604,否则使用TLC5620

#define	MainFreq_Mhz	36

#define	TIMFreq_Mhz	1

#endif


