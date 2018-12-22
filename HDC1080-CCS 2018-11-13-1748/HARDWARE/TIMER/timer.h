#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define u16 unsigned int

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM2_Int_Init(u16 arr,u16 psc);
 
#endif
