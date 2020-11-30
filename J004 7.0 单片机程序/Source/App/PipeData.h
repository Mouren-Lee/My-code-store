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
#define SPEED_GK1                 32						  //测速
#define TOTAL_COUNT               33						  //总数
#define TOTAL_COUNT2              34						  //总数
#define GK1_COUNT                 35							//GK1计数
#define WORK_INF                  36							//运行状态

#define SPEED_SET                 40							//主机速度
#define AMOUNT_BATCH              41				 	    //整本数
#define BATCH_MODE	              42					    //机型选择
#define MaiChongDangLiang1        43              //  脉冲当量1 
#define MaiChongDangLiang2        44              //  脉冲当量2 
#define LOSE_MARK                 45						//脱标个数
#define ALARM_CNT                 46						//报警个数
#define PAUSE_TIME                47						//暂停时间
#define MAIN_REGULATOR            48				    //主机系数
#define CURVELINE                 49             //曲线选择	
#define SEEK_STYLE                50            //颜色选择
#define MATERIAL_LENGTH           51			      //长度1设定
#define LENGTH_CNT                52			      //长度1对应的脉冲个数CP1
#define MATERIAL_LENGTH2          53			      //长度2设定
#define LENGTH_CNT2               54			      //长度2对应的脉冲个数CP2
#define MARK_WIDTH_LENGTH         55						//寻标范围长度
#define MARK_WIDTH_CNT            56						//寻标范围脉冲个数
#define YUTUI_LENGTH              57            //预退长度
#define YUTUI_CNT                 58            //预退长度脉冲个数
#define HUISUO_LENGTH             59            //回缩长度
#define HUISUO_CNT                60            //回缩长度脉冲个数
#define DuanJiao_LENGTH           61            //断胶长度
#define DuanJiao_CNT              62            //断胶长度脉冲个数
#define BuChan_LENGTH             63            //补偿长度
#define BuChan_CNT                64            //补偿长度脉冲个数
#define SPEED_STEPCP1             65						//加速时间1，送料速度
#define SPEED_STEPCP2             66						//加速时间2，送料速度
#define SPEED_YUTUI               67            //预退速度
#define SPEED_HUISUO              68            //回缩速度

#define JOG_Frequency             70					  //点进频率
#define JOG_Frequency_T           71					  //点进频率对应时间
#define XunBiao_Frequency         72            //寻标频率
#define XunBiao_Frequency_T       73            //寻标频率对应时间
#define TOP_FrequencyCP1          74						//最高速度1
#define TOP_FrequencyCP1_T        75						// 最高频率对应时间1
#define TOP_FrequencyCP2          76						//最高速度2 
#define TOP_FrequencyCP2_T        77						// 最高频率对应时间2
#define TOP_YUTUI                 78						//最高速度预退
#define TOP_YUTUI_T               79						//最高速度预退  计算后
#define TOP_HUISUO                80						//最高速度回缩
#define TOP_HUISUO_T              81						//最高速度回缩
 
#define ShuChui_Time              84				//竖吹时间
#define HengChuiBFB               85         //横吹百分比
#define ChaoShengBo_Dealy         86					  //超声波延时
#define JingDian_Dealy            87        //静电延时 
#define HeDao_Dealy               88 
#define FangLiaoTiQian_Time       89 


#define APART1_Dealy             90					//脱袋延时一
#define APART1_Time              91					//脱袋时间一
#define BanZheng_Dealy           92 //
#define BanZheng_Time            93 //
#define TangYa_Dealy             94 
#define QiDong_Dealy             95 
#define Blocking_Time            96
#define GaoWei_Dealy             97             //高位延时停车  2015-1-22
#define DUTY                     98             //占空比例
#define AutoAccPar               99             //自动加速系数
#define ComTest                  100            //通讯校验  一秒钟一次数据138
#define SYSTEM1_Time             101            //锁机时间
#define ZhuJiDianDongSpeed       102            //主机点动频率
#define HOLE1_DELAY              103					//打孔延时一
#define HOLE1_KEEP               104						//打孔时间一
#define ShiJi_LENGTH1            105	         //实际长度  算当量
#define STWOSPEEDFRE             106






#define MarkWait_CNT             110           //等待脉冲
#define SPEED_CP1JianSu          111           //减速倍率
#define Clear_Time               112           //伺服清理时间



#define JIAMI_INF                139							//运行状态2
#define LASTDAY                  140          //上次日期时间
#define RIQITIME                 144          //日期时间





//#define USART_OUT0 6			//0x97~0x112
//#define USART_OUT1 7			//0x113~0x128


//----------------0-48  位参数 不保存--------------------------

//#define   USART_PB_HandOrAuto          0       //0  手动  1 自动
//#define   USART_PB_HandLeft            1       //手动 左转
//#define   USART_PB_HandRight           2       //手动 右转
//#define   USART_PB_GoToMiddle          3       //手动 回中点
//#define   USART_PB_Clear               4      //重量清零
//#define   USART_PB_QuPi                5      //去皮


#define USART_START_IN           0		  //起动
#define USART_STOP_IN            1		  //停止
#define USART_STOP_F             2			//强制停止
#define USART_JOGF               3			//点进
#define USART_JOGB               4			//点退
#define USART_SEEK               5			//手动寻标
#define USART_ZhuJiAdjust        6			//主机修正
#define USART_ZhuJiAdjustTure    7      //主机修正反馈标志
#define USART_TOTAL_CLR          8	  	//总数清零
#define USART_CNT_CLR            9		  //个数清零
#define USART_BATCH_CLR          10		  //批数清零
#define USART_SYSTEM1            11      //系统1
#define USART_AutoAccPar         12    //自动加速数据更新反馈标志        
#define USART_ShuJuBaoCun        13     //数据保存到备份区
#define USART_ShuJuHuiFu         14     //数据恢复
#define USART_BuShu              15     //计数暂停



//--------------------49-175  位参数 保存--------------------------------------
#define   USART_PB_SavePara              60        //保存参数到FLASH  1 有效自动清零
//#define   USART_PB_LOADED              81  

//#define   USART_PB_JiXing              86       //极性
//#define   USART_PB_DanGOrShuangG       87       //单光双光


#define USART_SUOZHOU                     81			//锁轴
#define USART_LOADED                      82    //初始化
#define USART_LongOrShort                 83			//长袋模式

#define USART_FEED_CUT                    85  		//先送后切
#define USART_SPEED_AUTO                  86    //自动加速切换按键
#define USART_TuoDaiPuTongOrBuJin         87
#define USART_DaKong                      88     //打孔开关
#define USART_MaiChongJiaoZhun            89     //脉冲当量校准
#define USART_BreakSwitch                 90			//断料开关
#define USART_MaiChongCW                  91			//脉冲方向



#endif
