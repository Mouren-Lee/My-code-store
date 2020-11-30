#include "Modbus.h"

//计算CRC16值
//参数：buf为缓冲区指针,len为数据个数，CRCH计算结果的高字节，CRCL计算结果的低字节
//返回值：无
void CRC16(u8 *buf,u8 len,u8* CRCH,u8* CRCL)
{
	u16 CRCRes;
 	u8 pos;
	
	for(CRCRes=0xFFFF;len>0;len--)
  {
      CRCRes=CRCRes^*buf++;
      for(pos=0;pos<8;pos++)
      {
          if(CRCRes&0x0001)
          {
              CRCRes>>=1;
              CRCRes^=0xA001;
           }
           else CRCRes>>=1;
      }
  }
	*CRCL = CRCRes>>8;
	*CRCH = CRCRes&0xFF;
} 
