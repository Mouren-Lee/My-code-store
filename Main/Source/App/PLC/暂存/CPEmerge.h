#include "datatype.h"
#include "Curve.h"

#ifndef _CP_EMERGE_H_
#define _CP_EMERGE_H_


#ifdef	Smart800_UsingNewCurve

#define CP_WAIT			0
#define CP_START		1
#define CP_ACCELERATE	2
#define CP_HIGH_SPEED	3
#define CP_DEC_COMP		4
#define CP_DECELERATE	5
#define CP_LOW_SPEED	6
#define CP_SEEK_MARK	7
#define CP_KEEP_LEN 	8

#define CP_TIME_SCALE_BIT 11

typedef struct tag_cp
{
	const ST_Curve* pCurve;
	u32 TimeSum;
	u32 TimeSumExp;
	u32 PlusCnt;
	u32 MaxCnt;
	u16 State;
	u16 Mark;
	u16 LostMark;
	u16 TimeScale;
	u16 MaxT;
	u16 MinT;
	u16 NextT;
	u16 UpCnt;
	u16 SeekCnt;
	u16 TopCnt;
	u16 KeepCnt;
	u16 TBufPt;
	u16 TBufT[2400];
	u16 TBufCnt[2400];
	u16 curve_line;
	u32 Havencnt;  
	u32 flast;
	u32 Givencnt;
	u16 duty;
}ST_CPEmerge;


//����Ƿ��ѱ�
u16 CPx_isLostMark(const ST_CPEmerge* pEmerge);
//����Ѱ����
void CPx_SetMark(ST_CPEmerge* pEmerge,u16 mark);
//ȡ�õ�ǰ����״̬
u16 CPx_GetState(ST_CPEmerge* pEmerge);
//ȡ����һ�����������
u16 CPx_GetNextT(ST_CPEmerge* pEmerge);
//�������ͺ㶨Ƶ������
void CPx_Keep(ST_CPEmerge* pEmerge,u32 PlusCnt,u16 MaxT);
//�������巢������
u16 CPx_SetParam(ST_CPEmerge* pEmerge,u32 PlusCnt,u16 TopCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 MaxT,u16 MinT,u16 Crve);
//��ʼ���巢��
void CPx_Start(ST_CPEmerge* pEmerge);
//ֹͣ���巢��
void CPx_Stop(ST_CPEmerge* pEmerge);
//�������巢��
void CPx_Deal(ST_CPEmerge* pEmerge);

#endif

#endif
