#include "Modbus.h"

//����CRC16ֵ
//������bufΪ������ָ��,lenΪ���ݸ�����CRCH�������ĸ��ֽڣ�CRCL�������ĵ��ֽ�
//����ֵ����
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
