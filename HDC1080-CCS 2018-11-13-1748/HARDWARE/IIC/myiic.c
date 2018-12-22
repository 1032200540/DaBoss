#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//初始化IIC
void IIC_Configuration(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13); 	//PB12,PB13 输出高
}

///**
//  * @brief  I2C 工作模式配置
//  * @param  无
//  * @retval 无
//  */
// void I2C_Mode_Configu(void)
//{
//  I2C_InitTypeDef  I2C_InitStructure; 

//  /* I2C 配置 */
//  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
//	
//	/* 高电平数据稳定，低电平数据变化 SCL 时钟线的占空比 */
//  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
//	
//  I2C_InitStructure.I2C_OwnAddress1 =I2C1_OWN_ADDRESS7; 
//  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
//	
//	/* I2C的寻址模式 */
//  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//	
//	/* 通信速率 */
//  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
//  
//	/* I2C1 初始化 */
//  I2C_Init(I2C1, &I2C_InitStructure);
//  
//	/* 使能 I2C1 */
//  I2C_Cmd(I2C1, ENABLE);   
//}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK	//不产生ACK应答	
    else
        IIC_Ack(); //发送ACK    //产生ACK应答
    return receive;
}

//**************************************
//向IIC设备写入一个字节数据
//**************************************
u8 I2C_WriteSinglebyte(u8 Slave_Address,u8 REG_Address,u8 data)
{
	IIC_Start();        
	IIC_Send_Byte(Slave_Address);   //发送设备地址+写信号
	if(!IIC_Wait_Ack())
	{
		IIC_Stop();
		return RESET;
	}

	IIC_Send_Byte(REG_Address);    //内部寄存器地址，
	if(!IIC_Wait_Ack())
	{
		IIC_Stop(); 
		return RESET;
	}

	IIC_Send_Byte(data);       //内部寄存器数据，
	if(!IIC_Wait_Ack())
	{
		IIC_Stop();
		return RESET;
	}

	IIC_Stop();   //发送停止信号

	return SET;
}

