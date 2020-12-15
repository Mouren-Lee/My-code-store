#include "stm32f10x.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "stm32f10x_i2c.h"
#include "PipeData.h"
#include "smec98sp.h"
#include "smec98spManage.h"
#include "iic_smec98sp.h"
#include "USART1.h"
#include "MainWork.h"
extern u8 	STOP_IN_flag;  //����������־
extern u8 	KeyStop_flag; 

 u8 	JiaMi1_flag;   
 u8 	JiaMi2_flag; 
//---------------------------------------------------------
//������: ��ȡSTM32��UID
//����˵����
//			pSTM32_UID - ���STM32��UID,12�ֽ�
//����ֵ˵����
//			void
//˵��: 
//---------------------------------------------------------
void GetStm32Uid(unsigned char *pSTM32_UID)
{
	pSTM32_UID[0] =  *(unsigned char*)(0x1FFFF7E8);
	pSTM32_UID[1] =  *(unsigned char*)(0x1FFFF7E9);
	pSTM32_UID[2] =  *(unsigned char*)(0x1FFFF7Ea);
	pSTM32_UID[3] =  *(unsigned char*)(0x1FFFF7Eb);
	pSTM32_UID[4] =  *(unsigned char*)(0x1FFFF7Ec);
	pSTM32_UID[5] =  *(unsigned char*)(0x1FFFF7Ed);
	pSTM32_UID[6] =  *(unsigned char*)(0x1FFFF7Ee);
	pSTM32_UID[7] =  *(unsigned char*)(0x1FFFF7Ef);
 	pSTM32_UID[8] =  *(unsigned char*)(0x1FFFF7f0);
 	pSTM32_UID[9] =  *(unsigned char*)(0x1FFFF7f1);
 	pSTM32_UID[10] =  *(unsigned char*)(0x1FFFF7f2);
 	pSTM32_UID[11] =  *(unsigned char*)(0x1FFFF7f3);
}




/*
  1.��ȡSMEC98SP��UID��, ��ȡSTM32��ID, ��ȡSTM32�����
  2.��֤PIN
  3.���ⲿ��֤
  4.SHA1=>ǰ������^�����
  5.���Ķ�
  6.������
  7.д����
  8.�����㷨(PA������->�����ͼ���оƬ, ���ķ���)

  ���ֱ������,�뽫print�ĵ�����Ϣȥ��
*/

