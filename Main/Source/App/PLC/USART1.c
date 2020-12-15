#include "USART1.h"
#include "CRC.h"
#include "PIPE.h"
#include "MainWork.h"


#define USART1_BUF_SIZE (USART1_PAR_SIZE*2+10)
#define USART1_BYTE_SIZE 	USART1_PAR_SIZE*2

 
 
 
 
 
 u16 Parameter[USART1_PAR_SIZE];

 
static u8* const ParaByte = (u8*)Parameter;

 

 



u32 RS485_Baudrate=9600;//ͨѶ������
u8 RS485_Parity=0;//0��У�飻1��У�飻2żУ��
u8 RS485_Addr=1;//�ӻ���ַ
u16 RS485_Frame_Distance=3;//����֡��С�����ms),������ʱ������Ϊ����һ֡
u8 RS485_RX_BUFF[2048];//���ջ�����2048�ֽ�
u16 RS485_RX_CNT=0;//���ռ�����
u8 RS485_FrameFlag=0;//֡�������
u8 RS485_TX_BUFF[2048];//���ͻ�����
u16 RS485_TX_CNT=0;//���ͼ�����


u16 startRegAddr;
u16 RegNum;
u16 calCRC;



u16 USART1_GetBuf(u16 index)
{
	if(index>=USART1_PAR_SIZE)
		return 0;
	return Parameter[index];
}

void USART1_SetBuf(u16 index,u16 value)
{
	if(index<USART1_PAR_SIZE)		
		Parameter[index] = value;
}

u8 USART1_GetIO(u8 index)
{
	u16 byte;
	byte = index>>3;
	if(byte>=USART1_BYTE_SIZE)
		return FALSE;	
	byte = ParaByte[byte];
	if(byte&BitMask[index&0x07])
		return TRUE;
	return FALSE;
}

void USART1_SetIO(u8 index,u8 value)
{
	u16 byte;
	byte = index>>3;
	if(byte>=(USART1_PAR_SIZE<<1))
		return;	
	if(value)
		ParaByte[byte]|=BitMask[index&0x07];
	else
		ParaByte[byte]&=(~BitMask[index&0x07]);
}

u8 USART1_GetParam8Bits(u8 index)
{
	u8 state,i,mask;
	u16 byte;	
	
	u8 tmp = 0;

	for(byte = index>>3,index&=0x07,i=0;byte<(USART1_PAR_SIZE<<1);byte++)
	{
		state = ParaByte[byte];
		mask = BitMask[index];

		for(;mask!=0;mask<<=1)
		{
			tmp = tmp>>1;
			if(state&mask)
				tmp|=BIT7;
			if(++i>=8)
				return tmp;
		}
		index = 0;
	}
	return tmp;
}


//void USART1_Configuration()
//{
//	USART_InitTypeDef USART_InitStructure;	
//	USART_InitStructure.USART_BaudRate            = 19200  ;
//	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
//	USART_InitStructure.USART_Parity              = USART_Parity_No;//USART_Parity_No;///USART_Parity_Even ;  USART_Parity_No
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART1, &USART_InitStructure);
//	USART_Cmd(USART1, ENABLE);  
//	
//	
//	
//}






//��ʱ��7��ʼ��
void Timer7_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        NVIC_InitTypeDef NVIC_InitStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //TIM7ʱ��ʹ�� 

        //TIM7��ʼ������
        TIM_TimeBaseStructure.TIM_Period = RS485_Frame_Distance*10; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
        TIM_TimeBaseStructure.TIM_Prescaler =7200; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ���ü���Ƶ��Ϊ10kHz
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
        TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

        TIM_ITConfig( TIM7, TIM_IT_Update, ENABLE );//TIM7 ��������ж�

        //TIM7�жϷ�������
        NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;  //TIM7�ж�
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�2��
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
        NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���                                                                  
}






