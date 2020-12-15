#ifndef _LABELROOM_H_
#define _LABELROOM_H_

#define STRING_COUNT 136
#define STRING_STYLE 2

#define NULL 0
#define STR_NUMPT 1
#define STR_NUMNEG 2
#define STR_COLON 3
#define STR_SPEEDUP 4
#define STR_SPEEDDN 5
#define STR_BRACKETLEFT 6
#define STR_BRACKETRIGHT 7
#define STR_CHINESE 8
#define STR_ENGLISH 9
#define STR_JISHU 10
#define STR_PISHU 11
#define STR_TOTAL_CNT 12
#define STR_ZERO 13
#define STR_SPPEDSET 14
#define STR_FANGLIAOSUDU 15
#define STR_SPEED 16
#define STR_MPERS 17
#define STR_GE 18
#define STR_GEMEIPI 19
#define STR_BATCH 20
#define STR_HEZI 21
#define STR_CHANGDUSHEDINGMM 22
#define STR_HAOMI 23
#define STR_Second 24
#define STR_COLOR1 25
#define STR_COLOR2 26
#define STR_COLOR3 27
#define STR_XUNBIAO 28
#define STR_DIANJIN 29
#define STR_DIANTUI 30
#define STR_BUSHU 31
#define STR_STATUSHOW 32
#define STR_ZHUANGTAIXIANSHI 33
#define STR_STOP 34
#define STR_RUN 35
#define STR_CHAOSU 36
#define STR_ZANTING 37
#define STR_TUOBIAO 38
#define STR_SYSTEM1 39
#define STR_SYSTEM2 40
#define STR_DUANLIAO 41
#define STR_DULIAO 42
#define STR_KongQie 43
#define STR_FUWEI 44
#define STR_SETPAR 45
#define STR_XITONGSHEZHI 46
#define STR_SHEDING 47
#define STR_SHANGYIYE 48
#define STR_XIAYIYE 49
#define STR_ZHUYE 50
#define STR_ZHANKONGBILI 51
#define STR_SHOUDONGZIDONG 52
#define STR_ZIDONGSHOUDONG 53
#define STR_PINGMUJIAOZHUN 54
#define STR_ZHUCAIDAN 55
#define STR_FUCAIDAN 56
#define STR_JIANSHICHUANGKOU 57
#define STR_XITONGJIANJIE 58
#define STR_ENTER 59
#define STR_CLR 60
#define STR_BACK 61
#define STR_ESC 62
#define STR_TOPIC_SYSTEM1 63
#define STR_TOPIC_SYSTEM2 64
#define STR_SETCOLOK 65
#define STR_CLOCKSET 66
#define STR_MIMA1 67
#define STR_MIMA2 68
#define STR_RETURN 69
#define STR_BAOCUNSHUJU 70
#define STR_HUIFUCHUCHANG 71
#define STR_X01 72
#define STR_X02 73
#define STR_X03 74
#define STR_X04 75
#define STR_X05 76
#define STR_X06 77
#define STR_X07 78
#define STR_X08 79
#define STR_X09 80
#define STR_X10 81
#define STR_X11 82
#define STR_X12 83
#define STR_X13 84
#define STR_X14 85
#define STR_X15 86
#define STR_X16 87
#define STR_Y01 88
#define STR_Y02 89
#define STR_Y03 90
#define STR_Y04 91
#define STR_Y05 92
#define STR_Y06 93
#define STR_Y07 94
#define STR_Y08 95
#define STR_Y09 96
#define STR_Y10 97
#define STR_Y11 98
#define STR_Y12 99
#define STR_Y13 100
#define STR_Y14 101
#define STR_Y15 102
#define STR_Y16 103
#define STR_ZHUJIMONI 104
#define STR_FANGLIAOMONI 105
#define STR_CHULIAOMONI 106
#define STR_FANGLIAOMONI2 107
#define STR_FANGLIAOJIASUKUAIMAN 108
#define STR_SHENGCHANSHANG 109
#define STR_DIANHUA 110
#define STR_CANSHUSHEZHI5 111
#define STR_CHUCHANG 112
#define STR_CHUCHANGBIANHAO 113
#define STR_RUANJIANBANBEN 114
#define STR_SHUOMINGSHU 115
#define STR_BUJINKUAISU 116
#define STR_BUJINMANSU 117
#define STR_SIFUKUAI 118
#define STR_SIFUMAN 119
#define STR_XITONGJIAOZHENG 120
#define STR_DUOGONGNENG 121
#define STR_DUOGONGNENGSHURU 122
#define STR_DUOGONGNENGSHUCHU 123
#define STR_MIAO 124
#define STR_CM 125
#define STR_NUMM0 126
#define STR_NUMM1 127
#define STR_NUMM2 128
#define STR_NUMM3 129
#define STR_NUMM4 130
#define STR_NUMM5 131
#define STR_NUMM6 132
#define STR_NUMM7 133
#define STR_NUMM8 134
#define STR_NUMM9 135

