#ifndef _MAINWORK_H_
#define _MAINWORK_H_
#include "LCDPLC.h"


#define RunLed_on()  (GPIOC->BRR = GPIO_Pin_2)
#define RunLed_off() (GPIOC->BSRR = GPIO_Pin_2)


// //系统变量列表
//#define INPUT_DATA1 0
//#define INPUT_DATA2 1
//#define INPUT_DATA3 2
//#define OUTPUT_DATA1 3
//#define OUTPUT_DATA2 4
//#define UP_STATU1 5
//#define SPEED_GK1 6							//测速
//用于测试



//======================输入端口定义X01-X10 10个=======================


//#define DI_MANUAL_AUTO_SW     X01	     //X01	外接手动自动
//#define DI_GD_Left 						X02		 	 //X02	光电左
//#define DI_GD_Right 					X03		   //X03	光电右
//#define DI_XW_Left  					X04	 	   //X04	左限位信号
//#define DI_XW_Right 					X05			 //X05	右限位信号
//#define DI_Left 							X06		   //X03	外接左转
//#define DI_Right		 					X07		   //X04	外接右转


#define DI_GK1                  X01		   //GK1霍尔1送料    
#define DI_GK2                  X02			 //GK2霍尔2超速
#define DI_GK3                  X03			 //GK3色标光电 
#define DI_START                X04      //外接启动   
#define DI_STOP                 X05      //外接停止  
#define DI_JOGF                 X06      //外接点进   
#define DI_JOGB                 X07			 //外接点退 
#define DI_SHUCHUI              X08		   //下吹  X11
#define DI_BLOCKING             X09			 //GK3色标光电1
#define DI_BREAK                X10			 //GK3色标光电1
#define DI_TangYa               X11			 //烫压
#define DI_JiShuPause           X12		
//==========================================================================

//======================输出端口Y01-Y10 10个=======================



//#define DO_GO_ZUO 					Y03			//Y03	纠偏左
//#define DO_GO_YOU 					Y04			//Y04	纠偏右


// 
//#define DO_BEEP 					  Y10			//蜂鸣器

#define DO_CP1                Y01     //脉冲1方向
#define DO_CW1                Y02     //脉冲1方向
#define DO_CLEAR              Y03     //伺服清理
#define DO_TWOSTAGE           Y04     //二段速
#define DO_BaZhen             Y05     //拔针 
#define DO_ShuSong            Y06     //输送 
#define DO_K                  Y07     //主机输出
#define DO_HOLE               Y08     //打孔输出
#define DO_SHUCHUI            Y09     //竖吹
#define DO_HENGCHUI           Y10     //横吹
#define DO_JD                 Y11
#define DO_LockAxle           Y12    
#define DO_BEEP               Y13     //蜂鸣器 


//==========================================================================
//运行状态
#define WORK_STOP     	0
#define WORK_RUN	      1
#define WORK_OVSPD	    2						   //超速
#define WORK_PAUSE	    3
#define WORK_LOSE_MARK	4
#define WORK_BREAK		  5					   //断料
#define WORK_BLOCKING		6					   //堵料
#define WORK_KongQie		7					//空切
#define WORK_SYSTEM1	  8					//系统1
#define WORK_ZANTINGZHENGLI   9
#define WORK_KONGQIEZHENGLI   10
#define WORK_DIANDONG        11



#define WORK_NeiBuZhengChang  0
#define WORK_NeiBuCuoWu       1

void MainWork_InitVar(void);
void MainWork(u32 TimChg);

#endif
