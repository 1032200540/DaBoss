#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "RS485.h"
#include "usart.h"
#include "LED.h"
#include "timer.h"
#include "adc.h"
#include "AnalogSwitch.h"
#include "myiic.h"
#include "HDC1080.h" 

float Temper = 0;
int main(void)
{	
    uint16_t temp = 0;
    delay_init();
    NVIC_Configuration();	  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    
    RS485_LowLevel_Init();
    
    IIC_Configuration();
    HDC1080_Init();   //软件复位、温度湿度获取模式、精度配置
    temp = HDC1080_Read_DeviceID();
    printf("Device ID = 0x%x\r\n",temp);
    
    Temper = HDC1080_Read_Temper();
    printf("Temper = %f\r\n",Temper);
    
    
    AnalogSwitch_LowLevel_Init();
    AnalogSwitch_channel_2();

    IR_LED_LowLevel_Init(); 
    Motor_LED_LowLevel_Init();
    Adc_Init();		 //ADC初始化


    TIM3_Int_Init(499,7199);//10Khz的计数频率，计数到5000为500ms  

    while(1)
    {}
}







