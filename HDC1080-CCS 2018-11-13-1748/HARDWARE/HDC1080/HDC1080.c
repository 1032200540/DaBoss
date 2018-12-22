#include "HDC1080.h" 
#include "delay.h"
/*******************************************************************************
  * HDC1080,д��start ==��senddata(Bus_Adderss(���һλΪ0����ʾд)) ==��senddata(Pointer Register)
  *              ==��senddata(Data MSB) ==��senddata(Data LSB) ==��stop
  * HDC1080,����start ==��senddata(Bus_Adderss(���һλΪ0����ʾд)) ==��senddata(Pointer Register)
  *         ==��senddata(Bus_Adderss(���һλΪ1����ʾ��)) ==��senddata(Data MSB) ==��senddata(Data LSB) ==��stop
  * ת��ģʽΪ1ʱ��Ӧ�ȶ��¶ȣ������¶ȼĴ�������ת�������ٶ�ʪ�ȡ�
  * ת��ģʽΪ0ʱ�������¶ȼĴ����������¶�ת��������ʪ�ȼĴ���������ʪ��ת����  
 *******************************************************************************/

/*******************************************************************************
  * @brief  
  * @param  uint8_t addr, д���Ŀ�ĵ�ַ
  * @param  uint8_t *buffer, д�������
  * @param  uint8_t len,д��ĸ���
  * @retval u8 ��0�ɹ���1ʧ��
 *******************************************************************************/
u8 HDC1080_Write_Buffer(uint8_t addr, uint8_t *buffer, uint8_t len)
{
	IIC_Start();  //��ʼ�ź�	 
	IIC_Send_Byte(HDC1080_Bus_Adderss);
	IIC_Wait_Ack();

	IIC_Send_Byte(addr);
	IIC_Wait_Ack();

	while ( len-- )
	{
		IIC_Send_Byte(*buffer);
		IIC_Wait_Ack();
		buffer++;
	}
	IIC_Stop();
	return 0;
}
/*******************************************************************************
  * @brief  �������üĴ���0x02��д�����á������λ��
  * @param  ��  
  * @retval ��
 *******************************************************************************/
void HDC1080_Soft_Reset(void)
{
    u8 temp[2];
    temp[0] = 0x80; 
    temp[1] = 0x00;
    HDC1080_Write_Buffer(HDC1080_ConfigRegister, temp, 2); // �����Ĵ���0x02��д������
    delay_ms(20);//there should be waiting for more than 15 ms.
}
/*******************************************************************************
  * @brief  �¶�ʪ�Ȼ�ȡģʽ�;�������
  * @param  �� 
  * @retval ��
 *******************************************************************************/
void HDC1080_Setting(void)
{
    uint16_t tempcom = 0;
    uint8_t temp[2];
	
    tempcom |= 1<<HDC1080_Mode ;//���λ���¶Ⱥ�ʪ�ȣ��������¶ȡ�
    // �¶����¶ȶ�Ϊ14bit
    temp[0] = (uint8_t)(tempcom >> 8); 
    temp[1] = (uint8_t)tempcom;
    HDC1080_Write_Buffer(HDC1080_ConfigRegister, temp, 2);
}
/*******************************************************************************
  * @brief  �����λ���¶�ʪ�Ȼ�ȡģʽ����������
  * @param  
  * @param  
  * @param  
  * @retval 
 *******************************************************************************/
void HDC1080_Init(void)
{
//		u8 temp = 0;
    HDC1080_Soft_Reset();
    HDC1080_Setting();
}

/*******************************************************************************
  * @brief  ��ָ���Ĵ�����ֵ
  * @param  uint8_t addr ��Ҫ��ȡ�ļĴ�����Pointer Register��
  * @param  uint8_t *buffer ����ȡ��������
  * @param  uint8_t len����ȡ�ĳ���
  * @retval 
 *******************************************************************************/
