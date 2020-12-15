/*******************************************

				  7寸 QVGA显示驱动程序







**********************************************/


#include "fsmc_sram.h"

unsigned long color1=0;
//void MUC_Init();
void LCD_Init1(void);

void LCD_test(void);
//void LCD_clear(unsigned int p);
void ini(void);

void lcd_wr_zf(unsigned int a, unsigned int b, unsigned int a1,unsigned int b1, unsigned int d,unsigned int e, unsigned char g, unsigned char *f); 
void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e) ;
unsigned char *num_pub(unsigned int a);
void LCD_clear(void);


unsigned int color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};
//=================================================================================

//七寸屏的显示设置

//=================================================================================

unsigned int  HDP=799; //Horizontal Display Period
unsigned int  HT=1000; //Horizontal Total
unsigned int  HPS=51;  //LLINE Pulse Start Position
unsigned int  LPS=3;   //	Horizontal Display Period Start Position
unsigned char HPW=8;   //	LLINE Pulse Width


unsigned int  VDP=479;	//Vertical Display Period
unsigned int  VT=530;	//Vertical Total
unsigned int  VPS=24;	//	LFRAME Pulse Start Position
unsigned int  FPS=23;	//Vertical Display Period Start Positio
unsigned char   VPW=3;	// LFRAME Pulse Width
//=================================================================================

extern unsigned char zm9[];
extern unsigned char zm8[];
extern unsigned char zm7[];
extern unsigned char zm6[];
extern unsigned char zm5[];
extern unsigned char zm4[];
extern unsigned char zm3[];
extern unsigned char zm2[];
extern unsigned char zm1[];
extern unsigned char zm0[];
extern unsigned char a1[];
extern unsigned char a2[];
extern unsigned char zf2[];
extern unsigned char zf3[];	

//unsigned int LCD_RD_data(void);
extern void lcd_rst(void);
void delay_time(unsigned int i);
void SetScrollArea(unsigned int top, unsigned int scroll, unsigned int bottom);
void SetScrollStart(unsigned int line);
void SetTearingCfg(unsigned char state, unsigned char mode);


