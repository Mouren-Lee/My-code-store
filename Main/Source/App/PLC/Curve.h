#include "datatype.h"

#ifndef _CURVE_H_
#define _CURVE_H_

typedef struct tag_curve
{
	const u16* pTable;
	u16 dSize;
}ST_Curve;

const u16* CRV_GetCurve(u16 index);
u16 CRV_GetCurveSize(u16 index);

#endif


