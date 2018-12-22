#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<16;}
#define SDA_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<16;}

//STM32 �ڲ�IIC��ַ����,�����ַֻҪ�����IIc��ַ��һ���Ϳ���
#define I2C1_OWN_ADDRESS7 0x0A
//IIC�������
#define I2C_Speed 400000


//IO��������	 
#define IIC_SCL    PBout(13) //SCL
#define IIC_SDA    PBout(12) //SDA	 
#define READ_SDA   PBin(12)  //����SDA 

//IIC���в�������
void IIC_Configuration(void);       //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void I2C_Mode_Configu(void);
u8 I2C_WriteSinglebyte(u8 Slave_Address,u8 REG_Address,u8 data);

//void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
//u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















