#include "MainWork.h"
#include "IOManage.h"
#include "USART1.h"
#include "USART2.h"
#include "USART3.h"
#include "USART4.h"
#include "DACCtrl.h"
#include "VSPIDAC.h"
#include "stm32f10x.h"
#include "PipeData.h"
#include "PlusOut.h"
//#include "GUI.h"
#include "ADC.h"
#include "PIPE.h"
#include "smec98spManage.h"
/*---------------------------------------参数定义---------------------------------------------------------------*/
u8 Led_flag=0;

//-----------------------------------------------------------------------

u16 ii=0;
u8 AD_flag=0;
u32 ADCTEMP1=0;
u32 ADCTEMP2=0;
u8 ADCTEMP1_js=0;
u8 ADCTEMP2_js=0;
	u16 ComTest_js=0;		
//------------------------------------------------------------------------ 
u16 GK1Buf[4];
u16 GK1Space; 
//-------------------------------------------------------------------------

u8 DianjinDiantui_flag=0;       //点进点退按键标志   0松开   1按下
u8 DianjinDiantui_flag1=0;      //点进点退脉冲发送辅助标志  //防止DianjinDiantui_flag=0时  一直CP0_Stop()
u8 DianjinDiantui_flag2=0;       //点进二倍速辅助标志
u16 DianJin_js=0;                 //点进计数
u8 ShouDongXunBiao_flag=0;                  //手动寻标脉冲停止标志
u8 SeekAnJian_flag=0;                     //寻标按键标志   
u8 XunBiaoShengYin_flag=0;  
u8 SeekRun_flag=0; 
u8 SeekRun_flag2=0; 


u8 BaZhen_flag=0;           //脱袋拔针标志
u8 JiXingChuLi_flag=0;     //整本数到后 机型处理标志
u16 BaZhen_js=0;          //拔针延时计数
u16 BaZhen_js2=0;        //拔针延时计数
u16 TuoDai_js=0;            //脱袋延时计数
   
u8 ChangDaiMode_flag=0; 
u16 LastSeekStyle=0;
//--------------------------------------------------------------------------
u8 Run_flag=0;           //运行标志
u8 FeedWait_flag=0;         //送料等待标志

u8 	STOP_IN_flag=0;  //启动按键标志
u8 HenChuiOff_flag=0;      //横吹信号复位延时标志位
u8 ShuChui_flag=0;     //竖吹标志位


u8 TangYa_flag=0;          
u16 TangYa_js=0;   
u8 MainSpeed_flag=0;
u16 ZhuJiXiuZheng_js=0;
u8 HuiSuoBuChan_flag=0;
u8 YuTuiBuChan_flag=0;
u8 START_IN_flag=0;   //启动按键标志
u8 START_INEX_flag=0;   //外接启动
u8 KeyStop_flag=0;        //按键停机标志
u8 FeedFirst_flag=0;        //第一次送料标志
u8 CountPause_flag=0;
u8 KeyStart_flag=0;      //按键启动标志
u8 OtherStart_flag=0;    //其他启动
u8 KongQieStart_flag=0;    //空切启动
u8 YuTui_flag=0;          //预退标志
u8 XianSongHouQie_flag=0;
u8 GaoWeiStop_flag=0;   //高位停车标志位
u8 LostMark_flag=0;   //脱标高位停车标志位
u8 ZanTing_flag=0;   //脱标高位停车标志位
u8 ZanTingZhengLi_flag=0;   //脱标高位停车标志位
u8 DuanLiao_flag=0;   //断料高位停车标志位
u8 DuLiao_flag=0;   //堵料高位停车标志位
u8 ZanTingDelay_flag=0;        //
u8 ZanTingZhengLiWait_flag=0;        //
u8 ShuSong_flag=0;
u8 ZhengChangPuleOut_flag=0;

u8  DianDongRun_flag=0;
u8  DianJinTwoSpeed_flag=0;




u16 PauseTMR;
u16 LostMark=0;           //脱标个数

u8 SelfCheck_flag=0;  //自检按键标志  按下1 松开2
u8 SelfCheckFuZhu_flag=0;   //自检辅助按键  防止一直刷新脉冲

u8 FMQXunBiao_flag=0;   //蜂鸣器标志  1响  0不响   自动寻标脱标
u8 FMQQiDong_flag=0;    //启动
u8 FMQHandXunBiao_flag=0;  //手动寻标
u8 FMQBaoJingNum_flag=0;   //脉冲计数报警
u8 FMQBaoBlocking_flag=0;   //堵料
u8 FMQBaoBreak_flag=0;   //断料
u8 FMQCountStop_flag=0; 
u8 XunBiao_flag=0;  //手动寻标
u8 ZiJian_flag=0;  //自检
u16 XunBiao_js=0;    //寻标计数


u8 PuleOut_flag=0;          //脉冲发送标志

u8 LostMarkCheck_flag=0;       //脉冲发送完自动寻标辅助标志   防止脱标后 LostMark 一直++++
u8 PulseFinishManage=0;       //送料处理完成标志
u8 Hole_flag=0;         //打孔标志
u8 Hole_flag2=0;         //打孔标志

u16 Hole_js1=0;             //打孔延时计数
u16 Hole_js2=0;
u16 ShuCui_js=0;        			//竖吹时间计数


u16 JingDianDealy_js=0;    		//静电延时时间变量


u16 ZhuJiXiuZhengDealy_js=0;    //主机系数修正  延时计数





u16 BlockingTime_js=0;   //堵料时间计数变量   2015-6-26
u16 GaoWeiStopTime_js=0;   //堵料时间计数变量   2015-6-26



u8 MIANJIJOG_flag=0;      //主机点动标志位

u8 jingdian_flag=0;    //静电延时标志位
u8 zhujixishuxiuzh_flag=0;  //暂停模式的标志变量
u8 zhujixishuxiuzhtrue_flag=0;  ////主机修正系数使能


u8 Pause_flag2=0;         //暂停辅助标志
u8 ZhengLiZanTing_flag=0;      //机型选择暂停整理标志
u8 KongQieZhengLi_flag=0;       //机型选择空切整理标志

u8 HuiSuo_flag=0;        //回缩标志

u16 Run_js=0;            //启动延时计数
u8 HeDao_flag=0;          //合刀标志
u8 HeDaoStop_flag=0;        //合刀停止标志
u16 HeDao_js=0;          //合刀计数
u16 HeDao_js1=0;          //合刀关闭计数
u16 Pause_js=0;          //暂停时间计数
u8 FangLiaoTiQian_flag=0;   //放料提前标志
u8 FangLiaoStart_flag=0;   //放料开始标志
u16 FangLiaoTiQian_js=0;      //放料提前计数
u16 CP1Plus;              
u16 DianJinSuDu;         //点进速度
u16 DianJinSuDu2;       //点进二倍速
u8 DianJin_flag=0;            //点进按键标志
u8 DianTui_flag=0;            //点退按键标志
u8 BuShu_flag=0;           //点退变  补数标志   
//------------------------------------------------------------------------
u8 ServoClear_flag=0;
u16 ServoClear_js=0;
u8 SVOClearTime;
//------------------------------------------------------------------------ 
 
/*------------------------------------------------------------------------------------------------------*/
 u16 LastKm,LastSpeed,MainOut;
extern u16  Master_ReadReg[100];
extern u8 JiaMi1_flag;   

//---------------------------------------------------------------
	u16 temp1;
	
//*******************************************************************************************************
//*************************模拟量输出计算****************************************************************
//*******************************************************************************************************	 
//将放料输出改至前台,将主机转速的变化改至前台,
void Analog()
{//模拟量相关参数计算和更新
	u32 tmp;
	u16 midKm,midSpeed;
	midKm =USART1_GetBuf(MAIN_REGULATOR);
	midSpeed = USART1_GetBuf(SPEED_SET);		
 
	if((LastKm!=midKm) ||(LastSpeed!=midSpeed))
	{
		
		MainSpeed_flag=1;
//		MainOut = (midKm*midSpeed)>>6;
//		MainOut = (midKm*midSpeed)/97.65625;
		tmp = (u32)midKm*midSpeed;
		MainOut = (tmp<<5)/3125;
//		MainOut = midKm*midSpeed;
//		MainOut>>=6;		//输出放大4倍，原是右移8位
		if(MainOut>1023)
		{
			MainOut = 1023;		
//			tmp=(1023*3125>>5)/midKm+1;                  //10V时主机速度   2015-6-5
			tmp=99902/midKm+1;                  //10V时主机速度   2015-6-5
			USART1_SetBuf(SPEED_SET,tmp);             //主机速度限制
			midSpeed = tmp;	                             //防止影响到后面的放料模拟和出料模拟
		}
		MainOut=MainOut*4;
		DAC_SetValueAO1(MainOut);
		//VSPI_SetValue(DAC_MAIN,MainOut);       //2015-1-26
	}

   LastSpeed=midSpeed;
  	LastKm = midKm;	
  // DAC_SetValueAO1(2047);
}	
	
	
//**********************************初始化子程序****************************************
void MainWork_InitVar()
{

	
 //Master_Clear();
	
	
}

