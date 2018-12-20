#include "HDC1080.h" 
#include "delay.h"
/*******************************************************************************
  * HDC1080,写：start ==》senddata(Bus_Adderss(最后一位为0，表示写)) ==》senddata(Pointer Register)
  *              ==》senddata(Data MSB) ==》senddata(Data LSB) ==》stop
  * HDC1080,读：start ==》senddata(Bus_Adderss(最后一位为0，表示写)) ==》senddata(Pointer Register)
  *         ==》senddata(Bus_Adderss(最后一位为1，表示读)) ==》senddata(Data MSB) ==》senddata(Data LSB) ==》stop
  * 转换模式为1时，应先读温度（发送温度寄存器触发转换），再度湿度。
  * 转换模式为0时：发送温度寄存器，触发温度转换；发送湿度寄存器，触发湿度转换。  
 *******************************************************************************/

/*******************************************************************************
  * @brief  
  * @param  uint8_t addr, 写入的目的地址
  * @param  uint8_t *buffer, 写入的数据
  * @param  uint8_t len,写入的个数
  * @retval u8 ，0成功，1失败
 *******************************************************************************/
u8 HDC1080_Write_Buffer(uint8_t addr, uint8_t *buffer, uint8_t len)
{
	IIC_Start();  //起始信号	 
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
  * @brief  操作配置寄存器0x02，写入配置。软件复位。
  * @param  无  
  * @retval 无
 *******************************************************************************/
void HDC1080_Soft_Reset(void)
{
    u8 temp[2];
    temp[0] = 0x80; 
    temp[1] = 0x00;
    HDC1080_Write_Buffer(HDC1080_ConfigRegister, temp, 2); // 操作寄存器0x02，写入配置
    delay_ms(20);//there should be waiting for more than 15 ms.
}
/*******************************************************************************
  * @brief  温度湿度获取模式和精度配置
  * @param  无 
  * @retval 无
 *******************************************************************************/
void HDC1080_Setting(void)
{
    uint16_t tempcom = 0;
    uint8_t temp[2];
	
    tempcom |= 1<<HDC1080_Mode ;//依次获得温度和湿度，首先是温度。
    // 温度与温度都为14bit
    temp[0] = (uint8_t)(tempcom >> 8); 
    temp[1] = (uint8_t)tempcom;
    HDC1080_Write_Buffer(HDC1080_ConfigRegister, temp, 2);
}
/*******************************************************************************
  * @brief  软件复位、温度湿度获取模式、精度配置
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
  * @brief  对指定寄存器的值
  * @param  uint8_t addr ，要读取的寄存器（Pointer Register）
  * @param  uint8_t *buffer ，读取到的数据
  * @param  uint8_t len，读取的长度
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

    
    IIC_Send_Byte(HDC1080_TemperatureRegister);  //寄存器0X00，温度测量转换
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
  * @brief  读取温度值
  * @param  无
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
  * @brief  HDC1080_Read_ManufacturerID ，寄存器0xfe，德州仪器的ID
  * @param  void
  * @retval ManufacturerID 
 *******************************************************************************/
u16 HDC1080_Read_ManufacturerID(void)
{
    uint8_t buffer[2];
	
    HDC1080_Read_Buffer(HDC1080_ManufacturerIdRegister, buffer, 2);  // 寄存器0xfe，德州仪器的ID

    return ((buffer[0]<<8)|buffer[1]);
}
/*******************************************************************************
  * @brief  HDC1080_Read_DeviceID ，寄存器0xff，设备的ID
  * @param  void
  * @retval DeviceID
 *******************************************************************************/
u16 HDC1080_Read_DeviceID(void)
{
    uint8_t buffer[2];
	
    HDC1080_Read_Buffer(HDC1080_DeviceIdRegister, buffer, 2);  //寄存器0xff，设备的ID

    return ((buffer[0]<<8)|buffer[1]);
}

