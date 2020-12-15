#include "BaseDraw.h"

u32 BrightColor(u32 color,s16 step)
{
	s16 mid;
	u8 i;
	u32 result = 0;
	
	for(i=0;i<3;i++)
	{
		mid = color&0x000000FF;
		color>>=8;
		mid+=step;
		if(mid<0)
			mid = 0;
		else if(mid>255)
			mid = 255;

		result=(result>>8)+((u32)mid<<16);
	}
	return result;
}

void Draw3DRect(const GUI_RECT *rect,u32 leftup,u32 rightdn,u8 height)
{
	s16 x0,y0,x1,y1;
	u8 step;
	GUI_SetColor(leftup);
	x0 = rect->x0;y0 = rect->y0;x1 = rect->x1;y1 = rect->y1;
	for(step=0;step<height;step++)
	{	
		GUI_SetColor(leftup);
		GUI_MoveTo(x0,y1);
		GUI_DrawLineTo(x0,y0);
		GUI_DrawLineTo(x1,y0);

		GUI_SetColor(rightdn);
		GUI_DrawLineTo(x1,y1);
		GUI_DrawLineTo(x0,y1);

		x0++;y0++;y1--;x1--;
	}
}
