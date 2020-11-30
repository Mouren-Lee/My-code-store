#ifndef LCDCONF_H
#define LCDCONF_H


#define LCD_XSIZE          (800)
#define LCD_YSIZE          (480)
#define LCD_CONTROLLER       (9320)
#define LCD_BITSPERPIXEL   (16)
#define LCD_FIXEDPALETTE   (565)
#define LCD_SWAP_RB        (0)
extern 	void LCD_Init0(void); 
#define LCD_INIT_CONTROLLER() LCD_Init0();   //
#endif /* LCDCONF_H */