//**********************************复位子程序****************************************
void SysStop()
{
//		IO_ResetDO(DO_YaLiao);
	CP0_Stop();
//	CP1_Stop();
//	CP2_Stop();
//	
//	IO_SetDO(DO_FEED);
//	IO_SetDO(DO_FEED2);	
	
	USART1_SetIO(USART_START_IN,0);							   //清除起动标志
	USART1_SetIO(USART_STOP_IN,0);							   //清除停止标志
	USART1_SetIO(USART_STOP_F,0);								   //清除强制停止标志

	IO_SetDO32(0);
	
	USART1_SetBuf(WORK_INF,WORK_STOP);	
	
  IO_ResetDO(DO_TWOSTAGE);									//二段速关   2015-1-27
	LastSeekStyle=0;	
  Run_flag=0;           //运行标志
  HuiSuoBuChan_flag=0;
  YuTuiBuChan_flag=0;
  START_IN_flag=0;   //启动按键标志
  START_INEX_flag=0;   //外接启动
  KeyStop_flag=0;        //按键停机标志
  FeedFirst_flag=0;        //第一次送料标志
  KeyStart_flag=0;      //按键启动标志
  OtherStart_flag=0;    //其他启动
  KongQieStart_flag=0;    //空切启动
  YuTui_flag=0;          //预退标志
  XianSongHouQie_flag=0;
  GaoWeiStop_flag=0;   //高位停车标志位
  LostMark_flag=0;   //脱标高位停车标志位
  ZanTing_flag=0;   //脱标高位停车标志位
  ZanTingZhengLi_flag=0;   //脱标高位停车标志位
  DuanLiao_flag=0;   //断料高位停车标志位
  DuLiao_flag=0;   //堵料高位停车标志位
  ZanTingDelay_flag=0;        //
  ZanTingZhengLiWait_flag=0;        //
  ShuSong_flag=0;
  MainSpeed_flag=0;
  ZhuJiXiuZheng_js=0;
  ZhengChangPuleOut_flag=0;
  DianDongRun_flag=0;
  DianJinTwoSpeed_flag=0;
  LostMark=0;           //脱标个数
  SelfCheck_flag=0;  //自检按键标志  按下1 松开2
  SelfCheckFuZhu_flag=0;   //自检辅助按键  防止一直刷新脉冲
  FMQXunBiao_flag=0;   //蜂鸣器标志  1响  0不响   自动寻标脱标
  FMQQiDong_flag=0;    //启动
  FMQHandXunBiao_flag=0;  //手动寻标
  FMQBaoJingNum_flag=0;   //脉冲计数报警
  FMQBaoBlocking_flag=0;   //堵料
  FMQBaoBreak_flag=0;   //断料
  XunBiao_flag=0;  //手动寻标
  ZiJian_flag=0;  //自检
  XunBiao_js=0;    //寻标计数
  BaZhen_flag=0;           //脱袋拔针标志
  JiXingChuLi_flag=0;     //整本数到后 机型处理标志
  BaZhen_js=0;          //拔针延时计数
  BaZhen_js2=0;        //拔针延时计数
  TuoDai_js=0;            //脱袋延时计数
  DianjinDiantui_flag=0;       //点进点退按键标志   0松开   1按下
  DianjinDiantui_flag1=0;      //点进点退脉冲发送辅助标志  //防止DianjinDiantui_flag=0时  一直CP0_Stop()
  DianjinDiantui_flag2=0;       //点进二倍速辅助标志
  DianJin_js=0;                 //点进计数
  ShouDongXunBiao_flag=0;                  //手动寻标脉冲停止标志
  SeekAnJian_flag=0;                     //寻标按键标志   
  XunBiaoShengYin_flag=0;  
  HuiSuo_flag=0;        //回缩标志
  Run_js=0;            //启动延时计数
  HeDao_flag=0;          //合刀标志
//  HeDaoStop_flag=0;        //合刀停止标志
  HeDao_js=0;          //合刀计数
  HeDao_js1=0;          //合刀关闭计数
  Pause_js=0;          //暂停时间计数
  FangLiaoTiQian_flag=0;   //放料提前标志
  FangLiaoStart_flag=0;   //放料开始标志
  FangLiaoTiQian_js=0;      //放料提前计数
  DianJin_flag=0;            //点进按键标志
  DianTui_flag=0;            //点退按键标志
  BuShu_flag=0;           //点退变  补数标志    
  FeedWait_flag=0;         //送料等待标志 
  Pause_flag2=0;         //暂停辅助标志
  ZhengLiZanTing_flag=0;      //机型选择暂停整理标志
  KongQieZhengLi_flag=0;       //机型选择空切整理标志
  PuleOut_flag=0;          //脉冲发送标志
  LostMarkCheck_flag=0;       //脉冲发送完自动寻标辅助标志   防止脱标后 LostMark 一直++++
  PulseFinishManage=0;       //送料处理完成标志
  Hole_flag=0;         //打孔标志
   Hole_flag2=0;	
  Hole_js1=0;             //打孔延时计数
  Hole_js2=0;
  ShuCui_js=0;        			//竖吹时间计数
  JingDianDealy_js=0;    		//静电延时时间变量
  ZhuJiXiuZhengDealy_js=0;    //主机系数修正  延时计数
  BlockingTime_js=0;   //堵料时间计数变量   2015-6-26
  MIANJIJOG_flag=0;      //主机点动标志位
  HenChuiOff_flag=0;      //横吹信号复位延时标志位
  ShuChui_flag=0;     //竖吹标志位
  jingdian_flag=0;    //静电延时标志位
  zhujixishuxiuzh_flag=0;  //暂停模式的标志变量
  zhujixishuxiuzhtrue_flag=0;  ////主机修正系数使能
  STOP_IN_flag=0;  //启动按键标志
  
//	Address_flagA=0;
//	Address_flagB=0;
//	Address_flagJ=0;
//  Heating_flagA=0;
//  Heating_flagB=0;
//  SetWenDu_flag=0; 
//  SetWenDu_flag2=0; 	
	
  SeekRun_flag=0;
	PauseTMR = 0;
	LostMark = 0;

  CountPause_flag=0;
//  JISUAN_JS=0;
//	JISUAN_flag=0;

	BlockingTime_js=0;
	XunBiao_flag=0;
	ZiJian_flag=0;
  ChangDaiMode_flag=0;
  GaoWeiStopTime_js=0;	
	//////////ZXS

 

	//////////ZXS
	USART1_SetIO(USART_ZhuJiAdjust,1);	 //主机修正系数 按钮	
	zhujixishuxiuzhtrue_flag=0;      //主机修正系数使能
	zhujixishuxiuzh_flag=0;
	ZhuJiXiuZhengDealy_js=0;

////-------------------------------------------------	 复位切换到主机点动频率
 DAC_SetValueAO1(MainOut);
//				VSPI_SetValue(DAC_MAIN,MainOut); 
////-------------------------------------------------			   

}
//**********************************脉冲子程序****************************************
void StartCP1()
{
	u16 CP1Plus,CP2Plus,CP2Compensate;
	u16 CP1Seek;
	u32 tmp32;	
	
 	u16 tmp,tmp2,YuTuiMaiChong,SongLiaoMaiChong,HuiSuoMaiChong;
  u16 TEST1,TEST2,TEST3,TEST4,TEST5;
	
	
	if(USART1_GetIO(USART_MaiChongCW)==0)
	IO_ResetDO(DO_CW1);  //电机转动方向控制
	else
	IO_SetDO(DO_CW1);	
	
	
	
	IO_OutPut();
	if(USART1_GetBuf(YUTUI_CNT)>2)
	YuTuiMaiChong=USART1_GetBuf(YUTUI_CNT)-2;    //脉冲发送时  需外加预退长度   执行回缩后第一次脉冲需外加回缩长度
	
	if(USART1_GetBuf(HUISUO_CNT)>2)
	HuiSuoMaiChong=USART1_GetBuf(HUISUO_CNT)-2;
	
	
	SongLiaoMaiChong= USART1_GetBuf(LENGTH_CNT);
	
	CP1Plus=SongLiaoMaiChong;
  CP2Plus=USART1_GetBuf(LENGTH_CNT2);	
  CP2Compensate=USART1_GetBuf(BuChan_CNT);	
	
	
	
	//-------------回缩补偿---------
	if(HuiSuoBuChan_flag)
	{	
	  CP1Plus=CP1Plus+HuiSuoMaiChong;
		HuiSuoBuChan_flag=0;
	}
	//-----------预退补偿-------
	if(YuTuiBuChan_flag)
	{
	  CP1Plus=CP1Plus+YuTuiMaiChong;
		YuTuiBuChan_flag=0;
	}

	
 
	CP1Seek = USART1_GetBuf(MARK_WIDTH_CNT);//xunbiao
 
	if(USART1_GetBuf(SEEK_STYLE)==0)
		CP1Seek = 0;
	
 
//	
//	if(USART1_GetBuf(DuanJiao_CNT))
//	{ 
//		IO_SetDO(DO_PENJIAO);       //2016-4-10 喷胶程序
//	  //CP0_StartHaven();							//计算已经跑
//		if(USART1_GetBuf(YUTUI_CNT)>2)
//			CP1Plus=CP1Plus-2;
//			
//  }
 
//	
//	CP0_Start(USART1_GetBuf(CURVELINE),CP1Plus,CP1Seek,0,USART1_GetBuf(SPEED_STEPCP1),
//	USART1_GetBuf(JOG_Frequency_T),USART1_GetBuf(TOP_FrequencyCP1_T),USART1_GetBuf(XunBiao_Frequency_T));
		
	CP0_Start(USART1_GetBuf(CURVELINE),CP1Plus,CP1Seek,0,USART1_GetBuf(SPEED_STEPCP1),
	USART1_GetBuf(JOG_Frequency_T),USART1_GetBuf(TOP_FrequencyCP1_T),USART1_GetBuf(XunBiao_Frequency_T));	
 
  if(IO_GetDO(DO_K))
	{
	  ZhuJiXiuZheng_js++;
	}
	tmp32=USART1_GetBuf(TOTAL_COUNT2)+65536*USART1_GetBuf(TOTAL_COUNT);
	
	if((USART1_GetIO(USART_BuShu)!=1)&&IO_GetDI(DI_JiShuPause))
	{
		tmp32++;
			USART1_SetBuf(TOTAL_COUNT2,tmp32%65536);	
			USART1_SetBuf(TOTAL_COUNT,tmp32/65536);
			//USART1_SetBuf(TOTAL_COUNT2,1);
		
	}	

	
//	else
//	 USART1_SetBuf(TOTAL_COUNT,0);

	
	
	
	tmp = USART1_GetBuf(GK1_COUNT);
	
	
  if(USART1_GetIO(USART_BuShu)!=1&&IO_GetDI(DI_JiShuPause))	
	USART1_SetBuf(GK1_COUNT,++tmp);	
	
	
	
	
	
	
	if((tmp>(USART1_GetBuf(AMOUNT_BATCH)-USART1_GetBuf(ALARM_CNT)))||FMQCountStop_flag==1)
	{
		 FMQBaoJingNum_flag=1;										//提示音
	}
	else
	{
		 FMQBaoJingNum_flag=0;
	} 
					


}



//-----------------------------------------------------
//*******************************************************************************************************
//***********************************预退子程序**********************************************************
//*******************************************************************************************************
void YuTui()
{
	u16 yutuimaichong;
  if(USART1_GetIO(USART_MaiChongCW)==0)				
	IO_SetDO(DO_CW1);  //电机转动方向控制
	else IO_ResetDO(DO_CW1); 	
	
	yutuimaichong=USART1_GetBuf(YUTUI_CNT);
//	CP0_Start(BACK_GetBuf(PIPE_CURVELINE),yutuimaichong,0,0,BACK_GetBuf(PIPE_SPEED_YUTUI),BACK_GetBuf(PIPE_YUTUI_Start),BACK_GetBuf(PIPE_YUTUI_TOP),BACK_GetBuf(PIPE_YUTUI_Stop));
 	CP0_Start(USART1_GetBuf(CURVELINE),yutuimaichong,0,0,USART1_GetBuf(SPEED_YUTUI),3000,USART1_GetBuf(TOP_YUTUI_T),3000);
	YuTuiBuChan_flag=1;
}

//*******************************************************************************************************
//***********************************回缩子程序**********************************************************
//*******************************************************************************************************
void HuiSuo()
{
	u16 huisuomaichong; 
  if(USART1_GetIO(USART_MaiChongCW)==0)				
	IO_SetDO(DO_CW1);
	else IO_ResetDO(DO_CW1); 
	
	HuiSuo_flag=2;
	huisuomaichong=USART1_GetBuf(HUISUO_CNT);	
	CP0_Start(USART1_GetBuf(CURVELINE),huisuomaichong,0,0,USART1_GetBuf(SPEED_HUISUO),3000,USART1_GetBuf(TOP_HUISUO_T),3000);
  HuiSuoBuChan_flag=1;
}