void LCD_Config(void)
{
	LCD_WR_REG(0x00E2);	
	LCD_WR_Data(0x0023);
	// Set PLL with OSC = 10MHz (hardware)
    // Multiplier N = 35, VCO (>250MHz)= OSC*(N+1), VCO = 360MHz	   
	LCD_WR_Data(0x0002);
	// Divider M = 2, PLL = 360/(M+1) = 120MHz
	LCD_WR_Data(0x0004);
	// Validate M and N values

	LCD_WR_REG(0x00E0);  // PLL enable
	LCD_WR_Data(0x0001);
	delay_time(1);
	LCD_WR_REG(0x00E0);
	LCD_WR_Data(0x0003);
	delay_time(5);
	LCD_WR_REG(0x0001);  // software reset
	delay_time(5);
	LCD_WR_REG(0x00E6);	//PLL setting for PCLK, depends on resolution
	
	
	//Set LSHIFT freq, i.e. the DCLK with PLL freq 120MHz set previously
	//Typical DCLK for AT070TN92 is 34MHz
	//34MHz = 120MHz*(LCDC_FPR+1)/2^20
	//LCDC_FPR = 300000 (0x0493E0)
	
	LCD_WR_Data(0x0004);
	LCD_WR_Data(0x0093);
	LCD_WR_Data(0x00e0);

	LCD_WR_REG(0x00B0);	//LCD SPECIFICATION
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_Data(HDP&0X00FF);
    LCD_WR_Data((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_Data(VDP&0X00FF);
    LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_Data((HT>>8)&0X00FF);  //Set HT
	LCD_WR_Data(HT&0X00FF);
	LCD_WR_Data((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(HPS&0X00FF);
	LCD_WR_Data(HPW);			   //Set HPW
	LCD_WR_Data((LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(LPS&0X00FF);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_Data((VT>>8)&0X00FF);   //Set VT
	LCD_WR_Data(VT&0X00FF);
	LCD_WR_Data((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_Data(VPS&0X00FF);
	LCD_WR_Data(VPW);			   //Set VPW
	LCD_WR_Data((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_Data(FPS&0X00FF);

	LCD_WR_REG(0x00BA);
	LCD_WR_Data(0x000F);    //GPIO[3:0] out 1

	LCD_WR_REG(0x00B8);
	LCD_WR_Data(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_Data(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x0036); //rotation
	LCD_WR_Data(0x0000);
//	LCD_WR_Data(0x0060);


	LCD_WR_REG(0x00F0); //pixel data interface
	LCD_WR_Data(0x0003);

	delay_time(5);

	LCD_WR_REG(0x0029); //display on

	LCD_WR_REG(0x00BE); //set PWM for B/L
	LCD_WR_Data(0x0006);
	//LCD_WR_Data(0x0008);
	LCD_WR_Data(0x0080);
	//LCD_WR_Data(0x00f0);
	
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x00f0);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00d0);//设置动态背光控制配置 
	LCD_WR_Data(0x000d);  			

	LCD_WR_REG(0x00B9);	//设置GPIO为输出
	LCD_WR_Data(0x000F);	//全部都为输出
}

//初始化函数
void LCD_Init1(void)
{
	//lcd_rst();	 
	GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    delay_time(60);					   
    GPIO_SetBits(GPIOD, GPIO_Pin_3 );		 	 
	delay_time(60);

	LCD_Config();
	LCD_clear();
}

void LCD_clear(void)
{
    unsigned int l=800,w;

	LCD_WR_REG(0x002A);	
	LCD_WR_Data(0);	    
	LCD_WR_Data(0);
	LCD_WR_Data(HDP>>8);	    
	LCD_WR_Data(HDP&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(0);	    
	LCD_WR_Data(0);
	LCD_WR_Data(VDP>>8);	    
	LCD_WR_Data(VDP&0x00ff);
	LCD_WR_REG(0x002c);
	
	
	while(l--)
	{
	    for(w=0;w<480;w++)
		{    
          	LCD_WR_Data(0xf800);
		}
	}
}

void delay_time(unsigned int i)
{
    unsigned int a;
    unsigned int b;
    for(b=0;b<i;b++)
    for(a=0;a<1000;a++);
}

/*********************************************************************
* Function:  SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
*
* PreCondition: none
*
* Input: top - Top Fixed Area in number of lines from the top
*				of the frame buffer
*		 scroll - Vertical scrolling area in number of lines
*		 bottom - Bottom Fixed Area in number of lines
*
* Output: none
*
* Side Effects: none
*
* Overview:
*
* Note: Reference: section 9.22 Set Scroll Area, SSD1963 datasheet Rev0.20
********************************************************************/
void SetScrollArea(unsigned int top, unsigned int scroll, unsigned int bottom)
{
//	WriteCommand(CMD_SET_SCROLL_AREA);
//	CS_LAT_BIT = 0;
	LCD_WR_REG(0x33);
	LCD_WR_Data(top>>8);
	LCD_WR_Data(top);
	LCD_WR_Data(scroll>>8);
	LCD_WR_Data(scroll);
	LCD_WR_Data(bottom>>8);
	LCD_WR_Data(bottom);
//	CS_LAT_BIT = 1;	
}

/*********************************************************************
* Function:  void  SetScrollStart(SHORT line)
*
* Overview: First, we need to define the scrolling area by SetScrollArea()
*			before using this function. 
*
* PreCondition: SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
*
* Input: line - Vertical scrolling pointer (in number of lines) as 
*		 the first display line from the Top Fixed Area defined in SetScrollArea()
*
* Output: none
*
* Note: Example -
*
*		SHORT line=0;
*		SetScrollArea(0,272,0);
*		for(line=0;line<272;line++) {SetScrollStart(line);DelayMs(100);}
*		
*		Code above scrolls the whole page upwards in 100ms interval 
*		with page 2 replacing the first page in scrolling
********************************************************************/
void SetScrollStart(unsigned int line)
{
//	LCD_WR_REG(0x002A);	
//    LCD_WR_Data(0);	  
//	LCD_WR_REG(CMD_SET_SCROLL_START);
	LCD_WR_REG(0x37);
//	CS_LAT_BIT = 0;
	LCD_WR_Data(line>>8);
	LCD_WR_Data(line);	
//	CS_LAT_BIT = 1;
}

/*********************************************************************
* Function:  void  SetTearingCfg(BOOL state, BOOL mode)
*
* Overview: This function enable/disable tearing effect
*
* PreCondition: none
*
* Input: 	BOOL state -	1 to enable
*							0 to disable
*			BOOL mode -		0:  the tearing effect output line consists
*								of V-blanking information only
*							1:	the tearing effect output line consists
*								of both V-blanking and H-blanking info.
* Output: none
*
* Note:
********************************************************************/
void SetTearingCfg(unsigned char state, unsigned char mode)
{
	if(state == 1)
	{
		LCD_WR_REG(0x35);
		//CS_LAT_BIT = 0;
		LCD_WR_Data(mode&0x01);
		//CS_LAT_BIT = 1;
	}
	else
	{
		LCD_WR_REG(0x34);
	}
}




/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

static u8 ChkPixel = 0;
static u16 ErroCnt = 0;

u8 ScreenCheck()
{
	ChkPixel = (ChkPixel+1)&0x0F;
	LCD_WR_REG(0x00BA);
	LCD_WR_Data(ChkPixel);

	LCD_WR_REG(0x00BB);
	if(ChkPixel!=LCD_RD_data())
		ErroCnt++;
	else
		ErroCnt = 0;

	if(ErroCnt>=10)
	{
		ErroCnt = 0;
		GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    	delay_time(1);
    	GPIO_SetBits(GPIOD, GPIO_Pin_3 );		 	 
		delay_time(1);
		LCD_Config();
	}
	return 0;
}