const static u8 LabelText_1[]={
"\0"
".\0"
"-\0"
":\0"
"+\0"
"-\0"
"(\0"
")\0"
"English\0"
"Chinese\0"
"计数/清零\0"
"批数/清零\0"
"总数/清零\0"
"清零\0"
"主机速度\0"
"后放料速度\0"
"测速:\0"
"转/分\0"
"个\0"
"个/批\0"
"批\0"
"Hz\0"
"长度设定\0"
"（毫米）\0"
"（秒）\0"
"空白\0"
"追浅\0"
"追深\0"
"寻标\0"
"点进\0"
"点退\0"
"补数\0"
"工作状态\0"
"状态显示\0"
"停止\0"
"运行\0"
"超速\0"
"暂停\0"
"脱标\0"
"系统1:\0"
"系统2:\0"
"断料\0"
"堵料\0"
"空切\0"
"复位\0"
"参数设置\0"
"系统设置\0"
"设定\0"
"上一页\0"
"下一页\0"
"主页\0"
"占空比例\0"
"手动\0"
"自动\0"
"屏幕校准\0"
"设置\0"
"副菜单\0"
"监控\0"
"简介\0"
"确定\0"
"清除\0"
"后退\0"
"取消\0"
"系  统1:\0"
"系  统2:\0"
"校准时间:\0"
"校准时间\0"
"修改密码1:\0"
"修改密码2:\0"
"返回\0"
"保存数据\0"
"恢复出厂\0"
"X01\0"
"X02\0"
"X03\0"
"X04\0"
"X05\0"
"X06\0"
"X07\0"
"X08\0"
"X09\0"
"X10\0"
"X11\0"
"X12\0"
"X13\0"
"X14\0"
"X15\0"
"X16\0"
"Y01\0"
"Y02\0"
"Y03\0"
"Y04\0"
"Y05\0"
"Y06\0"
"Y07\0"
"Y08\0"
"Y09\0"
"Y10\0"
"Y11\0"
"Y12\0"
"Y13\0"
"Y14\0"
"Y15\0"
"Y16\0"
"主机模拟\0"
"放料模拟\0"
"出料模拟\0"
"放料模拟2\0"
"放料修正\0"
"制造商:\0"
"电话:\0"
"参数设置5分钟后保存\0"
"出厂:\0"
"出厂编号:\0"
"软件版本:\0"
"说明书\0"
"步进快速\0"
"步进慢速\0"
"伺服快速\0"
"伺服慢速\0"
"系统校正\0"
"多功能端子\0"
"输入端子\0"
"输出端子\0"
"秒\0"
"无锡市海利达自动化仪器厂\0"
"0\0"
"1\0"
"2\0"
"3\0"
"4\0"
"5\0"
"6\0"
"7\0"
"8\0"
"9\0"
};