//**********************************手动子程序****************************************
void ManualWork(TimChg)//手动操作控制
{  
	u16 temp;
	u32 tmp3;
	
	//停止状态下手动
 if(Run_flag==0)
 {	

//----------------------------------------------------------------------------------------------------------
//*********************************** 点进点退按键 **********************************************************
//----------------------------------------------------------------------------------------------------------
	
   if(DianDongRun_flag)
	 {
		 
			 if(USART1_GetIO(USART_JOGF)==0&&DianDongRun_flag==1)
			 {
						CP0_Stop();
						DianJinTwoSpeed_flag=0;
						DianJin_js=0;
		        IO_ResetDO(DO_HENGCHUI);	
   				  DianDongRun_flag=0;
			 }
			 
			 if(USART1_GetIO(USART_JOGB)==0&&DianDongRun_flag==2)
			 {
						CP0_Stop();
						DianJinTwoSpeed_flag=0;
						DianJin_js=0;
		        IO_ResetDO(DO_HENGCHUI);	
   				  DianDongRun_flag=0;
			 }			 
			 
//			 if(USART1_GetIO(USART_JOGF2)==0&&DianDongRun_flag==3)
//			 {
//						CP1_Stop();
//						DianJinTwoSpeed_flag=0;
//						//DianJin_js=0;
//   				  DianDongRun_flag=0;
//			 }
//			 
//			 if(USART1_GetIO(USART_JOGB2)==0&&DianDongRun_flag==4)
//			 {
//						CP1_Stop();
//						DianJinTwoSpeed_flag=0;
//						//DianJin_js=0;
//   				  DianDongRun_flag=0;
//			 }				 
			 
			 
			if(USART1_GetIO(USART_JOGF)==1&&DianJinTwoSpeed_flag==0)      //点进
			{
				  
						if(TimChg&BIT1)
					{
						DianJin_js++;
						if(DianJin_js>2000)
						{
							DianJin_js=0;
							CP0_Stop();
				      CP0_Keep(0x7FFFFFFF,USART1_GetBuf(JOG_Frequency_T)/2);							
							DianJinTwoSpeed_flag=1;
						}
					}	
				
			}				
			
		 
	 }
   else  
   {
		 	if(USART1_GetIO(USART_JOGF)==1&&SeekRun_flag==0&&ZiJian_flag==0)      //点进 寻标自检过程中不能点进
		  {
				 CP0_Keep(0x7FFFFFFF,USART1_GetBuf(JOG_Frequency_T));
				 if(USART1_GetIO(USART_MaiChongCW)==1)				
				 IO_SetDO(DO_CW1);
				 else IO_ResetDO(DO_CW1); 		
				 
				 DianDongRun_flag=1;
			   IO_SetDO(DO_HENGCHUI);           //点进时横吹输出
				 HuiSuoBuChan_flag=0;
    		// MaiChong_EN=1;                 //脉冲灯标志				
			}
		  
    	if(USART1_GetIO(USART_JOGB)==1&&SeekRun_flag==0&&ZiJian_flag==0)     //点退 
			{
				 CP0_Keep(0x7FFFFFFF,USART1_GetBuf(JOG_Frequency_T));		
         if(USART1_GetIO(USART_MaiChongCW)==0)				
				 IO_SetDO(DO_CW1);				 
				 else IO_ResetDO(DO_CW1); 		 
				 
				 DianDongRun_flag=2;	
		     HuiSuoBuChan_flag=0;		
    		 //MaiChong_EN=1;                 //脉冲灯标志				
			}
			
//		 	if(USART1_GetIO(USART_JOGF2)==1&&SeekRun_flag==0)      //点进 寻标自检过程中不能点进
//		  {
//				 CP1_Keep(0x7FFFFFFF,USART1_GetBuf(JOG_SPEED));
//				 DianDongRun_flag=3;
//			   //IO_SetDO(DO_HENGCHUI);           //点进时横吹输出
//				 HuiSuoBuChan_flag=0;
//    		// MaiChong_EN=1;                 //脉冲灯标志				
//			}
//		  
//    	if(USART1_GetIO(USART_JOGB2)==1&&SeekRun_flag==0)     //点退 
//			{
//				 CP1_Keep(0x7FFFFFFF,USART1_GetBuf(JOG_SPEED));				
//				 IO_SetDO(DO_CW2);
//				 DianDongRun_flag=4;	
//		     HuiSuoBuChan_flag=0;		
//    		 //MaiChong_EN=1;                 //脉冲灯标志				
//			}			
			
			
		 
	 }

   //---------------------------------------
//	 }	
 //----------------------------------------------------------------------------------------------------------	
//*********************************** 自检按键 **********************************************************
////----------------------------------------------------------------------------------------------------------
//   if(BACK_GetIO(PIPE_SelfCheck)==1)
//   {
//		  MaiChong_EN=1;                 //脉冲灯标志
//	    SelfCheck_flag=1;
//		 HuiSuoBuChan_flag=0;
//   }
//	 else if(SelfCheck_flag==1)
//	 {
//		  SelfCheck_flag=2;
//	 }
//------------------------------------------------------------------------------------
//***********************************  手动寻标**********************************************************
//------------------------------------------------------------------------------------

	if(USART1_GetIO(USART_SEEK)==1)
	{
		//MaiChong_EN=1;                 //脉冲灯标志
		SeekAnJian_flag=1;                   //手动寻标标志
		HuiSuoBuChan_flag=0;
	}
	else if(SeekAnJian_flag==1)
	{
		SeekAnJian_flag=2;  	
		if(IO_GetDI(DI_GK3))
		{
			XunBiaoShengYin_flag=1;
		}
		if(!IO_GetDI(DI_GK3))
		{
			XunBiaoShengYin_flag=2;
		}
	}

  if(USART1_GetBuf(SEEK_STYLE)==1)	
	{
		if(IO_GetDI(DI_GK3)&&SeekAnJian_flag==2)    //x03下降沿
			{
				  SeekAnJian_flag=0;
					ShouDongXunBiao_flag=1;
				
				if(XunBiaoShengYin_flag!=1)
				{
			    XunBiao_flag=1;
					XunBiaoShengYin_flag=0;
				}
				
				
				
			}
	}
	if(USART1_GetBuf(SEEK_STYLE)==2)	
	{
		if(!IO_GetDI(DI_GK3)&&SeekAnJian_flag==2)
		{
		   	SeekAnJian_flag=0;
				ShouDongXunBiao_flag=1;
			            
			if(XunBiaoShengYin_flag!=2)
				{
			    XunBiao_flag=1;       //寻到标后蜂鸣器响 
					XunBiaoShengYin_flag=0;
				}
		}
  }
			
 if(SeekAnJian_flag==1&&USART1_GetBuf(SEEK_STYLE)!=0)  //寻标 
	{
		  if(USART1_GetIO(USART_MaiChongCW)==1)				
		 IO_SetDO(DO_CW1);
		 else IO_ResetDO(DO_CW1); 
					
		CP0_Keep(0x7FFFFFFF,USART1_GetBuf(XunBiao_Frequency_T));  
    SeekRun_flag=1;	
		 
	}		
	if(ShouDongXunBiao_flag==1)    //x03下降沿
	{
		CP0_Stop();
		SeekRun_flag=0;
		ShouDongXunBiao_flag=0;
	}
	if(SeekAnJian_flag==2&&USART1_GetBuf(SEEK_STYLE)==0)  //寻标过程中改变颜色至空白  停止
	{
		CP0_Stop();
		SeekRun_flag=0;
		SeekAnJian_flag=0;
	}
					
//------------------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&点进点退处理&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&	 
//------------------------------------------------------------------------------------	 


 
 
 
 //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@主机点动处理@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

//	 if(!IO_GetDI(DI_ZhuJiDianDong))		 
//		{
//			USART1_SetBuf(WORK_INF,WORK_DIANDONG);
//		   MIANJIJOG_flag=1;
//		   IO_SetDO(DO_K);	
//			 tmp3=USART1_GetBuf(ZhuJiDianDongSpeed);//主机点动频率  模拟量输出处理
//		  	tmp3=1024*tmp3/60;
//				 tmp3=tmp3*4;
//		  	if(tmp3>4095) tmp3=4095;
//		
//			  DAC_SetValueAO1(tmp3);
//     //  VSPI_SetValue(DAC_MAIN,tmp3);							
//		}
//		else  if(MIANJIJOG_flag==1)
//		{
//		  MIANJIJOG_flag=0;
//		  IO_ResetDO(DO_K);
//	    DAC_SetValueAO1(MainOut);
//		 // VSPI_SetValue(DAC_MAIN,MainOut);	
//      USART1_SetBuf(WORK_INF,WORK_STOP);			
//		}
//		
		
		
	//--------------------------------------------------------------------------------------------	
		
		
	}	
	
	//-------------------------------------------------------------------------------
	//停止状态下手动		
	

	  

}

 /////////////////////////ZXS

 /////////////////////////ZXS
//*************************************************************************