void SMEC_Test(void)
{
	/*������Կ,������I2C��·�ϴ���,����ʹ��ͬһ��.Ӧ�ý���Կ��ɢ�洢,��ֹ����оƬ���ƽ��,���������ڶ����������ҵ���Կ */
	unsigned char InternalKey[16] = {0x27,0x48,0x56,0x36,0x09,0x65,0x96,0xF7,0x0D,0x39,0xDA,0x2B,0xC5,0x9D,0x5E,0x7E};//�ڲ���֤��Կ,�����SMEC98SPһ�� 0x27,0x48,0x56,0x36,0x09,0x65,0x96,0xF7,0x0D,0x39,0xDA,0x2B,0xC5,0x9D,0x5E,0x7E
//	unsigned char ExternalKey[16] = {0x30,0x41,0x52,0x73,0x94,0x38,0x17,0x19,0x88,0x39,0xAA,0x8B,0x8C,0x3D,0x6E,0x7F};//�ⲿ��֤��Կ,�����SMEC98SPһ��
  unsigned char ExternalKey[16];
	unsigned char ExternalKey1[4] = {0x30,0x41,0x52,0x73};
  unsigned char ExternalKey10[] = {0x35,0x61,0x22,0x93,0x35,0x88,0x42,0x53,0x26,0x93,0x55,0x28,0x28,};
	unsigned char ExternalKey2[4] = {0x94,0x38,0x17,0x19};
  unsigned char ExternalKey11[] = {0x15,0xF1,0x2D,0x93,0x3E,0x18,0xE2,0x53,0xF6,0x13,0x55,0xEE,0xEE,0xAE,0xB8,0xC2};	
  unsigned char ExternalKey3[4] = {0x88,0x39,0xAA,0x8B};
  unsigned char ExternalKey12[] = {0x35,0xE1,0x2D,0x23,0x31,0x1A,0xEB,0x53,0x16,0x13,0x65,0xEE,0xEF,0x1E,0xB4,0xC2,0xF1,0x3D,0x96,0x3E,0x38,0xE2,0xF3,0xF6,0x23,0x85,0x1E};	
  unsigned char ExternalKey4[4] = {0x8C,0x3D,0x6E,0x7F};	
//	unsigned char SHA1_Key[16] = {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F};   //��ϣ�㷨��֤��Կ,�����SMEC98SPһ��
//	unsigned char MKey[16] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F};   //������Կ,���ڲ���������Կ,�����SMEC98SPһ��

//	unsigned char Pin[8] = {0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc};			//Pin��֤��Կ,�����SMEC98SPһ��
//		
	unsigned char bStm32Uid[12] = {0};			//���STM32��UID
	unsigned char bSmec98spUid[12] = {0};		//���SMEC98SP��UID
	unsigned short RandomSeek;					//���������
	unsigned char bRandom[8] = {0};				//��������
	unsigned char bSessionKey[8] = {0};			//��Ź�����Կ,������ԿΪ��ʱ��������Կ
	unsigned char bDataBuf[64] = {0};
	unsigned char ret, bLen;
	unsigned short i, j;

	/*����ADC�������Ų��������*/
//	Adc_Init();									//�ɷ�����������
//	RandomSeek = Get_Adc_RandomSeek();			//����ADC�������Ų��������

	/*��ȡSTM32��UID*/
//	GetStm32Uid(bStm32Uid);

		
	/*��ȡSMEC98SP��UID*/
//	ret = SMEC_GetUid(bSmec98spUid);
//	if(ret)
//	{
// 
//		while(1);
//	}



//	/*�������RandomSeek������һ���������(��STM32��UID, SMEC98SP��UID����, ʹ�ü�ʹ��ͬ�����,��ͬ��STM32,SMEC98SP���������Ҳ��ͬ)*/
//	for(i = 0; i < 6; i += 2)
//	{
//		/*ʹRandomSeek��STM32��UID���*/
//		j = (bStm32Uid[i] << 8) + bStm32Uid[i + 1];
//		RandomSeek ^= j;

//		/*ʹRandomSeek��SMEC98SP��UID���*/
//		j = (bSmec98spUid[i] << 8) + bSmec98spUid[i + 1];
//		RandomSeek ^= j;
//	}
//	srand(RandomSeek);


//	/*PIN����֤*/
//	ret = SMEC_CheckPin(Pin, (unsigned char)sizeof(Pin));
//	if(ret)
//	{
//		while(1);
//	}


//	/*�ڲ���֤, ����оƬ��SMEC98SP����оƬ�Ϸ����ж�*/
	for(i = 0; i < 8; i ++)
	{
		bRandom[i] = (unsigned char) rand();
	}
	ret = SMEC_IntrAuth(InternalKey, bRandom);
	if(ret)
	{
		 JiaMi1_flag=1;
	}
  else
    JiaMi1_flag=0;

	/*�ⲿ��֤, SMEC98SP����оƬ������оƬ�Ϸ����ж�*/
	
	ExternalKey[0]=ExternalKey1[0];
	ExternalKey[1]=ExternalKey1[1];	
	ExternalKey[2]=ExternalKey1[2];	
	ExternalKey[3]=ExternalKey1[3];
	
	ExternalKey[4]=ExternalKey2[0];
	ExternalKey[5]=ExternalKey2[1];	
	ExternalKey[6]=ExternalKey2[2];	
	ExternalKey[7]=ExternalKey2[3];

	ExternalKey[8]=ExternalKey3[0];
	ExternalKey[9]=ExternalKey3[1];	
	ExternalKey[10]=ExternalKey3[2];	
	ExternalKey[11]=ExternalKey3[3];
	
	ExternalKey[12]=ExternalKey4[0];
	ExternalKey[13]=ExternalKey4[1];	
	ExternalKey[14]=ExternalKey4[2];	
	ExternalKey[15]=ExternalKey4[3];	
	
	ret = SMEC_ExtrAuth(ExternalKey);
	if(ret)
	{
    JiaMi2_flag=1;	
	}
	else
   JiaMi2_flag=0;	

	
	
		
		 // if(JiaMi2_flag==1)
			//  USART1_SetBuf(LENGTH_CNT,USART1_GetBuf(LENGTH_CNT)+1); 				
			 
			 if(JiaMi1_flag==0&&JiaMi2_flag==0)
		      USART1_SetBuf(JIAMI_INF,WORK_NeiBuZhengChang);
       else			
	       USART1_SetBuf(JIAMI_INF,WORK_NeiBuCuoWu);  
	
	
	
	
	
//	/*SHA1ժҪ�㷨��֤, ���ݳ��ȿ��Լ��趨*/
//	for(i = 0; i < 16; i ++)
//	{
//		bDataBuf[i] = (unsigned char) rand();
//	}
//	ret = SMEC_Sha1Auth(SHA1_Key, (unsigned char)sizeof(SHA1_Key), bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*���ü���оƬ�ڲ�����Բ�ܳ��㷨*/
//	bDataBuf[0] = 0x02;
//	ret = SMEC_CircleAlg(bDataBuf, 1, bDataBuf, &bLen);
//	if(ret)
//	{
//		while(1);
//	}


//	/*����������Կ,���ں�����Flash���ݼ��ܶ�,�������"�˿���������"*/
//	for(i = 0; i < 8; i ++)
//	{
//		bRandom[i] = (unsigned char) rand();
//	}
//	ret = SMEC_GenSessionKey(MKey, bRandom, bSessionKey);
//	if(ret)
//	{

//		while(1);
//	}


//	/*���Ķ�ȡFlash����*/
//	ret = SMEC_CryptReadFlash(bSessionKey, 0x0000, bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*��ȡFlash����*/
//	ret = SMEC_ReadFlash(0x0000, bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*дFlash����*/
//	for(i = 0; i < 16; i ++)
//	{
//		bDataBuf[i] = (unsigned char) i;
//	}
//	ret = SMEC_WriteFlash(0x0000, bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*����"�˿���������", ������ʵ�ʵ�PA~PC�˿�����*/
//	bDataBuf[0] = 0x00;
//	bDataBuf[1] = 0x00;
//	ret = SMEC_GpioAlg(bSessionKey, bDataBuf,2, bDataBuf);
//	if(ret)
//	{
//		while(1);
//	}


//	/*���ü���оƬ�ڲ�����Բ�ܳ��㷨,����������·�ϴ���*/
//	bDataBuf[0] = 0x02;
//	ret = SMEC_CircleAlgCrypt(bSessionKey, bDataBuf, 1, bDataBuf, &bLen);
//	if(ret)
//	{

//		while(1);
//	}

}
