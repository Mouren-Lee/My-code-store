#include "CPArray.h"
#include "Curve.h"
#include "PipeData.h"
#include "MainWork.h"
#include "IOManage.h"
#include "USART1.h"

#define ARRAY_STEP_READY 0
#define ARRAY_STEP_INIT 1
#define ARRAY_STEP_FIRST 2
#define ARRAY_STEP_START 3
#define ARRAY_STEP_ACCELERATE 4
#define ARRAY_STEP_ARRANGE 5
#define ARRAY_STEP_DONE 6

#define TIME_SCALE_BIT 15				//���16λ
#define TIME_SCALE_FULL ((1<<TIME_SCALE_BIT)-1)

 
u16* SetArrayMemory(ST_CPArray* pArray,u16* pPlus,u16 size)
{
	u16* pTmp;
	pTmp = pArray->pArray;
	pArray->pArray = pPlus;
	pArray->ArraySize = size;
	return pTmp;
}

u16 SetArrayParam(ST_CPArray* pArray,u32 PlusCnt,u16 curve,u16 StartT,u16 StopT,u16 MinT,u16 TimeScale)
{
	u16 bChanged = 0;
	if(pArray->Curve != curve||pArray->PlusCnt!=PlusCnt||pArray->StartT!=StartT||pArray->StopT!=StopT
		||pArray->MinT!=MinT||pArray->TimeScale!=TimeScale)
		bChanged = 1;
	
	pArray->Curve = curve;
	pArray->PlusCnt = PlusCnt;
	pArray->StartT = StartT;
	pArray->StopT = StopT;
	pArray->MinT = MinT;
	pArray->TimeScale = TimeScale;
	pArray->pCurveTable = CRV_GetCurve(pArray->Curve);
	pArray->TableSize = CRV_GetCurveSize(pArray->Curve);
			pArray->DingChangCnt = 0;
	return bChanged;
}

void ArrayInit(ST_CPArray *pArray)
{
	pArray->ArrayStep = ARRAY_STEP_INIT;
}

