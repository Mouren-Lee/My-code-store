#include "PIPE.h"

#ifndef _PIPEDATA_H_
#define _PIPEDATA_H_


// //系统变量列表
//#define INPUT_DATA1 0
//#define INPUT_DATA2 1
//#define INPUT_DATA3 2
//#define OUTPUT_DATA1 3
//#define OUTPUT_DATA2 4
//#define UP_STATU1 5
//#define SPEED_GK1 6							//测速
//用于测试
//---------------------16位参数 0-127  前面10个位参数不能动-----------------------------
#define USART_PARA_0    0     //BIT 0-15 
#define USART_PARA_1    1     //BIT 16-31 
#define USART_PARA_2    2     //BIT 32-47 
#define USART_PARA_3    3     //BIT 48-63 
#define USART_PARA_4    4     //BIT 64-79 
#define USART_PARA_5    5     //BIT 80-95 
#define USART_PARA_6    6     //BIT 96-111 
#define USART_PARA_7    7     //BIT 112-127 
#define USART_PARA_8    8     //BIT 128-143 
#define USART_PARA_9    9     //BIT 144-159 
#define USART_PARA_10   10    //BIT 160-175 


#define USART_PARA_DI0  11			  //      X01-X16
#define USART_PARA_DI1  12			  //      X17-X32
#define USART_PARA_DO0  13 			  //0x33~0x48     Y01-Y16
#define USART_PARA_DO1  14				//0x49~0x64     Y17-Y32

#define USART_PARA_AD1  16	
#define USART_PARA_AD2  17	
#define USART_PARA_DA1  18	
#define USART_PARA_DA2  19	 

 


 



#define BATCH_COUNT               31						  //批数
#define TOTAL_COUNT               32						  //总数
#define TOTAL_COUNT2              33						  //总数
#define GK1_COUNT                 34							//GK1计数
#define AMOUNT_BATCH              35	
#define ALARM_CNT                 36	


#define ChuiQi_Time               37
#define YaLiao_Time               38
#define ShuSong_Delay             39
#define ShuSong_Time              40
#define QiDong_Dealy              41 
#define WORK_INF                  42 
#define Js_Pause                  55


#define ComTest                  100            //通讯校验  一秒钟一次数据138
#define SYSTEM1_Time             101            //锁机时间
#define JIAMI_INF                139							//运行状态2
#define LASTDAY                  140          //上次日期时间
#define RIQITIME                 144          //日期时间







//----------------0-48  位参数 不保存--------------------------





#define USART_START_IN           0		  //起动
#define USART_STOP_IN            1		  //停止
#define USART_STOP_F             2			//强制停止
#define USART_ShuJuBaoCun        3     //数据保存到备份区
#define USART_ShuJuHuiFu         4     //数据恢复 
#define USART_TOTAL_CLR          5	  	//总数清零
#define USART_CNT_CLR            6		  //个数清零
#define USART_BATCH_CLR          7		  //批数清零
 
#define USART_DuiJia             8	   
#define USART_ChuiQi             9		  
#define USART_DangLiao           10		 
#define USART_YaLiao             11	
#define USART_ShuSong            12	



//--------------------49-175  位参数 保存--------------------------------------
#define   USART_PB_SavePara              60        //保存参数到FLASH  1 有效自动清零
//#define   USART_PB_LOADED              81  

//#define   USART_PB_JiXing              86       //极性
//#define   USART_PB_DanGOrShuangG       87       //单光双光


#define USART_SUOZHOU                     81			//锁轴
#define USART_LOADED                      82    //初始化
#define USART_BuShu                       83    




#endif
