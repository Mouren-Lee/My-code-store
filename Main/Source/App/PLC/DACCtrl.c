#include "DACCtrl.h"

u16 voltA = 0;
u16 voltB = 0;
u16 DacOffset[2];
u16 DacSendBuf;
u16 DacSendBuf2;
//����DAC������üĴ���
void DAC_Configuration(void)
{
	DAC_InitTypeDef DAC_InitStructure;

    DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
  	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  	DAC_Init(DAC_Channel_2, &DAC_InitStructure);	  	/* DAC channel2 Configuration */
	DAC_SetChannel1Data(DAC_Align_12b_R,0);
	DAC_SetChannel2Data(DAC_Align_12b_R,0);
	voltA = voltB = 0;
	DAC_Cmd(DAC_Channel_1,ENABLE);
	DAC_Cmd(DAC_Channel_2,ENABLE);	
}

//����DAC1�������ѹ
void DAC_SetValueAO1(u16 volt)
{
//	voltA = volt*3970/4095;
//	if(voltA>4095)
//		voltA = 4095;
//	DAC_SetChannel1Data(DAC_Align_12b_R,voltA);
	
			  DacSendBuf = DacOffset[0]+volt;
					if(DacSendBuf>2048)
						DacSendBuf-=2048;
					else
						DacSendBuf = 0;	
	       if(DacSendBuf>4095)
		     DacSendBuf = 4095;
	       DAC_SetChannel1Data(DAC_Align_12b_R,DacSendBuf);	
}
//����DAC2�������ѹ
void DAC_SetValueAO2(u16 volt)
{
	voltB = volt;
	if(voltB>4095)
		voltB = 4095;
	DAC_SetChannel2Data(DAC_Align_12b_R,voltB);
	
//				 	DacSendBuf2 = DacOffset[0]+volt;
//					if(DacSendBuf2>2048)
//						DacSendBuf2-=2048;
//					else
//						DacSendBuf2 = 0;	
//	       if(DacSendBuf2>4095)
//		     DacSendBuf2 = 4095;
//	       DAC_SetChannel2Data(DAC_Align_12b_R,DacSendBuf2);	
}

//ȡ��DAC1��ǰ��ѹ
u16 DAC_GetValueAO1(void)
{
	return DacSendBuf;	
}

//ȡ��DAC2��ǰ��ѹ		
u16 DAC_GetValueAO2(void)
{
	return voltB;
}
void DAC_SetOffset(u8 index,u16 offset)
{
	DacOffset[index] = offset;		
}

