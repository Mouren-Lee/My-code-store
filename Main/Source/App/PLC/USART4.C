#include "USART4.h"
#include "CRC.h"

#include "MainWork.h"
#include "IOManage.h"
#include "USART1.h"
#include "PipeData.h"



//#define USART2_BUF_SIZE (USART2_PAR_SIZE*2+10)
//#define USART2_BYTE_SIZE 	USART2_PAR_SIZE*2

//static u8 OVTimer2;									//超时计数
//static u8 SCIState2=0;									//通道状态
//static u8 SCIBuf2[USART2_BUF_SIZE];					//通讯缓冲
//static u8 SCIBufPt2;
//static u8 SendPt2;
//static u16 Parameter2[USART2_PAR_SIZE];
//extern u8 ZhongLiangClear_flag;

//u8 TimeDealy_js=0;



//u32 RS485_Baudrate2=9600;//通讯波特率
//u8 RS485_Parity2=0;//0无校验；1奇校验；2偶校验
//u16 RS485_Frame_Distance2=4;//数据帧最小间隔（ms),超过此时间则认为是下一帧

//u8 RS485_RX_BUFF2[200];//接收缓冲区2048字节
//u16 RS485_RX_CNT2=0;//接收计数器
//u8 RS485_RxFlag2=0;//接收一帧结束标记

//u8 RS485_TX_BUFF2[200];//发送缓冲区
//u16 RS485_TX_CNT2=0;//发送计数器
//u8 RS485_TxFlag2=0;//发送一帧结束标记

/////////////////////////////////////////////////////////////////////////////////////
//主机命令区
//u8   SlaverAddr2=01;    //从机地址
//u8   Fuction2=16;      // 功能码
//u16  StartAddr2=2;    //起始地址
//u16  ValueOrLenth2=5;  //数据or长度
//////////////////////////////////////////////////////////////////////////////////////////
//u8 TX_RX_SET2=0; //发送，接受命令切换。 0 发送模式 1接受模式
//u8 ComErr2=8; //0代表通讯正常
             //1代表CRC错误
			// 2代表功能码错误 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Master寄存器和单片机寄存器的映射关系
//u16   Master_InputIO[100];  //输入开关量寄存器(这里使用的是位带操作)   注意： 这里储存从机返回的数据。    开关量的数据只能是0，1 例如 Master_InputIO[5]=0；Master_InputIO[8]=1；
//u16   Master_OutputIO[100]; //输出开关量寄存器(这里使用的是位带操作)    功能码 05 15

//u16  Master_ReadReg[100]; //只读寄存器----存储从机返回的数据          功能码 03
//u16  Master_WriteReg[100];//写寄存器-------将寄存器中的数据送给从机   功能码 06 16








//static u16 SCITemp16;
//static u8* const ParaByte = (u8*)Parameter;
//static u8 CRCHi,CRCLo;
//static u8 Address = 1;

//static u16 TxDelay=0;


//u16 USART1_GetBuf(u8 index)
//{
//	if(index>=USART1_PAR_SIZE)
//		return 0;
//	return Parameter[index];
//}

//void USART1_SetBuf(u8 index,u16 value)
//{
//	if(index<USART1_PAR_SIZE)		
//		Parameter[index] = value;
//}

//u8 USART1_GetIO(u8 index)
//{
//	u8 byte;
//	byte = index>>3;
//	if(byte>=USART1_BYTE_SIZE)
//		return FALSE;	
//	byte = ParaByte[byte];
//	if(byte&BitMask[index&0x07])
//		return TRUE;
//	return FALSE;
//}

//void USART1_SetIO(u8 index,u8 value)
//{
//	u8 byte;
//	byte = index>>3;
//	if(byte>=(USART1_PAR_SIZE<<1))
//		return;	
//	if(value)
//		ParaByte[byte]|=BitMask[index&0x07];
//	else
//		ParaByte[byte]&=(~BitMask[index&0x07]);
//}

//u8 USART1_GetParam8Bits(u8 index)
//{
//	u8 byte,state,i,mask;
//	u8 tmp = 0;

