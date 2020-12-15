#ifndef _LABELROOM_H_
#define _LABELROOM_H_

#define STRING_COUNT 309
#define STRING_STYLE 2

#define NULL 0
#define STR_NUM0 1
#define STR_NUM1 2
#define STR_NUM2 3
#define STR_NUM3 4
#define STR_NUM4 5
#define STR_NUM5 6
#define STR_NUM6 7
#define STR_NUM7 8
#define STR_NUM8 9
#define STR_NUM9 10
#define STR_NUMPT 11
#define STR_NUMNEG 12
#define STR_COLON 13
#define STR_SPEEDUP 14
#define STR_SPEEDDN 15
#define STR_BRACKETLEFT 16
#define STR_BRACKETRIGHT 17
#define STR_CHINESE 18
#define STR_ENGLISH 19
#define STR_JISHU 20
#define STR_PISHU 21
#define STR_TOTAL_CNT 22
#define STR_ZERO 23
#define STR_SPPEDSET 24
#define STR_FANGLIAOSUDU 25
#define STR_SPEED 26
#define STR_MPERS 27
#define STR_CHANGDUSHEDINGMM 28
#define STR_HAOMI 29
#define STR_COLOR1 30
#define STR_COLOR2 31
#define STR_COLOR3 32
#define STR_XUNBIAO 33
#define STR_DIANJIN 34
#define STR_DIANTUI 35
#define STR_BUSHU 36
#define STR_STATUSHOW 37
#define STR_ZHUANGTAIXIANSHI 38
#define STR_STOP 39
#define STR_RUN 40
#define STR_CHAOSU 41
#define STR_ZANTING 42
#define STR_TUOBIAO 43
#define STR_SYSTEM1 44
#define STR_SYSTEM2 45
#define STR_DUANLIAO 46
#define STR_DULIAO 47
#define STR_FUWEI 48
#define STR_SETPAR 49
#define STR_XITONGSHEZHI 50
#define STR_SHEDING 51
#define STR_SHANGYIYE 52
#define STR_XIAYIYE 53
#define STR_ZHUYE 54
#define STR_JIXINGXUANZE 55
#define STR_JIXING1 56
#define STR_JIXING2 57
#define STR_JIXING3 58
#define STR_JIXING4 59
#define STR_XIANQIEHOUSONG 60
#define STR_XIANSONGHOUQIE 61
#define STR_ZHENGBENYUZHI 62
#define STR_ZANTINGSHIJIAN 63
#define STR_SONGLIAOSUDU 64
#define STR_ZUIGAOPINLV 65
#define STR_JIAOGUNZHOUCHANG 66
#define STR_SEBIAOFANWEI 67
#define STR_DIANJINSUDU 68
#define STR_ZHUJIXISHU 69
#define STR_FANGLIAOXISHU 70
#define STR_SHOUDONGFANGLIAO 71
#define STR_ZHENGQUANBUSHU 72
#define STR_CHULIAOZHUANSU 73
#define STR_GAOWEIYANSHI 74
#define STR_DAKONGYANSHI 75
#define STR_DAKONGSHIJIAN 76
#define STR_TUOBIAOGESHU 77
#define STR_BAOJINGGESHU 78
#define STR_TUODAIYANSHI 79
#define STR_TUODAISHIJIAN 80
#define STR_JIASUCAIDAN 81
#define STR_FANGSHI 82
#define STR_ZHANKONGBILI 83
#define STR_SHOUDONGZIDONG 84
#define STR_ZIDONGSHOUDONG 85
#define STR_PINGMUJIAOZHUN 86
#define STR_HENGCHUISHI 87
#define STR_SHUCHUISHI 88
#define STR_BULIAOCHANGDU 89
#define STR_HOUTUICHANGDU 90
#define STR_JIASUSHIJIAN 91
#define STR_SIFUZHUANSU 92
#define STR_BULIAOCANSHU 93
#define STR_CHAOSHENGYANSHI 94
#define STR_QUXIAN 95
#define STR_Stop 96
#define STR_Start 97
#define STR_DecCoef 98
#define STR_ZHUCAIDAN 99
#define STR_FUCAIDAN 100
#define STR_JIANSHICHUANGKOU 101
#define STR_XITONGJIANJIE 102
#define STR_ENTER 103
#define STR_CLR 104
#define STR_BACK 105
#define STR_ESC 106
#define STR_TOPIC_SYSTEM1 107
#define STR_TOPIC_SYSTEM2 108
#define STR_SETCOLOK 109
#define STR_CLOCKSET 110
#define STR_MIMA1 111
#define STR_MIMA2 112
#define STR_RETURN 113
#define STR_BAOCUNSHUJU 114
#define STR_HUIFUCHUCHANG 115
#define STR_X01 116
#define STR_X02 117
#define STR_X03 118
#define STR_X04 119
#define STR_X05 120
#define STR_X06 121
#define STR_X07 122
#define STR_X08 123
#define STR_X09 124
#define STR_X10 125
#define STR_X11 126
#define STR_X12 127
#define STR_X13 128
#define STR_X14 129
#define STR_X15 130
#define STR_X16 131
#define STR_Y01 132
#define STR_Y02 133
#define STR_Y03 134
#define STR_Y04 135
#define STR_Y05 136
#define STR_Y06 137
#define STR_Y07 138
#define STR_Y08 139
#define STR_Y09 140
#define STR_Y10 141
#define STR_Y11 142
#define STR_Y12 143
#define STR_Y13 144
#define STR_Y14 145
#define STR_Y15 146
#define STR_Y16 147
#define STR_ZHUJIMONI 148
#define STR_FANGLIAOMONI 149
#define STR_CHULIAOMONI 150
#define STR_FANGLIAOMONI2 151
#define STR_FANGLIAOJIASUKUAIMAN 152
#define STR_SHENGCHANSHANG 153
#define STR_DIANHUA 154
#define STR_CANSHUSHEZHI5 155
#define STR_CHUCHANG 156
#define STR_CHUCHANGBIANHAO 157
#define STR_RUANJIANBANBEN 158
#define STR_CHUANGANLUOJITU 159
#define STR_DIDAO 160
#define STR_QIEDAO 161
#define STR_PICTURE 162
#define STR_WAIBUJIEXIANTU 163
#define STR_ZHUCAIDAN1 164
#define STR_ZHUCAIDAN2 165
#define STR_ZHUCAIDAN3 166
#define STR_LUOJIGUANXI 167
#define STR_JIEXIANSHUOMING 168
#define STR_ZHUCAIDAN4 169
#define STR_ZHUCAIDAN5 170
#define STR_ZHUCAIDAN6 171
#define STR_ZHUCAIDAN7 172
#define STR_KAIGUANDIANYUAN 173
#define STR_GUANGDIANYAN 174
#define STR_SONGLIAOHUOER 175
#define STR_CHAOSUHUOER 176
#define STR_BLACK 177
#define STR_RED 178
#define STR_BLUE 179
#define STR_BROWN 180
#define STR_WG 181
#define STR_START 182
#define STR_SHURU 183
#define STR_BEEP 184
#define STR_BIANPINQI 185
#define STR_BUJINDIANJI 186
#define STR_JIDIANQI 187
#define STR_TIAOSUBAN 188
#define STR_QUDONGQI 189
#define STR_LICI 190
#define STR_ZHILIUDIANJI 191
#define STR_SHUOMINGSHU 192
#define STR_BUJINKUAISU 193
#define STR_BUJINMANSU 194
#define STR_SIFUKUAI 195
#define STR_SIFUMAN 196
#define STR_JINGDIANYANSHI 197
#define STR_CHULIAOSUDU 198
#define STR_TUODAIYANSHI2 199
#define STR_TUODAISHIJIAN2 200
#define STR_FANGLIAOSUDU2 201
#define STR_XITONGJIAOZHENG 202
#define STR_BUPIANJIEMIAN 203
#define STR_BUPIANCHANGDU 204
#define STR_JIAOGUNZHOUCHANG2 205
#define STR_ZUIGAOPINLV2 206
#define STR_SONGLIAOSUDU2 207
#define STR_REVIN0 208
#define STR_REVIN1 209
#define STR_REVIN2 210
#define STR_REVIN3 211
#define STR_REVIN4 212
#define STR_REVIN5 213
#define STR_REVIN6 214
#define STR_REVIN7 215
#define STR_REVIN8 216
#define STR_REVIN9 217
#define STR_REVIN10 218
#define STR_REVIN11 219
#define STR_REVIN12 220
#define STR_REVIN13 221
#define STR_REVIN14 222
#define STR_REVIN15 223
#define STR_REVIN16 224
#define STR_REVIN17 225
#define STR_REVOUT0 226
#define STR_REVOUT1 227
#define STR_REVOUT2 228
#define STR_REVOUT3 229
#define STR_REVOUT4 230
#define STR_REVOUT5 231
#define STR_REVOUT6 232
#define STR_REVOUT7 233
#define STR_REVOUT8 234
#define STR_REVOUT9 235
#define STR_REVOUT10 236
#define STR_REVOUT11 237
#define STR_DUOGONGNENG 238
#define STR_DUOGONGNENGSHURU 239
#define STR_DUOGONGNENGSHUCHU 240
#define STR_DAKONGYANSHI2 241
#define STR_DAKONGSHIJIAN2 242
#define STR_DINGLIAOGESHU 243
#define STR_TUODAIPISHU 244
#define STR_DUOZOUCHANGDU 245
#define STR_TINGCHETUILIAO 246
#define STR_LALIAOCHANGDU 247
#define STR_LADUANCHANGDU 248
#define STR_DULIAOSHIJIAN 249
#define STR_QIBUKUAIMAN 250
#define STR_Curve_6_0 251
#define STR_Curve_6_2 252
#define STR_Curve_6_4 253
#define STR_Curve_6_6 254
#define STR_Curve_6_8 255
#define STR_Curve_7_0 256
#define STR_Curve_7_2 257
#define STR_Curve_7_4 258
#define STR_Curve_7_6 259
#define STR_Curve_7_8 260
#define STR_Curve_8_0 261
#define STR_Curve_8_2 262
#define STR_Curve_8_4 263
#define STR_Curve_8_6 264
#define STR_Curve_8_8 265
#define STR_Curve_9_0 266
#define STR_MIAO 267
#define STR_XS0 268
#define STR_XS1 269
#define STR_XS2 270
#define STR_XS3 271
#define STR_XS4 272
#define STR_XS5 273
#define STR_XS6 274
#define STR_XS7 275
#define STR_XS8 276
#define STR_XS9 277
#define STR_XS10 278
#define STR_XS11 279
#define STR_XS12 280
#define STR_XS13 281
#define STR_XS14 282
#define STR_XS15 283
#define STR_XS16 284
#define STR_XS17 285
#define STR_YS0 286
#define STR_YS1 287
#define STR_YS2 288
#define STR_YS3 289
#define STR_YS4 290
#define STR_YS5 291
#define STR_YS6 292
#define STR_YS7 293
#define STR_YS8 294
#define STR_YS9 295
#define STR_YS10 296
#define STR_YS11 297
#define STR_NUMM0 298
#define STR_NUMM1 299
#define STR_NUMM2 300
#define STR_NUMM3 301
#define STR_NUMM4 302
#define STR_NUMM5 303
#define STR_NUMM6 304
#define STR_NUMM7 305
#define STR_NUMM8 306
#define STR_NUMM9 307
#define STR_XunBiaoSuDu 308

