#ifndef __HDC1080_H
#define __HDC1080_H
#include "myiic.h" 

#define u16 unsigned int
	
//HDC1080
/////////���㹫ʽ///////////////////////////////////////////
//temper=[(d15:d0)/2^16]*165c-40c
//relative=[(d15:d0)/2^16]*100%
///////////HDC1080�Ĵ���˵��////////////////////////////////
#define HDC1080_Bus_Adderss      0x80   //1000000x��xΪ��(1)��д����(0)
#define HDC1080_TemperatureRegister    0x00  //�¶Ȳ�������Ĵ���
#define HDC1080_HumidityRegister       0x01   //���ʪ�Ȳ�������Ĵ���
#define HDC1080_ConfigRegister         0x02   //HDC1080�����ú�״̬�Ĵ���
#define HDC1080_ManufacturerIdRegister 0xFE    //����������ID

#define HDC1080_DeviceIdRegister       0xff  //�豸��ID
#define HDC1080_ID                  0x1000
//////////////////////////////////////////////////////////////
#define HDC1080_Rst                 15//0x8000��λ
#define HDC1080_Enht                13//0x2000//ʹ�ܼ���
#define HDC1080_Mode                12//0x1000//ת��ģʽ-Ϊ0ʱ�ֿ�������Ϊ1ʱ�����������¶���ǰ
#define HDC1080_Trest               10//0x0000  0Ϊ�¶�14bit 1Ϊ11bit
#define HDC1080_Hres                8//0x0000 14 11 7bit �¶�

void HDC1080_Init(void);
void HDC1080_Setting(void);
float HDC1080_Read_Temper(void);
u16 HDC1080_Read_Humidi(void);
u16 HDC1080_Read_DeviceID(void);

#endif     /*HDC1080.h*/