//	for(byte = index>>3,index&=0x07,i=0;byte<(USART1_PAR_SIZE<<1);byte++)
//	{
//		state = ParaByte[byte];
//		mask = BitMask[index];

//		for(;mask!=0;mask<<=1)
//		{
//			tmp = tmp>>1;
//			if(state&mask)
//				tmp|=BIT7;
//			if(++i>=8)
//				return tmp;
//		}
//		index = 0;
//	}
//	return tmp;
//}


void USART4_Configuration()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;	
	USART_InitStructure.USART_BaudRate            = 19200  ;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;//USART_Parity_No;///USART_Parity_Even ;  USART_Parity_No
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);
	
	
	      USART_ClearITPendingBit(UART4,USART_IT_RXNE);
        USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);//使能串口2接收中断
        
        NVIC_InitStructure.NVIC_IRQChannel=UART4_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority=5;
        NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        USART_Cmd(UART4,ENABLE);//使能串口2
	
	
        SET_TX4();//默认为发送模式
	
	
	
	
	
 
}



/////////////////////////////////////////////////////////////////////////////////////
void UART4_IRQHandler(void)//串口2中断服务程序
{
	   
        u8 res;
        u8 err;
	 
//        if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
//        {
//                if(USART_GetFlagStatus(USART2,USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE)) err=1;//检测到噪音、帧错误或校验错误
//                else err=0;
//                res=USART_ReceiveData(USART2); //读接收到的字节，同时相关标志自动清除
//                
//                if((RS485_RX_CNT2<2047)&&(err==0))
//                {
//                        RS485_RX_BUFF2[RS485_RX_CNT2]=res;
//                        RS485_RX_CNT2++;
//                        TimeDealy_js=0;
// 
//                }
//        }
}




//void USART1_Init()
//{
//	u8 i;
//	for(i=0;i<USART1_PAR_SIZE;i++)
//		Parameter[i]= 0;
//	SET_RX();									//置为接收状态
//}

//void USART1_Init(void)
//{
//	u16 i;
//	for(i=0;i<USART1_PAR_SIZE;i++)
//		Parameter[i] = 0;
//	USART1_SetIO(USART1_POWERON,1);
//}



//void USART1_SetAddress(u8 value)
//{
//	if(value!=0)
//		Address	 = value;
//}

//void USART1_ChkOVtime()
//{
//	if(OVTimer2<USART2_OVTIME2)
//		OVTimer2++;
//	else
//	{
//		SCIState2 = SCI_WAIT;
//		SET_RX2();
//		OVTimer2 = 0;
//	}
//}


//----------------------------------------------------------------

//void USART_Master(u8 Addr, u8 DataStart)
//{

//  if(SCIState2 == 0)   //主机空闲
//	   { 


//			 
//		 }
//	





//}


//////////////////////////////////////////////////////////////////////////////
//发送n个字节数据
//buff:发送区首地址
//len：发送的字节数
void RS485_SendData4(u8 *buff,u8 len)
{ 
        SET_TX4();//切换为发送模式
        while(len--)
        {
                while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//等待发送区为空
                USART_SendData(USART2,*(buff++));
        }
        while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);//等待发送完成
		   // TX_RX_SET2=1; //发送命令完成，定时器T4处理接收到的数据
          SET_RX4();   //切换为接收模式
			//	RS485_RxFlag4=1;
}


//-------------------------------------------------------------------------
//void Master_OVER(void)
//{

//	TimeDealy_js++;
//	if(TimeDealy_js>50)
//	{
//		if(RS485_RxFlag2==1)
//		RS485_RxFlag2=2;//置位帧结束标记
//		TimeDealy_js=0;
//	}



//}

////-------------------------------------------------------------------------
//void Master_Clear(void)
//{
//	u16 calCRC;	
//	
//		RS485_TX_BUFF2[0] = 0x01;
//    RS485_TX_BUFF2[1] = 0x06;    //modbus 指令码01
//    RS485_TX_BUFF2[2] = 0x00;  
//    RS485_TX_BUFF2[3] = 0x24; 
//    RS485_TX_BUFF2[4] = 0x00;
//    RS485_TX_BUFF2[5] = 0x00;
//    calCRC=crc16(RS485_TX_BUFF2,6);
//    RS485_TX_BUFF2[6]=(calCRC>>8)&0xFF;
//    RS485_TX_BUFF2[7]=(calCRC)&0xFF;
//	  RS485_SendData2(RS485_TX_BUFF2,8);	
//	
//	
//}










