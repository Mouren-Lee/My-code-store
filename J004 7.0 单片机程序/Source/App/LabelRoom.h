#ifndef _LABELROOM_H_
#define _LABELROOM_H_

#define STRING_COUNT 320
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
#define STR_GE 28
#define STR_GEMEIPI 29
#define STR_BATCH 30
#define STR_HEZI 31
#define STR_CHANGDUSHEDINGMM 32
#define STR_HAOMI 33
#define STR_Second 34
#define STR_COLOR1 35
#define STR_COLOR2 36
#define STR_COLOR3 37
#define STR_XUNBIAO 38
#define STR_DIANJIN 39
#define STR_DIANTUI 40
#define STR_BUSHU 41
#define STR_STATUSHOW 42
#define STR_ZHUANGTAIXIANSHI 43
#define STR_STOP 44
#define STR_RUN 45
#define STR_CHAOSU 46
#define STR_ZANTING 47
#define STR_TUOBIAO 48
#define STR_SYSTEM1 49
#define STR_SYSTEM2 50
#define STR_DUANLIAO 51
#define STR_DULIAO 52
#define STR_KongQie 53
#define STR_FUWEI 54
#define STR_SETPAR 55
#define STR_XITONGSHEZHI 56
#define STR_SHEDING 57
#define STR_SHANGYIYE 58
#define STR_XIAYIYE 59
#define STR_ZHUYE 60
#define STR_JIXINGXUANZE 61
#define STR_JIXING1 62
#define STR_JIXING2 63
#define STR_JIXING3 64
#define STR_JIXING4 65
#define STR_JIXING5 66
#define STR_XIANQIEHOUSONG 67
#define STR_XIANSONGHOUQIE 68
#define STR_ZHENGBENYUZHI 69
#define STR_ZANTINGSHIJIAN 70
#define STR_SONGLIAOSUDU 71
#define STR_ZUIGAOPINLV 72
#define STR_JIAOGUNZHOUCHANG 73
#define STR_SEBIAOFANWEI 74
#define STR_DIANJINSUDU 75
#define STR_ZHUJIXISHU 76
#define STR_FANGLIAOXISHU 77
#define STR_SHOUDONGFANGLIAO 78
#define STR_ZHENGQUANBUSHU 79
#define STR_CHULIAOZHUANSU 80
#define STR_GAOWEIYANSHI 81
#define STR_DAKONGYANSHI 82
#define STR_DAKONGSHIJIAN 83
#define STR_TUOBIAOGESHU 84
#define STR_BAOJINGGESHU 85
#define STR_TUODAIYANSHI 86
#define STR_TUODAISHIJIAN 87
#define STR_JIASUCAIDAN 88
#define STR_FANGSHI 89
#define STR_ZHANKONGBILI 90
#define STR_SHOUDONGZIDONG 91
#define STR_ZIDONGSHOUDONG 92
#define STR_PINGMUJIAOZHUN 93
#define STR_HENGCHUISHI 94
#define STR_SHUCHUISHI 95
#define STR_BULIAOCHANGDU 96
#define STR_HOUTUICHANGDU 97
#define STR_JIASUSHIJIAN 98
#define STR_SIFUZHUANSU 99
#define STR_BULIAOCANSHU 100
#define STR_CHAOSHENGYANSHI 101
#define STR_QUXIAN 102
#define STR_Stop 103
#define STR_Start 104
#define STR_DecCoef 105
#define STR_ZHUCAIDAN 106
#define STR_FUCAIDAN 107
#define STR_JIANSHICHUANGKOU 108
#define STR_XITONGJIANJIE 109
#define STR_ENTER 110
#define STR_CLR 111
#define STR_BACK 112
#define STR_ESC 113
#define STR_TOPIC_SYSTEM1 114
#define STR_TOPIC_SYSTEM2 115
#define STR_SETCOLOK 116
#define STR_CLOCKSET 117
#define STR_MIMA1 118
#define STR_MIMA2 119
#define STR_RETURN 120
#define STR_BAOCUNSHUJU 121
#define STR_HUIFUCHUCHANG 122
#define STR_X01 123
#define STR_X02 124
#define STR_X03 125
#define STR_X04 126
#define STR_X05 127
#define STR_X06 128
#define STR_X07 129
#define STR_X08 130
#define STR_X09 131
#define STR_X10 132
#define STR_X11 133
#define STR_X12 134
#define STR_X13 135
#define STR_X14 136
#define STR_X15 137
#define STR_X16 138
#define STR_Y01 139
#define STR_Y02 140
#define STR_Y03 141
#define STR_Y04 142
#define STR_Y05 143
#define STR_Y06 144
#define STR_Y07 145
#define STR_Y08 146
#define STR_Y09 147
#define STR_Y10 148
#define STR_Y11 149
#define STR_Y12 150
#define STR_Y13 151
#define STR_Y14 152
#define STR_Y15 153
#define STR_Y16 154
#define STR_ZHUJIMONI 155
#define STR_FANGLIAOMONI 156
#define STR_CHULIAOMONI 157
#define STR_FANGLIAOMONI2 158
#define STR_FANGLIAOJIASUKUAIMAN 159
#define STR_SHENGCHANSHANG 160
#define STR_DIANHUA 161
#define STR_CANSHUSHEZHI5 162
#define STR_CHUCHANG 163
#define STR_CHUCHANGBIANHAO 164
#define STR_RUANJIANBANBEN 165
#define STR_CHUANGANLUOJITU 166
#define STR_DIDAO 167
#define STR_QIEDAO 168
#define STR_PICTURE 169
#define STR_WAIBUJIEXIANTU 170
#define STR_ZHUCAIDAN1 171
#define STR_ZHUCAIDAN2 172
#define STR_ZHUCAIDAN3 173
#define STR_LUOJIGUANXI 174
#define STR_JIEXIANSHUOMING 175
#define STR_ZHUCAIDAN4 176
#define STR_ZHUCAIDAN5 177
#define STR_ZHUCAIDAN6 178
#define STR_ZHUCAIDAN7 179
#define STR_KAIGUANDIANYUAN 180
#define STR_GUANGDIANYAN 181
#define STR_SONGLIAOHUOER 182
#define STR_CHAOSUHUOER 183
#define STR_BLACK 184
#define STR_RED 185
#define STR_BLUE 186
#define STR_BROWN 187
#define STR_WG 188
#define STR_START 189
#define STR_SHURU 190
#define STR_BEEP 191
#define STR_BIANPINQI 192
#define STR_BUJINDIANJI 193
#define STR_JIDIANQI 194
#define STR_TIAOSUBAN 195
#define STR_QUDONGQI 196
#define STR_LICI 197
#define STR_ZHILIUDIANJI 198
#define STR_SHUOMINGSHU 199
#define STR_BUJINKUAISU 200
#define STR_BUJINMANSU 201
#define STR_SIFUKUAI 202
#define STR_SIFUMAN 203
#define STR_JINGDIANYANSHI 204
#define STR_CHULIAOSUDU 205
#define STR_TUODAIYANSHI2 206
#define STR_TUODAISHIJIAN2 207
#define STR_FANGLIAOSUDU2 208
#define STR_XITONGJIAOZHENG 209
#define STR_BUPIANJIEMIAN 210
#define STR_BUPIANCHANGDU 211
#define STR_JIAOGUNZHOUCHANG2 212
#define STR_ZUIGAOPINLV2 213
#define STR_SONGLIAOSUDU2 214
#define STR_REVIN0 215
#define STR_REVIN1 216
#define STR_REVIN2 217
#define STR_REVIN3 218
#define STR_REVIN4 219
#define STR_REVIN5 220
#define STR_REVIN6 221
#define STR_REVIN7 222
#define STR_REVIN8 223
#define STR_REVIN9 224
#define STR_REVIN10 225
#define STR_REVIN11 226
#define STR_REVIN12 227
#define STR_REVIN13 228
#define STR_REVIN14 229
#define STR_REVIN15 230
#define STR_REVIN16 231
#define STR_REVIN17 232
#define STR_REVOUT0 233
#define STR_REVOUT1 234
#define STR_REVOUT2 235
#define STR_REVOUT3 236
#define STR_REVOUT4 237
#define STR_REVOUT5 238
#define STR_REVOUT6 239
#define STR_REVOUT7 240
#define STR_REVOUT8 241
#define STR_REVOUT9 242
#define STR_REVOUT10 243
#define STR_REVOUT11 244
#define STR_DUOGONGNENG 245
#define STR_DUOGONGNENGSHURU 246
#define STR_DUOGONGNENGSHUCHU 247
#define STR_DAKONGYANSHI2 248
#define STR_DAKONGSHIJIAN2 249
#define STR_DINGLIAOGESHU 250
#define STR_TUODAIPISHU 251
#define STR_DUOZOUCHANGDU 252
#define STR_TuiLiaoChangDu 253
#define STR_TuoDaiZhiHou 254
#define STR_TINGCHETUILIAO 255
#define STR_LALIAOCHANGDU 256
#define STR_LADUANCHANGDU 257
#define STR_DULIAOSHIJIAN 258
#define STR_QIBUKUAIMAN 259
#define STR_Curve_6_0 260
#define STR_Curve_6_2 261
#define STR_Curve_6_4 262
#define STR_Curve_6_6 263
#define STR_Curve_6_8 264
#define STR_Curve_7_0 265
#define STR_Curve_7_2 266
#define STR_Curve_7_4 267
#define STR_Curve_7_6 268
#define STR_Curve_7_8 269
#define STR_Curve_8_0 270
#define STR_Curve_8_2 271
#define STR_Curve_8_4 272
#define STR_Curve_8_6 273
#define STR_Curve_8_8 274
#define STR_Curve_9_0 275
#define STR_MIAO 276
#define STR_XS0 277
#define STR_XS1 278
#define STR_XS2 279
#define STR_XS3 280
#define STR_XS4 281
#define STR_XS5 282
#define STR_XS6 283
#define STR_XS7 284
#define STR_XS8 285
#define STR_XS9 286
#define STR_XS10 287
#define STR_XS11 288
#define STR_XS12 289
#define STR_XS13 290
#define STR_XS14 291
#define STR_XS15 292
#define STR_XS16 293
#define STR_XS17 294
#define STR_YS0 295
#define STR_YS1 296
#define STR_YS2 297
#define STR_YS3 298
#define STR_YS4 299
#define STR_YS5 300
#define STR_YS6 301
#define STR_YS7 302
#define STR_YS8 303
#define STR_YS9 304
#define STR_YS10 305
#define STR_YS11 306
#define STR_XunBiaoSpeed 307
#define STR_BackSpeed 308
#define STR_CM 309
#define STR_NUMM0 310
#define STR_NUMM1 311
#define STR_NUMM2 312
#define STR_NUMM3 313
#define STR_NUMM4 314
#define STR_NUMM5 315
#define STR_NUMM6 316
#define STR_NUMM7 317
#define STR_NUMM8 318
#define STR_NUMM9 319

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
"����/����\0"
"����/����\0"
"����/����\0"
"����\0"
"�����ٶ�\0"
"������ٶ�\0"
"����:\0"
"ת/��\0"
"��\0"
"��/��\0"
"��\0"
"Hz\0"
"�����趨\0"
"�����ף�\0"
"���룩\0"
"�հ�\0"
"׷ǳ\0"
"׷��\0"
"Ѱ��\0"
"���\0"
"����\0"
"����\0"
"����״̬\0"
"״̬��ʾ\0"
"ֹͣ\0"
"����\0"
"����\0"
"��ͣ\0"
"�ѱ�\0"
"ϵͳ1:\0"
"ϵͳ2:\0"
"����\0"
"����\0"
"����\0"
"��λ\0"
"��������\0"
"ϵͳ����\0"
"�趨\0"
"��һҳ\0"
"��һҳ\0"
"��ҳ\0"
"����ѡ��:\0"
"1.��ͣ\0"
"2.��ͣ\0"
"3.ͣ��\0"
"4.�����Ѵ�\0"
"5.�����Ѵ�\0"
"���к���\0"
"���ͺ���\0"
"����Ԥ��\0"
"��ͣʱ��\0"
"�����ٶ�\0"
"Ƶ������\0"
"�����ܳ�\0"
"ɫ�귶Χ\0"
"����ٶ�\0"
"����ϵ��\0"
"����ϵ��\0"
"�ֶ�����\0"
"��Ȧ����\0"
"����ת��\0"
"��λ��ʱ\0"
"�����ʱ\0"
"���ʱ��\0"
"�ѱ����\0"
"��������\0"
"�Ѵ���ʱ\0"
"�Ѵ�ʱ��\0"
"���ٲ˵�\0"
"���Ϸ�ʽ:\0"
"ռ�ձ���\0"
"�ֶ�\0"
"�Զ�\0"
"��ĻУ׼\0"
"�ᴵʱ��\0"
"����ʱ��\0"
"���ϳ���\0"
"���˳���\0"
"����ʱ��\0"
"�ŷ�ת��\0"
"���ϲ���\0"
"��������ʱ\0"
"����(Ĭ��Ϊ5)\0"
"ĩ��\0"
"����\0"
"��������\0"
"����\0"
"���˵�\0"
"���\0"
"���\0"
"ȷ��\0"
"���\0"
"����\0"
"ȡ��\0"
"ϵ  ͳ1:\0"
"ϵ  ͳ2:\0"
"У׼ʱ��:\0"
"У׼ʱ��\0"
"�޸�����1:\0"
"�޸�����2:\0"
"����\0"
"��������\0"
"�ָ�����\0"
"X01\n����\0"
"X02\n����\0"
"X03\n���\0"
"X04\n\0"
"X05\n����\0"
"X06\n����\0"
"X07\n����\0"
"X08\nֹͣ\0"
"X09\0"
"X10\0"
"X11\0"
"X12\0"
"X13\0"
"X14\0"
"X15\0"
"X16\0"
"Y01\n����\0"
"Y02\n����2\0"
"Y03\n\0"
"Y04\n����\0"
"Y05\n����2\0"
"Y06\n\0"
"Y07\n����\0"
"Y08\n����\0"
"Y09\n���\0"
"Y10\n�Ѵ�\0"
"Y11\n����\0"
"Y12\0"
"Y13\0"
"Y14\0"
"Y15\0"
"Y16\0"
"����ģ��\0"
"����ģ��\0"
"����ģ��\0"
"����ģ��2\0"
"��������\0"
"������:\0"
"�绰:\0"
"��������5���Ӻ󱣴�\0"
"����:\0"
"�������:\0"
"����汾:\0"
"���봫�����߼���ϵͼ\0"
"�׵�\0"
"�е�\0"
"ͼ\0"
"�ⲿ����ͼ\0"
"��ͣ/��ͣ/ͣ��������ͣ������һ�����ͽ���ʱ��������ͣ��������������\n                  ����\n                ����ͣ����һ������������ͣ��ͣ����ͣʱ�����������\n                  �Զ�������\n                ��ͣ������һ�����������Զ�ͣ���������У��ֶ�����\n                  �����������С�\0"
"���к���/���ͺ��У������к��͡����������������������У�GK1������\n                �ؼ�⵽�ŷ�������������������źţ������ʼ���ϡ�\n                �����ͺ��С��������������ŷ��������������ϣ����Ͻ�\n                �������������С�\0"
"�ָ����������˼��ָ��������ã����ã���\n����Ԥ�ã�һ���趨�ĸ�������ǰ5����������λ����\n��ͣʱ�䣺������ѡ����ͣ��һ�������������Զ�ͣ�����趨��ʱ�䡣\n����ٶȣ�1����ֹͣ״̬�£��ֶ�����ŷ��������������ת�ĺ㶨\n             �ٶȡ�\0"
"1. ��ʼ����λ�ã���ʱ�е������˶������뿪�׵�1�������ҵ�λ�ã���һ\n   ����������ͼ1��\n2. ���ϼ���λ�ã���ʱ�е������˶����յ��׵�����λ�ã���һ��������\n   ��ͼ2��\0"
"�뿴������ҳ���ֱ�ΪHLD-800����˿ں�����˿ڵĽ���ͼ��\0"
"���ǵ�����2������������ʱ����һ�������Ƶ�ʡ�\n          3�����ò�ɫʱ��Ѱ����ٶȡ�\n�����ٶȣ��ŷ�������������ļӼ���ʱ�䣬�趨Խ���ŷ������������\n          ��Խ�졣\0"
"��λ��ʱ����ͣ����ʱ���������������λ��λ�á����趨ֵԽ��ͣ��λ��\n          Խ�ߡ�\n���ߣ��ŷ�������������ļӼ��ٿ������趨ֵԽС���ŷ��������������\n      ��Խ�졣\0"
"ɫ�귶Χ��������ɫ��Ʒʱ���ŷ�������������Ժ㶨�ٶ�Ѱ��ɫ���ķ�\nΧ��������ڡ�����-���趨ֵ����������+���趨ֵ����Χ��Ѱ��ɫ�꣩��\n�ѱ�������趨N����������ɫ��Ʒʱ������N��ɫ�����ٲ�ס�Զ�ͣ����\n�����ٶȣ��������ʹ����ٶȿ������ڡ�\0"
"�����ܳ����ŷ�����������������𽺹�תһȦ�ĳ��ȡ�\n���ʱ�䣺�ŷ������������ת��������׵�ŷ�������ʱ�䡣\n����ϵ�������������ٶȺ�ʵ�ʲ���֮������趨ֵԽ������ת��\n          Խ�죨����Խ�󣩡�\0"
"���ص�Դ\0"
"�����\0"
"���ϻ���\0"
"���ٻ���\0"
"��\0"
"��\0"
"��\0"
"��\0"
"�ף��̣�\0"
"����\0"
"����\0"
"������\0"
"��Ƶ��\0"
"�������\0"
"�̵���\0"
"ֱ�����ٰ�\0"
"������\0"
"����\0"
"ֱ�����\0"
"˵����\0"
"��������\0"
"��������\0"
"�ŷ�����\0"
"�ŷ�����\0"
"������ʱ\0"
"�����ٶ�\0"
"������ʱ\0"
"����ʱ��\0"
"������ٶ�2\0"
"ϵͳУ��\0"
"��Ƭ�Ͷ��Ͻ���\0"
"��Ƭ����\0"
"��Ƭ�ܳ�\0"
"Ƶ������2\0"
"�����ٶ�2\0"
"0.���\0"
"1.����\0"
"2.����+\0"
"3.����-\0"
"4.����+\0"
"5.����-\0"
"6.����2+\0"
"7.����2-\0"
"8.����2\0"
"9.����2\0"
"10.�ᴵ����\0"
"11.��������\0"
"12.Ԥ��\0"
"13.����\0"
"14.���Ͽ���\0"
"15.��Ƭ����\0"
"16.����\0"
"17.������ͣ\0"
"0.����\0"
"1.���2\0"
"2.���Ͽ���2\0"
"3.ƽ��\0"
"4.����\0"
"5.����\0"
"6.�ᴵ���\0"
"7.�������\0"
"8.������\0"
"9.�ŷ�����\0"
"10.������\0"
"11.�Ѵ���ǰ\0"
"�๦�ܶ���\0"
"�������\0"
"�������\0"
"�����ʱ2\0"
"���ʱ��2\0"
"���ϸ���\0"
"�Ѵ�����\0"
"���߳���\0"
"���ϳ���\0"
"�Ѵ��ͺ�\0"
"��������\0"
"Ԥ�˳���\0"
"���ϳ���\0"
"����ʱ��\0"
"�𲽿�����\0"
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
"��\0"
"���\0"
"����\0"
"����+\0"
"����-\0"
"����+\0"
"����-\0"
"����2+\0"
"����2-\0"
"����2\0"
"����2\0"
"�ᴵ\0"
"����\0"
"Ԥ��\0"
"����\0"
"����\0"
"����\0"
"����\0"
"��ͣ\0"
"����\0"
"���2\0"
"����2\0"
"ƽ��\0"
"����\0"
"����\0"
"�ᴵ\0"
"����\0"
"����\0"
"����\0"
"����\0"
"��ǰ\0"
"Ѱ���ٶ�\0"
"�����ٶ�\0"
"�����к������Զ���������\0"
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
"Ӣ��\0"
"����\0"
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
"TYPE:\0"
"NOT STOP\0"
"PAUSE\0"
"STOP\0"
"MULTI DRAG\0"
"EmptyCut DRAG\0"
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
"Bottom\nknife\0"
"Cutting\n knife\0"
"pic\0"
"External Wiring Diagram\0"
"NOT STOP / PAUSE/ STOP: ' NOT STOP': A number of end host does\n not stop, continue to work properly.\n'PAUSE': A number of end host pause, stop to pause time, the host\n automatically boot.\n'STOP': A number of end host automatically shutdown is no longer\n running, manual press the start button to be run.\0"
"FIRST CUT / FIRST FEED: 'FIRST CUT': Press the start button, the\n host first run, GK1 Holzer detect material signals of the motor,\n motor begin feeding.\n'FIRST FEED': press start button, motor feed first,then host run.\0"
"RECOVER: Click this button to restore the factory settings.\nCOUNT: A number of set number, advance 5 alarm.\nPAUSE TIME: When the choice of models suspended, a number of end\n host automatically shut down after the set time.\nJOG SPEED: 1.Constant speed of manual jogging motor when stop.\0"
"1.At the start position of feeding material,the cutting knife is \n moving up, just leave the bottom knife about 1 cm, put a magnet.\n2.At pull material limit position, the cutting knife is moving\n down,just arrive to the bottom knife, put a magnet.\0"
"Please see the following two page,respectively for the wiring\n diagram of HLD-800 output port and the input port.\0"
"2. The frequency of first pulse transmitted.\n3. The speed of seeking mark when multicolour is set.\nFEEDING SPEED: Servo motor acceleration and deceleration time,\n set more big, servo motor (stepper) starts more quickly.\0"
"STOP DELAY: The highest position of host stops when stops.The\n set value is bigger,it stops higher.\nCURVE: Servo (stepper) motor acceleration and deceleration speed, \nset value is smaller,the servo motor (stepper) accelerates faster.\0"
"COLOR LABEL SCOPE: When making colorful products, servo (stepping)\n motor seeks the colored punctuation in a range by this parameter.\nLOSING NUMBER: If tracking N punctuation failed,then shutdown.\nOUT SPEED: Adjust the speed of discharge conveyor.\0"
"ROLLER GIRTH:The girth of rubber roller.\nPUNCH TIME: The time of punch EM valve working after motor stops. \nMAIN FACTOR: The regulation error factor of speed, set value is\n bigger, the engine speed is faster.\0"
"SMPS\0"
"photoelectric eye\0"
"feeding\n Hall\0"
"overspeed\n  Hall\0"
"black\0"
"red\0"
"blue\0"
"brown\0"
"white\n(green)\0"
"START\0"
"input\0"
"BEEP\0"
"inverter\0"
"stepping\n motor\0"
"relay\0"
"DC speed\ncontrol board\0"
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
"ReBack LENGTH\0"
"DRAG Delay\0"
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
"Seek_Speed\0"
"BackSpeed\0"
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
1,3,5,7,9,11,13,15,17,19,
21,23,25,27,29,31,33,35,43,51,
61,71,81,86,95,106,112,118,121,127,
130,133,142,151,158,163,168,173,178,183,
188,193,202,211,216,221,226,231,236,243,
250,255,260,265,270,279,288,293,300,307,
312,322,329,336,343,354,365,374,383,392,
401,410,419,428,437,446,455,464,473,482,
491,500,509,518,527,536,545,554,563,573,
582,587,592,601,610,619,628,637,646,655,
664,675,689,694,699,708,713,720,725,730,
735,740,745,750,759,768,778,787,798,809,
814,823,832,841,850,859,864,873,882,891,
900,904,908,912,916,920,924,928,932,941,
951,956,965,975,980,989,998,1007,1016,1025,
1029,1033,1037,1041,1045,1054,1063,1072,1082,1091,
1099,1105,1125,1131,1141,1151,1172,1177,1182,1185,
1196,1482,1714,1946,2109,2165,2337,2507,2745,2947,
2956,2963,2972,2981,2984,2987,2990,2993,3002,3007,
3012,3019,3026,3035,3042,3053,3060,3065,3074,3081,
3090,3099,3108,3117,3126,3135,3144,3153,3165,3174,
3189,3198,3207,3217,3227,3234,3241,3249,3257,3265,
3273,3282,3291,3299,3307,3319,3331,3339,3347,3359,
3371,3379,3391,3398,3406,3418,3425,3432,3439,3450,
3461,3470,3481,3491,3503,3514,3523,3532,3542,3552,
3561,3570,3579,3588,3597,3606,3615,3624,3633,3644,
3649,3654,3659,3664,3669,3674,3679,3684,3689,3694,
3699,3704,3709,3714,3719,3724,3727,3732,3737,3743,
3749,3755,3761,3768,3775,3781,3787,3792,3797,3802,
3807,3812,3817,3822,3827,3832,3838,3844,3849,3854,
3859,3864,3869,3874,3879,3884,3889,3898,3907,3932,
3934,3936,3938,3940,3942,3944,3946,3948,3950,};

