#include "LCDPLC.h"
#include "CPArray.h"

#ifndef _PLUSOUT_H_
#define _PLUSOUT_H_

void TMR235_Configuration(void);

bool CP0_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT);
//bool CP0_Start(u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 XStep,u16 MaxT,u16 MinT,u16 StopT);
void CP0_Stop(void);
u8 CP0_GetState(void);
void CP0_SetMark(u8 mark);
bool CP0_Keep(u32 PlusCnt,u16 MaxT);
bool CP0_isLostMark(void);
u16 CP0_GetHavenplus(void);
void CP0_StartHaven(void);
u32 Get_CP0();
void CP0_ClearDingChang();

bool CP1_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT);
//bool CP1_Start(u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 XStep,u16 MaxT,u16 MinT,u16 StopT);
void CP1_Stop(void);
u8 CP1_GetState(void);
void CP1_SetMark(u8 mark);
bool CP1_Keep(u32 PlusCnt,u16 MaxT);
bool CP1_isLostMark(void);

bool CP2_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT);
//bool CP1_Start(u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 XStep,u16 MaxT,u16 MinT,u16 StopT);
void CP2_Stop(void);
u8 CP2_GetState(void);
void CP2_SetMark(u8 mark);
bool CP2_Keep(u32 PlusCnt,u16 MaxT);
bool CP2_isLostMark(void);

bool CP3_Start(u16 curve,u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 TimeScale,u16 StartT,u16 MinT,u16 StopT);
//bool CP1_Start(u32 PlusCnt,u16 SeekCnt,u16 KeepCnt,u16 XStep,u16 MaxT,u16 MinT,u16 StopT);
void CP3_Stop(void);
u8 CP3_GetState(void);
void CP3_SetMark(u8 mark);
bool CP3_Keep(u32 PlusCnt,u16 MaxT);
bool CP3_isLostMark(void);


#endif