////Modbus功能码01处理程序 ///////////////////////////////////////////////////////////程序已验证OK
////读输出开关量
//void Master_01_Slove( u8 board_adr,u16 start_address, u16 lenth )
//{
//	u16 calCRC;
//	  RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = READ_COIL;    //modbus 指令码01
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(lenth);
//    RS485_TX_BUFF2[5] = LOW(lenth);
//    calCRC=crc16(RS485_TX_BUFF2,6);
//    RS485_TX_BUFF2[6]=(calCRC>>8)&0xFF;
//    RS485_TX_BUFF2[7]=(calCRC)&0xFF;
//	  RS485_SendData2(RS485_TX_BUFF2,8);	
//}

////Modbus功能码02处理程序/////////////////////////////////////////////////////程序已验证OK -----必须先配置PE4 PE3 PE2 PA0 初始化按键才可以OK    KEY_Init();
////读输入开关量
//void Master_02_Slove(u8 board_adr,u16 start_address, u16 lenth)
//{	
//	u16 calCRC;
//	  RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = READ_DI;    //modbus 指令码02
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(lenth);
//    RS485_TX_BUFF2[5] = LOW(lenth);
//    calCRC=crc16(RS485_TX_BUFF2,6);
//    RS485_TX_BUFF2[6]=(calCRC>>8)&0xFF;
//    RS485_TX_BUFF2[7]=(calCRC)&0xFF;
//	  RS485_SendData2(RS485_TX_BUFF2,8);
//}

////Modbus功能码03处理程序///////////////////////////////////////////////////////////////////////////////////////
////读保持寄存器
//void Master_03_Slove( u8 board_adr,u16 start_address,u16 lenth )
//{ 
//	u16 calCRC;
//    RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = READ_HLD_REG;    //modbus 指令码03
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(lenth);
//    RS485_TX_BUFF2[5] = LOW(lenth);
//    calCRC=crc16(RS485_TX_BUFF2,6);
//    RS485_TX_BUFF2[6]=(calCRC>>8)&0xFF;
//    RS485_TX_BUFF2[7]=(calCRC)&0xFF;
//	RS485_SendData2(RS485_TX_BUFF2,8);
//}
////Modbus功能码04处理程序/////////////////////////////////////////////////////////////////////////////////////// 未使用
////读输入寄存器
//void Master_04_Slove( u8 board_adr,u16 start_address,u16 lenth )
//{ 
//	u16 calCRC;
//    RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = READ_AI;    //modbus 指令码04
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(lenth);
//    RS485_TX_BUFF2[5] = LOW(lenth);
//    calCRC=crc16(RS485_TX_BUFF2,6);
//    RS485_TX_BUFF2[6]=(calCRC>>8)&0xFF;
//    RS485_TX_BUFF2[7]=(calCRC)&0xFF;
//	RS485_SendData2(RS485_TX_BUFF2,8);
//}

////Modbus功能码05处理程序   ///////////////////////////////////////////////////////程序已验证OK
////写单个输出开关量 输出只能是0XFF00->1 ON; 0X0000->0 OFF;
//void Master_05_Slove(u8 board_adr,u16 start_address, u16 value)
//{
//	
//	u16 i;
//	u16 calCRC;
//	if(value==1)
//	{
//	if(Master_OutputIO[start_address]) i=0xff00;
//	else  i=0x0000;
//	  RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = SET_COIL;   //modbus 指令码05
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(i);
//    RS485_TX_BUFF2[5] = LOW(i);
//    calCRC=crc16(RS485_TX_BUFF2,6);
//	RS485_TX_BUFF2[6]=(calCRC>>8)&0xFF;
//    RS485_TX_BUFF2[7]=(calCRC)&0xFF;
//	RS485_SendData2(RS485_TX_BUFF2,8);
//	}

