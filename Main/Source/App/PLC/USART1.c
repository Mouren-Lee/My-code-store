#include "USART1.h"
#include "CRC.h"
#include "PIPE.h"
#include "MainWork.h"


#define USART1_BUF_SIZE (USART1_PAR_SIZE*2+10)
#define USART1_BYTE_SIZE 	USART1_PAR_SIZE*2

 
 
 
 
 
 u16 Parameter[USART1_PAR_SIZE];

 
static u8* const ParaByte = (u8*)Parameter;

 

 



u32 RS485_Baudrate=9600;//通讯波特率
u8 RS485_Parity=0;//0无校验；1奇校验；2偶校验
u8 RS485_Addr=1;//从机地址
u16 RS485_Frame_Distance=3;//数据帧最小间隔（ms),超过此时间则认为是下一帧
u8 RS485_RX_BUFF[2048];//接收缓冲区2048字节
u16 RS485_RX_CNT=0;//接收计数器
u8 RS485_FrameFlag=0;//帧结束标记
u8 RS485_TX_BUFF[2048];//发送缓冲区
u16 RS485_TX_CNT=0;//发送计数器


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






//定时器7初始化
void Timer7_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        NVIC_InitTypeDef NVIC_InitStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //TIM7时钟使能 

        //TIM7初始化设置
        TIM_TimeBaseStructure.TIM_Period = RS485_Frame_Distance*10; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
        TIM_TimeBaseStructure.TIM_Prescaler =7200; //设置用来作为TIMx时钟频率除数的预分频值 设置计数频率为10kHz
        TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
        TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

        TIM_ITConfig( TIM7, TIM_IT_Update, ENABLE );//TIM7 允许更新中断

        //TIM7中断分组配置
        NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;  //TIM7中断
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级2级
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
        NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器                                                                  
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
        USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使能串口2接收中断
        
        NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
        NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        USART_Cmd(USART1,ENABLE);//使能串口2
        SET_RX();//默认为接收模式
	
       Timer7_Init();//定时器7初始化，用于监视空闲时间
}


//////////////////////////////////////////////////////////////////////////////
//发送n个字节数据
//buff:发送区首地址
//len：发送的字节数
void RS485_SendData(u8 *buff,u8 len)
{ 
        SET_TX();//切换为发送模式
        while(len--)
        {
                while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待发送区为空
                USART_SendData(USART1,*(buff++));
        }
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//等待发送完成
}



/////////////////////////////////////////////////////////////////////////////////////
void USART1_IRQHandler(void)//串口2中断服务程序
{
        u8 res;
        u8 err;
        if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
        {
                if(USART_GetFlagStatus(USART1,USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE)) err=1;//检测到噪音、帧错误或校验错误
                else err=0;
                res=USART_ReceiveData(USART1); //读接收到的字节，同时相关标志自动清除
                
                if((RS485_RX_CNT<2047)&&(err==0))
                {
                        RS485_RX_BUFF[RS485_RX_CNT]=res;
                        RS485_RX_CNT++;
                        
                        TIM_ClearITPendingBit(TIM7,TIM_IT_Update);//清除定时器溢出中断
                        TIM_SetCounter(TIM7,0);//当接收到一个新的字节，将定时器7复位为0，重新计时（相当于喂狗）
                        TIM_Cmd(TIM7,ENABLE);//开始计时
                }
								
							USART_ClearITPendingBit(USART1,USART_IT_RXNE)	;
        }
				
				if(USART_GetITStatus(USART1,USART_IT_ORE)==SET)
				{
					
				  	USART_ClearFlag(USART1,USART_FLAG_ORE)	;
				}
				
}

///////////////////////////////////////////////////////////////////////////////////////
//用定时器7判断接收空闲时间，当空闲时间大于指定时间，认为一帧结束
//定时器7中断服务程序         
void TIM7_IRQHandler(void)
{                                                                   
        if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
        {
                TIM_ClearITPendingBit(TIM7,TIM_IT_Update);//清除中断标志
                TIM_Cmd(TIM7,DISABLE);//停止定时器
                SET_TX();;//停止接收，切换为发送状态
                RS485_FrameFlag=1;//置位帧结束标记
        }
}











