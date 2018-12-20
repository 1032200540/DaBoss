#ifndef __MENUTOP_H
#define __MENUTOP_H	 

//#include "ST7565R.h"
#include "Menu.h"
//#include "delay.h"


#define U8  unsigned char
#define U16 unsigned int
#define U32 unsigned long


void InitMenuVal(void);//初始化菜单系统
void DispHomeScreen(void);//待机界面
void DispHomeScreenEnter(void); //待机界面下Enter键的处理
void DispHomeScreenBack(void); //待机界面下Back键的处理
void DispHomeScreenUp(void); //待机界面下Up键的处理
void DispHomeScreenDown(void); //待机界面下Down键的处理
void PUSH(void); //菜单备份函数
void POP(void); //菜单还原函数
void BarDisp(U8 *s,U8 X,U8 Y,U8 HighLight); //Bar型菜单显示
void BarMenuInit(void); //Bar型菜单初始化  公共部分
void BarMenuUp(void); //Bar项菜单向上按键的行为
void BarMenuDown(void); //Bar项菜单向下按键的行为
void DispIcoMenuInit(void); //图标层菜单界面
void DispIcoMenuEnter(void);
void DispIcoMenuBack(void);
void DispIcoMenuUp(void);
void DispIcoMenuDown(void);
void DispBuildTime(void);//编译时间

#endif  
