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
    NVIC_Configuration();	  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    
    RS485_LowLevel_Init();
    
    IIC_Configuration();
    HDC1080_Init();   //�����λ���¶�ʪ�Ȼ�ȡģʽ����������
    temp = HDC1080_Read_DeviceID();
    printf("Device ID = 0x%x\r\n",temp);
    
    Temper = HDC1080_Read_Temper();
    printf("Temper = %f\r\n",Temper);
    
    
    AnalogSwitch_LowLevel_Init();
    AnalogSwitch_channel_2();

    IR_LED_LowLevel_Init(); 
    Motor_LED_LowLevel_Init();
    Adc_Init();		 //ADC��ʼ��


    TIM3_Int_Init(499,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  

    while(1)
    {}
}







