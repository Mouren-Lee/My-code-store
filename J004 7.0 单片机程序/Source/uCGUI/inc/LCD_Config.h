#include "stm32f10x_type.h"
#ifndef	__LCD_CONFIG_h__
#define	__LCD_CONFIG_h__
//	write your header here
#define LCD_X_MAX			800				//��Ļ��X���������
#define LCD_Y_MAX			480				//��Ļ��Y���������
			
#define LCD_XY_Switch		0				//��ʾʱX���Y�ɽ���
#define LCD_X_Rev			0				//��ʾʱX�ᷴת
#define LCD_Y_Rev			0				//��ʾʱY�ᷴת

#if LCD_XY_Switch == 0
	#define Dis_X_MAX		LCD_X_MAX
	#define Dis_Y_MAX		LCD_Y_MAX
#endif

#if LCD_XY_Switch == 1
	#define Dis_X_MAX		LCD_Y_MAX
	#define Dis_Y_MAX		LCD_X_MAX
#endif

//GPIOC_BASE + 16
#define	H_S					1<<10
#define	H_BP				40
#define	H_FP				1<<6
#define	H_W					479

#define	V_S					1<<10
#define	V_BP				9
#define	V_FP				1<<6
#define	V_W					271

#define TFT_CLK_INV			1<<15
#define TFT_HYNC_INV		1<<13
#define TFT_VYNC_INV		1<<12
#define TFT_EN_INV			1<<14

#define TFT_Work			1<<15
#define TFT_CLK_DIV			1<<12

#define TFT_Reg0	H_W|H_S
#define TFT_Reg1	H_BP|H_FP|TFT_HYNC_INV|TFT_VYNC_INV
#define TFT_Reg2	V_W|V_S
#define TFT_Reg3	V_BP|V_FP|TFT_Work|TFT_CLK_DIV

#define		TFT_Base_Addr		0x6c000000							//TFT����ַ


#define	TFT_Reg_Ptr			((vu16 *)TFT_Base_Addr)
#define	TFT_DAT_Ptr			((vu16 *)(TFT_Base_Addr+(0x1<<1)))
#define	TFT_Y_Ptr			
#define	TFT_X_Ptr			
#define	TFT_Sys_Ptr			
/*
#define	TFT_DAT_Read_Ptr	((vu16 *)TFT_Base_Addr)
#define	TFT_DAT_Write_Ptr	((vu16 *)(TFT_Base_Addr+(0x10<<1)))
#define	TFT_Reg0_Ptr		((vu16 *)(TFT_Base_Addr+(0x18<<1)))
#define	TFT_Reg1_Ptr		((vu16 *)(TFT_Base_Addr+(0x19<<1)))
#define	TFT_Reg2_Ptr		((vu16 *)(TFT_Base_Addr+(0x1A<<1)))
#define	TFT_Reg3_Ptr		((vu16 *)(TFT_Base_Addr+(0x1B<<1)))
#define	TFT_Reg4_Ptr		((vu16 *)(TFT_Base_Addr+(0x1C<<1)))
#define	TFT_Reg5_Ptr		((vu16 *)(TFT_Base_Addr+(0x1D<<1)))
#define	TFT_Reg6_Ptr		((vu16 *)(TFT_Base_Addr+(0x1E<<1)))
#define	TFT_Reg7_Ptr		((vu16 *)(TFT_Base_Addr+(0x1F<<1)))
*/

#define LCD_RES_Enable	  GPIO_ResetBits(GPIOD, GPIO_Pin_3);
#define LCD_RES_Disable	  GPIO_SetBits(GPIOD, GPIO_Pin_3);

#endif
void LCD_Dis_ON(void);
void LCD_Dis_OFF(void);
void LCD_Dis_Switch(u8 Dis_Num);
void LCD_Buffer_Switch(u8 Buffer_Num);
void Back_Light_SET(u8 PWM_Duty);
void Back_Light_ON_OFF(u8 ON_OFF);
void LCD_DataWrite(u16 Data);
u16 LCD_DataRead(void);
void Fill_Dot_LCD(u16 Color);
void Write_Dot_LCD(int x,int y,u16 Color);
void Clear_Dot_LCD(int x,int y);
 unsigned int Get_Dot_LCD(int x,int y);
void Set_Dot_Addr_LCD(int x,int y);
void LCD_Fill(u16 Data);
void LCD_Fill_s(u16 Number,u16 Color);
void LCD_Init0(void);

void ili9320_Initializtion(void);;;
void ili9320_SetCursor(u16 x,u16 y);
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic);
void ili9320_SetPoint(u16 x,u16 y,u16 point);
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);
void ili9320_Clear(u16 dat);
void ili9320_Delay(u32 nCount);
u16 ili9320_GetCode(void);;

void ili9320_BackLight(u8 status);

u16 ili9320_BGR2RGB(u16 c);

u16 ili9320_GetPoint(u16 x,u16 y);;

u16 GUI_Color565(u32 RGB);  // RGB��ɫתΪ16λ(565)

void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor);
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);  // ����
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill);  // ��԰
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill); // ������
void GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill);  // ��������


void Touch_Initializtion(void);
u16  Touch_GetPhyX(void);
u16  Touch_GetPhyY(void);
u16  Touch_MeasurementX(void);
u16  Touch_MeasurementY(void);





