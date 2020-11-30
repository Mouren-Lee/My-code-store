#include "DACCtrl.h"

u16 voltA = 0;
u16 voltB = 0;
//配置DAC相关设置寄存器
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

//设置DAC1的输出电压
void DAC_SetValueAO1(u16 volt)
{
	voltA = volt*3970/4095;
	if(voltA>4095)
		voltA = 4095;
	DAC_SetChannel1Data(DAC_Align_12b_R,voltA);
}
//设置DAC2的输出电压
void DAC_SetValueAO2(u16 volt)
{
	voltB = volt;
	if(voltB>4095)
		voltB = 4095;
	DAC_SetChannel2Data(DAC_Align_12b_R,voltB);
}

//取得DAC1当前电压
u16 DAC_GetValueAO1(void)
{
	return voltA;	
}

//取得DAC2当前电压		
u16 DAC_GetValueAO2(void)
{
	return voltB;
}