void USART1_Configuration()
{
	USART_InitTypeDef USART_InitStructure;	
  NVIC_InitTypeDef NVIC_InitStructure;	
	
	USART_InitStructure.USART_BaudRate            = 19200  ;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;//USART_Parity_No;///USART_Parity_Even ;  USART_Parity_No
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE); 


        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
        USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//ʹ�ܴ���2�����ж�
        
        NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
        NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        USART_Cmd(USART1,ENABLE);//ʹ�ܴ���2
        SET_RX();//Ĭ��Ϊ����ģʽ
	
       Timer7_Init();//��ʱ��7��ʼ�������ڼ��ӿ���ʱ��
}


//////////////////////////////////////////////////////////////////////////////
//����n���ֽ�����
//buff:�������׵�ַ
//len�����͵��ֽ���
void RS485_SendData(u8 *buff,u8 len)
{ 
        SET_TX();//�л�Ϊ����ģʽ
        while(len--)
        {
                while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ�������Ϊ��
                USART_SendData(USART1,*(buff++));
        }
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ��������
}



/////////////////////////////////////////////////////////////////////////////////////
void USART1_IRQHandler(void)//����2�жϷ������
{
        u8 res;
        u8 err;
        if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
        {
                if(USART_GetFlagStatus(USART1,USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE)) err=1;//��⵽������֡�����У�����
                else err=0;
                res=USART_ReceiveData(USART1); //�����յ����ֽڣ�ͬʱ��ر�־�Զ����
                
                if((RS485_RX_CNT<2047)&&(err==0))
                {
                        RS485_RX_BUFF[RS485_RX_CNT]=res;
                        RS485_RX_CNT++;
                        
                        TIM_ClearITPendingBit(TIM7,TIM_IT_Update);//�����ʱ������ж�
                        TIM_SetCounter(TIM7,0);//�����յ�һ���µ��ֽڣ�����ʱ��7��λΪ0�����¼�ʱ���൱��ι����
                        TIM_Cmd(TIM7,ENABLE);//��ʼ��ʱ
                }
								
							USART_ClearITPendingBit(USART1,USART_IT_RXNE)	;
        }
				
				if(USART_GetITStatus(USART1,USART_IT_ORE)==SET)
				{
					
				  	USART_ClearFlag(USART1,USART_FLAG_ORE)	;
				}
				
}

///////////////////////////////////////////////////////////////////////////////////////
//�ö�ʱ��7�жϽ��տ���ʱ�䣬������ʱ�����ָ��ʱ�䣬��Ϊһ֡����
//��ʱ��7�жϷ������         
void TIM7_IRQHandler(void)
{                                                                   
        if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
        {
                TIM_ClearITPendingBit(TIM7,TIM_IT_Update);//����жϱ�־
                TIM_Cmd(TIM7,DISABLE);//ֹͣ��ʱ��
                SET_TX();;//ֹͣ���գ��л�Ϊ����״̬
                RS485_FrameFlag=1;//��λ֡�������
        }
}











