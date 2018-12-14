#ifndef __HDC1080_H
#define __HDC1080_H
#include "myiic.h" 

#define u16 unsigned int
	
//HDC1080
/////////计算公式///////////////////////////////////////////
//temper=[(d15:d0)/2^16]*165c-40c
//relative=[(d15:d0)/2^16]*100%
///////////HDC1080寄存器说明////////////////////////////////
#define HDC1080_Bus_Adderss      0x80   //1000000x，x为读(1)、写命令(0)
#define HDC1080_TemperatureRegister    0x00  //温度测量输出寄存器
#define HDC1080_HumidityRegister       0x01   //相对湿度测量输出寄存器
#define HDC1080_ConfigRegister         0x02   //HDC1080的配置和状态寄存器
#define HDC1080_ManufacturerIdRegister 0xFE    //德州仪器的ID

#define HDC1080_DeviceIdRegister       0xff  //设备的ID
#define HDC1080_ID                  0x1000
//////////////////////////////////////////////////////////////
#define HDC1080_Rst                 15//0x8000软复位
#define HDC1080_Enht                13//0x2000//使能加热
#define HDC1080_Mode                12//0x1000//转换模式-为0时分开来读，为1时可以连续读温度在前
#define HDC1080_Trest               10//0x0000  0为温度14bit 1为11bit
#define HDC1080_Hres                8//0x0000 14 11 7bit 温度

void HDC1080_Init(void);
void HDC1080_Setting(void);
float HDC1080_Read_Temper(void);
u16 HDC1080_Read_Humidi(void);
u16 HDC1080_Read_DeviceID(void);

#endif     /*HDC1080.h*/