//}


////Modbus功能码06处理程序   //////////////////////////////////////////////////////////////////////////////////
////写单个保持寄存器
//void Master_06_Slove(u8 board_adr,u16 start_address, u16 value)
//{
//	u16 calCRC;
//	if(value==1)
//	{
//	  RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = SET_HLD_REG;   //modbus 指令码06
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(Master_WriteReg[start_address]);
//    RS485_TX_BUFF2[5] = LOW(Master_WriteReg[start_address]);
//    calCRC=crc16(RS485_TX_BUFF2,6);
//	  RS485_TX_BUFF2[6]=(calCRC>>8)&0xFF;
//    RS485_TX_BUFF2[7]=(calCRC)&0xFF;
//	  RS485_SendData2(RS485_TX_BUFF2,8);
//	}		
//	
//}
////Modbus功能码15处理程序   //////////////////////////////////////////////////////程序已验证OK
////写多个输出开关量
//void Master_15_Slove(u8 board_adr,u16 start_address, u16 lenth) 
//{	
//		u16 calCRC;
//	    u16 ByteNum;
//        u16 i;
//        if((start_address+lenth)<100)//寄存器地址+数量在范围内
//        {

//                ByteNum=lenth/8;//字节数
//                if(lenth%8) ByteNum+=1;//如果位数还有余数，则字节数+1
//                for(i=0;i<lenth;i++)
//                {
//                         if(i%8==0) RS485_TX_BUFF2[7+i/8]=0x00;
//						             RS485_TX_BUFF2[7+i/8]=RS485_TX_BUFF2[7+i/8]>>1;
//                         if(Master_OutputIO[start_address+i]) RS485_TX_BUFF2[7+i/8]=RS485_TX_BUFF2[7+i/8]|0x80;//低位先发送
//                         if(i==lenth-1)//发送到最后一个位了
//                         {
//                                if(lenth%8) RS485_TX_BUFF2[7+i/8]>>=8-(lenth%8);//如果最后一个字节还有余数，则剩余MSB填充0
//                         }
//                }
//				
//			}	      
//	  RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = WRITE_COIL;   //modbus 指令码15
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(lenth);
//    RS485_TX_BUFF2[5] = LOW(lenth);	
//	  RS485_TX_BUFF2[6] = ByteNum;
//    calCRC=crc16(RS485_TX_BUFF2,7+ByteNum);
//	  RS485_TX_BUFF2[7+ByteNum]=(calCRC>>8)&0xFF; 
//    RS485_TX_BUFF2[8+ByteNum]=(calCRC)&0xFF;
//	  RS485_SendData2(RS485_TX_BUFF2,9+ByteNum);	


//		

//}
////Modbus功能码16处理程序 /////////////////////////////////////////////////////////////////////////////////////////////////已验证程序OK
////写多个保持寄存器
//void Master_16_Slove(u8 board_adr,u16 start_address, u16 lenth) ///
//{
//		u16 calCRC;
//	    u8 i;
//        if((start_address+lenth)<1000)//寄存器地址+数量在范围内
//        {
//                for(i=0;i<lenth;i++)
//                {
//                      RS485_TX_BUFF2[7+i*2]= Master_WriteReg[start_address+i]>>8;  //高字节在前               
//                      RS485_TX_BUFF2[8+i*2]= Master_WriteReg[start_address+i]; //低字节在后
//                }
//		}       //
//	  RS485_TX_BUFF2[0] = board_adr;
//    RS485_TX_BUFF2[1] = WRITE_HLD_REG;   //modbus 指令码16
//    RS485_TX_BUFF2[2] = HI(start_address);  
//    RS485_TX_BUFF2[3] = LOW(start_address); 
//    RS485_TX_BUFF2[4] = HI(lenth);
//    RS485_TX_BUFF2[5] = LOW(lenth);
//	  RS485_TX_BUFF2[6] = 2*lenth;
//    calCRC=crc16(RS485_TX_BUFF2,7+2*lenth);
//	  RS485_TX_BUFF2[7+2*lenth]=(calCRC>>8)&0xFF; 
//    RS485_TX_BUFF2[8+2*lenth]=(calCRC)&0xFF;
//	  RS485_SendData2(RS485_TX_BUFF2,9+2*lenth);
//}











