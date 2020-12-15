#include "datatype.h"

#ifndef _MODBUS_H_
#define _MODBUS_H_

#define SCI_WAIT 0
#define SCI_RECV 1
#define SCI_LISTEN 2
#define SCI_FRAM 3
#define SCI_CRC 4
#define SCI_SEND_WAIT 5
#define SCI_SEND 6

void CRC16(u8 *buf,u8 len,u8* CRCH,u8* CRCL);

#endif
