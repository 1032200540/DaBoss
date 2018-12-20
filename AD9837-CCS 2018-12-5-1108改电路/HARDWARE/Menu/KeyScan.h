#ifndef __KeyScan_H
#define __KeyScan_H 

#include "stm32f10x.h"
#include "sys.h"

u8 KeyScan(void);
u8 WaitKey(void);
void KEY_IOinit(void);
void EXTIX_IO_Init(void);

#define EXTIX_IO  0 //0�������ж�ɨ�裬1ʹ���ж�ɨ��

#define Key0 PFin(14)  //Key_Enter
#define Key1 PFin(13)  //Key_Down
#define Key2 PFin(12)  //Key_Up
#define Key3 PFin(11)  //Key_Back

#endif  
