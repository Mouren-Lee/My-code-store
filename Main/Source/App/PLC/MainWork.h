#ifndef _MAINWORK_H_
#define _MAINWORK_H_
#include "LCDPLC.h"


#define RunLed_on()  (GPIOC->BRR = GPIO_Pin_2)
#define RunLed_off() (GPIOC->BSRR = GPIO_Pin_2)


// //ϵͳ�����б�
//#define INPUT_DATA1 0
//#define INPUT_DATA2 1
//#define INPUT_DATA3 2
//#define OUTPUT_DATA1 3
//#define OUTPUT_DATA2 4
//#define UP_STATU1 5
//#define SPEED_GK1 6							//����
//���ڲ���



//======================����˿ڶ���X01-X10 10��=======================


//#define DI_MANUAL_AUTO_SW     X01	     //X01	����ֶ��Զ�
//#define DI_GD_Left 						X02		 	 //X02	�����
//#define DI_GD_Right 					X03		   //X03	�����
//#define DI_XW_Left  					X04	 	   //X04	����λ�ź�
//#define DI_XW_Right 					X05			 //X05	����λ�ź�
//#define DI_Left 							X06		   //X03	�����ת
//#define DI_Right		 					X07		   //X04	�����ת


#define DI_GK1                  X01		   //GK1����1����    
#define DI_GK2                  X02			 //GK2����2���� 
#define DI_GK3                  X03			 //GK2����2���� 
#define DI_JiShuPause           X04	
#define DI_START                X05      //�������   
#define DI_STOP                 X06      //���ֹͣ  


#define DI_FUWEI                X12			 // 

//==========================================================================

//======================����˿�Y01-Y10 10��=======================


#define DO_CP1                Y01     //����1����
#define DO_CW1                Y02     //����1����
#define DO_DuiJia             Y03     // 
#define DO_ChuiQi             Y04      
#define DO_DangLiao           Y05     
#define DO_YaLiao             Y06     
#define DO_ShuSong            Y07     //���� 


#define DO_BEEP               Y13     //������ 
//============================================================================
//��־λ�ṹ��
typedef struct {    //ϵͳ��־λ
    u8 Start_Flag;//������־λ             0:ֹͣ                              1:����
    u8 Mode_Flag;//���˳���־λ          0:�Լ��봵�����     1:������ʱ�����������   2:�رյ���   3:ѹ�����   4:ѹ�ϼ��� 
    u8 Tran_Flag;//���ͱ�־λ              0��δ���           1:���ǰ��ʱ            2:���ʱ��      
//----------������־λ------------
    bool BuzzerS_Flag;//������������־λ   false:���������ʱ��־λͬʱΪ0ʱ�رշ�����   true:����������
    bool BuzzerJs_Flag;//��������ʱ��־λ  false:�������������־λͬʱΪ0ʱ�رշ�����   true:����������
    bool StartIO_Flag;//���������־λ     false:���δ�����������������               true:���������
    bool Start_Button;//����������־λ     false:δ����                        true:������
    bool Count_Pause;//������ͣ��־λ      false:��������                       true:������ͣ
    bool Stop_Flag;//ֹͣ��־λ            false:ֹͣ״̬                      true:����ֹͣ״̬
    bool Stop_Button;//ֹͣ��־λ����       false:ֹͣ����δ����                true:ֹͣ��������
    bool HighStop_Flag;//��λֹͣ��־λ     false:δ�����λֹͣ״̬            true:�����λֹͣ״̬
    bool Count_Cnt;//������־λ             false:δ�������                   true:�������  
    bool X01_Flag;//���1�Ƿ������־λ      false:����                         true:δ����
    bool YaLiao_Flag;//ѹ�ϱ�־λ           false:δѹ��                       true:ѹ����           
} Sys_Flag;
//----------------------------
typedef struct {    //ʱ�������־λ
    u16 ChuiQic_Time;//������ʱ
    u16 YaLiaoc_Time;//ѹ�ϼ�ʱ
    u16 Run_Time;//������ʱ
    u16 Buzzer_Time;//��������ʱ
    u16 Tran_Time;//���ͼ�ʱ
} Time_Flag;
//==========================================================================
//����״̬
#define WORK_STOP     	0
#define WORK_RUN	      1
#define WORK_SYSTEM1	  2					//ϵͳ1


//==========================================================================
#define WORK_NeiBuZhengChang  0
#define WORK_NeiBuCuoWu       1		
//====================================================
//��־λ����
extern Sys_Flag Sys_Data;
extern Time_Flag Time_Data;
//====================================================
void MainWork_InitVar(void);
void MainWork(u32 TimChg);
 void Typedef_Init(void);//�ṹ���ʼ��
#endif