//void Master_Service(u8 SlaverAddr,u8 Fuction,u16 StartAddr,u16 ValueOrLenth)
//{    

//	switch(Fuction)
//	{
//		case 01:
//				Master_01_Slove(SlaverAddr,StartAddr,ValueOrLenth);
//				
//				break;
//		case 02:
//				Master_02_Slove(SlaverAddr,StartAddr,ValueOrLenth);
//				break;
//		case 03:
//				Master_03_Slove(SlaverAddr,StartAddr,ValueOrLenth);
//				break;
//		case 05:
//				Master_05_Slove(SlaverAddr,StartAddr,ValueOrLenth);
//				break;
//		case 06:
//				Master_06_Slove(SlaverAddr,StartAddr,ValueOrLenth);
//				break;
//		case 15:
//				Master_15_Slove(SlaverAddr,StartAddr,ValueOrLenth);
//				break;
//		case 16:
//				Master_16_Slove(SlaverAddr,StartAddr,ValueOrLenth);
//				break;

//	}
//		
//}


//void RS485_TX_Service(void)
//{
//	//Master_Service( SlaverAddr2, Fuction2, StartAddr2, ValueOrLenth2);
//	
//	//Master_Service( 01, 03, 01, 01);
//	Master_03_Slove(01,01,01);
//	
//	
//}




////Modbus功能码01处理程序 ///////////////////////////////////////////////////////////程序已验证OK
////读输出开关量
//void Modbus_01_Solve2(void)   
//{

//		
//	    u16 i;
//        if((StartAddr2+ValueOrLenth2)<100)//寄存器地址+数量在范围内
//        {
//                for(i=0;i<ValueOrLenth2;i++)
//                {
//                       Master_OutputIO[StartAddr2+i]=RS485_RX_BUFF2[3+i/8]&0x01;//低位先发送
//                       RS485_RX_BUFF2[3+i/8]>>=1;
//				}
//				
//				ComErr2=0;
//        }
//		else
//		{
//				ComErr2=1;
//		}	
//		TX_RX_SET2=0; //命令完成
//		
//}

////Modbus功能码02处理程序 ///////////////////////////////////////////////////////////程序已验证OK
////读输入开关量
//void Modbus_02_Solve2(void)   
//{

//		
//	    u16 i;
//        if((StartAddr2+ValueOrLenth2)<100)//寄存器地址+数量在范围内
//        {
//                for(i=0;i<ValueOrLenth2;i++)
//                {
//                       Master_InputIO[StartAddr2+i]=RS485_RX_BUFF2[3+i/8]&0x01;//低位先发送
//                       RS485_RX_BUFF2[3+i/8]>>=1;
//				}
//		
//				ComErr2=0;
//        }
//		else
//		{
//				ComErr2=2;
//		}
//		TX_RX_SET2=0; //命令完成
//}



////Modbus功能码03处理程序///////////////////////////////////////////////////////////////////////////////////////已验证程序OK
////读保持寄存器
//void Modbus_03_Solve2(void)
//{
//        u8 i;
//		u8 RegNum;
//        RegNum= RS485_RX_BUFF2[2]/2;//获取字节数 6
//        if((StartAddr2+RegNum)<1000)//寄存器地址+数量在范围内
//        {
//                for(i=0;i<RegNum;i++)
//                {
//                       Master_ReadReg[StartAddr2+i]= RS485_RX_BUFF2[3+i*2];           /////////高8位
//                       Master_ReadReg[StartAddr2+i]= RS485_RX_BUFF2[4+i*2]+(Master_ReadReg[StartAddr2+i]<<8);// 低8位+高8位
//									     
//									    
//									
//                } 
//		
//				ComErr2=0;
//        }
//		else
//		{
//				ComErr2=3;
//		}
//		TX_RX_SET2=0; //命令完成
//}

