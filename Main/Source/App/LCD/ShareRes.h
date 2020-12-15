#ifndef _SHARERES_H_
#define _SHARERES_H_

#include "Interface.h"

#include "LabelRoom.h"

#define COLOR_REDLED 3

const ST_LabelFont* GetShareLabelFont(u16 index);
const u8* GetShareString(u16 index);
const ST_CtrlColor* GetShareColor(u16 index);

#endif