//Modbus功能码02处理程序
//读输入开关量
void Modbus_02_Solve(void)
{
        u16 ByteNum;
        u16 i,j,t;
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//获取寄存器数量
	     
        if((startRegAddr+RegNum)<100)//寄存器地址+数量在范围内
        {
					
					      j=RS485_RX_BUFF[3]+(RS485_RX_BUFF[2]<<8);	//地址
					
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                ByteNum=RegNum/8;//字节数
                if(RegNum%8) ByteNum+=1;//如果位数还有余数，则字节数+1
                RS485_TX_BUFF[2]=ByteNum;//返回要读取的字节数
							
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
        else//寄存器地址+数量超出范围
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //异常码
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus功能码01处理程序
//读输出开关量
void Modbus_01_Solve(void)
{
        u16 ByteNum;
        u16 i,j,t;
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//获取寄存器数量
        if((startRegAddr+RegNum)<100)//寄存器地址+数量在范围内
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1];
                ByteNum=RegNum/8;//字节数
                if(RegNum%8) ByteNum+=1;//如果位数还有余数，则字节数+1
                RS485_TX_BUFF[2]=ByteNum;//返回要读取的字节数
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
        else//寄存器地址+数量超出范围
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //异常码
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus功能码05处理程序
//写单个输出开关量
void Modbus_05_Solve(void)
{
  u16 i,j;
	if(startRegAddr<1000)//寄存器地址在范围内
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
        else//寄存器地址超出范围
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //异常码
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus功能码15处理程序
//写多个输出开关量
void Modbus_15_Solve(void)
{
        u16 i;
        RegNum=(((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//获取寄存器数量
        if((startRegAddr+RegNum)<1000)//寄存器地址+数量在范围内
        {        
                for(i=0;i<RegNum;i++)
                {

                        if(RS485_RX_BUFF[7+i/8]&0x01) USART1_SetIO(startRegAddr+i,1);  
                        else  USART1_SetIO(startRegAddr+i,0);  							
									
									
                        RS485_RX_BUFF[7+i/8]>>=1;//从低位开始
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
        else//寄存器地址+数量超出范围
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //异常码
                RS485_SendData(RS485_TX_BUFF,3);
        }
}

//Modbus功能码03处理程序
//读保持寄存器
void Modbus_03_Solve(void)
{
        u16 i,j;
       	
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//获取寄存器数量
        if((startRegAddr+RegNum)<1000)//寄存器地址+数量在范围内
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
        else//寄存器地址+数量超出范围
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //异常码
                RS485_SendData(RS485_TX_BUFF,3);
        }
}


//Modbus功能码03处理程序
//读保持寄存器
void Modbus_04_Solve(void)
{
        u16 i,j;
         
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//获取寄存器数量
        if((startRegAddr+RegNum)<1000)//寄存器地址+数量在范围内
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
        else//寄存器地址+数量超出范围
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //异常码
                RS485_SendData(RS485_TX_BUFF,3);
        }
}


//Modbus功能码06处理程序
//写单个保持寄存器
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

//Modbus功能码16处理程序
//写多个保持寄存器
void Modbus_16_Solve(void)
{
        u16 i,j,t;
        u16 SCITemp16;	
	
        RegNum= (((u16)RS485_RX_BUFF[4])<<8)|RS485_RX_BUFF[5];//获取寄存器数量
        if((startRegAddr+RegNum)<1000)//寄存器地址+数量在范围内
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
        else//寄存器地址+数量超出范围
        {
                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                RS485_TX_BUFF[2]=0x02; //异常码
                RS485_SendData(RS485_TX_BUFF,3);
        }
}


/////////////////////////////////////////////////////////////////////////////////////
//RS485服务程序，用于处理接收到的数据(请在主函数中循环调用)

void RS485_Service(void)
{
        u16 recCRC;
        if(RS485_FrameFlag==1)
        {
                if(RS485_RX_BUFF[0]==RS485_Addr)//地址正确
                {
                        if((RS485_RX_BUFF[1]==01)||(RS485_RX_BUFF[1]==02)||(RS485_RX_BUFF[1]==03)||(RS485_RX_BUFF[1]==04)||(RS485_RX_BUFF[1]==05)||(RS485_RX_BUFF[1]==06)||(RS485_RX_BUFF[1]==15)||(RS485_RX_BUFF[1]==16))//功能码正确
                  {
                                startRegAddr=(((u16)RS485_RX_BUFF[2])<<8)|RS485_RX_BUFF[3];//获取寄存器起始地址
                                if((startRegAddr<2000)&&(RS485_RX_CNT<100))//寄存器地址在范围内
                                {
                                       calCRC=crc16(RS485_RX_BUFF,RS485_RX_CNT-2);//计算所接收数据的CRC
                                        recCRC=RS485_RX_BUFF[RS485_RX_CNT-2]<<8|(((u16)RS485_RX_BUFF[RS485_RX_CNT-1]));//接收到的CRC(低字节在前，高字节在后)
//																	        calCRC=1;
//																	        recCRC=1;
																	
                                        if(calCRC==recCRC)//CRC校验正确
                                        {
                                                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                switch(RS485_RX_BUFF[1])//根据不同的功能码进行处理
                                                {
                                                        case 2://读输入开关量
                                                        {
                                                                Modbus_02_Solve();
                                                                break;
                                                        }
                                                        
                                                        case 1://读输出开关量
                                                        {
                                                                Modbus_01_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 5://写单个输出开关量
                                                        {
                                                                Modbus_05_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 15://写多个输出开关量
                                                        {
                                                                Modbus_15_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 03: //读多个寄存器
                                                        {
                                                                Modbus_03_Solve();
                                                                break;
                                                        }
                                                        case 04: // 
                                                        {
                                                                Modbus_03_Solve();
                                                                break;
                                                        }																												
																												
                                                                
                                                        case 06: //写单个寄存器
                                                        {
                                                                Modbus_06_Solve();
                                                                break;
                                                        }
                                                                
                                                        case 16: //写多个寄存器
                                                        {
                                                                Modbus_16_Solve();
                                                                break;
                                                        }
																												default:  break;
																												
                                                                                        
                                                }
                                                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        }
                                        else//CRC校验错误
                                        {
                                                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                                                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                                                RS485_TX_BUFF[2]=0x04; //异常码
                                                RS485_SendData(RS485_TX_BUFF,3);
                                        }        
                                }
                                else//寄存器地址超出范围
                                {
                                        RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                                        RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                                        RS485_TX_BUFF[2]=0x02; //异常码
                                        RS485_SendData(RS485_TX_BUFF,3);
                                }                                                
                        }
                        else//功能码错误
                        {
                                RS485_TX_BUFF[0]=RS485_RX_BUFF[0];
                                RS485_TX_BUFF[1]=RS485_RX_BUFF[1]|0x80;
                                RS485_TX_BUFF[2]=0x01; //异常码
                                RS485_SendData(RS485_TX_BUFF,3);
                        }
          }
                                
                RS485_FrameFlag=0;//复位帧结束标志
                RS485_RX_CNT=0;//接收计数器清零
                SET_RX();//开启接收模式                
        }   

        									   //  PAR_SetData(AMOUNT_BATCH,10);				
}