u16 ArrayRun(ST_CPArray *pArray)
{
	u16 lastT;
	u16 nextT;
	u16 mid;
  		pArray->DingChangCnt++;
	switch(pArray->ArrayStep)
	{
	case ARRAY_STEP_INIT:
		pArray->TimeIndex = 0;
		pArray->TimeSumTrail = 0;
		pArray->StartIndex = 0;
		pArray->DiffCount = 0;								//�������½�ʱ�ĸ�����		
		pArray->TopCnt = pArray->PlusCnt;					//��ֹû������л�
		pArray->DownCnt = pArray->PlusCnt;					//��ֹû������л�

		if(pArray->StartT>pArray->StopT)					//ȡ����С��Ƶ��
		{
			pArray->CurT = pArray->StartT;
			pArray->SecT = pArray->StopT;
		}
		else
		{
			pArray->CurT = pArray->StopT;
			pArray->SecT = pArray->StartT;
		}

		pArray->pArray[0] = pArray->CurT;						//��һ���������СƵ��
		pArray->Count = 1;				
		//ʹ�ö��ַ��ҵ�һ���� ���ڼ�����ֵͬʱ�����ҵĲ�һ�� �𶯶ο����Խ�С
	
		lastT = 0;
		nextT = pArray->TableSize-1;				
		mid = nextT>>2;				//�����ܼ�����ǰ�벿��
		
		do{
			if(pArray->CurT<=pArray->pCurveTable[mid])
				lastT = mid;
			else
				nextT = mid;
			
			mid = (lastT+nextT)>>1;

		}while(nextT>lastT+1);
		
		if(pArray->CurT<pArray->pCurveTable[nextT])	//û�ҵ�
		{
			pArray->ArrayStep = ARRAY_STEP_ARRANGE;			//���ٽ���
			break;
		}
		else
		{
			pArray->TimeIndex = mid;
			pArray->ArrayStep = ARRAY_STEP_START;
		}

	case ARRAY_STEP_START:			//������ڼ��������ɿأ���������²���̫��
		if(pArray->CurT>pArray->SecT)
			pArray->DiffCount++;
		else 
		{
			if(pArray->StartT<=pArray->StopT)
				pArray->StartIndex = pArray->DiffCount;
			pArray->ArrayStep = ARRAY_STEP_ACCELERATE;
		}

	case ARRAY_STEP_ACCELERATE:	
		pArray->TimeSumTrail += (pArray->CurT*pArray->TimeScale);
		pArray->TimeIndex+= (pArray->TimeSumTrail>>TIME_SCALE_BIT);
		pArray->TimeSumTrail &= (TIME_SCALE_FULL);
		
		if(pArray->TimeIndex+1>=pArray->TableSize)
		{
			pArray->CurT = pArray->pCurveTable[pArray->TableSize-1];
			pArray->ArrayStep = ARRAY_STEP_ARRANGE;					//����������
		}
		else
		{															//Ҫ��ݼ�
			lastT = pArray->pCurveTable[pArray->TimeIndex];
			nextT = pArray->pCurveTable[pArray->TimeIndex+1];
			if(lastT>=nextT)
				pArray->CurT = lastT-(((lastT-nextT)*pArray->TimeSumTrail)>>TIME_SCALE_BIT);
			else
				pArray->CurT = lastT;
		
			if(pArray->CurT<pArray->MinT)							//�ﵽ���Ƶ��
			{
				pArray->CurT = pArray->MinT;
				pArray->ArrayStep = ARRAY_STEP_ARRANGE;
			}
		}
															
		pArray->pArray[pArray->Count++] = pArray->CurT;			//���������к������Ƶ����Ϣ
																//���л������� ���� �����������巢����
		if((pArray->Count>=pArray->ArraySize)||((pArray->Count*2-pArray->DiffCount)>=pArray->PlusCnt))
			pArray->ArrayStep = ARRAY_STEP_ARRANGE;	

		break;

	case ARRAY_STEP_ARRANGE:

		if(pArray->StartT>pArray->StopT)
		{
			pArray->StartIndex = 0;
			pArray->TopCnt = pArray->Count;							//�ȱȽ��ٸ�ֵ
			pArray->DownCnt = pArray->PlusCnt+pArray->DiffCount+1;
	
			if(pArray->DownCnt>pArray->Count)
				pArray->DownCnt -= pArray->Count;			
			else
				pArray->DownCnt = 0;
		}
		else
		{
			pArray->StartIndex = pArray->DiffCount;
			pArray->TopCnt = pArray->Count-pArray->DiffCount;							//�ȱȽ��ٸ�ֵ
			pArray->DownCnt = pArray->PlusCnt+1;
			if(pArray->DownCnt>pArray->Count)
				pArray->DownCnt -= pArray->Count;
			else
				pArray->DownCnt = 0;
		}

		pArray->ArrayStep = ARRAY_STEP_DONE;
		break;
	}

	return (pArray->ArrayStep>=ARRAY_STEP_ACCELERATE);
}




//��һ�������������Ϊ40us
void CPArraySend2(ST_CPSend* pSend)
{
	pSend->SendCnt++;
	
	
	switch(pSend->State)
	{
	case CP_START:
		pSend->Mark = 0;
		pSend->Index = pSend->pArray->StartIndex+1;			//�ڶ�����������Ƶ�ʾ���
		pSend->NextT = pSend->pArray->StartT;
		pSend->SendCnt = 2;									//��һ������Ϊ�̶�40us�����ܹ�50us
		pSend->State = CP_ACCELERATE;
		pSend->LostMark = 0;								//ʧ��		

		break;
	case CP_ACCELERATE:
		pSend->NextT = pSend->pArray->pArray[pSend->Index];

		if(pSend->SendCnt>=pSend->pArray->TopCnt)
		{
			if(pSend->pArray->TopCnt>pSend->pArray->DownCnt)
			{
				pSend->State = CP_DECELERATE;
			}
			else
				pSend->State = CP_HIGH_SPEED;
		}
		else
			pSend->Index++;
				
		break;
	case CP_HIGH_SPEED:
		pSend->NextT = pSend->pArray->pArray[pSend->Index];
		if(pSend->SendCnt>=pSend->pArray->DownCnt)
		{
			pSend->State = CP_DECELERATE;		
		}
		break;
	case CP_DECELERATE:
		if(pSend->Index)
			pSend->Index--;
		
		pSend->NextT = pSend->pArray->pArray[pSend->Index];
		if(pSend->SendCnt>=pSend->pArray->PlusCnt)			
		{//��ʱpSend->SendCntӦ��ΪpSend->pArray->PlusCnt;
			pSend->NextT = pSend->pArray->StopT;			
			if(pSend->SeekCnt==0)
			{
				pSend->State = CP_KEEP_LEN;
				pSend->SendCnt = pSend->KeepCnt;
			}
			else
			{
				pSend->State = CP_SEEK_MARK;
				pSend->SendCnt = 0;
				
			}			
		}

		
		
		break;
			
	case CP_SEEK_MARK:
		pSend->NextT = pSend->SeekT;
		if(pSend->SendCnt<=pSend->SeekCnt)
		{
			if(pSend->Mark)
			{
				if(pSend->KeepCnt)
				{
					pSend->State = CP_KEEP_LEN;
					pSend->SendCnt = 0;
				}
				else
					pSend->State = CP_WAIT;
												  //Ѱ����
        
			}
		}	
		else
		{
			pSend->LostMark = 1;
			pSend->State = CP_WAIT;
		
		}
		
		
		
		
		break;
		
		
		
		
	case CP_KEEP_LEN:
		if(pSend->SendCnt>pSend->KeepCnt)
			pSend->State = CP_WAIT;

		break;
	}
	
	//�������Ƶ��
	if(pSend->NextT<pSend->pArray->MinT)
		pSend->NextT = pSend->pArray->MinT;
}


