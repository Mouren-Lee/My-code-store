#include "Beeper.h"

u16 timecnt;

void BEEP_SetBeeper(u16 count)
{
	timecnt = count;
}
void BEEP_Check()
{
	if(timecnt!=0)
	{
		timecnt--;
		BEEP_ON();
	}
	else
		BEEP_OFF();
}
