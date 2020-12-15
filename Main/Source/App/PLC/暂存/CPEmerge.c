#include "CPEmerge.h"
#include "PipeData.h"

#ifdef	Smart800_UsingNewCurve

//static uint64_t xpos2=0; 

static u16 CPx_GetStepSlow(ST_CPEmerge* pEmerge)      //伺服四段改  0626g  4段，根据频率分一段  减速两段 1/4
{                                                                 //步进慢速
	u32 mid;
//	u32 xpos2;                               //pEmerge->TimeSumExp代替了xpos

	if(pEmerge->TimeSumExp<4096)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/5+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;	
	else if(pEmerge->TimeSumExp<8192)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/7+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;
	else if(pEmerge->TimeSumExp<16384)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/8+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;
	else if(pEmerge->TimeSumExp<24576)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/9+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;			
	else if(pEmerge->TimeSumExp<32768)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/10+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;		
	else if(pEmerge->TimeSumExp<40960)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/12+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;	
	else if(pEmerge->TimeSumExp<49152)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/14+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;	
	else if(pEmerge->TimeSumExp<57344)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/15+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;		
	else if(pEmerge->TimeSumExp<65535)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/16+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;		
	
	if(pEmerge->TimeSumExp>=65535)
	{
		mid = 256;
	}
	else if(pEmerge->TimeSumExp>=16384)
	{
		mid = pEmerge->pCurve->pExpGT[(pEmerge->TimeSumExp>>8)-64];
	}
	else
	{
		mid = pEmerge->pCurve->pExpLT[pEmerge->TimeSumExp>>5];
	}

	mid = (mid*pEmerge->MinT)>>8;
	if(mid>0xFFFF)
		return 0xFFFF;

	return mid;
}  

/* 
static u16 CPx_GetStepSlow(ST_CPEmerge* pEmerge)      //伺服四段改  0626g  4段，根据频率分一段  减速两段 1/4
{                                                                 //步进慢速
	u32 mid;
//	u32 xpos2;                               //pEmerge->TimeSumExp代替了xpos

	if(pEmerge->TimeSumExp<4096)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/4+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;	
	else if(pEmerge->TimeSumExp<8192)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/6+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;
	else if(pEmerge->TimeSumExp<16384)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/7+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;
	else if(pEmerge->TimeSumExp<24576)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/8+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;			
	else if(pEmerge->TimeSumExp<32768)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/9+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;		
	else if(pEmerge->TimeSumExp<40960)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/12+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;	
	else if(pEmerge->TimeSumExp<49152)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/14+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;	
	else if(pEmerge->TimeSumExp<57344)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/17+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;		
	else if(pEmerge->TimeSumExp<65535)
		pEmerge->TimeSumExp += (pEmerge->NextT*pEmerge->TimeScale/20+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;		
	
	if(pEmerge->TimeSumExp>=65535)
	{
		mid = 256;
	}
	else if(pEmerge->TimeSumExp>=16384)
	{
		mid = pEmerge->pCurve->pExpGT[(pEmerge->TimeSumExp>>8)-64];
	}
	else
	{
		mid = pEmerge->pCurve->pExpLT[pEmerge->TimeSumExp>>5];
	}

	mid = (mid*pEmerge->MinT)>>8;
	if(mid>0xFFFF)
		return 0xFFFF;

	return mid;
}  
*/ 
static u16 CPx_GetTimerT(ST_CPEmerge* pEmerge)              //步进快速
{
	u32 mid;
	u32 xpos;

	xpos = (pEmerge->TimeSum*pEmerge->TimeScale/12+(1<<(CP_TIME_SCALE_BIT-1)))>>CP_TIME_SCALE_BIT;
	
	if(xpos>=65535)
		mid = 256;
	else if(xpos>=16384)
		mid = pEmerge->pCurve->pExpGT[(xpos>>8)-64];
	else
		mid = pEmerge->pCurve->pExpLT[xpos>>5];

	mid = (mid*pEmerge->MinT)>>8;
	if(mid>0xFFFF)
		return 0xFFFF;

	return mid;
}