const static u8 LabelText_2[]={
"\0"
".\0"
"-\0"
":\0"
"+\0"
"-\0"
"(\0"
")\0"
"英文\0"
"中文\0"
"COUNT/CLEAR\0"
"BATCH/CLEAR\0"
"TOTAL/CLEAR\0"
"CLEAR\0"
"HOST VEL\0"
"PUT VEL\0"
"SPEED:\0"
"R/MIN\0"
"pcs\0"
"p/bat\0"
"batch\0"
"Hz\0"
"LENGTH\0"
"(mm)\0"
"(s)\0"
"WHITE\0"
"LIGHT\0"
"DARK\0"
"SEARCH\0"
"FOR\0"
"BACK\0"
"COMPLE\0"
"STATUS\0"
"STATUS\0"
"STOP\0"
"RUN\0"
"OVSPEED\0"
"PAUSE\0"
"LOSEMARK\0"
"SYSTEM1:\0"
"SYSTEM2:\0"
"BREAK\0"
"BLOCKING\0"
"EmptyCut\0"
"RESET\0"
"PAR SET\0"
"SYSTEM SET\0"
"SET\0"
"LAST\0"
"NEXT\0"
"HOME\0"
"DUTY RATIO\0"
"MANUAL\0"
"AUTO\0"
"ADJUST\0"
"SET\0"
"S MENU\0"
"WATCH\0"
"INF\0"
"ENTER\0"
"CLR\0"
"BACK\0"
"ESC\0"
"SYSTEM1:\0"
"SYSTEM2:\0"
"SET CLOCK:\0"
"CLOCK SET\0"
"password1:\0"
"password2:\0"
"RETURN\0"
"SAVE DATA\0"
"RECOVER\0"
"X01\0"
"X02\0"
"X03\0"
"X04\0"
"X05\0"
"X06\0"
"X07\0"
"X08\0"
"X09\0"
"X10\0"
"X11\0"
"X12\0"
"X13\0"
"X14\0"
"X15\0"
"X16\0"
"Y01\0"
"Y02\0"
"Y03\0"
"Y04\0"
"Y05\0"
"Y06\0"
"Y07\0"
"Y08\0"
"Y09\0"
"Y10\0"
"Y11\0"
"Y12\0"
"Y13\0"
"Y14\0"
"Y15\0"
"Y16\0"
"MAIN\0"
"DIS\0"
"OUT\0"
"DIS2\0"
"DISCHARGE FIX\0"
"MANUFACTURER:\0"
"TEL:\0"
"PAR SAVE AFTER 5 MIN\0"
"FACTORY:\0"
"FACTORY NO.:\0"
"SW VER\0"
"Manual\0"
"STEP FAST\0"
"STEP SLOW\0"
"SERVO FAST\0"
"SERVO SLOW\0"
"SYS ADJUST\0"
"MULTI PORT\0"
"input port\0"
"output port\0"
"s\0"
"\0"
"0\0"
"1\0"
"2\0"
"3\0"
"4\0"
"5\0"
"6\0"
"7\0"
"8\0"
"9\0"
};

const static u16 LabelIndex_1[]={
0,
1,3,5,7,9,11,13,15,23,31,
41,51,61,66,75,86,92,98,101,107,
110,113,122,131,138,143,148,153,158,163,
168,173,182,191,196,201,206,211,216,223,
230,235,240,245,250,259,268,273,280,287,
292,301,306,311,320,325,332,337,342,347,
352,357,362,371,380,390,399,410,421,426,
435,444,448,452,456,460,464,468,472,476,
480,484,488,492,496,500,504,508,512,516,
520,524,528,532,536,540,544,548,552,556,
560,564,568,572,581,590,599,609,618,626,
632,652,658,668,678,685,694,703,712,721,
730,741,750,759,762,787,789,791,793,795,
797,799,801,803,805,};

const static u16 LabelIndex_2[]={
0,1,3,5,7,
9,11,13,15,20,25,37,49,61,67,
76,84,91,97,101,107,113,116,123,128,
132,138,144,149,156,160,165,172,179,186,
191,195,203,209,218,227,236,242,251,260,
266,274,285,289,294,299,304,315,322,327,
334,338,345,351,355,361,365,370,374,383,
392,403,413,424,435,442,452,460,464,468,
472,476,480,484,488,492,496,500,504,508,
512,516,520,524,528,532,536,540,544,548,
552,556,560,564,568,572,576,580,584,588,
593,597,601,606,620,634,639,660,669,682,
689,696,706,716,727,738,749,760,771,783,
785,786,788,790,792,794,796,798,800,802,
804,};
const static u16* pLabelIndex[] = {
LabelIndex_1,
LabelIndex_2,
};
const static u8* pLabelText[] = {
LabelText_1,
LabelText_2,
};

#endif