void InAction(u32 TimChg)   //外接输入接口处理
{
	u32 tmp32;
	u16 tmp1,tmp2,tmp3;
		
	
	
	
	if(IO_GetDIChange(DI_GK1)&&(!IO_GetDI(DI_GK1)))		  //检测GK1的个数计算速度
	{
		GK1Buf[0] = GK1Buf[1];
		GK1Buf[1] = GK1Buf[2];
		GK1Buf[2] = GK1Buf[3];
		GK1Buf[3] = GK1Space;
		tmp32=GK1Buf[0]+GK1Buf[1]+GK1Buf[2]+GK1Buf[3];
		GK1Space = tmp32>>2;                           //GK1Space = tmp32/4;
			
		if((GK1Space>40)&&(GK1Buf[0]!=0))
		{
			tmp32=30000+(GK1Space>>1);	//虚假计算156/150*30000=30800
		//准确计算	tmp32=30000+GK1Space>>1;					
			USART1_SetBuf(SPEED_GK1,tmp32/GK1Space);	//USART1_SetBuf(SPEED_GK1,tmp32/GK1Space);
		}
		GK1Space = 0;
	}
		
	if(GK1Space>2000)
		USART1_SetBuf(SPEED_GK1,0);	//USART1_SetBuf(SPEED_GK1,0);	  //把速度置0
				
	if(TimChg&BIT2)					//2^3*0.25ms = 2ms
	{
		if(GK1Space<32767)
			GK1Space++;
	}
	//--------------------------------------------------

//	u16 tmp100,tmp200;	
//----------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------------	

		//--------------------------------------------------
	//----------------------------------------------------------	
	//&&&&&&&&&&&&&&&&&外接起动  X07  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&						

	
		if(!IO_GetDI(DI_START)&&Run_flag==0)  // 启动延时
		{	
			START_INEX_flag=1;
		
			FMQQiDong_flag=1;   //蜂鸣器
			if(TimChg&BIT4)   //0.5 1 2 4 8  
			{
				Run_js++;
				if(Run_js>USART1_GetBuf(QiDong_Dealy))
				{
					 FMQXunBiao_flag=0;
					 FMQQiDong_flag=0;
					 FMQBaoBlocking_flag=0;
					 FMQBaoBreak_flag=0;
					 Run_js=0;
//					if(IO_GetDO(DO_YaLiao))
//					{
//				  	  USART1_SetBuf(WORK_INF,WORK_YaLiao);  
//					}
//					else 
					if(USART1_GetBuf(SYSTEM1_Time)==0)
					{
				  	  //USART1_SetBuf(WORK_INF,WORK_RUN);  
					}					
   			  else if(JiaMi1_flag==1)
					{
				  	   
					}	
 					else
					{
					//-------------------
					 Run_flag=1;
           FeedFirst_flag=1;
					 KeyStart_flag=1;	
           START_INEX_flag=0;					
					//-----------------
            USART1_SetIO(USART_START_IN,1);	
					 //BACK_SetBuf(PIPE_BUSHU,WORK_BUSHU);     //点退 补数按键切换
					 USART1_SetBuf(WORK_INF,WORK_RUN);
					}
				}
			}	
		}	
   else if(START_INEX_flag==1) 
		{
			Run_js=0;
			FMQQiDong_flag=0;
	
	  }	
	
		

//----------------------------------------------------------------------------------------------------------
//*********************************** 外接横吹  X13  **********************************************************
//----------------------------------------------------------------------------------------------------------
//if(IO_GetDIChange(DI_HENGCHUI)&&!IO_GetDI(DI_HENGCHUI)&&(FeedWait_flag==1))
//	{
//			IO_SetDO(DO_HENGCHUI); 
//	}
//----------------------------------------------------------------------------------------------------------
//*********************************** 外接竖吹 X14  **********************************************************
//----------------------------------------------------------------------------------------------------------
 if(IO_GetDIChange(DI_SHUCHUI)&&!IO_GetDI(DI_SHUCHUI)&&Run_flag==1&&(FeedWait_flag==1))
	{
		if(USART1_GetBuf(ShuChui_Time)>0)    //竖吹时间    运行状态
		{
			IO_SetDO(DO_SHUCHUI);
			ShuChui_flag=1;
	  }
	}
 if(IO_GetDIChange(DI_SHUCHUI)&&!IO_GetDI(DI_SHUCHUI))		 
	{
		if(USART1_GetBuf(ShuChui_Time)>0)    //竖吹时间   主机点动状态
		{
			IO_SetDO(DO_SHUCHUI);
			ShuChui_flag=1;
	  }
	}
	//---------------------------------------------------------
	//&&&&&&&&&&&&&&&&&外接点进  X9  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  
	if(IO_GetDIChange(DI_JOGF))		 //
	{
      USART1_SetIO(USART_JOGF,!IO_GetDI(DI_JOGF));
	}

	//----------------------------------------------------------	
	//&&&&&&&&&&&&&&&&&外接点退  X10  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&	X10
	if(IO_GetDIChange(DI_JOGB))		 //
	{
       USART1_SetIO(USART_JOGB,!IO_GetDI(DI_JOGB));
	}
	
	//---------------------------------------------------------
	//&&&&&&&&&&&&&&&&&外接点进  X18  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  
//	if(IO_GetDIChange(DI_JOGF2))		 //
//	{
//      USART1_SetIO(USART_JOGF2,!IO_GetDI(DI_JOGF2));
//	}

//	//----------------------------------------------------------	
//	//&&&&&&&&&&&&&&&&&外接点退  X19  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&	X10
//	if(IO_GetDIChange(DI_JOGB2))		 //
//	{
//       USART1_SetIO(USART_JOGB2,!IO_GetDI(DI_JOGB2));
//	}
	
	
	//----------------------------------------------------------	
	//&&&&&&&&&&&&&&&&&外接停止   X08  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&			
	if(IO_GetDIChange(DI_STOP)&&!IO_GetDI(DI_STOP))	      //
		USART1_SetIO(USART_STOP_IN,1);	
	
	
//----------------------------------------------------------	
//----------------------------------------------------------------------------------------	      
//-----------------------------堵料处理-----------------------------	
//----------------------------------------------------------	
      if(!IO_GetDI(DI_BLOCKING)&&Run_flag==1)			
				{
					
					
				 if((TimChg&BIT0)&&DuLiao_flag==0)
				  {
				  	 BlockingTime_js++;
					   if(BlockingTime_js>USART1_GetBuf(Blocking_Time)*20&&USART1_GetBuf(Blocking_Time))
					   {
					   	  BlockingTime_js=0;				
 
                 GaoWeiStop_flag=1;
							  USART1_SetBuf(WORK_INF,WORK_BLOCKING);  
						 	  FeedWait_flag=0;
							   DuLiao_flag=1;
							   FMQBaoBlocking_flag=1;
									ZanTing_flag=0;
									ZanTingZhengLi_flag=0;
									KongQieZhengLi_flag=0;		
                 if(ZanTingZhengLiWait_flag==1||ZanTingDelay_flag==1)							 
								 {
									 ZanTingZhengLiWait_flag=0;
									 ZanTingDelay_flag=0;
									  Run_flag=0;
				           GaoWeiStop_flag=0;			
				            DuLiao_flag=0;
								 }									 
					   }
				  }					
		
				}		
				else
				{
					 BlockingTime_js=0;
				}			
//----------------------------------------------------------	
//&&&&&&&&&&&&&&&&&外接 X16	断料&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&			
  	
	//if(IO_GetDIChange(DI_BREAK)&&!IO_GetDI(DI_BREAK))		 //
		
	if(IO_GetDI(DI_BREAK)&&USART1_GetIO(USART_BreakSwitch)&&DuanLiao_flag==0)		 
	{	
		USART1_SetBuf(WORK_INF,WORK_BREAK);        //状态显示切换 
		FMQBaoBreak_flag=1;	
		
		//IO_SetDO(DO_YaLiao);
		if(Run_flag==1)
		{
	  	DuanLiao_flag=1;
      GaoWeiStop_flag=1;
			
			 ZanTing_flag=0;
			 ZanTingZhengLi_flag=0;
			 KongQieZhengLi_flag=0;
		}		
	}
	
	//----------------------------------------------------------	
	//&&&&&&&&&&&&&&&&&外接 X05  烫压&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&			
	if(IO_GetDIChange(DI_TangYa)&&!IO_GetDI(DI_TangYa)&&USART1_GetIO(USART_LongOrShort)==0)		 // 烫压下降沿 Y07off  延时  on
	{
		if(Run_flag==1&&IO_GetDO(DO_K))
		{
			IO_ResetDO(DO_K);
			TangYa_flag=1;
		}
	}
	//----------------------------------------------------------	
//	//&&&&&&&&&&&&&&&&&外接主机+ X11  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&						
//	if(IO_GetDIChange(DI_HOST_ADD))		 //
//	{
//		if(!IO_GetDI(DI_HOST_ADD))		 
//			BACK_SetIO(PIPE_START_IN,1);	
//		else
//			BACK_SetIO(PIPE_START_IN,0);	
//	}
	
	
//		//----------------------------------------------------------	
//	//&&&&&&&&&&&&&&&&&外接主机-  X12  &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&						
//	if(IO_GetDIChange(DI_HOST_SUB))		 //
//	{
//		if(!IO_GetDI(DI_HOST_SUB))		 
//			BACK_SetIO(PIPE_START_IN,1);	
//		else
//			BACK_SetIO(PIPE_START_IN,0);	
//	}
//	//----------------------------------------------------------	
//	if(BACK_GetIO(PIPE_CountPause))	
//	{
//		 CountPause_flag=1;
//	}		
//	else
//	{
//		 CountPause_flag=0;
//	}	
	
	
}

//-------------------------------------------


//-----------------------------------------------------------





