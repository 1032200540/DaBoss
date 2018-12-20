#ifndef __MenuFunc_H
#define __MenuFunc_H	


#include "Menu.H"


void DispMenuFuncInit(void);
void DispMenuFuncEnter(void);
void DispMenuFuncBack(void);
void DispMenuFuncUp(void);
void DispMenuFuncDown(void);


#ifdef DynamicBar
void DispMenuDataInit(void);
void DispMenuDataEnter(void);
void DispMenuDataBack(void);
void DispMenuDataUp(void);
void DispMenuDataDown(void);
#endif

#endif