//---------------------------------------------------------------------

//��һ�������������Ϊ40us
void CPArraySend(ST_CPSend* pSend)
{
	pSend->SendCnt++;
	
	
		switch(pSend->State)
	{
	case CP_START:
		pSend->Mark = 0;
		pSend->Index = pSend->pArray->StartIndex+1;			//�ڶ�����������Ƶ�ʾ���
		pSend->NextT = pSend->pArray->StartT;
		pSend->SendCnt = 2;									//��һ������Ϊ�̶�40us�����ܹ�50us
		pSend->State = CP_ACCELERATE;
		pSend->LostMark = 0;								//ʧ��		

		break;
	case CP_ACCELERATE:
		pSend->NextT = pSend->pArray->pArray[pSend->Index];

		if(pSend->SendCnt>=pSend->pArray->TopCnt)
		{
			if(pSend->pArray->TopCnt>pSend->pArray->DownCnt)
			{
				pSend->State = CP_DECELERATE;
			}
			else
				pSend->State = CP_HIGH_SPEED;
		}
		else
			pSend->Index++;
				
		break;
	case CP_HIGH_SPEED:
		pSend->NextT = pSend->pArray->pArray[pSend->Index];
		if(pSend->SendCnt>=pSend->pArray->DownCnt)
		{
			pSend->State = CP_DECELERATE;		
		}
		break;
	case CP_DECELERATE:
		if(pSend->Index)
			pSend->Index--;
		
		pSend->NextT = pSend->pArray->pArray[pSend->Index];
		if(pSend->SendCnt>=pSend->pArray->PlusCnt)			
		{//��ʱpSend->SendCntӦ��ΪpSend->pArray->PlusCnt;
			pSend->NextT = pSend->pArray->StopT;			
			if(pSend->SeekCnt==0)
			{
				pSend->State = CP_KEEP_LEN;
				pSend->SendCnt = pSend->KeepCnt;
			}
			else
			{
				pSend->State = CP_SEEK_MARK;
				pSend->SendCnt = 0;
				
			}			
		}

		
		
		break;
			
	case CP_SEEK_MARK:
		pSend->NextT = pSend->SeekT;
		if(pSend->SendCnt<=pSend->SeekCnt)
		{
			if(pSend->Mark)
			{
				if(pSend->KeepCnt)
				{
					pSend->State = CP_KEEP_LEN;
					pSend->SendCnt = 0;
				}
				else
					pSend->State = CP_WAIT;
												  //Ѱ����
        
			}
		}	
		else
		{
			pSend->LostMark = 1;
			pSend->State = CP_WAIT;
		
		}
		
		
		
		
		break;
		
		
		
		
	case CP_KEEP_LEN:
		if(pSend->SendCnt>pSend->KeepCnt)
			pSend->State = CP_WAIT;

		break;
	}
	
	//�������Ƶ��
	if(pSend->NextT<pSend->pArray->MinT)
		pSend->NextT = pSend->pArray->MinT;
}




