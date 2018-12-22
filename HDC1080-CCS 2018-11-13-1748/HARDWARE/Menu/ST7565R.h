#ifndef __ST7565R_H
#define __ST7565R_H	 

#include "CPU.h"

#define LCD_XSIZE      192
#define LCD_YSIZE      8

#define ST7565R_CMD_Disp_ON          0XAF
#define ST7565R_CMD_Disp_OFF         0XAE
//#define ST7565R_CMD_Set_Addr         0x40
//#define ST7565R_CMD_Set_Page         0xB8
#define ST7565R_CMD_Disp_Start_Line       0X40

//显示模式
#define GUI_TEXTMODE_NORMAL      (0)
#define GUI_TEXTMODE_REVERSE     (1<<0)
#define GUI_TEXTMODE_UNDERLINE   (1<<1)
#define GUI_TEXTMODE_XOR         (1<<2)
//对齐方式
#define GUI_TA_LEFT              (0<<4)
#define GUI_TA_HCENTER           (1<<4)
#define GUI_TA_RIGHT             (2<<4)
#define GUI_JUST_TEXT            (1<<7)

//英文的两种字体
#define En_8x16      (0)
#define En_5x8       (1)

//字体宽度定义
#define En_8x16_XSIZE  8
#define En_8x16_YSIZE  2
#define En_5x8_XSIZE   8
#define En_5x8_YSIZE   1
//英文字体宽度定义
extern U8 Char_XSIZE;
extern U8 Char_YSIZE;


//中文字体宽度定义
#define Chinese_XSIZE  16
#define Chinese_YSIZE  2

void GUI_GotoX(U8 x);
void GUI_GotoY(U8 y);
void GUI_GotoXY(U8 x,U8 y);
U8 GUI_SetTextMode(U8 TextMode);  //设置文字显示模式
void GUI_SetEnFont(U8 EnFont);   //设置显示的英文字体
void GUI_DispCharAt(U8 c, U8 x, U8 y);  //指定位置显示一个ASCII码
void GUI_DispChar(U8 c);
void WriteData_ST7565R(U8 Data);
void Display_Init(void);
void LCD_IOinit(void);
void GUI_Init(void);               //初始化GUI显示
void lcd_address(U8 column,U8 page);
void GUI_Clear(void);
void GUI_DispCEOL(void);
//void GUI_DispStringAt(U8 const *s,U8 X,U8 Y);
void GUI_DispStringAt(U8 *s,U8 X,U8 Y);  //指定位置显示一个字符串
void GUI_DispString(U8 const *s);
void GUI_DispStringLen(U8 const *s, U16 Len);
void GUI_DrawCursor(U8 x, U8 y);
void GUI_CursorOn(U8 x, U8 y);
void GUI_CursorOFF(U8 x, U8 y);
void GUI_DispDecAt(U16 v, U16 x, U16 y, U8 Len);
void GUI_DispHexAt(U32 v, U8 x, U8 y, U8 Len);
//void GUI_DispStringAtBar(U8 const *s,U8 x0, U8 y0, U8 x1,U8 Mode);
void GUI_DispStringAtBar(U8 *s,U8 x0, U8 y0, U8 x1,U8 Mode); // 显示一个字符串在一个BAR中
void GUI_Delay(U16 Period);
void GUI_DrawIcon(U8 const *Ico,U8 X,U8 Y);  //显示一个32x32的图标
void HBar(U8 y, U8 x0, U8 x1,U8 percent);
void Bar(U8 Item_,U8 ItemNum_,U8 BarPosX,U8 BarNumPosX);
void TipDisp( U8 x0, U8 y0, U8 x1, U8 y1);
void TipClr( U8 x0, U8 y0, U8 x1, U8 y1);
void Display_Number(U16 Number, U8 X, U8 Y, U8 Lenth); //显示不带符号的整数  (数字 起始位置XY,显示长度)
void Display_SignedNumber(int Number,U8 X,U16 Y,U8 Lenth); //显示带符号的整数  (数字 起始位置XY,显示长度)
void Display_Decimal(unsigned long int Number, char X, U16 Y, U8 INT, U8 DEC); //显示不带符号的小数 (数字 起始位置XY,整数位数,小数位数)
void Display_SignedDecimal(long int Number, char X, U16 Y, U8 INT, U8 DEC); //显示带符号的小数 (数字 起始位置XY,整数位数,小数位数)


//采用8080工作模式
#define LCM_DB0 PFout(0)
#define LCM_DB1 PFout(1)
#define LCM_DB2 PFout(2)
#define LCM_DB3 PFout(3)
#define LCM_DB4 PFout(4)
#define LCM_DB5 PFout(5)
#define LCM_DB6 PFout(6)
#define LCM_DB7 PFout(7)

#define BLKA PCout(1)
#define LCM_RS PCout(0)  //
#define LCM_RESET PFout(10) 
#define LCM_CS PCout(2)  //
#define LCM_RD PFout(9)   //读
#define LCM_WR PFout(8)      //写 


#endif
