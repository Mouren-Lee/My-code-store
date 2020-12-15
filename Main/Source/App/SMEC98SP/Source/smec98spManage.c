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
extern u8 	STOP_IN_flag;  //启动按键标志
extern u8 	KeyStop_flag; 

 u8 	JiaMi1_flag;   
 u8 	JiaMi2_flag; 
//---------------------------------------------------------
//函数名: 获取STM32的UID
//参数说明：
//			pSTM32_UID - 存放STM32的UID,12字节
//返回值说明：
//			void
//说明: 
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
  1.获取SMEC98SP的UID号, 获取STM32的ID, 获取STM32随机数
  2.验证PIN
  3.内外部认证
  4.SHA1=>前置数据^随机数
  5.密文读
  6.读数据
  7.写数据
  8.构造算法(PA口数据->密文送加密芯片, 密文返回)

  如果直接引用,请将print的调试信息去除
*/

void SMEC_Test(void)
{
	/*各种密钥,不会在I2C线路上传输,可以使用同一组.应该将密钥分散存储,防止主控芯片被破解后,被攻击者在二进制码中找到密钥 */
	unsigned char InternalKey[16] = {0x27,0x48,0x56,0x36,0x09,0x65,0x96,0xF7,0x0D,0x39,0xDA,0x2B,0xC5,0x9D,0x5E,0x7E};//内部认证密钥,必须和SMEC98SP一致 0x27,0x48,0x56,0x36,0x09,0x65,0x96,0xF7,0x0D,0x39,0xDA,0x2B,0xC5,0x9D,0x5E,0x7E
//	unsigned char ExternalKey[16] = {0x30,0x41,0x52,0x73,0x94,0x38,0x17,0x19,0x88,0x39,0xAA,0x8B,0x8C,0x3D,0x6E,0x7F};//外部认证密钥,必须和SMEC98SP一致
  unsigned char ExternalKey[16];
	unsigned char ExternalKey1[4] = {0x30,0x41,0x52,0x73};
  unsigned char ExternalKey10[] = {0x35,0x61,0x22,0x93,0x35,0x88,0x42,0x53,0x26,0x93,0x55,0x28,0x28,};
	unsigned char ExternalKey2[4] = {0x94,0x38,0x17,0x19};
  unsigned char ExternalKey11[] = {0x15,0xF1,0x2D,0x93,0x3E,0x18,0xE2,0x53,0xF6,0x13,0x55,0xEE,0xEE,0xAE,0xB8,0xC2};	
  unsigned char ExternalKey3[4] = {0x88,0x39,0xAA,0x8B};
  unsigned char ExternalKey12[] = {0x35,0xE1,0x2D,0x23,0x31,0x1A,0xEB,0x53,0x16,0x13,0x65,0xEE,0xEF,0x1E,0xB4,0xC2,0xF1,0x3D,0x96,0x3E,0x38,0xE2,0xF3,0xF6,0x23,0x85,0x1E};	
  unsigned char ExternalKey4[4] = {0x8C,0x3D,0x6E,0x7F};	
//	unsigned char SHA1_Key[16] = {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F};   //哈希算法认证密钥,必须和SMEC98SP一致
//	unsigned char MKey[16] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F};   //主控密钥,用于产生过程密钥,必须和SMEC98SP一致

//	unsigned char Pin[8] = {0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc};			//Pin认证密钥,必须和SMEC98SP一致
//		
	unsigned char bStm32Uid[12] = {0};			//存放STM32的UID
	unsigned char bSmec98spUid[12] = {0};		//存放SMEC98SP的UID
	unsigned short RandomSeek;					//随机数种子
	unsigned char bRandom[8] = {0};				//存放随机数
	unsigned char bSessionKey[8] = {0};			//存放过程密钥,过程密钥为临时产生的密钥
	unsigned char bDataBuf[64] = {0};
	unsigned char ret, bLen;
	unsigned short i, j;

	/*利用ADC悬空引脚产生随机数*/
//	Adc_Init();									//可放在主程序中
//	RandomSeek = Get_Adc_RandomSeek();			//利用ADC悬空引脚产生随机数

	/*获取STM32的UID*/
//	GetStm32Uid(bStm32Uid);

		
	/*获取SMEC98SP的UID*/
//	ret = SMEC_GetUid(bSmec98spUid);
//	if(ret)
//	{
// 
//		while(1);
//	}



//	/*将随机数RandomSeek，再做一次随机处理(与STM32的UID, SMEC98SP的UID作绑定, 使得即使相同情况下,不同的STM32,SMEC98SP随机数种子也不同)*/
//	for(i = 0; i < 6; i += 2)
//	{
//		/*使RandomSeek与STM32的UID相关*/
//		j = (bStm32Uid[i] << 8) + bStm32Uid[i + 1];
//		RandomSeek ^= j;

//		/*使RandomSeek与SMEC98SP的UID相关*/
//		j = (bSmec98spUid[i] << 8) + bSmec98spUid[i + 1];
//		RandomSeek ^= j;
//	}
//	srand(RandomSeek);


//	/*PIN码验证*/
//	ret = SMEC_CheckPin(Pin, (unsigned char)sizeof(Pin));
//	if(ret)
//	{
//		while(1);
//	}


//	/*内部认证, 主控芯片对SMEC98SP加密芯片合法性判断*/
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

	/*外部认证, SMEC98SP加密芯片对主控芯片合法性判断*/
	
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
	
	
	
	
	
//	/*SHA1摘要算法认证, 数据长度可自己设定*/
//	for(i = 0; i < 16; i ++)
//	{
//		bDataBuf[i] = (unsigned char) rand();
//	}
//	ret = SMEC_Sha1Auth(SHA1_Key, (unsigned char)sizeof(SHA1_Key), bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*调用加密芯片内部计算圆周长算法*/
//	bDataBuf[0] = 0x02;
//	ret = SMEC_CircleAlg(bDataBuf, 1, bDataBuf, &bLen);
//	if(ret)
//	{
//		while(1);
//	}


//	/*产生过程密钥,用于后续的Flash数据加密读,及构造的"端口数据运算"*/
//	for(i = 0; i < 8; i ++)
//	{
//		bRandom[i] = (unsigned char) rand();
//	}
//	ret = SMEC_GenSessionKey(MKey, bRandom, bSessionKey);
//	if(ret)
//	{

//		while(1);
//	}


//	/*密文读取Flash数据*/
//	ret = SMEC_CryptReadFlash(bSessionKey, 0x0000, bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*读取Flash数据*/
//	ret = SMEC_ReadFlash(0x0000, bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*写Flash数据*/
//	for(i = 0; i < 16; i ++)
//	{
//		bDataBuf[i] = (unsigned char) i;
//	}
//	ret = SMEC_WriteFlash(0x0000, bDataBuf, 16);
//	if(ret)
//	{

//		while(1);
//	}


//	/*构造"端口数据运算", 可以用实际的PA~PC端口数据*/
//	bDataBuf[0] = 0x00;
//	bDataBuf[1] = 0x00;
//	ret = SMEC_GpioAlg(bSessionKey, bDataBuf,2, bDataBuf);
//	if(ret)
//	{
//		while(1);
//	}


//	/*调用加密芯片内部计算圆周长算法,并密文在线路上传输*/
//	bDataBuf[0] = 0x02;
//	ret = SMEC_CircleAlgCrypt(bSessionKey, bDataBuf, 1, bDataBuf, &bLen);
//	if(ret)
//	{

//		while(1);
//	}

}
