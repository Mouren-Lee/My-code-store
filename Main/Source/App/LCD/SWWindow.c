#include "SWWindow.h"
#include "GUIType.h"
#include "GUI.h"
#include "interface.h"

void DefaultInit(SW_SingleWindow* pWin,const SW_SingleWindowScript* pScript)
{
	u16 pt;
	const SW_CtrlScript* pCtrl;

	pWin->bkColor = pScript->bkColor;
	pWin->pScript = pScript;
	pWin->sign|=SW_INVALIDATE;
	
	for(pt=0,pCtrl = pScript->pScript;pt<pScript->size;pt++,pCtrl++)
	{
		switch(pCtrl->style)
		{
		case STATIC_LABEL:
			StaticLabelInit(pCtrl->pCtrlScript,pCtrl->pVariable);
			break;
		case STATE_SHOW:
			StateShowInit(pCtrl->pCtrlScript,pCtrl->pVariable);
			break;
		case VALUE_SHOW:
			ValueShowInit(pCtrl->pCtrlScript,pCtrl->pVariable);
			break;
		case STATE_SET:
			StateSetInit(pCtrl->pCtrlScript,pCtrl->pVariable);
			break;
		}
	}
}

void DefaultProc0(void* pWin,SW_ProcessMsg* pMsg)
{
	DefaultProc(pWin,pMsg);
}	

void DefaultProc(SW_SingleWindow* pWin,SW_ProcessMsg* pMsg)
{
	GUI_RECT* pRect;
	GUI_RECT* pChkRect;
	u8* pSign;
	u8* pChkSign;
	const SW_SingleWindowScript* pScript;
	const SW_CtrlScript* pCtrl;
	const SW_CtrlScript* pChkCtrl;
	u16 pt,checkpt;
	u8 changed;
	u16 UnRedraw;
	u8 bGetStart;

	pScript = pWin->pScript;
	if(pWin->sign&SW_INVALIDATE)
	{
		if(pWin->pScript->pBackDraw==0)
		{
			GUI_SetBkColor(pWin->bkColor);
			GUI_Clear();
		}
		else
			pWin->pScript->pBackDraw(pWin);

		for(pt=0,pChkCtrl=pScript->pScript;pt<pScript->size;pt++,pChkCtrl++)
		{
			pChkSign = (u8*)(pChkCtrl->pVariable);
			*pChkSign|=SW_INVALIDATE;
		}
		pWin->sign&=(~SW_INVALIDATE);
	}

	
	//��鴥������ //�����ֵ����
	for(pt=0,pCtrl = pScript->pScript;pt<pScript->size;pt++,pCtrl++)
	{
		switch(pCtrl->style)
		{
		case STATIC_LABEL:
			StaticLabelCheck(pCtrl->pCtrlScript,pCtrl->pVariable,pMsg);
			break;
		case STATE_SHOW:
			StateShowCheck(pCtrl->pCtrlScript,pCtrl->pVariable,pMsg);
			break;
		case VALUE_SHOW:
			ValueShowCheck(pCtrl->pCtrlScript,pCtrl->pVariable,pMsg);
			break;
		case STATE_SET:
			StateSetCheck(pCtrl->pCtrlScript,pCtrl->pVariable,pMsg);
			break;
		case FUNCTION_SET:
			FunctionSetCheck(pCtrl->pCtrlScript,pCtrl->pVariable,pMsg);
			break;

		}
	}
	
	UnRedraw = 0;
	//�����Ҫ�ػ�
	for(pt=0,pCtrl = pScript->pScript;pt<pScript->size;)
	{
		changed = 0;
		pSign = pCtrl->pVariable;
		if(*pSign&SW_INVALIDATE)		//Ҫ���ػ�
		{
			pRect = (GUI_RECT* )(pCtrl->pCtrlScript);
			
			bGetStart = 0;
			for(checkpt=UnRedraw,pChkCtrl = pScript->pScript;checkpt<pScript->size;checkpt++,pChkCtrl++)
			{
				pChkRect = (GUI_RECT* )(pChkCtrl->pCtrlScript);
				pChkSign = (u8*)(pChkCtrl->pVariable);
				
				if(*pChkSign&SW_INVALIDATE)	continue;
			
				if(!bGetStart)
				{
					UnRedraw = checkpt;
					bGetStart = 1;
				}
				if((pChkRect->x0>pRect->x1)				//pChkCtrl��pCtrl�Ҳ�		
					||(pChkRect->x1<pRect->x0)				//pChkCtrl��pCtrl���
					||(pChkRect->y1<pRect->y0)				//pChkCtrl��pCtrl�Ϸ�
					||(pChkRect->y0>pRect->y1))				//pChkCtrl��pCtrl�·�
					continue;

				*pChkSign|=SW_INVALIDATE;
				changed = 1;
			}

		}
		pt++,pCtrl++;

		if(changed)
		{
			pt=0;
			pCtrl = pScript->pScript;	//��ͷ����			
		}
	}
	
	//�ػ�����͸�������ر���
	for(pt=0,pCtrl = pScript->pScript;pt<pScript->size;pt++,pCtrl++)
	{
		pSign = (u8*)(pCtrl->pVariable);
		if(*pSign&SW_INVALIDATE)
		{			
			if(*pSign&(SW_HIDE|SW_FLASH_HIDE|SW_TRANS))
			{
				pRect = (GUI_RECT* )(pCtrl->pCtrlScript);
				GUI_SetBkColor(pWin->bkColor);
				GUI_ClearRectEx(pRect);
			}
		}
	}
	//�ػ�ͼ��
	for(pt=0,pCtrl = pScript->pScript;pt<pScript->size;pt++,pCtrl++)
	{
		pSign = (u8*)(pCtrl->pVariable);
		if(*pSign&SW_INVALIDATE)
		{				
			switch(pCtrl->style)
			{
			case STATIC_LABEL:
				StaticLabelDraw(pCtrl->pCtrlScript,pCtrl->pVariable);
				break;
			case STATE_SHOW:
				StateShowDraw(pCtrl->pCtrlScript,pCtrl->pVariable);
				break;
			case VALUE_SHOW:
				ValueShowDraw(pCtrl->pCtrlScript,pCtrl->pVariable);
				break;
			case STATE_SET:
				StateSetDraw(pCtrl->pCtrlScript,pCtrl->pVariable);
				break;
			case FUNCTION_SET:
				FunctionSetDraw(pCtrl->pCtrlScript,pCtrl->pVariable);
				break;

			}

		}
	}

	pMsg->timeup = 0;
	pMsg->dMsg = 0;
}