const static u8 LabelText_1[]={
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
"长度设定\0"
"（毫米）\0"
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
"复位\0"
"参数设置\0"
"系统设置\0"
"设定\0"
"上一页\0"
"下一页\0"
"主页\0"
"机型选择:\0"
"1.不停\0"
"2.暂停\0"
"3.停机\0"
"4.多批脱袋\0"
"先切后送\0"
"先送后切\0"
"整本预置\0"
"暂停时间\0"
"送料速度\0"
"频率上限\0"
"胶辊周长\0"
"色标范围\0"
"点进速度\0"
"主机系数\0"
"放料系数\0"
"手动放料\0"
"整圈步数\0"
"出料转速\0"
"高位延时\0"
"打孔延时\0"
"打孔时间\0"
"脱标个数\0"
"报警个数\0"
"脱袋延时\0"
"脱袋时间\0"
"加速菜单\0"
"送料方式:\0"
"占空比例\0"
"手动\0"
"自动\0"
"屏幕校准\0"
"横吹时间\0"
"竖吹时间\0"
"补料长度\0"
"后退长度\0"
"加速时间\0"
"伺服转速\0"
"补料参数\0"
"超声波延时\0"
"曲线(默认为5)\0"
"末速\0"
"初速\0"
"减速因子\0"
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
"X01@送料\0"
"X02@极限\0"
"X03@光电\0"
"X04@\0"
"X05@加速\0"
"X06@减速\0"
"X07@启动\0"
"X08@停止\0"
"X09\0"
"X10\0"
"X11\0"
"X12\0"
"X13\0"
"X14\0"
"X15\0"
"X16\0"
"Y01@脉冲\0"
"Y02@脉冲2\0"
"Y03@\0"
"Y04@方向\0"
"Y05@方向2\0"
"Y06@\0"
"Y07@主机\0"
"Y08@放料\0"
"Y09@打孔\0"
"Y10@脱袋\0"
"Y11@超声\0"
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
"输入传感器逻辑关系图\0"
"底刀\0"
"切刀\0"
"图\0"
"外部接线图\0"
"不停/暂停/停机：“不停”：当一批料送结束时，主机不停机，继续正常工@                  作。@                “暂停”：一批结束主机暂停，停到暂停时间结束，主机@                  自动开机。@                “停机”：一批结束主机自动停机后不再运行，手动按启@                  动键方可运行。\0"
"先切后送/先送后切：“先切后送”：按启动键，主机先运行，GK1霍尔开@                关检测到伺服（步进）电机的送料信号，电机开始送料。@                “先送后切”：按启动键，伺服（步进）先送料，送料结@                束后主机再运行。\0"
"恢复出厂：按此键恢复出厂设置（慎用）。@整本预置：一批设定的个数，提前5个报警。单位：个@暂停时间：当机型选择暂停，一批结束后主机自动停机所设定的时间。@点进速度：1，在停止状态下，手动点进伺服（步进）电机运转的恒定@             速度。\0"
"1. 开始送料位置，此时切刀向上运动，刚离开底刀1厘米左右的位置，放一@   个磁铁。（图1）@2. 拖料极限位置，此时切刀向下运动，刚到底刀处的位置，放一个磁铁。@   （图2）\0"
"请看下面两页，分别为HLD-800输出端口和输入端口的接线图。\0"
"我是挡箭牌2，步进发脉冲时，第一个脉冲的频率。@          3，设置彩色时，寻标的速度。@送料速度：伺服（步进）电机的加减速时间，设定越大，伺服（步进）电机@          起步越快。\0"
"高位延时：在停机的时候，主机上升的最高位的位置。该设定值越大，停的位置@          越高。@曲线：伺服（步进）电机的加减速快慢，设定值越小，伺服（步进）电机加@      速越快。\0"
"色标范围：制作彩色制品时，伺服（步进）电机以恒定速度寻找色标点的范@围（即光电在『长度-此设定值』至『长度+此设定值』范围内寻找色标）。@脱标个数：设定N个，制作彩色制品时，跟踪N次色标点跟踪不住自动停机。@出料速度：出料输送带的速度快慢调节。\0"
"胶辊周长：伺服（步进）电机带动橡胶辊转一圈的长度。@打孔时间：伺服（步进）电机转结束，打孔电磁阀工作的时间。@主机系数：调节主机速度和实际测速之间的误差，设定值越大，主机转速@          越快（测速越大）。\0"
"开关电源\0"
"光电眼\0"
"送料霍尔\0"
"超速霍尔\0"
"黑\0"
"红\0"
"蓝\0"
"棕\0"
"白（绿）\0"
"启动\0"
"输入\0"
"蜂鸣器\0"
"变频器\0"
"步进电机\0"
"继电器\0"
"直流调速板\0"
"驱动器\0"
"励磁\0"
"直流电机\0"
"说明书\0"
"步进快速\0"
"步进慢速\0"
"伺服快速\0"
"伺服慢速\0"
"静电延时\0"
"出料速度\0"
"输送延时\0"
"输送时间\0"
"后放料速度2\0"
"系统校正\0"
"补片和顶料界面\0"
"补片长度\0"
"补片周长\0"
"频率上限2\0"
"送料速度2\0"
"0.点进\0"
"1.点退\0"
"2.主机+\0"
"3.主机-\0"
"4.放料+\0"
"5.放料-\0"
"6.放料2+\0"
"7.放料2-\0"
"8.加速2\0"
"9.减速2\0"
"10.横吹开关\0"
"11.竖吹开关\0"
"12.预退\0"
"13.断料\0"
"14.堵料开关\0"
"15.补片拉断\0"
"16.补数\0"
"17.计数暂停\0"
"0.输送\0"
"1.打孔2\0"
"2.放料开关2\0"
"3.平吹\0"
"4.顶料\0"
"5.静电\0"
"6.横吹输出\0"
"7.竖吹输出\0"
"8.二段速\0"
"9.伺服清零\0"
"10.蜂鸣器\0"
"11.脱袋提前\0"
"多功能端子\0"
"输入端子\0"
"输出端子\0"
"打孔延时2\0"
"打孔时间2\0"
"顶料个数\0"
"脱袋批数\0"
"多走长度\0"
"回缩长度\0"
"预退长度\0"
"拉断长度\0"
"堵料时间\0"
"起步快慢：\0"
"0.60\0"
"0.62\0"
"0.64\0"
"0.66\0"
"0.68\0"
"0.70\0"
"0.72\0"
"0.74\0"
"0.76\0"
"0.78\0"
"0.80\0"
"0.82\0"
"0.84\0"
"0.86\0"
"0.88\0"
"0.90\0"
"秒\0"
"点进\0"
"点退\0"
"主机+\0"
"主机-\0"
"放料+\0"
"放料-\0"
"放料2+\0"
"放料2-\0"
"加速2\0"
"减速2\0"
"横吹\0"
"竖吹\0"
"预退\0"
"断料\0"
"堵料\0"
"拉断\0"
"补数\0"
"计停\0"
"输送\0"
"打孔2\0"
"放料2\0"
"平吹\0"
"顶料\0"
"静电\0"
"横吹\0"
"竖吹\0"
"二段\0"
"清零\0"
"蜂鸣\0"
"提前\0"
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
"寻标速度\0"
};