////Modbus功能码05处理程序   ///////////////////////////////////////////////////////程序已验证OK
////写单个输出开关量
//void Modbus_05_Solve2(void)
//{
//       u16 i;
//	   i=ValueOrLenth2;
//	   if((i>0&&RS485_RX_BUFF2[4]==0XFF&&RS485_RX_BUFF2[5]==0X00)||(i==0&&RS485_RX_BUFF2[4]==0X00&&RS485_RX_BUFF2[5]==0X00))
//	   {
//			ComErr2=0;
//			
//	   }
//	   else
//	   {
//			ComErr2=5;
//	   }
//	   TX_RX_SET2=0; //命令完成	   
//}

////Modbus功能码06处理程序   //////////////////////////////////////////////////////////////////////////////////已验证程序OK
////写单个保持寄存器
//void Modbus_06_Solve2(void)
//{
//		u16 i; //数据返回校验用    
//		i=(((u16)RS485_RX_BUFF2[4])<<8)|RS485_RX_BUFF2[5];//获取寄存器数量
//        if(i==Master_WriteReg[StartAddr2])
//		{
//			ComErr2=0;
//		}
//		else
//		{
//			ComErr2=6;
//		}
//		TX_RX_SET2=0; //命令完成

//}
////Modbus功能码15处理程序   //////////////////////////////////////////////////////程序已验证OK
////写多个输出开关量
//void Modbus_15_Solve2(void)
//{
//        u16 i;//数据返回校验用
//        i=(((u16)RS485_RX_BUFF2[4])<<8)|RS485_RX_BUFF2[5];//获取寄存器数量
//         if(i==ValueOrLenth2)
//		{
//			ComErr2=0;
//		}
//         else
//		{
//			ComErr2=15;
//		}
//		TX_RX_SET2=0; //命令完成   
//}

////Modbus功能码16处理程序 /////////////////////////////////////////////////////////////////////////////////////////////////已验证程序OK
////写多个保持寄存器
//void Modbus_16_Solve2(void)
//{
//        u16 i;//数据返回校验用
//        i= (((u16)RS485_RX_BUFF2[4])<<8)|((RS485_RX_BUFF2[5]));//获取寄存器数量
//        if(i==ValueOrLenth2)
//		{
//			ComErr2=0;
//		}
//         else
//		{
//			ComErr2=16;
//		}
//		TX_RX_SET2=0; //命令完成           
//}


///////////////////////////////////////////////////////////////////////////////////////
////RS485服务程序，用于处理接收到的数据(请在主函数中循环调用)

//void RS485_RX_Service(void)
//{
//		u16 calCRC;
//        u16 recCRC;
//        if(RS485_RxFlag2==2)
//        {
//                if(RS485_RX_BUFF2[0]==SlaverAddr2)//地址正确
//                {
//                        if((RS485_RX_BUFF2[1]==01)||(RS485_RX_BUFF2[1]==02)||(RS485_RX_BUFF2[1]==03)||(RS485_RX_BUFF2[1]==05)||(RS485_RX_BUFF2[1]==06)||(RS485_RX_BUFF2[1]==15)||(RS485_RX_BUFF2[1]==16))//功能码正确
//					           	{
//                                        calCRC=crc16(RS485_RX_BUFF2,RS485_RX_CNT2-2);//计算所接收数据的CRC
//                                        recCRC=RS485_RX_BUFF2[RS485_RX_CNT2-1]|(((u16)RS485_RX_BUFF2[RS485_RX_CNT2-2])<<8);//接收到的CRC(低字节在前，高字节在后)
//                                        if(calCRC==recCRC)//CRC校验正确
//                                        {
//                                                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                switch(RS485_RX_BUFF2[1])//根据不同的功能码进行处理
//                                                {
//                                                        case 2://读输入开关量
//                                                        {
//                                                                Modbus_02_Solve2();
//                                                                break;
//                                                        }
//                                                        
//                                                        case 1://读输出开关量
//                                                        {
//                                                                Modbus_01_Solve2();
//                                                                break;
//                                                        }
//                                                                
//                                                        case 5://写单个输出开关量
//                                                        {
//                                                                Modbus_05_Solve2();
//                                                                break;
//                                                        }
//                                                                
//                                                        case 15://写多个输出开关量
//                                                        {
//                                                                Modbus_15_Solve2();
//                                                                break;
//                                                        }
//                                                                
//                                                        case 03: //读多个寄存器
//                                                        {																
//                                                                Modbus_03_Solve2();
//                                                                break;
//                                                        }
//                                                                
//                                                        case 06: //写单个寄存器
//                                                        {
//                                                                Modbus_06_Solve2();
//                                                                break;
//                                                        }
//                                                                
//                                                        case 16: //写多个寄存器
//                                                        {
//                                                                Modbus_16_Solve2();															
//                                                                break;
//                                                        }
//                                                                                        
//                                                }
//										                     }
//                                        else//CRC校验错误
//                                        {
//												  ComErr2=14;