static u16 CPx_GetTT2(ST_CPEmerge* pEmerge)    //伺服五段     伺服慢速     减加速1/8
{
	u32 tmp;
	if(pEmerge->flast>960000000000ULL/pEmerge->MinT)
	{
		return pEmerge->NextT;
	}
	else if(pEmerge->Havencnt<=pEmerge->Givencnt>>5)
	{	
//		tmp=((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*(0.2f+25.6f*((float)pEmerge->Havencnt)/(float)pEmerge->Givencnt);
//		pEmerge->flast+=MyMin(pEmerge->duty,(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*(0.2f+25.6f*((float)pEmerge->Havencnt)/(float)pEmerge->Givencnt));
		tmp=(uint64_t)(pEmerge->Givencnt+(pEmerge->Havencnt<<7))*pEmerge->NextT*pEmerge->TimeScale/(pEmerge->Givencnt*5);
//		pEmerge->flast+=MyMin(pEmerge->duty,tmp);
		if(tmp>80000ul*pEmerge->duty)
			tmp=80000ul*pEmerge->duty;
		pEmerge->flast+=tmp;
	}		
	else if(pEmerge->Havencnt<=pEmerge->Givencnt>>3)
	{	
//		pEmerge->flast+=MyMin(pEmerge->duty,(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f);
		tmp=(u32)pEmerge->NextT*pEmerge->TimeScale;
//		pEmerge->flast+=MyMin(pEmerge->duty,tmp);
		if(tmp>80000ul*pEmerge->duty)
			tmp=80000ul*pEmerge->duty;
		pEmerge->flast+=tmp;
	}
	else if(pEmerge->Havencnt<=pEmerge->Givencnt>>2)
	{	
//		pEmerge->flast+=(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*(1.875f-7.0f*(float)pEmerge->Havencnt/(float)pEmerge->Givencnt);
		tmp=(uint64_t)(pEmerge->Givencnt*15-pEmerge->Havencnt*56)*pEmerge->NextT*pEmerge->TimeScale/((pEmerge->Givencnt<<3));
		pEmerge->flast+=tmp;
	}		
	else if(pEmerge->Havencnt<=pEmerge->Givencnt>>1)
	{	
//		pEmerge->flast+=(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*(0.25f-0.5f*(float)pEmerge->Havencnt/(float)pEmerge->Givencnt);
		tmp=(uint64_t)(pEmerge->Givencnt-(pEmerge->Havencnt<<1))*pEmerge->NextT*pEmerge->TimeScale/((pEmerge->Givencnt<<2));
		pEmerge->flast+=tmp;
	}		
	
	return 960000000000ULL/pEmerge->flast;
}

