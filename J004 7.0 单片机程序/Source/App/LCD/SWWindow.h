#include "SWDataType.h"

#ifndef _SW_WINDOW_H_
#define _SW_WINDOW_H_

void DefaultInit(SW_SingleWindow* pWin,const SW_SingleWindowScript* pScript);
void DefaultProc(SW_SingleWindow* pWin,SW_ProcessMsg* pMsg);
void DefaultProc0(void* pWin,SW_ProcessMsg* pMsg);


#endif