//Modbus������02�������
//�����뿪����
void Modbus_02_Solve(void)
{
        u16 ByteNum;
        u16 i,j,t;
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//��ȡ�Ĵ�������
	     
        if((startRegAddr+RegNum)<100)//�Ĵ�����ַ+�����ڷ�Χ��
        {
					
					      j=RS485_RX_BUFF[3]+(RS485_RX_BUFF[2]<<8);	//��ַ
					
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                ByteNum=RegNum/8;//�ֽ���
                if(RegNum%8) ByteNum+=1;//���λ���������������ֽ���+1
                RS485_TX_BUFF[2]=ByteNum;//����Ҫ��ȡ���ֽ���
							
					      t = 3;
				
				        for(i = startRegAddr,j=RS485_RX_BUFF[3]+RS485_RX_BUFF[5];i<j;i+=8)
				        {
					        RS485_TX_BUFF[t++] = USART1_GetParam8Bits(i);
			         	}
							
								
								
                calCRC=crc16(RS485_TX_BUFF,ByteNum+3);
                RS485_TX_BUFF[ByteNum+4]=calCRC&0xFF;
                RS485_TX_BUFF[ByteNum+3]=(calCRC>>8)&0xFF;
                RS485_SendData(RS485_TX_BUFF,ByteNum+5);
        }
        else//�Ĵ�����ַ+����������Χ
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //�쳣��
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus������01�������
//�����������
void Modbus_01_Solve(void)
{
        u16 ByteNum;
        u16 i,j,t;
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//��ȡ�Ĵ�������
        if((startRegAddr+RegNum)<100)//�Ĵ�����ַ+�����ڷ�Χ��
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                ByteNum=RegNum/8;//�ֽ���
                if(RegNum%8) ByteNum+=1;//���λ���������������ֽ���+1
                RS485_TX_BUFF[2]=ByteNum;//����Ҫ��ȡ���ֽ���
					      t = 3;
				
				        for(i = startRegAddr,j=RS485_RX_BUFF[3]+RS485_RX_BUFF[5];i<j;i+=8)
				        {
					        RS485_TX_BUFF[t++] = USART1_GetParam8Bits(i);
			         	}
                calCRC=crc16(RS485_TX_BUFF,ByteNum+3);
                RS485_TX_BUFF[ByteNum+4]=calCRC&0xFF;
                RS485_TX_BUFF[ByteNum+3]=(calCRC>>8)&0xFF;
                RS485_SendData(RS485_TX_BUFF,ByteNum+5);
        }
        else//�Ĵ�����ַ+����������Χ
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //�쳣��
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus������05�������
//д�������������
void Modbus_05_Solve(void)
{
  u16 i,j;
	if(startRegAddr<1000)//�Ĵ�����ַ�ڷ�Χ��
        {
					
									i = RS485_RX_BUFF[3];
				          j = i>>3;
				          i&=0x0007;					
					

                if((RS485_RX_BUFF[4]==0xFF)||(RS485_RX_BUFF[5]==0xFF)) USART1_SetIO(startRegAddr,1);  
                else USART1_SetIO(startRegAddr,0); 
					
					
		
                
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                RS485_TX_BUFF[2]=RS485_RX_BUFF[2];
                RS485_TX_BUFF[3]=RS485_RX_BUFF[3];
                RS485_TX_BUFF[4]=RS485_RX_BUFF[4];
                RS485_TX_BUFF[5]=RS485_RX_BUFF[5];
                
                calCRC=crc16(RS485_TX_BUFF,6);
                RS485_TX_BUFF[7]=calCRC&0xFF;
                RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
                RS485_SendData(RS485_TX_BUFF,8);
        }
        else//�Ĵ�����ַ������Χ
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //�쳣��
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus������15�������
//д������������
void Modbus_15_Solve(void)
{
        u16 i;
        RegNum=(((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//��ȡ�Ĵ�������
        if((startRegAddr+RegNum)<1000)//�Ĵ�����ַ+�����ڷ�Χ��
        {        
                for(i=0;i<RegNum;i++)
                {

                        if(RS485_RX_BUFF[7+i/8]&0x01) USART1_SetIO(startRegAddr+i,1);  
                        else  USART1_SetIO(startRegAddr+i,0);  							
									
									
                        RS485_RX_BUFF[7+i/8]>>=1;//�ӵ�λ��ʼ
                }
								
								
								
                
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                RS485_TX_BUFF[2]=RS485_RX_BUFF[2];
                RS485_TX_BUFF[3]=RS485_RX_BUFF[3];
                RS485_TX_BUFF[4]=RS485_RX_BUFF[4];
                RS485_TX_BUFF[5]=RS485_RX_BUFF[5];
                calCRC=crc16(RS485_TX_BUFF,6);
                RS485_TX_BUFF[7]=calCRC&0xFF;
                RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
                RS485_SendData(RS485_TX_BUFF,8);
        }
        else//�Ĵ�����ַ+����������Χ
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //�쳣��
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus������03�������
//�����ּĴ���
void Modbus_03_Solve(void)
{
        u16 i,j;
       	
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//��ȡ�Ĵ�������
        if((startRegAddr+RegNum)<1000)//�Ĵ�����ַ+�����ڷ�Χ��
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                RS485_TX_BUFF[2]=RegNum*2;
					
					       j=startRegAddr;
                for(i=0;i<RegNum;i++)
                {

									RS485_TX_BUFF[3+i*2]=USART1_GetBuf(j+i)>>8;
   							  RS485_TX_BUFF[4+i*2]=USART1_GetBuf(j+i)&0x00FF;
									
									
                }

                calCRC=crc16(RS485_TX_BUFF,RegNum*2+3);
                RS485_TX_BUFF[RegNum*2+4]=calCRC&0xFF;
                RS485_TX_BUFF[RegNum*2+3]=(calCRC>>8)&0xFF;
                RS485_SendData(RS485_TX_BUFF,RegNum*2+5);
        }
        else//�Ĵ�����ַ+����������Χ
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //�쳣��
                RS485_SendData(RS485_TX_BUFF,3);
        }
}


//Modbus������03�������
//�����ּĴ���
void Modbus_04_Solve(void)
{
        u16 i,j;
         
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//��ȡ�Ĵ�������
        if((startRegAddr+RegNum)<1000)//�Ĵ�����ַ+�����ڷ�Χ��
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                RS485_TX_BUFF[2]=RegNum*2;
					
					       j=startRegAddr;
                for(i=0;i<RegNum;i++)
                {

									RS485_TX_BUFF[3+i*2]=USART1_GetBuf(j+i)>>8;
   							  RS485_TX_BUFF[4+i*2]=USART1_GetBuf(j+i)&0x00FF;
									
									
                }

                calCRC=crc16(RS485_TX_BUFF,RegNum*2+3);
                RS485_TX_BUFF[RegNum*2+4]=calCRC&0xFF;
                RS485_TX_BUFF[RegNum*2+3]=(calCRC>>8)&0xFF;
                RS485_SendData(RS485_TX_BUFF,RegNum*2+5);
        }
        else//�Ĵ�����ַ+����������Χ
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //�쳣��
                RS485_SendData(RS485_TX_BUFF,3);
        }
}


//Modbus������06�������
//д�������ּĴ���
void Modbus_06_Solve(void)
{
	      u16 i,j;
        u16 SCITemp16;	
	
	
	          j=startRegAddr;
			   SCITemp16=(((u16)RS485_RX_BUFF[4])<<8)+RS485_RX_BUFF[5];
				 USART1_SetBuf(j,SCITemp16);	
        
        RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
        RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
        RS485_TX_BUFF[2]=RS485_RX_BUFF[2];
        RS485_TX_BUFF[3]=RS485_RX_BUFF[3];
        RS485_TX_BUFF[4]=RS485_RX_BUFF[4];
        RS485_TX_BUFF[5]=RS485_RX_BUFF[5];
        
        calCRC=crc16(RS485_TX_BUFF,6);
        RS485_TX_BUFF[7]=calCRC&0xFF;
        RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
        RS485_SendData(RS485_TX_BUFF,8);
}

//Modbus������16�������
//д������ּĴ���
void Modbus_16_Solve(void)
{
        u16 i,j,t;
        u16 SCITemp16;	
	
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//��ȡ�Ĵ�������
        if((startRegAddr+RegNum)<1000)//�Ĵ�����ַ+�����ڷ�Χ��
        {
					
								j=startRegAddr;
					
					
                for(i=0;i<RegNum;i++)
                {
									      t= j+i; 
									    SCITemp16=(((u16)RS485_RX_BUFF[7+i*2])<<8)+RS485_RX_BUFF[8+i*2];
									     
									     USART1_SetBuf(t,SCITemp16);
                  //     USART1_SetBuf(t,SCITemp16);
								   //	PAR_SetData(AMOUNT_BATCH,11);	
									   // PAR_SetData(AMOUNT_BATCH,SCITemp16);	
                }
                
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                RS485_TX_BUFF[2]=RS485_RX_BUFF[2];
                RS485_TX_BUFF[3]=RS485_RX_BUFF[3];
                RS485_TX_BUFF[4]=RS485_RX_BUFF[4];
                RS485_TX_BUFF[5]=RS485_RX_BUFF[5];
                
                calCRC=crc16(RS485_TX_BUFF,6);
                RS485_TX_BUFF[7]=calCRC&0xFF;
                RS485_TX_BUFF[6]=(calCRC>>8)&0xFF;
                RS485_SendData(RS485_TX_BUFF,8);
								
        }
        else//�Ĵ�����ַ+����������Χ
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //�쳣��
                RS485_SendData(RS485_TX_BUFF,3);
        }
}


/////////////////////////////////////////////////////////////////////////////////////
//RS485����������ڴ�����յ�������(������������ѭ������)

void RS485_Service(void)
{
        u16 recCRC;
        if(RS485_FrameFlag==1)
        {
                if(RS485_RX_BUFF[0]==RS485_Addr)//��ַ��ȷ
                {
                        if((RS485_RX_BUFF[1]==01)||(RS485_RX_BUFF[1]==02)||(RS485_RX_BUFF[1]==03)||(RS485_RX_BUFF[1]==04)||(RS485_RX_BUFF[1]==05)||(RS485_RX_BUFF[1]==06)||(RS485_RX_BUFF[1]==15)||(RS485_RX_BUFF[1]==16))//��������ȷ
                  {
                                startRegAddr=(((u16)RS485_RX_BUFF[2])<<8)|RS485_RX_BUFF[3];//��ȡ�Ĵ�����ʼ��ַ
                                if((startRegAddr<2000)&&(RS485_RX_CNT<100))//�Ĵ�����ַ�ڷ�Χ��
                                {
                                       calCRC=crc16(RS485_RX_BUFF,RS485_RX_CNT-2);//�������������ݵ�CRC
                                        recCRC=RS485_RX_BUFF[RS485_RX_CNT-2]<<8|(((u16)RS485_RX_BUFF[RS485_RX_CNT-1]));//���յ���CRC(���ֽ���ǰ�����ֽ��ں�)
//																	        calCRC=1;
//																	        recCRC=1;
																	
                                        if(calCRC==recCRC)//CRCУ����ȷ
                                        {
                                                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                switch(RS485_RX_BUFF[1])//���ݲ�ͬ�Ĺ�������д���
                                                {
                                                        case 2://�����뿪����
                                                        {
                                                                Modbus_02_Solve();
                                                                break;
                                                        }
                                                        
                                                        case 1://�����������
                                                        {
                                                                Modbus_01_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 5://д�������������
                                                        {
                                                                Modbus_05_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 15://д������������
                                                        {
                                                                Modbus_15_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 03: //������Ĵ���
                                                        {
                                                                Modbus_03_Solve();
                                                                break;
                                                        }
                                                        case 04: // 
                                                        {
                                                                Modbus_03_Solve();
                                                                break;
                                                        }																												
																												
                                                                
                                                        case 06: //д�����Ĵ���
                                                        {
                                                                Modbus_06_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 16: //д����Ĵ���
                                                        {
                                                                Modbus_16_Solve();
                                                                break;
                                                        }
																												default:  break;
																												
                                                                                        
                                                }
                                                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        }
                                        else//CRCУ�����
                                        {
                                                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                                                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                                                RS485_TX_BUFF[2]=0x04; //�쳣��
                                                RS485_SendData(RS485_TX_BUFF,3);
                                        }        
                                }
                                else//�Ĵ�����ַ������Χ
                                {
                                        RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                                        RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                                        RS485_TX_BUFF[2]=0x02; //�쳣��
                                        RS485_SendData(RS485_TX_BUFF,3);
                                }                                                
                        }
                        else//���������
                        {
                                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                                RS485_TX_BUFF[2]=0x01; //�쳣��
                                RS485_SendData(RS485_TX_BUFF,3);
                        }
          }
                                
                RS485_FrameFlag=0;//��λ֡������־
                RS485_RX_CNT=0;//���ռ���������
                SET_RX();//��������ģʽ                
        }   

        									   //  PAR_SetData(AMOUNT_BATCH,10);				
}












