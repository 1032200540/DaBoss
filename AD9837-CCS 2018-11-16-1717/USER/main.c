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
double Current = 0; //����
double Voltage = 0; //��ѹ(V)

float Temper = 22;      //�¶�
float AD_Sin1Khz = 264; //1Khz���η�������Чֵ 10k����У׼,1��      ADG1604_Channel_10K()
//float  AD_Sin1Khz = 262.4;  //1Khz���η�������Чֵ 2K����У׼,5��,   ADG1604_Channel_10K()
//float  AD_Sin1Khz = 261.66;  //1Khz���η�������Чֵ 1K����У׼,3��   ADG1604_Channel_3K()
//float  AD_Sin1Khz = 255.4;  //1Khz���η�������Чֵ 20K����У׼,5��   ADG1604_Channel_100K()
//float  AD_Sin1Khz = 259.8;  //1Khz���η�������Чֵ 200R����У׼,5��   ADG1604_Channel_1K()

//float  AD_Sin1Khz = 253.9;  //500HZ���η�������Чֵ 10k����У׼,1��   ADG1604_Channel_10K()
//float  AD_Sin1Khz = 253;  //500HZ���η�������Чֵ 2K����У׼,5��,     ADG1604_Channel_10K()
//float  AD_Sin1Khz = 248.3;  //500HZ���η�������Чֵ 100K����У׼,1��, ADG1604_Channel_10K()
//float  AD_Sin1Khz = 252;  //500HZ���η�������Чֵ 1K����У׼,3��      ADG1604_Channel_3K()

float CondNoTemper = 0; //δ�¶�ǰ�ĵ絼��
double CondTemper = 0;  //�²���ĵ絼��
//unsigned char ChannelRes = 100;  //ͨ������ֵ(10K)
double Resistance = 0;   //��Һ����
float K = 1;             //�缫Kֵ
float a = 0.019;         //�²�ϵ��
float WireRes = 0;       //���ߵ���(��)
float const ADG1604_OnRes = 0.001; //adg1604��ͨ����(K)

uint8_t Channel;
uint16_t ChannelRes;
/***************************************************
*  �Ŵ�ͨ��
*  Channel_1: 100R  
*  Channel_2: 3K   
*  Channel_3: 10K  
*  Channel_4: 100K 
*******************************************************/
//enum {Channel_500K = 1, Channel_3K = 2, Channel_10K = 3, Channel_100K = 4}; //�Ŵ�ͨ��

/***************************************************
*  Channel_1: 100R 
*  Channel_2: 3K   
*  Channel_3: 10K  
*  Channel_4: 100K 
*******************************************************/
float ChannelRes1K = 1 + ADG1604_OnRes;     //ͨ������ֵ(K)
float ChannelRes3K = 3 + ADG1604_OnRes;     //ͨ������ֵ(K)
float ChannelRes10K = 10 + ADG1604_OnRes;   //ͨ������ֵ(K)
float ChannelRes100K = 100 + ADG1604_OnRes; //ͨ������ֵ(K)

void Get_CondTemper(void);

int main(void)
{
    uint16_t NTimes = 100;
    delay_init();
    NVIC_Configuration(); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

    RS485_LowLevel_Init();

    AD9837_LowLevel_Init();
    //  AD9837_WaveSet_500HZSIN();  //500hz���Ҳ����
    AD9837_WaveSet_1KSIN(); //1Khz���Ҳ����

    ADG1604_LowLevel_Init();
    ADG1604_Channel_100K(); //100K����ͨ��

    Adc_Init();
    AD_Cond = Get_Adc_Average(8, NTimes);
    while (1)
    {
        ADG1604_Channel_100K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond <= 2000) //����100Kͨ��
        {
            AD_Sin1Khz = 255.4;
            ChannelRes = ChannelRes100K;
          //  WireRes = 0; //���Ե��ߵ���
            Get_CondTemper();
            printf("ADG1604_Channel_100K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_10K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 180 && AD_Cond <= 2000) //����10Kͨ��
        {
            AD_Sin1Khz = 262.4; //261.8;
            ChannelRes = ChannelRes10K;
          //  WireRes = 0; //���Ե��ߵ���
            Get_CondTemper();
            printf("ADG1604_Channel_10K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_3K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 180 && AD_Cond <= 1500) //����3Kͨ��
        {
            NTimes = 150;
            AD_Sin1Khz = 261.66;
            ChannelRes = ChannelRes3K;
          //  WireRes = 2; //2�����ߵ���
            Get_CondTemper();
            printf("ADG1604_Channel_3K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_1K();
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond > 450) //����1Kͨ��
        {
            NTimes = 150;
            AD_Sin1Khz = 259.8;
            ChannelRes = ChannelRes1K;
           // WireRes = 2; //2�����ߵ���
            Get_CondTemper();
            printf("ADG1604_Channel_1K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }
    }
}

void Get_CondTemper(void)
{
    //  AD_Cond =  Get_Adc_Average(8,80);
    Voltage = (3.3 / 4095) * AD_Cond * 1000; //��ѹ(mv)
    printf("AD_Cond = %f\r\n", AD_Cond);

    Current = Voltage / (ChannelRes * 1000); //����(mv/��)
    printf("Current = %f\r\n", Current);

    Resistance = (((3.3 / 4095) * AD_Sin1Khz * 1000) * 1000 / Current) - WireRes * 1000; //����(m��)
    printf("Resistance = %f\r\n", Resistance);

    CondNoTemper = (1000000000 / (((3.3 / 4095) * AD_Sin1Khz * 1000) * 1000 / Current)) / K; //δ�²�ǰ�ĵ絼��
    printf("CondNoTemper = %f\r\n", CondNoTemper);

    CondTemper = CondNoTemper * (1 + a * (25 - Temper)); //�²���ĵ絼��
    printf("Temper = %f\r\n", Temper);
    printf("CondTemper = %f\r\n", CondTemper);

    //  printf("\r\n");
}
