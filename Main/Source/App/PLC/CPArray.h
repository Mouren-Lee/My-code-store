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
//给定条件
	const u16* pCurveTable;		//曲线表指针 需要周期为单调减
	u16 TableSize;
	u16 Curve;					//曲线编号
	u16 MinT;					//最小周期对应最高频率
	u16 StartT;					//起动周期
	u16 StopT;					//停车周期
	u16 TimeScale;				//加速时间
	u32 PlusCnt;				//脉冲个数不含寻标长度
//序列
	u16* pArray;				//序列指针
	u16 ArraySize;				//序列长度 初定为1024个2k
//计算用中间变量
	u32 TimeSumTrail;			//时间累计的尾数
	u16 TimeIndex;				//时间累计
	u16 CurT;					//当前计算周期，
	u16 SecT;					//第二速度
	u16 Count;					//有效计算数周期个数
	u16 DiffCount;				//两个频率间的差异脉冲数
	u16 ArrayStep;				//计算状态
//序列索引
	u16 StartIndex;				//起动对应的索引
	u16 TopCnt;					//达到最高频率对应的脉冲个数
	u32 DownCnt;				//开始降速对应脉冲个数
		u32 DingChangCnt;				//定长计数个数
}ST_CPArray;

typedef struct tag_send
{
	ST_CPArray* pArray;			//生成的加速序列缓冲
	ST_CPArray* pArray2;			//生成的减速序列缓冲	
	u32 SendCnt;				//发送个数
	u16 State;					//发达状态
	u16 Index;					//发送索引
	u16 SeekT;					//寻标周期
	u16 Mark;					//寻标
	u16 LostMark;				//失标
	u16 SeekCnt;				//录标脉冲数
	u16 KeepCnt;				//保持脉冲数
	u16 NextT;					//下一个要发送的周期值
	u16 Havencnt;		   //ZXS加 已经跑脉冲数	
		u32 DingChangCnt;				//定长计数个数
		u16 MarkAdvanceNum;		   //ZXS加 寻标前多走脉冲个数
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
