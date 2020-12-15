				#include "stm32f10x.h"

#ifndef _MY_DATA_TYPE_H
#define _MY_DATA_TYPE_H


#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
#define BIT8 0x0100
#define BIT9 0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000
#define BIT16 0x010000
#define BIT17 0x020000
#define BIT18 0x040000
#define BIT19 0x080000
#define BIT20 0x100000
#define BIT21 0x200000
#define BIT22 0x400000
#define BIT23 0x800000
#define BIT24 0x1000000
#define BIT25 0x2000000
#define BIT26 0x4000000
#define BIT27 0x8000000
#define BIT28 0x10000000
#define BIT29 0x20000000
#define BIT30 0x40000000
#define BIT31 0x80000000

typedef union	{
		u16 Word;
		struct{
			u8 LoByte;
			u8 HiByte;
		}Bytes;
}WBYTE;
//Ð¡¶ËÄ£Ê½
const static u16 BitMask[16] = {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7,
BIT8,BIT9,BIT10,BIT11,BIT12,BIT13,BIT14,BIT15};

#define MyMin(a,b) ((a>b)?(b):(a))

#endif

