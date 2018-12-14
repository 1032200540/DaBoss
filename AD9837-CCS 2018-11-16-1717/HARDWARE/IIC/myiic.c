#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//��ʼ��IIC
void IIC_Configuration(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13); 	//PB12,PB13 �����
}

///**
//  * @brief  I2C ����ģʽ����
//  * @param  ��
//  * @retval ��
//  */
// void I2C_Mode_Configu(void)
//{
//  I2C_InitTypeDef  I2C_InitStructure; 

//  /* I2C ���� */
//  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
//	
//	/* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
//  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
//	
//  I2C_InitStructure.I2C_OwnAddress1 =I2C1_OWN_ADDRESS7; 
//  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
//	
//	/* I2C��Ѱַģʽ */
//  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	
//	/* ͨ������ */
//  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
//  
//	/* I2C1 ��ʼ�� */
//  I2C_Init(I2C1, &I2C_InitStructure);
//  
//	/* ʹ�� I2C1 */
//  I2C_Cmd(I2C1, ENABLE);   
//}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK	//������ACKӦ��	
    else
        IIC_Ack(); //����ACK    //����ACKӦ��
    return receive;
}

//**************************************
//��IIC�豸д��һ���ֽ�����
//**************************************
u8 I2C_WriteSinglebyte(u8 Slave_Address,u8 REG_Address,u8 data)
{
	IIC_Start();        
	IIC_Send_Byte(Slave_Address);   //�����豸��ַ+д�ź�
	if(!IIC_Wait_Ack())
	{
		IIC_Stop();
		return RESET;
	}

	IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ��
	if(!IIC_Wait_Ack())
	{
		IIC_Stop(); 
		return RESET;
	}

	IIC_Send_Byte(data);       //�ڲ��Ĵ������ݣ�
	if(!IIC_Wait_Ack())
	{
		IIC_Stop();
		return RESET;
	}

	IIC_Stop();   //����ֹͣ�ź�

	return SET;
}