u8 HDC1080_Read_Buffer(uint8_t addr, uint8_t *buffer, uint8_t len)
{	
//  uint8_t temp = 0;
	
	IIC_Start();
		
    IIC_Send_Byte(HDC1080_Bus_Adderss);
    IIC_Wait_Ack();
		
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
		 
    IIC_Stop();

	delay_ms(1);
	IIC_Start();
	delay_ms(10);
	IIC_Send_Byte(HDC1080_Bus_Adderss|0x01);    //read
	IIC_Wait_Ack();
		 
    while ( len-- )
    {
		if (len == 0) *buffer = IIC_Read_Byte(0);
		else *buffer = IIC_Read_Byte(1);
    	buffer++;   		
    }
    IIC_Stop();
	return SET;
}

/*******************************************************************************
  * @brief  HDC1080_Read_MBuffer becareful between triger and read there is a wait.
  * @param  uint8_t addr is point register
  * @param  uint8_t *buffer is the need to read data point
  * @param  uint8_t len is the read data length
  * @retval void
 *******************************************************************************/
u8 HDC1080_Read_MBuffer(uint8_t addr, uint8_t *buffer, uint8_t len)
{
   // uint8_t temp = 0;
	
   
	IIC_Start();
		
    IIC_Send_Byte(HDC1080_Bus_Adderss);
    IIC_Wait_Ack();

    
    IIC_Send_Byte(HDC1080_TemperatureRegister);  //�Ĵ���0X00���¶Ȳ���ת��
    IIC_Wait_Ack();
		
	IIC_Stop();
    delay_ms(10);      // after triger should wait at least 6.5ms
    delay_ms(10);      //Device Start-up time
	IIC_Start();
    IIC_Send_Byte(HDC1080_Bus_Adderss|0x01); //read   
	IIC_Wait_Ack();
	
    while ( len-- )
    {
    	if ( len == 0 ) *buffer = IIC_Read_Byte(0); 
    	else *buffer = IIC_Read_Byte(1);
		buffer++;
    }
    IIC_Stop();
	return SET;
}

/*******************************************************************************
  * @brief  ��ȡ�¶�ֵ
  * @param  ��
  * @retval 
 *******************************************************************************/
float HDC1080_Read_Temper(void)
{
    uint8_t buffer[2];

    HDC1080_Read_MBuffer(HDC1080_TemperatureRegister, buffer, 2);
    //return ((buffer[0]<<8)|buffer[1]);
    return (float)((((buffer[0]<<8)|buffer[1])/65536.0)*165-40);  
}
/*******************************************************************************
  * @brief  HDC1080_Read_Humidity 
  * @param  void
  * @retval int16_t Humidity value
 *******************************************************************************/
u16 HDC1080_Read_Humidi(void)
{
    uint8_t buffer[2];
	
    HDC1080_Read_MBuffer(HDC1080_HumidityRegister, buffer, 2);

   // return (buffer[0]<<8)|buffer[1];
    return (u16)((((buffer[0]<<8)|buffer[1])/65536.0)*10000);//Humidi*100
}
/*******************************************************************************
  * @brief  HDC1080_Read_Configuration 
  * @param  void
  * @retval Config value
 *******************************************************************************/
u16 HDC1080_Read_Conf(void)
{
    uint8_t buffer[2];
	
    HDC1080_Read_Buffer(HDC1080_ConfigRegister, buffer, 2);

    return ((buffer[0]<<8)|buffer[1]);
}
/*******************************************************************************
  * @brief  HDC1080_Read_ManufacturerID ���Ĵ���0xfe������������ID
  * @param  void
  * @retval ManufacturerID 
 *******************************************************************************/
u16 HDC1080_Read_ManufacturerID(void)
{
    uint8_t buffer[2];
	
    HDC1080_Read_Buffer(HDC1080_ManufacturerIdRegister, buffer, 2);  // �Ĵ���0xfe������������ID

    return ((buffer[0]<<8)|buffer[1]);
}
/*******************************************************************************
  * @brief  HDC1080_Read_DeviceID ���Ĵ���0xff���豸��ID
  * @param  void
  * @retval DeviceID
 *******************************************************************************/
u16 HDC1080_Read_DeviceID(void)
{
    uint8_t buffer[2];
	
    HDC1080_Read_Buffer(HDC1080_DeviceIdRegister, buffer, 2);  //�Ĵ���0xff���豸��ID

    return ((buffer[0]<<8)|buffer[1]);
}