//**********************************主逻辑子程序****************************************
void MainLogic(u32 TimChg)
{
	u16 tmp,tmp2;
	u32 tmp1,tem32;
  	 	EXTI_InitTypeDef EXTI_InitStructure;
				if(CP0_GetState()==CP_WAIT)
			{
				 IO_ResetDO(DO_CW1);
				 IO_ResetDO(DO_CP1);
				
			}
	    else
			{
				 IO_SetDO(DO_CP1);
				
			}
			
			
//				if(CP1_GetState()==CP_WAIT)
//			{
//				 IO_ResetDO(DO_CW2);
//				  IO_ResetDO(DO_CP2);
//			}	
//	    else
//			{
//				 IO_SetDO(DO_CP2);
//				
//			}			
			

				
		//--------------------------------------
		     tmp=USART1_GetBuf(SEEK_STYLE);
//		
//				if(tmp==1)
//				CP0_SetMark(GPIOB->IDR&GPIO_Pin_5);
//				else if(tmp==2)
//				CP0_SetMark(!(GPIOB->IDR&GPIO_Pin_5));

         if(tmp==1)
				CP0_SetMark(IO_GetDI(DI_GK3));
	      else if(tmp==2)
    		CP0_SetMark(!IO_GetDI(DI_GK3));	
			
			

				
 	if(USART1_GetBuf(SEEK_STYLE)!=LastSeekStyle)
	{

		if(USART1_GetBuf(WORK_INF)==WORK_LOSE_MARK)
		{
			USART1_SetBuf(WORK_INF,WORK_STOP);           //状态显示切换 
			LostMark=0;
		}
//		//--------------------------------------------
//				
//   	if(PAR_GetData(SEEK_STYLE)==1)
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;			
//	  else if(PAR_GetData(SEEK_STYLE)==2)
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//		
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//		

//		
		//--------------------------------------------
		
	 	LastSeekStyle=USART1_GetBuf(SEEK_STYLE);		
	}
	
	 
			//--------------------------------------
//	   if(ServoClear_flag==1)
//		 {
//		  // SVOClearTime = CLEAR1_TMR;
//		  	SVOClearTime = USART1_GetBuf(Clear_Time);
//			  ServoClear_flag=2;				 
//			  IO_SetDO(DO_CLEAR);				//输出低电平	  zxs
//		 }
//			

		//DAC_SetValueAO1(500);
//------------------------------------------------------------------------------------	
//***********************************  运行状态 **********************************************************
//------------------------------------------------------------------------------------
	if(Run_flag==1)
	{
    //------------------------------------------------------------------------------------			
    //*********************************** 第一次送料处理 **********************************************************		
    //------------------------------------------------------------------------------------		
		if(FeedFirst_flag==1)
		{
			 FangLiaoTiQian_flag=0;         //开始提前放料
			 FeedFirst_flag=2;
		   ZhuJiXiuZheng_js=0;
		   zhujixishuxiuzh_flag=1;         //主机修正开始有效			
			
		}
		else if(FeedFirst_flag==2)
		{
			if(FangLiaoTiQian_flag==0)   //提前放料结束
			{
				//------------------------按键第一次启动------------------------------------
				if(KeyStart_flag)
				{

					 if(USART1_GetIO(USART_FEED_CUT)==0)   //先切后送
					 {
						  IO_SetDO(DO_K);  //Y07主输出
						  FeedWait_flag=1;
					    KeyStart_flag=0;
					    FeedFirst_flag=0;						 
					 }
					 else                               //先送后切
					 {
		          switch(XianSongHouQie_flag)	
			       {
					
							case 0:	
	      
                       YuTui_flag=1;
											 XianSongHouQie_flag=1;
							break;
							//---------------------------
							case 1:							
                     if(YuTui_flag==0)
							       {
											 IO_SetDO(DO_HENGCHUI);
											 PuleOut_flag=1;
											 XianSongHouQie_flag=2;
										 }
							break;							
							//---------------------------
							case 2:							
						         if(PuleOut_flag==0)
										 {
													IO_SetDO(DO_K);  //Y07主输出
												//   FeedWait_flag=1;
												KeyStart_flag=0;
												FeedFirst_flag=0;											 
											  XianSongHouQie_flag=0;
											 if(GaoWeiStop_flag==0)
												  FeedWait_flag=1;
										 }
							       
							break;							


							
					    }
						}
				}
				//------------------除按键外其他方式第一次启动-------------------------------
				if(OtherStart_flag)
				{
				   if(USART1_GetIO(USART_FEED_CUT)==0)   //先切后送
					 {
						  IO_SetDO(DO_K);  //Y07主输出
						  FeedWait_flag=1;
					    OtherStart_flag=0; 
					    FeedFirst_flag=0;						 
					 }
					 else                               //先送后切
					 {
		          switch(XianSongHouQie_flag)	
			       {
					
							case 0:	
	      
                       YuTui_flag=1;
											 XianSongHouQie_flag=1;
							break;
							//---------------------------
							case 1:							
                     if(YuTui_flag==0)
							       {
											 IO_SetDO(DO_HENGCHUI);
											 PuleOut_flag=1;
											 XianSongHouQie_flag=2;
										 }
							break;							
							//---------------------------
							case 2:							
						         if(PuleOut_flag==0)
										 {
													IO_SetDO(DO_K);  //Y07主输出
												//   FeedWait_flag=1;
												OtherStart_flag=0;
												FeedFirst_flag=0;											 
											  XianSongHouQie_flag=0;
											 if(GaoWeiStop_flag==0)
												  FeedWait_flag=1;
										 }
							       
							break;							


							
					    }
						}		
				}
				//---------------空切启动------------------------------
				if(KongQieStart_flag)	
				{
					FeedWait_flag=1;
					KongQieStart_flag=0;
				  FeedFirst_flag=0;	
				}	
        //-------------------------				
			}
			
		}
		//--------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------			
    //***********************************  等待送料 **********************************************************		
    //------------------------------------------------------------------------------------			

		if(FeedWait_flag==1)   //等待送料标志
		{
			 if(KeyStop_flag==1)   //运行状态下 停止
			 {
					GaoWeiStop_flag=1;
				  FeedWait_flag=0; 
			 }
			else
			{
				if(IO_GetDIChange(DI_GK1)&&!IO_GetDI(DI_GK1)&&CP0_GetState()==CP_WAIT)    //x01下降沿送料标志
				{
				
				  ZhengChangPuleOut_flag=1;
					
					
				}
		  }
		}
		
    //-----------------------------------------------------------------------------------------------------			
    //***********************************  长袋模式 **********************************************************		
    //------------------------------------------------------------------------------------------------------				
		if(ChangDaiMode_flag==1)
		{
			
				  if(IO_GetDIChange(DI_GK2)&&!IO_GetDI(DI_GK2))
				  {			


						   IO_ResetDO(DO_K);
						   ChangDaiMode_flag=2;
						   FeedWait_flag=0 ;
						   

			    }
			
			
			
		}
		else if (ChangDaiMode_flag==2)		
		{
			if(CP0_GetState()==CP_WAIT)
			{
				ChangDaiMode_flag=3;
				
			}
			
		}
		
		else if (ChangDaiMode_flag==3)
		{
			    GaoWeiStopTime_js++;
					if((GaoWeiStopTime_js>=USART1_GetBuf(GaoWei_Dealy)*20)||USART1_GetBuf(GaoWei_Dealy)==0)			
					{	
						GaoWeiStopTime_js=0;
						ChangDaiMode_flag=0;
						IO_SetDO(DO_K);
						 FeedWait_flag=1;
					}			
			
			
		}

		
//		if((ChangDaiMode_flag==2||ChangDaiMode_flag==3)&&KeyStop_flag==1)
//		{
//        SysStop();
//			  ChangDaiMode_flag=0;
//		}
//		if((ChangDaiMode_flag==1)&&KeyStop_flag==1)
//		{
//      
//			  ChangDaiMode_flag=0;
//		}
	 
    //------------------------------------------------------------------------------------			
    //***********************************  横吹处理 **********************************************************		
    //------------------------------------------------------------------------------------		
		
    if(HenChuiOff_flag==1) //在送料长度达到送料百分比之后关闭 横吹信号
		 {
			 if(Get_CP0()>USART1_GetBuf(LENGTH_CNT)*USART1_GetBuf(HengChuiBFB)/100)
			 {
				  IO_ResetDO(DO_HENGCHUI);           //复位横吹信号
				  HenChuiOff_flag=0;                //横吹信号标志位
			 }
		 }			
		//---------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------			
		//*********************************** 脱标处理 **********************************************************		
		//------------------------------------------------------------------------------------	
			if(LostMarkCheck_flag==1)
			{
				 LostMarkCheck_flag=0;
				  //-------------------------------
					 if(CP0_isLostMark())//脱标
					 {
				        
						 LostMark++;		         //脱标个数
						 FMQXunBiao_flag=1;                     //蜂鸣器响	 
					

							 if((USART1_GetBuf(LOSE_MARK)!=0)&&(LostMark>=USART1_GetBuf(LOSE_MARK)))   //脱标个数超过设定值 停机报警
								{
								
									 LostMark_flag=1; 	  //设置脱标要停标志 		
										USART1_SetBuf(WORK_INF,WORK_LOSE_MARK);	  //脱标状态显示
									 GaoWeiStop_flag=1;
									 FeedWait_flag=0;
                   LostMark=0;	
									
                   ZanTing_flag=0;
									 ZanTingZhengLi_flag=0;
									 KongQieZhengLi_flag=0;
								}						 
						 
					 }					
				   else
					 {

							FMQXunBiao_flag=0;
					
             
							LostMark=0;      //如果寻到标 清除脱标个数   也就是脱标个数不累计   需要连续脱标个数达到设定值才停机
												 
						 
						 
					 }
				
				
			 }

		
				//----------------------------------------------------------------------------------------	
				//--------------------------------------主机系数修正-------------------------------------
				//----------------------------------------------------------------------------------------	
							if(zhujixishuxiuzhtrue_flag==1)      //主机修正系数使能
							{
								 if(USART1_GetIO(USART_ZhuJiAdjust)==1)         
								 {
									 ZhuJiXiuZheng_js=0;
									 zhujixishuxiuzh_flag=1;         //主机修正开始有效		
                   zhujixishuxiuzhtrue_flag=0;    									 
									 if(USART1_GetBuf(SPEED_GK1)!=0)
									 {										 
									  tmp1=USART1_GetBuf(SPEED_SET)*USART1_GetBuf(MAIN_REGULATOR)/USART1_GetBuf(SPEED_GK1);
										 if(tmp1<50)
											 tmp1=50;
									   USART1_SetBuf(MAIN_REGULATOR,tmp1);
										 
										 USART1_SetIO(USART_ZhuJiAdjustTure,1);
										 
									 }		 
								 }
								
							}


       //--------------------------------------------------------------
          
					if(ZhengChangPuleOut_flag==1)	
					{
						IO_SetDO(DO_HENGCHUI); 						
						YuTui_flag=1;
						ZhengChangPuleOut_flag=2;

					}						
					else 	if(ZhengChangPuleOut_flag==2)	
					{
						if(YuTui_flag==0)
						{
						  ZhengChangPuleOut_flag=3;							
						}
					}		
					else 	if(ZhengChangPuleOut_flag==3)	
					{
						
						PuleOut_flag=1;
						ZhengChangPuleOut_flag=0;
					}						
						
	//--------------------------------------------------
				if(YuTui_flag==1)//预退
				{
					if(USART1_GetBuf(YUTUI_CNT))
					{	
					 YuTui();////
					 YuTui_flag=2;
					}
					else
					 YuTui_flag=0;	
				}
			 if(CP0_GetState()==CP_WAIT&&YuTui_flag==2)//预退脉冲发送完成
				{
					IO_ResetDO(DO_CW1);
					YuTui_flag=0;
				}
		
		/////////////////////////////////////////////////////////////////
    //---------------------脉冲发送处理------------------------------------
					
					if(PuleOut_flag==1)//脉冲发送
					{
//						 JISUAN_flag=1;
						 HenChuiOff_flag=1;
  					 IO_SetDO(DO_JD);		
						 jingdian_flag=0;  //清除静电标志位 防止高位后时间过短  脉冲发送后再清除静电信号
						 StartCP1();
						 PuleOut_flag=2;
						if(USART1_GetIO(USART_LongOrShort)==1)
						ChangDaiMode_flag=1;
						
					}
							 //2016-4-10 喷胶程序   当送料长度大于喷胶长度时，复位喷胶输出
//				 if(CP0_GetHavenplus()>=BACK_GetBuf(PIPE_DuanJiao_CNT))
//				  {				
//             IO_ResetDO(DO_PENJIAO);      
//				  }
					if(PuleOut_flag==2&&CP0_GetState()==CP_WAIT)    //脉冲发送完成	
					{	
							//2016-4-10 喷胶程序   当送料完成时，复位喷胶输出，防止喷胶过长异常
//			  	   if(USART1_GetBuf(DuanJiao_CNT)!=0)
//				     {
//					     IO_ResetDO(DO_PENJIAO);       //2017-3-20 喷胶程序
//				     }
						 
						 IO_ResetDO(DO_HENGCHUI); 						 
//						 JISUAN_flag=2;
						FMQBaoJingNum_flag=0; 			
						PuleOut_flag=0;
						PulseFinishManage=1;   //脉冲发完处理
						LostMarkCheck_flag=1;  //脱标检测
					}   		

	 		
//----------------------------------------------------------		
				if(PulseFinishManage==1)	//脉冲发结束处理
				{
					PulseFinishManage=0;
					//---------------------------
//					//打孔处理
//					if(USART1_GetIO(USART_DaKong)==0)
//					{
//					  Hole_flag=1;
//					  Hole_flag2=1;
//					}
					 //----------------------------------
					 //批数处理
						tmp1=USART1_GetBuf(AMOUNT_BATCH); 
					if(USART1_GetBuf(GK1_COUNT)>=USART1_GetBuf(AMOUNT_BATCH)&&USART1_GetBuf(AMOUNT_BATCH)!=0) 
					 {
						 //机型处理
						 JiXingChuLi_flag=1;
//						 BACK_SetBuf(PIPE_GK1_COUNT,0);	                              //计数数清零
//						 BACK_SetBuf(PIPE_BATCH_COUNT2,BACK_GetBuf(PIPE_BATCH_COUNT2)+1);  //批数加1
						 USART1_SetBuf(GK1_COUNT,0);
						 USART1_SetBuf(BATCH_COUNT,USART1_GetBuf(BATCH_COUNT)+1);
						 
					 }
				 }
	  //-------------------------------------------------------
					 if(JiXingChuLi_flag==1)//脱带及机型处理 
					 {		
							JiXingChuLi_flag=0;
						 //--------------------------------
						 
							ShuSong_flag=1; //脱带 

				
						//--------------------机型选择处理--------------------
								switch(USART1_GetBuf(BATCH_MODE))	
								{
										//-----------------------------------
										//不停
										case 0:									      
																															 
										break;
										//----------------------------------
										 //暂停
									 case 1:	
										 
												 GaoWeiStop_flag=1;
												 FeedWait_flag=0 ;
												 ZanTing_flag=1 ;
												  USART1_SetBuf(WORK_INF,WORK_PAUSE);
									 break;
										//----------------------------------						 						
										//停机 
										case 2:		
											
												 GaoWeiStop_flag=1;
												 FeedWait_flag=0 ;
										 
											break;
										//----------------------------------							
										//暂停整理
										
										case 3:									      
												 GaoWeiStop_flag=1;
												 FeedWait_flag=0 ;
												 ZanTingZhengLi_flag=1;
												 USART1_SetBuf(WORK_INF,WORK_ZANTINGZHENGLI);
											break;
										//----------------------------------			
										 //空切整理
									 case 4:	
													FeedWait_flag=0 ;							 
													KongQieZhengLi_flag=1;
													USART1_SetBuf(WORK_INF,WORK_KONGQIEZHENGLI);
									        
											break;	
										//----------------------------------						 
									 }							
					}						
		
		
	}
//------------------------------------------------------------------------------------	
//***********************************  运行状态结束 **********************************************************
//------------------------------------------------------------------------------------					
	//---------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------			
			//***********************************  输送处理 **********************************************************		
			//------------------------------------------------------------------------------------	
					
				if(ShuSong_flag==1)	
					{
//						if(USART1_GetIO(USART_TuoDaiPuTongOrBuJin)==0) //普通脱带
//						{
							if(IO_GetDIChange(DI_GK1)&&!IO_GetDI(DI_GK1)&&BaZhen_flag==0)
							{
								BaZhen_flag=1;      
							}
//						}
//						else
//						{
//							if(IO_GetDIChange(DI_GK1)&&!IO_GetDI(DI_GK1)&&BaZhen_flag==0)
//							{
//								BaZhen_flag=1;      
//							}
//							//-----------------------
//							if(BaZhen_flag==3)   
//							{	
//								
//								TuoDaiMaiChong();
//								BaZhen_flag=4;
//							}
//							if(CP1_GetState()==CP_WAIT&&BaZhen_flag==4)
//							{
//								IO_ResetDO(DO_BaZhen);
//								BaZhen_flag=0;

//								ShuSong_flag=0;
//							}
//						}		
					}						

	
//------------------------------------------------------------------------------------			
//***********************************  暂停整理状态 **********************************************************		
//------------------------------------------------------------------------------------
 if(ZanTingZhengLiWait_flag==1)  //  等待脱袋完成
 {
	    //---------输送完成 正常送料-------
	    if(ShuSong_flag==0)
	    {
				FeedFirst_flag=1;
				OtherStart_flag=1;
				ZanTingZhengLiWait_flag=0;
        USART1_SetBuf(WORK_INF,WORK_RUN);
			}
	 
	    //---------有停止要求，直接停车-------	 
	 
		 if(KeyStop_flag==1)   //暂停整理状态时按停止  直接停
		 {
				USART1_SetBuf(WORK_INF,WORK_STOP);
				ZanTingZhengLiWait_flag=0;
				Run_flag=0;
	 
			 //BACK_SetBuf(PIPE_BUSHU,WORK_DIANTUI);
		 }	 
	 
 }
				

//------------------------------------------------------------------------------------			
//***********************************  空切整理状态 **********************************************************		
//------------------------------------------------------------------------------------
		 if(KongQieZhengLi_flag==1) //  空切回缩
		 {
			 if(IO_GetDIChange(DI_GK1)&&!IO_GetDI(DI_GK1)) // X01 
			 {
					KongQieZhengLi_flag=2;
					HuiSuo_flag=1;
				  FangLiaoStart_flag=0;  //放料停止 
			 }
			 if(KeyStop_flag==1)
			 {
				 GaoWeiStop_flag=1;
				 KongQieZhengLi_flag=0;
			 }
			 
		 }
		 else if(KongQieZhengLi_flag==2)
		 {
			 if(ShuSong_flag==0)
			 {
				 FeedFirst_flag=1;
				 KongQieStart_flag=1;
				 KongQieZhengLi_flag=0;
				  USART1_SetBuf(WORK_INF,WORK_RUN);		 
			 }
			 if(KeyStop_flag==1)
			 {
				 GaoWeiStop_flag=1;
				 KongQieZhengLi_flag=0;		 
			 }	 
			 
		 }
 


//------------------------------------------------------------------------------------			
//***********************************  高位停机过程 **********************************************************		
//------------------------------------------------------------------------------------

	
if(GaoWeiStop_flag==1)
{
  if(IO_GetDIChange(DI_GK1)&&!IO_GetDI(DI_GK1)) // X01  输出二段速
   {
	  GaoWeiStop_flag=2;
		if(HuiSuoBuChan_flag==0)
		{
	    HuiSuo_flag=1;
		}
	
	  tem32=1024*USART1_GetBuf(STWOSPEEDFRE)/60;
		tem32=tem32*4;		
	  if(tem32>4095) tem32=4095;

		 DAC_SetValueAO1(tem32);
   // VSPI_SetValue(DAC_MAIN,tem32);	
		IO_SetDO(DO_TWOSTAGE);	// 二段速
   }
 }
if(GaoWeiStop_flag==2)
{
   if((IO_GetDIChange(DI_GK2)&&!IO_GetDI(DI_GK2))) //  X02  高位
    {
	
			IO_ResetDO(DO_K);									//断开常开继电器K
			FangLiaoStart_flag=0;			
			
			zhujixishuxiuzh_flag=0;             //2016-6-5  主机系数修正标志位
      zhujixishuxiuzhtrue_flag=0;        //主机修正系数使能清零
      //BACK_SetIO(PIPE_ZHUJIXIUZHENG,1);	 //主机修正系数 按钮
			
			USART1_SetIO(USART_ZhuJiAdjust,0);
			ZhuJiXiuZhengDealy_js=0;

	   DAC_SetValueAO1(MainOut);
//			VSPI_SetValue(DAC_MAIN,MainOut);      //主机模拟恢复   2015-1-26
	    IO_ResetDO(DO_TWOSTAGE);				

			PIPE_SaveFlash();             //按停止键保存现有的flash数据			
			
			jingdian_flag=1;             //静电标志位置为1			
			BlockingTime_js=0;
	
			
			
	//		USART1_SetIO(USART_START_IN,0);			//清除起动标志
			USART1_SetIO(USART_STOP_IN,0);			//清除停止标志
			USART1_SetIO(USART_STOP_F,0);				//清除强制停止标志
			
		  STOP_IN_flag=0;		
			//--------------------------------------------
			 if( ChangDaiMode_flag==88)
			 {
				 ChangDaiMode_flag=0;
				 
				 
			 }				 
			
			
			
			//----------------按键停止高位处理--------------------------------------

		   if(KeyStop_flag==1)
       {
				  GaoWeiStop_flag=0; 
				  KeyStop_flag=0; 
				  Run_flag=0; 
				 	USART1_SetIO(USART_START_IN,0);			//清除起动标志
				 	USART1_SetBuf(WORK_INF,WORK_STOP);
				 // BACK_SetBuf(PIPE_BUSHU,WORK_DIANTUI);
			 }
			 
			//----------------暂停停止高位处理--------------------------------------

		   else if(ZanTing_flag==1)
       {
				  GaoWeiStop_flag=0;  
				  ZanTing_flag=0;				 
				  ZanTingDelay_flag=1;
				 
          
			 }		
			//----------------暂停整理停止高位处理--------------------------------------

		   else   if(ZanTingZhengLi_flag==1)
       {
				 GaoWeiStop_flag=0;
				 ZanTingZhengLi_flag=0;
				 ZanTingZhengLiWait_flag=1;
				 
				  
				 
				 
			 }

			//----------------脱标停止高位处理--------------------------------------

		   else  	if(LostMark_flag==1)
       {
				 GaoWeiStop_flag=0;				 
				 LostMark_flag=0;	
				  Run_flag=0; 
				 	USART1_SetIO(USART_START_IN,0);			//清除起动标志
         // BACK_SetBuf(PIPE_BUSHU,WORK_DIANTUI);
				 
			 }		


			//----------------断料停止高位处理--------------------------------------

		   else  if(DuanLiao_flag==1)
       {
				  Run_flag=0;
				  GaoWeiStop_flag=0;			
				  DuanLiao_flag=0;
				 	USART1_SetIO(USART_START_IN,0);			//清除起动标志
				 // BACK_SetBuf(PIPE_BUSHU,WORK_DIANTUI);
			 }					

			//----------------堵料停止高位处理--------------------------------------

		   else  if(DuLiao_flag==1)
       {
				  Run_flag=0;
				  GaoWeiStop_flag=0;			
				  DuLiao_flag=0;
				 	USART1_SetIO(USART_START_IN,0);			//清除起动标志
				  //BACK_SetBuf(PIPE_BUSHU,WORK_DIANTUI);
			 }					
     //-----------------停机机型----------------------------
       else
			 {
				  GaoWeiStop_flag=0; 
				  Run_flag=0; 
				 USART1_SetBuf(WORK_INF,WORK_STOP);		
	        USART1_SetIO(USART_START_IN,0);			//清除起动标志				 
				 // BACK_SetBuf(PIPE_BUSHU,WORK_DIANTUI);
			 }



			
     DuLiao_flag=0;



				

			
			
			//-------------------------------------------------------
    }
 }
 //	//------------------------------------------------------------------------------------
	//&&&&&&&&&&&&&&&&&&&&&&&&&&&高位处理子程序&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&			


 //--------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&回缩处理?&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&		
 if(HuiSuo_flag==1)       //停机状态下  X01后 回缩
	{
    if(USART1_GetBuf(HUISUO_CNT))
		{
		  HuiSuo_flag=2;  //回缩运行过
		  HuiSuo();
		}
		else   HuiSuo_flag=0;  //回缩运行过
	}
 if(CP0_GetState()==CP_WAIT&&HuiSuo_flag==2)
 {
	   HuiSuo_flag=0;	
 } 


//------------------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&蜂鸣器设置&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&	
//------------------------------------------------------------------------------------
	if(FMQXunBiao_flag==0&&FMQQiDong_flag==0&&FMQHandXunBiao_flag==0&&FMQBaoJingNum_flag==0&&FMQBaoBlocking_flag==0&&FMQBaoBreak_flag==0)
	{
		  IO_ResetDO(DO_BEEP);
	}
	
	if(FMQXunBiao_flag==1||FMQQiDong_flag==1||FMQHandXunBiao_flag==1||FMQBaoJingNum_flag==1||FMQBaoBlocking_flag==1||FMQBaoBreak_flag==1)
	{	
	  	IO_SetDO(DO_BEEP);
	}
	
	
	if(STOP_IN_flag==1)        //停止按键按下 1  清掉蜂鸣器
	{
		//IO_ResetDO(DO_BEEP);
		FMQXunBiao_flag=0;
		FMQQiDong_flag=0;
		FMQHandXunBiao_flag=0;
		FMQBaoJingNum_flag=0;
    FMQBaoBlocking_flag=0;
		FMQBaoBreak_flag=0;
	}				
			
	
	
	

}
//***********************************触摸屏按键处理**********************************/
void HMI_Manage(u32 TimChg)	  // 
{

	if(USART1_GetIO(USART_TOTAL_CLR))		
	{
		USART1_SetIO(USART_TOTAL_CLR,0);	
		USART1_SetBuf(TOTAL_COUNT,0);	
		USART1_SetBuf(TOTAL_COUNT2,0);			
	}	
	
	if(USART1_GetIO(USART_CNT_CLR))		
	{
		USART1_SetIO(USART_CNT_CLR,0);	
		USART1_SetBuf(GK1_COUNT,0);	
	}	
	
	if(USART1_GetIO(USART_BATCH_CLR))		
	{
		USART1_SetIO(USART_BATCH_CLR,0);	
		USART1_SetBuf(BATCH_COUNT,0);	
	}	

	
//----------------------------------------------------------------------------------------------------------	
//*********************************** 计数暂停 **********************************************************
//----------------------------------------------------------------------------------------------------------
	if(USART1_GetIO(USART_BuShu)==1||!IO_GetDI(DI_JiShuPause))
	{
		FMQCountStop_flag=1;
		
	}
	else
	{
		FMQCountStop_flag=0;
		
	}			
	
//----------------------------------------------------------------------------------------------------------	
//*********************************** 复位按键 **********************************************************
//----------------------------------------------------------------------------------------------------------
	
	
	if(USART1_GetIO(USART_STOP_F))        //强制停止
	{
		SysStop();
	}
	//------------------------------------
	

	
	//----------------------------------------------
//----------------------------------------------------------------------------------------------------------	
//*********************************** 启动按键 **********************************************************
//----------------------------------------------------------------------------------------------------------

	
		if(USART1_GetIO(USART_START_IN)&&Run_flag==0)  // 启动延时
		{	
			START_IN_flag=1;
		

					 FMQXunBiao_flag=0;
					 FMQQiDong_flag=0;
				  	FMQBaoBlocking_flag=0;
					 FMQBaoBreak_flag=0;
 					
					
//					if(IO_GetDO(DO_YaLiao))
//					{
//				  	  USART1_SetBuf(WORK_INF,WORK_YaLiao);  
//					}
//					else

   			  if(USART1_GetBuf(SYSTEM1_Time)==0)
					{
				  	  //USART1_SetBuf(WORK_INF,WORK_RUN);  
					}
   			  else if(JiaMi1_flag==1)
					{
				  	   
					}					
				 else
				 {

					//-------------------
					 Run_flag=1;
           FeedFirst_flag=1;
					 KeyStart_flag=1;
					  START_IN_flag=0;
					//-----------------


					 USART1_SetBuf(WORK_INF,WORK_RUN);
					
			   }	
		}	
   else if(START_IN_flag==1) 
		{
 
			FMQQiDong_flag=0;
	
	  }	
		//--------------------------------------------------		
		
//----------------------------------------------------------------------------------------------------------
//***********************************  停止按键 **********************************************************
//----------------------------------------------------------------------------------------------------------
 if(USART1_GetIO(USART_STOP_IN)==1&&STOP_IN_flag==0)
	{
		STOP_IN_flag=1;
	  KeyStop_flag=1;
		
		PIPE_SaveFlash();
	  IO_ResetDO(DO_HENGCHUI);

	   USART1_SetIO(USART_STOP_IN,0);	
		
		
		
	}

//------------------------------------------------------------------------------------			
//***********************************  停止状态下按停止按键 **********************************************************		
//------------------------------------------------------------------------------------
 	if(KeyStop_flag==1&&Run_flag==0)   //脱标 后  按停止  
	{
		
		 KeyStop_flag=0;
		 USART1_SetBuf(WORK_INF,WORK_STOP);
		
     USART1_SetIO(USART_STOP_IN,0);					//清除停止标志
			STOP_IN_flag=0;
		
//		IO_ResetDO(DO_BEEP);
		FMQXunBiao_flag=0;
		FMQQiDong_flag=0;
		FMQHandXunBiao_flag=0;
		FMQBaoJingNum_flag=0;
		FMQBaoBlocking_flag=0;
		FMQBaoBreak_flag=0;
  }		
	
	
	

}