static u16 CPx_GetTT(ST_CPEmerge* pEmerge)      //伺服快速
{ 
	u32 tmp;
	if(pEmerge->Havencnt<=pEmerge->Givencnt>>5)
	{	
//		pEmerge->flast+=MyMin(pEmerge->duty,(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*(0.2f+25.6f*((float)pEmerge->Havencnt)/(float)pEmerge->Givencnt));
//		tmp=((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*(0.2f+25.6f*((float)pEmerge->Havencnt)/(float)pEmerge->Givencnt);
		tmp=(uint64_t)(pEmerge->Givencnt+(pEmerge->Havencnt<<7))*pEmerge->NextT*pEmerge->TimeScale/(pEmerge->Givencnt*5);
//		pEmerge->flast+=MyMin(pEmerge->duty,tmp);	
		if(tmp>80000ul*pEmerge->duty)
			tmp=80000ul*pEmerge->duty;
		pEmerge->flast+=tmp;
	}		
	else if(pEmerge->Havencnt<=pEmerge->Givencnt>>1)	
	{
		if(pEmerge->flast>960000000000ULL/pEmerge->MinT)
		{
			return pEmerge->NextT;
		}
		else if(pEmerge->flast<480000000000ULL/pEmerge->MinT)
		{
//			pEmerge->flast+=MyMin(pEmerge->duty,(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f);
			tmp=(u32)pEmerge->NextT*pEmerge->TimeScale;
//			pEmerge->flast+=MyMin(pEmerge->duty,tmp);
			if(tmp>80000ul*pEmerge->duty)
				tmp=80000ul*pEmerge->duty;
			pEmerge->flast+=tmp;
		}
		else
		{
			if(pEmerge->TimeSumExp)
			{
				if(pEmerge->Havencnt<=(pEmerge->Givencnt>>3)+(pEmerge->TimeSumExp*3>>2))
				{
//					pEmerge->flast+=(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*((float)(pEmerge->Givencnt+pEmerge->TimeSumExp*5-pEmerge->Havencnt*7)/(float)(pEmerge->Givencnt-(pEmerge->TimeSumExp<<1)));	   //1/4 1/8
//					pEmerge->flast+=(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*((float)(pEmerge->Givencnt+(pEmerge->TimeSumExp<<2)-pEmerge->Havencnt*6)/(float)(pEmerge->Givencnt-(pEmerge->TimeSumExp<<1)));	   //1/4 1/4
					tmp=(uint64_t)(pEmerge->Givencnt+(pEmerge->TimeSumExp<<2)-pEmerge->Havencnt*6)*pEmerge->NextT*pEmerge->TimeScale/((pEmerge->Givencnt-(pEmerge->TimeSumExp<<1)));
					pEmerge->flast+=tmp;
				}
				else
				{
//					pEmerge->flast+=(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*((float)(pEmerge->Givencnt-(pEmerge->Havencnt<<1))/(float)(pEmerge->Givencnt*6-pEmerge->TimeSumExp*12));          //1/4   1/8
//					pEmerge->flast+=(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f*((float)(pEmerge->Givencnt-(pEmerge->Havencnt<<1))/(float)(pEmerge->Givencnt*3-pEmerge->TimeSumExp*6));          //1/4   1/4
					tmp=(uint64_t)(pEmerge->Givencnt-(pEmerge->Havencnt<<1))*pEmerge->NextT*pEmerge->TimeScale/((pEmerge->Givencnt*3-pEmerge->TimeSumExp*6));
					pEmerge->flast+=tmp;
				}
			}
			else
			{
				pEmerge->TimeSumExp=pEmerge->Havencnt;          //这里因为伺服曲线没有用到TimeSumExp，所以用作储存一个定值。
//				pEmerge->flast+=(float)((u32)pEmerge->NextT*pEmerge->TimeScale)/80000.0f;
				tmp=(u32)pEmerge->NextT*pEmerge->TimeScale;
//			  pEmerge->flast+=MyMin(pEmerge->duty,tmp);
				pEmerge->flast+=tmp;
			}
		}		
	}

	return 960000000000ULL/pEmerge->flast;
}


void CPx_Keep(ST_CPEmerge* pEmerge,u32 PlusCnt,u16 MaxT)
{
	pEmerge->PlusCnt = PlusCnt;
	pEmerge->NextT = MaxT;
	pEmerge->MaxT = MaxT;
	pEmerge->State = CP_KEEP_LEN;
}


u16 CPx_SetParam(ST_CPEmerge* pEmerge,u32 PlusCnt,u16 TopCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 MaxT,u16 MinT,u16 Curve)
{
	if(pEmerge->State!=CP_WAIT)
		return 0;
	if(PlusCnt==0)
		return 0;
	if(PlusCnt<=SeekCnt)
		return 0;
	if(MaxT<MinT)
		return 0;
	if(TimeScale<32)
		TimeScale = 32;
	pEmerge->TimeScale = TimeScale+1;
	pEmerge->MaxT = MaxT;
	pEmerge->MinT = MinT;
	pEmerge->pCurve = CRV_GetCurve(Curve);
	
	pEmerge->TimeSumExp = 0;
	pEmerge->TimeSum = 0;
	pEmerge->MaxCnt = PlusCnt-SeekCnt;

	pEmerge->Mark = 0;
	pEmerge->LostMark = 0;

	pEmerge->NextT = pEmerge->MaxT;
	pEmerge->UpCnt = 1;

	pEmerge->SeekCnt = SeekCnt;
	pEmerge->PlusCnt = PlusCnt;
	pEmerge->TopCnt = TopCnt;
	pEmerge->KeepCnt = KeepCnt;	
	pEmerge->State =  CP_START;

	pEmerge->TBufPt = 0;
	pEmerge->TBufT[0] = pEmerge->MaxT;
	pEmerge->TBufCnt[0] = 1;

	pEmerge->curve_line = Curve;
	pEmerge->Havencnt=0;
	pEmerge->flast=960000000000ULL/MaxT;
	pEmerge->Givencnt=PlusCnt;
	pEmerge->duty= BACK_GetBuf(PIPE_DUTY);	 //test	
	
	return 1;
}

