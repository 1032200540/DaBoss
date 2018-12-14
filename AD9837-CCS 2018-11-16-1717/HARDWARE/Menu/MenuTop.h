#ifndef __MENUTOP_H
#define __MENUTOP_H	 

//#include "ST7565R.h"
#include "Menu.h"
//#include "delay.h"


#define U8  unsigned char
#define U16 unsigned int
#define U32 unsigned long


void InitMenuVal(void);//��ʼ���˵�ϵͳ
void DispHomeScreen(void);//��������
void DispHomeScreenEnter(void); //����������Enter���Ĵ���
void DispHomeScreenBack(void); //����������Back���Ĵ���
void DispHomeScreenUp(void); //����������Up���Ĵ���
void DispHomeScreenDown(void); //����������Down���Ĵ���
void PUSH(void); //�˵����ݺ���
void POP(void); //�˵���ԭ����
void BarDisp(U8 *s,U8 X,U8 Y,U8 HighLight); //Bar�Ͳ˵���ʾ
void BarMenuInit(void); //Bar�Ͳ˵���ʼ��  ��������
void BarMenuUp(void); //Bar��˵����ϰ�������Ϊ
void BarMenuDown(void); //Bar��˵����°�������Ϊ
void DispIcoMenuInit(void); //ͼ���˵�����
void DispIcoMenuEnter(void);
void DispIcoMenuBack(void);
void DispIcoMenuUp(void);
void DispIcoMenuDown(void);
void DispBuildTime(void);//����ʱ��

#endif  