const static u8 LabelText_2[]={
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
"LENGTH\0"
"(mm)\0"
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
"RESET\0"
"PAR SET\0"
"SYSTEM SET\0"
"SET\0"
"LAST\0"
"NEXT\0"
"HOME\0"
"TYPE:\0"
"NOT STOP\0"
"PAUSE\0"
"STOP\0"
"MULTI DRAG\0"
"FIRST CUT\0"
"FIRST FEED\0"
"COUNT\0"
"PAUSE TIME\0"
"FEEDING SPEED\0"
"TOP FREQUENCY\0"
"ROLLER GIRTH\0"
"COLOR SCOPE\0"
"JOG SPEED\0"
"MAIN FACTOR\0"
"DISCHARGE FACTOR\0"
"MANUAL DIS\0"
"STEPS CIRCLE\0"
"OUT SPEED\0"
"STOP DELAY\0"
"PUNCH DELAY\0"
"PUNCH TIME\0"
"LOSING NUMBER\0"
"ALARM NUMBER\0"
"DRAG DELAY\0"
"DRAG TIME\0"
"THIRD\0"
"MODE:\0"
"DUTY RATIO\0"
"MANUAL\0"
"AUTO\0"
"ADJUST\0"
"H BLOWTIME\0"
"V BLOWTIME\0"
"LOADING\0"
"BACKING\0"
"ACCELERATION\0"
"ROTATION\0"
"PARAMETER\0"
"ULTRASONIC\0"
"CURVE\0"
"Stop Speed\0"
"Start Speed\0"
"Decelerate Coef\0"
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
"Logical Diagram of Input Sensor\0"
"Bottom@knife\0"
"Cutting@ knife\0"
"pic\0"
"External Wiring Diagram\0"
"NOT STOP / PAUSE/ STOP: ' NOT STOP': A number of end host does@ not stop, continue to work properly.@'PAUSE': A number of end host pause, stop to pause time, the host@ automatically boot.@'STOP': A number of end host automatically shutdown is no longer@ running, manual press the start button to be run.\0"
"FIRST CUT / FIRST FEED: 'FIRST CUT': Press the start button, the@ host first run, GK1 Holzer detect material signals of the motor,@ motor begin feeding.@'FIRST FEED': press start button, motor feed first,then host run.\0"
"RECOVER: Click this button to restore the factory settings.@COUNT: A number of set number, advance 5 alarm.@PAUSE TIME: When the choice of models suspended, a number of end@ host automatically shut down after the set time.@JOG SPEED: 1.Constant speed of manual jogging motor when stop.\0"
"1.At the start position of feeding material,the cutting knife is @ moving up, just leave the bottom knife about 1 cm, put a magnet.@2.At pull material limit position, the cutting knife is moving@ down,just arrive to the bottom knife, put a magnet.\0"
"Please see the following two page,respectively for the wiring@ diagram of HLD-800 output port and the input port.\0"
"2. The frequency of first pulse transmitted.@3. The speed of seeking mark when multicolour is set.@FEEDING SPEED: Servo motor acceleration and deceleration time,@ set more big, servo motor (stepper) starts more quickly.\0"
"STOP DELAY: The highest position of host stops when stops.The@ set value is bigger,it stops higher.@CURVE: Servo (stepper) motor acceleration and deceleration speed, @set value is smaller,the servo motor (stepper) accelerates faster.\0"
"COLOR LABEL SCOPE: When making colorful products, servo (stepping)@ motor seeks the colored punctuation in a range by this parameter.@LOSING NUMBER: If tracking N punctuation failed,then shutdown.@OUT SPEED: Adjust the speed of discharge conveyor.\0"
"ROLLER GIRTH:The girth of rubber roller.@PUNCH TIME: The time of punch EM valve working after motor stops. @MAIN FACTOR: The regulation error factor of speed, set value is@ bigger, the engine speed is faster.\0"
"SMPS\0"
"photoelectric eye\0"
"feeding@ Hall\0"
"overspeed@  Hall\0"
"black\0"
"red\0"
"blue\0"
"brown\0"
"white@(green)\0"
"START\0"
"input\0"
"BEEP\0"
"inverter\0"
"stepping@ motor\0"
"relay\0"
"DC speed@control board\0"
"driver\0"
"excite\0"
"DC Motor\0"
"Manual\0"
"STEP FAST\0"
"STEP SLOW\0"
"SERVO FAST\0"
"SERVO SLOW\0"
"ESD DELAY\0"
"OUT SPEED\0"
"CONVEY DELAY\0"
"CONVEY TIME\0"
"PUT VEL 2\0"
"SYS ADJUST\0"
"PATCH PRESS PAGE\0"
"PATCH LENGTH\0"
"PATCH GIRTH\0"
"TOP FREQUENCY2\0"
"FEEDING SPEED2\0"
"0.FORWARD\0"
"1.BACKWARD\0"
"2.MASTER+\0"
"3.MASTER-\0"
"4.DIS+\0"
"5.DIS-\0"
"6.DIS2+\0"
"7.DIS2-\0"
"8.FEED2+\0"
"9.FEED2-\0"
"10.H BLOW\0"
"11.V BLOW\0"
"12.PRE BACK\0"
"13.BREAK\0"
"14.BLOCKING\0"
"15.PATCH SNAP\0"
"16.COMPLEMENT\0"
"17.COUNT PAUSE\0"
"0.CONVEY\0"
"1.PUNCH 2\0"
"2.DIS 2\0"
"3.FLAT BLOW\0"
"4.PRESS\0"
"5.ESD\0"
"6.H BLOW\0"
"7.V BLOW\0"
"8.TWO STAGE\0"
"9.CLEAR\0"
"10.BUZZER\0"
"11.PRE-DRAG\0"
"MULTI PORT\0"
"input port\0"
"output port\0"
"PUNCH DELAY2\0"
"PUNCH TIME2\0"
"PRESS COUNT\0"
"DRAG BATCH\0"
"MORE LENGTH\0"
"BACK LENGTH\0"
"PULL LENGTH\0"
"SNAP LENGTH\0"
"BLOCKING TIME\0"
"START SPEED:\0"
"0.60\0"
"0.62\0"
"0.64\0"
"0.66\0"
"0.68\0"
"0.70\0"
"0.72\0"
"0.74\0"
"0.76\0"
"0.78\0"
"0.80\0"
"0.82\0"
"0.84\0"
"0.86\0"
"0.88\0"
"0.90\0"
"s\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
"\0"
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
"SEEK_SPEED\0"
};