void  CPx_Deal(ST_CPEmerge* pEmerge)
{
	if(pEmerge->PlusCnt)
	{
		pEmerge->PlusCnt--;	
		pEmerge->Havencnt++;
	}
	
	switch(pEmerge->State)
	{
		case CP_START:

			pEmerge->TimeSum+=pEmerge->NextT;			
		
			if(pEmerge->MaxCnt<=1)
			{
				pEmerge->State = CP_SEEK_MARK;
				pEmerge->NextT = pEmerge->MaxT;
			}
			else
			{
				pEmerge->MaxCnt--;
	
				if(pEmerge->curve_line==0)                   
				  pEmerge->NextT = CPx_GetTimerT(pEmerge);				//步进快速
				else if(pEmerge->curve_line==2)               
					pEmerge->NextT = CPx_GetTT(pEmerge);		        //伺服快速
				else if(pEmerge->curve_line==3)                                       
					pEmerge->NextT = CPx_GetTT2(pEmerge);		        //伺服慢速  
				else
					pEmerge->NextT = CPx_GetStepSlow(pEmerge);      //步进慢速
				
				if(pEmerge->NextT<pEmerge->MaxT)
				{					
					pEmerge->State = CP_ACCELERATE;
					if(pEmerge->PlusCnt>(pEmerge->SeekCnt+pEmerge->TopCnt+2))
						pEmerge->MaxCnt = (pEmerge->PlusCnt-pEmerge->TopCnt-pEmerge->SeekCnt)>>1;
					else
						pEmerge->MaxCnt = 0;
					
					pEmerge->UpCnt = 1;	
					pEmerge->TBufPt = 0;
					pEmerge->TBufT[0] = pEmerge->NextT;
					pEmerge->TBufCnt[0] = 0;					
				}
				else
					pEmerge->NextT = pEmerge->MaxT;
			}
			break;
		case CP_ACCELERATE:
			pEmerge->UpCnt++;
		
			pEmerge->TimeSum+=pEmerge->NextT;	
		
			if(pEmerge->curve_line==0)                      //步进快速
			{	
				pEmerge->NextT = CPx_GetTimerT(pEmerge);
			}		
			else if(pEmerge->curve_line==2)		              //伺服快速 
			{
				pEmerge->NextT = CPx_GetTT(pEmerge);								
			}			
			else if(pEmerge->curve_line==3)                 //伺服慢速  
			{
				pEmerge->NextT = CPx_GetTT2(pEmerge);								
			}	
			else                                            //步进慢速
			{
				pEmerge->NextT = CPx_GetStepSlow(pEmerge);							
			}
			
			if((pEmerge->MaxCnt<=1)||(pEmerge->PlusCnt<=(pEmerge->SeekCnt+pEmerge->UpCnt+2)))
			{
				if(pEmerge->PlusCnt>(pEmerge->SeekCnt+pEmerge->UpCnt))
				{
					pEmerge->MaxCnt = pEmerge->PlusCnt-pEmerge->SeekCnt-pEmerge->UpCnt;
					pEmerge->State = CP_DEC_COMP;
				}
				else
				{
					pEmerge->State = CP_DECELERATE;
					pEmerge->NextT = pEmerge->TBufT[pEmerge->TBufPt];
				}
				break;
			}
			else
			{
				pEmerge->MaxCnt--;
				if(pEmerge->NextT<=pEmerge->MinT)
				{
					pEmerge->NextT = pEmerge->MinT;
					if(pEmerge->PlusCnt>(pEmerge->SeekCnt+pEmerge->UpCnt))
						pEmerge->MaxCnt = pEmerge->PlusCnt-pEmerge->SeekCnt-pEmerge->UpCnt;
					else
						pEmerge->MaxCnt = 0;
					pEmerge->State = CP_HIGH_SPEED;
					break;
				}
			}

			if(pEmerge->TBufT[pEmerge->TBufPt]!=pEmerge->NextT)
			{							
				pEmerge->TBufPt++;
				pEmerge->TBufT[pEmerge->TBufPt] = pEmerge->NextT;
				pEmerge->TBufCnt[pEmerge->TBufPt] = 0;
			}
			else
				pEmerge->TBufCnt[pEmerge->TBufPt]++;


			break;
		case CP_DEC_COMP:
			
			if(pEmerge->MaxCnt<=1)
			{
				pEmerge->MaxCnt = pEmerge->UpCnt;
				pEmerge->NextT = pEmerge->TBufT[pEmerge->TBufPt];
				pEmerge->State = CP_DECELERATE;
			}
			else
				pEmerge->MaxCnt--;
			break;		
		case  CP_HIGH_SPEED:
			if(pEmerge->MaxCnt<=1)
			{
				pEmerge->MaxCnt = pEmerge->PlusCnt;
				pEmerge->State = CP_DECELERATE;				
				pEmerge->NextT = pEmerge->TBufT[pEmerge->TBufPt];
			}
			else
				pEmerge->MaxCnt--;
			break;

		case CP_DECELERATE:			
			if(pEmerge->TBufCnt[pEmerge->TBufPt])
			{
			   pEmerge->TBufCnt[pEmerge->TBufPt]--;
			   pEmerge->NextT = pEmerge->TBufT[pEmerge->TBufPt];
			}
			else if(pEmerge->TBufPt)
			{
				pEmerge->TBufPt--;
			   	pEmerge->NextT = pEmerge->TBufT[pEmerge->TBufPt];
			}
			else
				pEmerge->NextT = pEmerge->MaxT;
 													
			if(pEmerge->MaxCnt<=1)
			{
				pEmerge->State = CP_SEEK_MARK;
				pEmerge->NextT = pEmerge->MaxT;
			}
			else
			{
				pEmerge->MaxCnt--;
				if(pEmerge->NextT>=pEmerge->MaxT)
				{
					pEmerge->State = CP_LOW_SPEED;
					pEmerge->NextT = pEmerge->MaxT;
					if(pEmerge->PlusCnt>pEmerge->SeekCnt)
						pEmerge->MaxCnt = pEmerge->PlusCnt-pEmerge->SeekCnt;
					else
						pEmerge->MaxCnt = 0;
				}
			}
			break;
		case CP_LOW_SPEED:
			if(pEmerge->MaxCnt<=1)
			{
				pEmerge->State = CP_SEEK_MARK;
				pEmerge->NextT = pEmerge->MaxT;
				pEmerge->MaxCnt = pEmerge->SeekCnt;
				if(pEmerge->SeekCnt==0)
					pEmerge->State = CP_WAIT;
			}
			else
				pEmerge->MaxCnt--;
			break;
		case CP_SEEK_MARK:
			pEmerge->NextT = pEmerge->MaxT;
			if(pEmerge->SeekCnt==0)break;
			if(pEmerge->Mark)
			{
				pEmerge->State = CP_KEEP_LEN;
				pEmerge->PlusCnt = pEmerge->KeepCnt;
			}
			else if(pEmerge->PlusCnt==0)
			{
				pEmerge->State = CP_WAIT;
				pEmerge->LostMark = 1;
			}
			break;
		case CP_KEEP_LEN:
			pEmerge->NextT = pEmerge->MaxT;
			break;
		default:
			pEmerge->State = CP_WAIT;

	}
}

#endif
