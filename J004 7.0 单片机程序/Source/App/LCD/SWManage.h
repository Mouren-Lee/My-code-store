#include "interface.h"
#include "SWDataType.h"
#include "WinInput.h"


#ifndef _SWMANAGE_H_
#define _SWMANAGE_H_

extern const SW_SingleWindowScript Window07;
extern const SW_SingleWindowScript Window06;
extern const SW_SingleWindowScript Window05;
extern const SW_SingleWindowScript Window04;
extern const SW_SingleWindowScript Window02;
extern const SW_SingleWindowScript Window01;
extern const SW_SingleWindowScript Window00;
extern const SW_SingleWindowScript WinCalibrate;
extern const SW_SingleWindowScript WinInput;

static const SW_SingleWindowScript* pWinScript[]={
	&WinInput,
	&WinCalibrate,
	&Window00,
	&Window01,
	&Window02,
  &Window04,
  &Window05,
  &Window06,
	&Window07,

};

#define WININPUT_INDEX 0
#define WINCALIBRATE_INDEX 1
#define WINDOW00_INDEX 2
#define WINDOW01_INDEX 3
#define WINDOW02_INDEX 4
#define WINDOW04_INDEX 5
#define WINDOW05_INDEX 6
#define WINDOW06_INDEX 7
#define WINDOW07_INDEX 8


#define WINMAIN WINDOW00_INDEX

void SWManageInit(void);
void SWManageCheck(SW_ProcessMsg* pMsg);
void SWCloseCurrentWin(void);
void SWOpenWindow(u16 index);
void SWRedraw(void);
u16 SWReturnWin(void);
#endif