//**********************************延时子程序****************************************
void Time_delay(u32 TimChg)	  // 
{

//*********************************手动寻标蜂鸣器发声 延时程序*********************************、
//////////////////////////////////////////////////////////////////
//////////////	手动寻标蜂鸣器发声 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////开始////////////////////////////////////////	
		 if(XunBiao_flag==1)  // 
		  {	
				FMQHandXunBiao_flag=1;
		    if(TimChg&BIT1)   
			  {
				 XunBiao_js++;
				 if(XunBiao_js>200)
				 {
           XunBiao_js=0;					 
					FMQHandXunBiao_flag=0;
					XunBiao_flag=2; 
				 }
			 }
			}
			else if (XunBiao_flag==2)
			{
		    if(TimChg&BIT1)   
			  {
				 XunBiao_js++;
				 if(XunBiao_js>200)
				 {
           XunBiao_js=0;					 
					 FMQHandXunBiao_flag=1;
					 XunBiao_flag=3; 
				 }
			 }					
			}
			else if (XunBiao_flag==3)
			{
		    if(TimChg&BIT1)   
			  {
				 XunBiao_js++;
				 if(XunBiao_js>200)
				 {
            XunBiao_js=0;					 
			    	FMQHandXunBiao_flag=0;
					  XunBiao_flag=0; 
				 }
			  }					
			}	
//////////////////////////////////////////////////////////////////
//////////////	手动寻标蜂鸣器发声 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////结束///////////////////////////////////////		
//--------------------------------------
//---------------- 放料提前延时--------------------------------		
 //--------------------------------------
//   if(FangLiaoTiQian_flag==1)
//	  {		 

//	    IO_SetDO(DO_FEED);
//		  IO_SetDO(DO_FEED2);
//			 //--------------------------------------
//			AdjustFeed = NormalFeed+24;		//清除修正值  点进
//			 if(AdjustFeed>1023)
//			 {
//				   AdjustFeed=1023;
//		   }
//		   if(AdjustFeed<64)
//			 {
//					AdjustFeed=64;
//			 }			 
//			AdjustFeed3 = NormalFeed3+24;		//清除修正值
//			if(AdjustFeed3>1023)
//			{
//			  AdjustFeed3=1023;
//			}
//		  if(AdjustFeed3<64)
//		  {
//			  AdjustFeed3=64;
//		  }			  
//			VSPI_SetValue(DAC_FEED2,AdjustFeed3);	
//	    VSPI_SetValue(DAC_FEED,AdjustFeed);		 
//		  FangLiaoTiQian_flag=2;
//			FangLiaoTiQian_js=0;
//			     //--------------------------------------- 
//	 } 
//  else	if(FangLiaoTiQian_flag==2)
//	{		 
//		if(TimChg&BIT2)   
//		{
//			FangLiaoTiQian_js++;
//		  if( FangLiaoTiQian_js>USART1_GetBuf(FangLiaoTiQian_Time)*5)  
//			 {
//				    IO_ResetDO(DO_FEED);
//				    IO_ResetDO(DO_FEED2);
//            FangLiaoTiQian_js=0;
//						FangLiaoTiQian_flag=0;
//				    FangLiaoStart_flag=1;
//			 }

//		 }			
//  }	

//----------------------------------------------------------			
//主机系数修正延时   在启动之后一段时间  主机修正按钮才弹起有效	
 if(MainSpeed_flag==1)		
	 {
		  MainSpeed_flag=0;
		  ZhuJiXiuZheng_js=0;
		  zhujixishuxiuzh_flag=1;
		  zhujixishuxiuzhtrue_flag=0;
		  USART1_SetIO(USART_ZhuJiAdjust,1);
	  }	
	if(zhujixishuxiuzh_flag==1&&MainSpeed_flag==0)  //
		{
			if(ZhuJiXiuZheng_js>=9)
			{
				zhujixishuxiuzh_flag=0;             //2016-6-5  主机系数修正标志位
        zhujixishuxiuzhtrue_flag=1;      //主机修正系数使能
				USART1_SetIO(USART_ZhuJiAdjust,0);
			}
		}	
//----------------------------------------------------------			
//---------------- 合刀延时--------------------------------
//----------------------------------------------------------			
//		 if(HeDao_flag==1)  // 合刀延时
//		  {	
//		    if(TimChg&BIT4)   
//			  {
//				 HeDao_js++;
//				 if(HeDao_js>USART1_GetBuf(HeDao_Dealy))
//				 {
//             HeDao_js=0;
//						 HeDao_flag=0;
//					  IO_SetDO(DO_FEED);
//				 }
//			  }	
//		 	}	
//			
////----------------------------------------------------------			
////---------------- 合刀停止延时--------------------------------
////----------------------------------------------------------			
//		 if(HeDaoStop_flag==1)  // 合刀延时
//		  {	
//		    if(TimChg&BIT4)   
//			  {
//				  HeDao_js1++;
//				 if(HeDao_js1>USART1_GetBuf(HeDao_Dealy))
//				 {
//             HeDao_js1=0;
//						 HeDaoStop_flag=0;
//					  // IO_ResetDO(DO_HEDAO);
//				 }
//			  }	
//		 	}



//////////////////////////////////////////////////////////////////
//////////////	暂停 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////开始////////////////////////////////////////	
		if(ZanTingDelay_flag==1)    //
		  {	

		    if(TimChg&BIT4)   
			  {
				 Pause_js++;
				 if(Pause_js>USART1_GetBuf(PAUSE_TIME))
				 {
					   USART1_SetBuf(WORK_INF,WORK_RUN);
             Pause_js=0;
						 ZanTingDelay_flag=0;

             FeedFirst_flag=1;
					   OtherStart_flag=1;
					 

  
				 }
			  }
				//--------------------------------
       if(KeyStop_flag==1)
				 {
					 USART1_SetBuf(WORK_INF,WORK_STOP);
					 Pause_js=0;
					 ZanTingDelay_flag=0;
	 
						USART1_SetIO(USART_STOP_IN,0);				//清除停止标志
					  Run_flag=0;
					  //BACK_SetBuf(PIPE_BUSHU,WORK_DIANTUI);

				 }				
		 	}	
//////////////////////////////////////////////////////////////////
//////////////	打孔处理 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////开始////////////////////////////////////////	
			
	//-------------------------------------------------	打孔1处理
		if(Hole_flag==1)  // 打孔延时
		  {	
		    if(TimChg&BIT4)   
			  {
				   Hole_js1++;
				 if(Hole_js1>USART1_GetBuf(HOLE1_DELAY))
				 {
            Hole_js1=0;
						Hole_flag=2;
					 	IO_SetDO(DO_HOLE);
					 // IO_SetDO(DO_CHAOSHENG);//
				 }
			  }	
		 	}	
		if(Hole_flag==2)  // 打孔时间
		  {	
		    if(TimChg&BIT4)   
			  {
				   Hole_js1++;
				 if(Hole_js1>USART1_GetBuf(HOLE1_KEEP))
				 {
            Hole_js1=0;
						Hole_flag=0;
					  IO_ResetDO(DO_HOLE);
					//  IO_ResetDO(DO_CHAOSHENG);
				 }
			  }	
		 	}
	//-------------------------------------------------	打孔2处理
//		if(Hole_flag2==1)  // 打孔延时
//		  {	
//		    if(TimChg&BIT4)   
//			  {
//				   Hole_js2++;
//				 if(Hole_js2>USART1_GetBuf(HOLE2_DELAY))
//				 {
//            Hole_js2=0;
//						Hole_flag2=2;
//					 	IO_SetDO(DO_HOLE2);
//					 // IO_SetDO(DO_CHAOSHENG);//
//				 }
//			  }	
//		 	}	
//		if(Hole_flag2==2)  // 打孔时间
//		  {	
//		    if(TimChg&BIT4)   
//			  {
//				   Hole_js2++;
//				 if(Hole_js2>USART1_GetBuf(HOLE2_KEEP))
//				 {
//            Hole_js2=0;
//						Hole_flag2=0;
//					  IO_ResetDO(DO_HOLE2);
//					//  IO_ResetDO(DO_CHAOSHENG);
//				 }
//			  }	
//		 	}				
//////////////////////////////////////////////////////////////////
//////////////	打孔处理  ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////结束////////////////////////////////////////	
			
			
			//-------------------------------------------------	烫压处理
		if(TangYa_flag==1)  // 打孔延时
		  {	
		    if(TimChg&BIT4)   
			  {
				   TangYa_js++;
				 if(TangYa_js>USART1_GetBuf(TangYa_Dealy))
				 {
            TangYa_js=0;
						TangYa_flag=0;
					 	IO_SetDO(DO_K);
				 }
			  }	
		 	}		
			
			
//////////////////////////////////////////////////////////////////
//////////////	普通脱带处理	////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////开始////////////////////////////////////////	
//-------------------------------------------------脱带处理	
	 if(BaZhen_flag==1)  // 
		  {	
		    if(TimChg&BIT4)   
			  {
				 BaZhen_js++;
				 if(BaZhen_js>USART1_GetBuf(BanZheng_Dealy))
				 {
           BaZhen_js=0;					 
					 BaZhen_flag=2;
				 }
			 }
			}
		if(BaZhen_flag==2)  // 
		  {	
				IO_SetDO(DO_BaZhen);
		    if(TimChg&BIT4)   
			  {
				 BaZhen_js2++;
				 if(BaZhen_js2>USART1_GetBuf(BanZheng_Time))
				 {
           BaZhen_js2=0;					 
					 BaZhen_flag=3;
					// IO_ResetDO(DO_BaZhen);
				 }
			 }
			}
			if(BaZhen_flag==3&&(USART1_GetIO(USART_TuoDaiPuTongOrBuJin)==0))  // 
		  {	
				IO_SetDO(DO_ShuSong);
		    if(TimChg&BIT4)   
			  {
				 TuoDai_js++;
				 if(TuoDai_js>USART1_GetBuf(APART1_Time))
				 {
           TuoDai_js=0;					 
					 BaZhen_flag=0;
					 IO_ResetDO(DO_ShuSong);
					 IO_ResetDO(DO_BaZhen);
					 ShuSong_flag=0;
				 }
			 }
			}
//////////////////////////////////////////////////////////////////
//////////////	普通脱带处理 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////结束////////////////////////////////////////	
			
			
			
//////////////////////////////////////////////////////////////////
//////////////	点进处理 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////开始////////////////////////////////////////		
 if(DianJin_flag==1&&DianjinDiantui_flag2==0) //点进计时  时间到速度翻倍
	{
	 if(TimChg&BIT1)
		{
			DianJin_js++;
			if(DianJin_js>2000)
		  {
				DianJinSuDu2=DianJinSuDu/2;
				DianJin_js=0;
				DianjinDiantui_flag2=1;        //点进二倍速辅助标志
				CP0_Stop();
			}
	  }
  }
	


	
			
//////////////////////////////////////////////////////////////////
//////////////	竖吹处理 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////开始////////////////////////////////////////	
	if(ShuChui_flag==1)  //在竖吹的条件下并延迟 
	{
	 if(TimChg&BIT4)
		{
			ShuCui_js++;
			if(ShuCui_js>USART1_GetBuf(ShuChui_Time))
		  {
				ShuCui_js=0;
				IO_ResetDO(DO_SHUCHUI);
				ShuChui_flag=0;
			}
	  }
  }
//////////////////////////////////////////////////////////////////
//////////////	竖吹处理 ////////////////////////////////////
///////////////2018-8-10/////////////////////////////////////////
/////////////////////结束////////////////////////////////////////		
//------------------------------------------------------------------------------------
	
	
////&&&&&&&&&&&&&&&&&&&&&&&&&&&静电处理子程序&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&		
	if(jingdian_flag==1)
	{
		if(TimChg&BIT4)
		{
	  	JingDianDealy_js++;
		  if(JingDianDealy_js>=USART1_GetBuf(JingDian_Dealy))
		  {
		  	IO_ResetDO(DO_JD);									//断开常开继电器K
		  	jingdian_flag=0;             //静电标志位置为0
		  	JingDianDealy_js=0;
		  }
	  }
	}


//if(JISUAN_flag==1)
//	{
//		if(TimChg&BIT0)
//		{
//	  	JISUAN_JS++;
//	  }
//	}
//	else if(JISUAN_flag==2)
//	{			
//		JISUAN_flag=3;
//	//	BACK_SetBuf(PIPE_jisuan,JISUAN_JS/2);
//		
//			//----------------------------------------------
//						if(USART1_GetIO(USART_SPEED_AUTO))
//						{							
//		          temp32=600*USART1_GetBuf(DUTY)/USART1_GetBuf(SPEED_SET);
//					//		temp=BACK_GetBuf(PIPE_jisuan);
//							temp=JISUAN_JS/2;
//							if(temp32>temp)
//							{
//								if(temp32-temp>100)
//								{
//									if(USART1_GetBuf(AutoAccPar)>250)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)-150) ;
//								}
//								else 	if(temp32-temp>50)
//								{
//									if(USART1_GetBuf(AutoAccPar)>200)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)-100) ;
//								}									
//								else 	if(temp32-temp>25)
//								{
//									if(USART1_GetBuf(AutoAccPar)>150)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)-50) ;
//								}										
//								else 	if(temp32-temp>10)
//								{
//									if(USART1_GetBuf(AutoAccPar)>120)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)-20) ;
//								}									
//								
//							}
//							else
//							{
//								if(temp-temp32>100)
//								{
//										if(USART1_GetBuf(AutoAccPar)<2000)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)+150) ;
//								}
//								else 	if(temp-temp32>50)
//								{
//										if(USART1_GetBuf(AutoAccPar)<2000)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)+100) ;
//								}									
//								else 	if(temp-temp32>20)
//								{
//										if(USART1_GetBuf(AutoAccPar)<2000)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)+50) ;
//								}										
//								else 	if(temp-temp32>10)
//								{
//										if(USART1_GetBuf(AutoAccPar)<2000)
//									USART1_SetBuf(AutoAccPar,USART1_GetBuf(AutoAccPar)+20) ;
//								}								
//							}							
//						}
//						//------------------------------------------------
//	}
//  else if(JISUAN_flag==3)
//	{
//		JISUAN_JS=0;
//		JISUAN_flag=0;
//	}	
	



	
		
}

