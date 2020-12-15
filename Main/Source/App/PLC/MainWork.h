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
#define DI_GK3                  X03			 //GK2霍尔2超速 
#define DI_JiShuPause           X04	
#define DI_START                X05      //外接启动   
#define DI_STOP                 X06      //外接停止  


#define DI_FUWEI                X12			 // 

//==========================================================================

//======================输出端口Y01-Y10 10个=======================


#define DO_CP1                Y01     //脉冲1方向
#define DO_CW1                Y02     //脉冲1方向
#define DO_DuiJia             Y03     // 
#define DO_ChuiQi             Y04      
#define DO_DangLiao           Y05     
#define DO_YaLiao             Y06     
#define DO_ShuSong            Y07     //输送 


#define DO_BEEP               Y13     //蜂鸣器 
//============================================================================
//标志位结构体
typedef struct {    //系统标志位
    u8 Start_Flag;//启动标志位             0:停止                              1:运行
    u8 Mode_Flag;//输出顺序标志位          0:对夹与吹气输出     1:吹气计时结束输出挡料   2:关闭挡料   3:压料输出   4:压料计数 
    u8 Tran_Flag;//输送标志位              0：未输出           1:输出前延时            2:输出时间      
//----------布尔标志位------------
    bool BuzzerS_Flag;//蜂鸣器启动标志位   false:与蜂鸣器计时标志位同时为0时关闭蜂鸣器   true:启动蜂鸣器
    bool BuzzerJs_Flag;//蜂鸣器计时标志位  false:与蜂鸣器启动标志位同时为0时关闭蜂鸣器   true:启动蜂鸣器
    bool StartIO_Flag;//外接启动标志位     false:外接未启动或外接启动结束               true:外接启动中
    bool Start_Button;//按键启动标志位     false:未启动                        true:已启动
    bool Count_Pause;//计数暂停标志位      false:计数正常                       true:计数暂停
    bool Stop_Flag;//停止标志位            false:停止状态                      true:进入停止状态
    bool Stop_Button;//停止标志位按键       false:停止按键未按下                true:停止按键按下
    bool HighStop_Flag;//高位停止标志位     false:未进入高位停止状态            true:进入高位停止状态
    bool Count_Cnt;//计数标志位             false:未进入计数                   true:进入计数  
    bool X01_Flag;//光标1是否结束标志位      false:结束                         true:未结束
    bool YaLiao_Flag;//压料标志位           false:未压料                       true:压料中           
} Sys_Flag;
//----------------------------
typedef struct {    //时间计数标志位
    u16 ChuiQic_Time;//吹气计时
    u16 YaLiaoc_Time;//压料计时
    u16 Run_Time;//启动延时
    u16 Buzzer_Time;//蜂鸣器计时
    u16 Tran_Time;//输送计时
} Time_Flag;
//==========================================================================
//运行状态
#define WORK_STOP     	0
#define WORK_RUN	      1
#define WORK_SYSTEM1	  2					//系统1


//==========================================================================
#define WORK_NeiBuZhengChang  0
#define WORK_NeiBuCuoWu       1		
//====================================================
//标志位声明
extern Sys_Flag Sys_Data;
extern Time_Flag Time_Data;
//====================================================
void MainWork_InitVar(void);
void MainWork(u32 TimChg);
 void Typedef_Init(void);//结构体初始化
#endif