const static u16 LabelIndex_2[]={
0,
1,3,5,7,9,11,13,15,17,19,
21,23,25,27,29,31,33,35,40,45,
57,69,81,87,96,104,111,117,121,127,
133,136,143,148,152,158,164,169,176,180,
185,192,199,206,211,215,223,229,238,247,
256,262,271,280,286,294,305,309,314,319,
324,330,339,345,350,361,375,385,396,402,
413,427,441,454,466,476,488,505,516,529,
539,550,562,573,587,600,611,621,627,633,
644,651,656,663,674,685,693,701,714,723,
733,744,750,761,773,789,793,800,806,810,
816,820,825,829,838,847,858,868,879,890,
897,907,915,919,923,927,931,935,939,943,
947,951,955,959,963,967,971,975,979,983,
987,991,995,999,1003,1007,1011,1015,1019,1023,
1027,1031,1035,1039,1043,1048,1052,1056,1061,1075,
1089,1094,1115,1124,1137,1144,1176,1189,1204,1208,
1232,1536,1755,2041,2289,2403,2623,2857,3105,3314,
3319,3337,3351,3368,3374,3378,3383,3389,3403,3409,
3415,3420,3429,3445,3451,3474,3481,3488,3497,3504,
3514,3524,3535,3546,3556,3566,3579,3591,3601,3612,
3629,3642,3654,3669,3684,3694,3705,3715,3725,3732,
3739,3747,3755,3764,3773,3783,3793,3805,3814,3826,
3840,3854,3869,3878,3888,3896,3908,3916,3922,3931,
3940,3952,3960,3970,3982,3993,4004,4016,4029,4041,
4053,4064,4076,4090,4101,4113,4125,4137,4151,4164,
4169,4174,4179,4184,4189,4194,4199,4204,4209,4214,
4219,4224,4229,4234,4239,4244,4246,4247,4248,4249,
4250,4251,4252,4253,4254,4255,4256,4257,4258,4259,
4260,4261,4262,4263,4264,4265,4266,4267,4268,4269,
4270,4271,4272,4273,4274,4275,4276,4287,4297,4298,
4300,4302,4304,4306,4308,4310,4312,4314,4316,};
const static u16* pLabelIndex[] = {
LabelIndex_1,
LabelIndex_2,
};
const static u8* pLabelText[] = {
LabelText_1,
LabelText_2,
};

#endif
