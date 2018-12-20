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

double Temper = 19.9;        //温度
double AD_Sin = 265.325; 
/***************************************************
* AD9837_WaveSet_500HZSIN()  251.125   
* AD9837_WaveSet_2KhzSIN()   263.5   
* AD9837_WaveSet_2KhzSIN()   263.9    
* AD9837_WaveSet_100HZSIN()  138  
* AD9837_WaveSet_50HZSIN()  78  
*******************************************************/

double CondNoTemper = 0; //未温度前的电导率
double CondTemper = 0;   //温补后的电导率

double Resistance = 0;              //溶液电阻
double K = 1.052;                       //电极K值
double a = 0.02;                   //温补系数
double WireRes = 0;                 //导线电阻(Ω)
double const ADG1604_OnRes = 0.001; //adg1604导通电阻(K)

uint32_t FCLK = 100;
double ChannelRes;
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
double ChannelRes1K = 1 + ADG1604_OnRes;     //通道电阻值(K)
double ChannelRes3K = 3 + ADG1604_OnRes;     //通道电阻值(K)
double ChannelRes10K = 10 + ADG1604_OnRes;   //通道电阻值(K)
double ChannelRes100K = 100 + ADG1604_OnRes; //通道电阻值(K)

void Get_CondTemper(void);

int main(void)
{
    uint16_t NTimes = 100;
    delay_init();
    NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

    RS485_LowLevel_Init();

    AD9837_LowLevel_Init();
    AD9837_WaveSet_HZSIN(FCLK);
    ADG1604_LowLevel_Init();
    ADG1604_Channel_100K(); //100K电阻通道

    Adc_Init();
    AD_Cond = Get_Adc_Average(8, NTimes);
    while (1)
    {
        ADG1604_Channel_100K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond <= 2000) //处于100K通道,10us附近
        {
            NTimes = 150;
            AD_Sin = 266;
            ChannelRes = ChannelRes100K;
            //  WireRes = 0; //忽略导线电阻
            Get_CondTemper();
            printf("ADG1604_Channel_100K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_10K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 390 && AD_Cond <= 2000) //处于10K通道,100us附近
        {                                         //AD_Cond >= AD_Sin1Khz + (2000-AD_Sin1Khz)/10 - 波动区间
            NTimes = 150;
            AD_Sin = 266;
            ChannelRes = ChannelRes10K;
            //  WireRes = 0; //忽略导线电阻
            Get_CondTemper();
            printf("ADG1604_Channel_10K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_3K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 715 && AD_Cond <= 2000) //处于3K通道,333.33us附近
        {                                         //AD_Cond >= AD_Sin1Khz + ((2000-AD_Sin1Khz)/10)*3 - 波动区间
            NTimes = 150;
            AD_Sin = 266;
            ChannelRes = ChannelRes3K;
            //  WireRes = 2; //2Ω导线电阻
            Get_CondTemper();
            printf("ADG1604_Channel_3K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_1K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 834) //处于1K通道,1000us附近
        {                      //AD_Cond >= AD_Sin1Khz + (2000-AD_Sin1Khz)/3 - 波动区间
            NTimes = 150;
            AD_Sin = 266;
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
    Voltage = (3.3 / 4095) * (AD_Cond - AD_Sin) * 1000; //电压(mv)
    printf("AD_Cond = %f\r\n", AD_Cond);

    Current = Voltage / (ChannelRes * 1000); //电流(mv/Ω)
    printf("Current = %f\r\n", Current);

    Resistance = (((3.3 / 4095) * AD_Sin * 1000) * 1000 / Current) - WireRes * 1000; //电阻(mΩ)
    printf("Resistance = %f\r\n", Resistance);

    CondNoTemper = (1000000000 / (((3.3 / 4095) * AD_Sin * 1000) * 1000 / Current)) * K; //未温补前的电导率
    printf("CondNoTemper = %f\r\n", CondNoTemper);

    CondTemper = CondNoTemper * (1 + a * (25 - Temper)); //温补后的电导率
    printf("Temper = %f\r\n", Temper);
    printf("CondTemper = %f\r\n", CondTemper);

    //  printf("\r\n");
}