//**********************************LED运行灯子程序****************************************
void Run_LED(u32 TimChg)	   
{
	
	
						if(TimChg&BIT10)
	        {
						if(Led_flag==0)
						{
								RunLed_on();
							  Led_flag=1;
						}		
            else
						{
								RunLed_off();
							  Led_flag=0;
						}							
						
					}	
	
	
		
}

//**********************************AD子程序****************************************
void AD_Manage(u32 TimChg)
{
		u16 tmp1;
	
							if(TimChg&BIT2)
	        {						
					
					
					if(AD_flag==0)
					{
					    ADC_START(10) ;
              AD_flag=1;
		      }
					
					
					
					
					
					else	if(AD_flag==1)
					{
						
					    tmp1=Get_AdcData() ;
						  ADCTEMP1_js++;
              ADCTEMP1=ADCTEMP1+tmp1;
						  if(ADCTEMP1_js==20)
						  {
								tmp1=ADCTEMP1/20;
								
								USART1_SetBuf(USART_PARA_AD1,tmp1);
								ADCTEMP1_js=0;
								ADCTEMP1=0;
							}
						
							

              AD_flag=2;						
						
		      }				
					
					else	if(AD_flag==2)
					{
					    ADC_START(11) ;
              AD_flag=3;
		      }
									
					else	if(AD_flag==3)
					{

					    tmp1=Get_AdcData() ;

						  ADCTEMP2_js++;
              ADCTEMP2=ADCTEMP2+tmp1;
						  if(ADCTEMP2_js==20)
						  {
								tmp1=ADCTEMP2/20;
								
								USART1_SetBuf(USART_PARA_AD2,tmp1);
								ADCTEMP2_js=0;
								ADCTEMP2=0;
							}

	              AD_flag=0;					
		      }							
					
					
				}
	
	
}