//                                        }                                                                                       
//						            }
//                        else//功能码错误
//                        {
//							if((RS485_RX_BUFF2[1]==0x81)||(RS485_RX_BUFF2[1]==0x82)||(RS485_RX_BUFF2[1]==0x83)||(RS485_RX_BUFF2[1]==0x85)||(RS485_RX_BUFF2[1]==0x86)||(RS485_RX_BUFF2[1]==0x8F)||(RS485_RX_BUFF2[1]==0x90))
//							{
//								switch(RS485_RX_BUFF2[2])
//								{
//									case 0x01:
//												ComErr2=11;
//												break;
//									case 0x02:
//												ComErr2=12;
//												break;
//									case 0x03:
//												ComErr2=13;
//												break;
//									case 0x04:
//												ComErr2=14;
//												break;
//									
//								}
//								TX_RX_SET2=0; //命令完成	
//							}
//                        }
//          }
//                                
//                RS485_RxFlag2=0;//复位帧结束标志
//                RS485_RX_CNT2=0;//接收计数器清零
//                //RS485_TX_EN=1;//开启发送模式  
//					
//					      SET_TX2();//开启发送模式  
//				        TX_RX_SET2=0; //命令完成
//        }                
//}





///////////////////////////////////////////////////////////////////////////////////////
//void modbus_rtu(void)
//{	
//	static u8 i=0;
//	static u8 j=0;
//	switch(SCIState2)
//	{
//		case 0:
//				//RS485_TX_Service();
////        TimeDealy_js++;
////		    if(TimeDealy_js>=100)
////				{	

//		     if(ZhongLiangClear_flag==1)
//				 {
//					 Master_Clear();
//				   ZhongLiangClear_flag=0;
//				 }
//				 else
//		      Master_03_Slove(01,0x2A,01);
//		
//		
//		      SCIState2=3;
//					TimeDealy_js=0;	
//		      
//		
//		
//		
////        }
//				break;
//		case 1:	
////				if(TX_RX_SET2) 
////				{
////					TX_RX_SET2=0;
////					SCIState2=2;
////         
////					 RS485_RxFlag2=1;//置位帧结束标记
////				}
//		
//				
//				break;				
//		case 2:	
////        TimeDealy_js++;
////		    if(TimeDealy_js>=50)
////				{
////					TimeDealy_js=0;
////					SCIState2=3;
////				}
//				break;		
//		case 3:
//			
//		     
//				  RS485_RX_Service();
//		    
//		    
//		   					SCIState2=4;;//完成命令更换功能码！
//		
////				if(ComErr2==0) 
////				{
////					SCIState2=4;;//完成命令更换功能码！
////				} 
//				
//				
////				else
////				{
////					i=1;//
////					j++;//一个命令发送3次没有应答切换下一个命令
////					if(j>=2)
////					{
////						j=0;
////						i=3;
////						//ComErr=7;  //通讯超时
////					}
////					
////				}
//				break;
//		case 4: //从机地址++
//				//SlaverAddr++;
//							SCIState2=0;;//完成命令更换功能码！
//				break;
//		case 5://功能码
//				break;				
//			
//	}
//	
//}
	

