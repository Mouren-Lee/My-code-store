#include "datatype.h"

#ifndef _CP_ARRAY_H_
#define _CP_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif 

#define CP_WAIT			0
#define CP_START		1
#define CP_ACCELERATE	2
#define CP_HIGH_SPEED	3
#define CP_DECELERATE	4
#define CP_SEEK_MARK	5
#define CP_KEEP_LEN 	6
#define CP_SEEK_MARK2	7
#define CP_DECELERATE2	8	
	
	
typedef struct tag_array
{
//��������
	const u16* pCurveTable;		//���߱�ָ�� ��Ҫ����Ϊ������
	u16 TableSize;
	u16 Curve;					//���߱��
	u16 MinT;					//��С���ڶ�Ӧ���Ƶ��
	u16 StartT;					//������
	u16 StopT;					//ͣ������
	u16 TimeScale;				//����ʱ��
	u32 PlusCnt;				//�����������Ѱ�곤��
//����
	u16* pArray;				//����ָ��
	u16 ArraySize;				//���г��� ����Ϊ1024��2k
//�������м����
	u32 TimeSumTrail;			//ʱ���ۼƵ�β��
	u16 TimeIndex;				//ʱ���ۼ�
	u16 CurT;					//��ǰ�������ڣ�
	u16 SecT;					//�ڶ��ٶ�
	u16 Count;					//��Ч���������ڸ���
	u16 DiffCount;				//����Ƶ�ʼ�Ĳ���������
	u16 ArrayStep;				//����״̬
//��������
	u16 StartIndex;				//�𶯶�Ӧ������
	u16 TopCnt;					//�ﵽ���Ƶ�ʶ�Ӧ���������
	u32 DownCnt;				//��ʼ���ٶ�Ӧ�������
		u32 DingChangCnt;				//������������
}ST_CPArray;

typedef struct tag_send
{
	ST_CPArray* pArray;			//���ɵļ������л���
	ST_CPArray* pArray2;			//���ɵļ������л���	
	u32 SendCnt;				//���͸���
	u16 State;					//����״̬
	u16 Index;					//��������
	u16 SeekT;					//Ѱ������
	u16 Mark;					//Ѱ��
	u16 LostMark;				//ʧ��
	u16 SeekCnt;				//¼��������
	u16 KeepCnt;				//����������
	u16 NextT;					//��һ��Ҫ���͵�����ֵ
	u16 Havencnt;		   //ZXS�� �Ѿ���������	
		u32 DingChangCnt;				//������������
		u16 MarkAdvanceNum;		   //ZXS�� Ѱ��ǰ�����������
}ST_CPSend;

u16* SetArrayMemory(ST_CPArray* pArray,u16* pPlus,u16 size);
u16 SetArrayParam(ST_CPArray* pArray,u32 PlusCnt,u16 curve,u16 StartT,u16 StopT,u16 MinT,u16 TimeScale);
u16 ArrayRun(ST_CPArray* pArray);
void ArrayInit(ST_CPArray *pArray);
void CPArraySend(ST_CPSend* pSend);
void CPArraySend2(ST_CPSend* pSend);
 
#ifdef __cplusplus
}
#endif

#endif
