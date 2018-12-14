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
#include "stm32100e_eval.h"
#include "AD9837.h"
#include "ADG1604.h"

float AD_Cond = 0;
double Current = 0; //电流
double Voltage = 0; //电压(V)

float Temper = 22;      //温度
float AD_Sin1Khz = 264; //1Khz波形发生器有效值 10k电阻校准,1倍      ADG1604_Channel_10K()
//float  AD_Sin1Khz = 262.4;  //1Khz波形发生器有效值 2K电阻校准,5倍,   ADG1604_Channel_10K()
//float  AD_Sin1Khz = 261.66;  //1Khz波形发生器有效值 1K电阻校准,3倍   ADG1604_Channel_3K()
//float  AD_Sin1Khz = 255.4;  //1Khz波形发生器有效值 20K电阻校准,5倍   ADG1604_Channel_100K()
//float  AD_Sin1Khz = 259.8;  //1Khz波形发生器有效值 200R电阻校准,5倍   ADG1604_Channel_1K()

//float  AD_Sin1Khz = 253.9;  //500HZ波形发生器有效值 10k电阻校准,1倍   ADG1604_Channel_10K()
//float  AD_Sin1Khz = 253;  //500HZ波形发生器有效值 2K电阻校准,5倍,     ADG1604_Channel_10K()
//float  AD_Sin1Khz = 248.3;  //500HZ波形发生器有效值 100K电阻校准,1倍, ADG1604_Channel_10K()
//float  AD_Sin1Khz = 252;  //500HZ波形发生器有效值 1K电阻校准,3倍      ADG1604_Channel_3K()

float CondNoTemper = 0; //未温度前的电导率
double CondTemper = 0;  //温补后的电导率
//unsigned char ChannelRes = 100;  //通道电阻值(10K)
double Resistance = 0;   //溶液电阻
float K = 1;             //电极K值
float a = 0.019;         //温补系数
float WireRes = 0;       //导线电阻(Ω)
float const ADG1604_OnRes = 0.001; //adg1604导通电阻(K)

uint8_t Channel;
uint16_t ChannelRes;
/***************************************************
*  放大通道
*  Channel_1: 100R  
*  Channel_2: 3K   
*  Channel_3: 10K  
*  Channel_4: 100K 
*******************************************************/
//enum {Channel_500K = 1, Channel_3K = 2, Channel_10K = 3, Channel_100K = 4}; //放大通道

/***************************************************
*  Channel_1: 100R 
*  Channel_2: 3K   
*  Channel_3: 10K  
*  Channel_4: 100K 
*******************************************************/
float ChannelRes1K = 1 + ADG1604_OnRes;     //通道电阻值(K)
float ChannelRes3K = 3 + ADG1604_OnRes;     //通道电阻值(K)
float ChannelRes10K = 10 + ADG1604_OnRes;   //通道电阻值(K)
float ChannelRes100K = 100 + ADG1604_OnRes; //通道电阻值(K)

void Get_CondTemper(void);

int main(void)
{
    uint16_t NTimes = 100;
    delay_init();
    NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

    RS485_LowLevel_Init();

    AD9837_LowLevel_Init();
    //  AD9837_WaveSet_500HZSIN();  //500hz正弦波输出
    AD9837_WaveSet_1KSIN(); //1Khz正弦波输出

    ADG1604_LowLevel_Init();
    ADG1604_Channel_100K(); //100K电阻通道

    Adc_Init();
    AD_Cond = Get_Adc_Average(8, NTimes);
    while (1)
    {
        ADG1604_Channel_100K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond <= 2000) //处于100K通道
        {
            AD_Sin1Khz = 255.4;
            ChannelRes = ChannelRes100K;
          //  WireRes = 0; //忽略导线电阻
            Get_CondTemper();
            printf("ADG1604_Channel_100K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_10K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 180 && AD_Cond <= 2000) //处于10K通道
        {
            AD_Sin1Khz = 262.4; //261.8;
            ChannelRes = ChannelRes10K;
          //  WireRes = 0; //忽略导线电阻
            Get_CondTemper();
            printf("ADG1604_Channel_10K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_3K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 180 && AD_Cond <= 1500) //处于3K通道
        {
            NTimes = 150;
            AD_Sin1Khz = 261.66;
            ChannelRes = ChannelRes3K;
          //  WireRes = 2; //2Ω导线电阻
            Get_CondTemper();
            printf("ADG1604_Channel_3K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_1K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond > 450) //处于1K通道
        {
            NTimes = 150;
            AD_Sin1Khz = 259.8;
            ChannelRes = ChannelRes1K;
           // WireRes = 2; //2Ω导线电阻
            Get_CondTemper();
            printf("ADG1604_Channel_1K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }
    }
}

void Get_CondTemper(void)
{
    //  AD_Cond =  Get_Adc_Average(8,80);
    Voltage = (3.3 / 4095) * AD_Cond * 1000; //电压(mv)
    printf("AD_Cond = %f\r\n", AD_Cond);

    Current = Voltage / (ChannelRes * 1000); //电流(mv/Ω)
    printf("Current = %f\r\n", Current);

    Resistance = (((3.3 / 4095) * AD_Sin1Khz * 1000) * 1000 / Current) - WireRes * 1000; //电阻(mΩ)
    printf("Resistance = %f\r\n", Resistance);

    CondNoTemper = (1000000000 / (((3.3 / 4095) * AD_Sin1Khz * 1000) * 1000 / Current)) / K; //未温补前的电导率
    printf("CondNoTemper = %f\r\n", CondNoTemper);

    CondTemper = CondNoTemper * (1 + a * (25 - Temper)); //温补后的电导率
    printf("Temper = %f\r\n", Temper);
    printf("CondTemper = %f\r\n", CondTemper);

    //  printf("\r\n");
}