//**********************************保持数据子程序****************************************
void ParaSave_Manage(u32 TimChg)
{
	
	//-------------------------------------

			
				if(USART1_GetIO(USART_PB_SavePara))
				{
					PIPE_SaveFlash();
					USART1_SetIO(USART_PB_SavePara,0);
					
					
					//tmp1=	USART1_GetIO(0);
				}
								
			

	//---------------------------------------				
	if(USART1_GetIO(USART_ShuJuBaoCun)==1)
	{
    
    BackSaveParameters();
		USART1_SetIO(USART_ShuJuBaoCun,0);
 							
	}
 
  //------------------------------------------------
	
	if(USART1_GetIO(USART_ShuJuHuiFu)==1)
	{
     BackLoadParameters();
	 	USART1_SetIO(USART_ShuJuHuiFu,0);		
		
	}	
 
	
}	

//**********************************伺服清理***************************************
void Servo_Clear(u32 TimChg)
{
	
		   if(ServoClear_flag==1)
		 {
		  // SVOClearTime = CLEAR1_TMR;
		  	SVOClearTime = USART1_GetBuf(Clear_Time);
			  ServoClear_flag=2;				 
			  IO_SetDO(DO_CLEAR);				//输出低电平	  zxs
		 }
  //-------------------------------------------------
	  //伺服清零 延时程序	
   if(ServoClear_flag==2)
     {	 

				if(SVOClearTime)
				{
					if(TimChg&BIT1)
						SVOClearTime--;
				}
			   else
			  {
			    	IO_ResetDO(DO_CLEAR);			//输出高电平
					  ServoClear_flag=0;
				}
			}				
	
	
}	

//------------------------------------------------------
void LockAxle()
{ 
    if(!USART1_GetIO(USART_SUOZHOU))
          IO_ResetDO(DO_LockAxle);
	 else   IO_SetDO(DO_LockAxle);
		
		
}	

//------------------------------------------------------
void ComTest1(u32 TimChg)		
{ 

	 // aaa=USART1_GetBuf(ComTest);
//	
// 		if(TimChg&BIT1)
//	  ComTest_js++;
//	  if(ComTest_js>2000)
//	  {
//			if(USART1_GetBuf(ComTest)==138)
//			{
//				ComTest_js=0;
//				USART1_SetBuf(ComTest,0);
//			}
//			else
//			{
//				USART1_Configuration();
//				ComTest_js=0;
//				
//			}				
//			
//		}
	
}	
/////////////////////////////////////////////////////////////////////////////
void JiaMiManage(u32 TimChg)		
{  
 		if((TimChg&BIT12)&&Run_flag==0)	
	  SMEC_Test();
	
}
//**********************************主程序****************************************
void MainWork(u32 TimChg)
{
	
	u16 tmp1,tmp2,tmp3;	
	u8 i;	
	
	//----------------------------------------
	 ParaSave_Manage(TimChg); //参数保存恢复
	 Run_LED(TimChg);         //运行灯
	 AD_Manage(TimChg);
	  Servo_Clear(TimChg); 
    HMI_Manage(TimChg); 	
	  Time_delay(TimChg); 
	  LockAxle(); 
 	ManualWork(TimChg);	
	InAction(TimChg);	  //外接控件设置与送料速度计算
	MainLogic(TimChg);	  //动作的逻辑关系

	
	
//	
  	Analog();			  //模拟量控制
//	FeedWork(TimChg);	  //放料相关控制
 	JiaMiManage(TimChg);
	
	
	
	  //  SET_RX2();

	



		
}
