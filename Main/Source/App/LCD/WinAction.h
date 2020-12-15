#include "interface.h"

#ifndef _WINACTION_H_
#define _WINACTION_H_

void Win_SaveParameters(u16 CmdID,const ST_PARAM* pParam);
void Win_LoadParameters(u16 CmdID,const ST_PARAM* pParam);
void Win_InitParameters(void);
u32 Win_isParaEmpty(void);

#endif