const static u16 LabelIndex_1[]={
0,
1,3,5,7,9,11,13,15,17,19,
21,23,25,27,29,31,33,35,43,51,
61,71,81,86,95,106,112,118,127,136,
141,146,151,156,161,166,171,180,189,194,
199,204,209,214,221,228,233,238,243,252,
261,266,273,280,285,295,302,309,316,327,
336,345,354,363,372,381,390,399,408,417,
426,435,444,453,462,471,480,489,498,507,
516,525,535,544,549,554,563,572,581,590,
599,608,617,626,637,651,656,661,670,675,
682,687,692,697,702,707,712,721,730,740,
749,760,771,776,785,794,803,812,821,826,
835,844,853,862,866,870,874,878,882,886,
890,894,903,913,918,927,937,942,951,960,
969,978,987,991,995,999,1003,1007,1016,1025,
1034,1044,1053,1061,1067,1087,1093,1103,1113,1134,
1139,1144,1147,1158,1444,1676,1908,2071,2127,2299,
2469,2707,2909,2918,2925,2934,2943,2946,2949,2952,
2955,2964,2969,2974,2981,2988,2997,3004,3015,3022,
3027,3036,3043,3052,3061,3070,3079,3088,3097,3106,
3115,3127,3136,3151,3160,3169,3179,3189,3196,3203,
3211,3219,3227,3235,3244,3253,3261,3269,3281,3293,
3301,3309,3321,3333,3341,3353,3360,3368,3380,3387,
3394,3401,3412,3423,3432,3443,3453,3465,3476,3485,
3494,3504,3514,3523,3532,3541,3550,3559,3568,3577,
3588,3593,3598,3603,3608,3613,3618,3623,3628,3633,
3638,3643,3648,3653,3658,3663,3668,3671,3676,3681,
3687,3693,3699,3705,3712,3719,3725,3731,3736,3741,
3746,3751,3756,3761,3766,3771,3776,3782,3788,3793,
3798,3803,3808,3813,3818,3823,3828,3833,3835,3837,
3839,3841,3843,3845,3847,3849,3851,3853,};

const static u16 LabelIndex_2[]={
0,1,
3,5,7,9,11,13,15,17,19,21,
23,25,27,29,31,33,35,40,45,57,
69,81,87,96,104,111,117,124,129,135,
141,146,153,157,162,169,176,183,188,192,
200,206,215,224,233,239,248,254,262,273,
277,282,287,292,298,307,313,318,329,339,
350,356,367,381,395,408,420,430,442,459,
470,483,493,504,516,527,541,554,565,575,
581,587,598,605,610,617,628,639,647,655,
668,677,687,698,704,715,727,743,747,754,
760,764,770,774,779,783,792,801,812,822,
833,844,851,861,869,873,877,881,885,889,
893,897,901,905,909,913,917,921,925,929,
933,937,941,945,949,953,957,961,965,969,
973,977,981,985,989,993,997,1002,1006,1010,
1015,1029,1043,1048,1069,1078,1091,1098,1130,1143,
1158,1162,1186,1490,1709,1995,2243,2357,2577,2811,
3059,3268,3273,3291,3305,3322,3328,3332,3337,3343,
3357,3363,3369,3374,3383,3399,3405,3428,3435,3442,
3451,3458,3468,3478,3489,3500,3510,3520,3533,3545,
3555,3566,3583,3596,3608,3623,3638,3648,3659,3669,
3679,3686,3693,3701,3709,3718,3727,3737,3747,3759,
3768,3780,3794,3808,3823,3832,3842,3850,3862,3870,
3876,3885,3894,3906,3914,3924,3936,3947,3958,3970,
3983,3995,4007,4018,4030,4042,4054,4066,4080,4093,
4098,4103,4108,4113,4118,4123,4128,4133,4138,4143,
4148,4153,4158,4163,4168,4173,4175,4176,4177,4178,
4179,4180,4181,4182,4183,4184,4185,4186,4187,4188,
4189,4190,4191,4192,4193,4194,4195,4196,4197,4198,
4199,4200,4201,4202,4203,4204,4205,4207,4209,4211,
4213,4215,4217,4219,4221,4223,4225,};
const static u16* pLabelIndex[] = {
LabelIndex_1,
LabelIndex_2,
};
const static u8* pLabelText[] = {
LabelText_1,
LabelText_2,
};

#endif
