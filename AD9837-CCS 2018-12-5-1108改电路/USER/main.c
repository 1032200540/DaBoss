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

double Temper = 19.9;        //�¶�
double AD_Sin = 265.325; 
/***************************************************
* AD9837_WaveSet_500HZSIN()  251.125   
* AD9837_WaveSet_2KhzSIN()   263.5   
* AD9837_WaveSet_2KhzSIN()   263.9    
* AD9837_WaveSet_100HZSIN()  138  
* AD9837_WaveSet_50HZSIN()  78  
*******************************************************/

double CondNoTemper = 0; //δ�¶�ǰ�ĵ絼��
double CondTemper = 0;   //�²���ĵ絼��

double Resistance = 0;              //��Һ����
double K = 1.052;                       //�缫Kֵ
double a = 0.02;                   //�²�ϵ��
double WireRes = 0;                 //���ߵ���(��)
double const ADG1604_OnRes = 0.001; //adg1604��ͨ����(K)

uint32_t FCLK = 100;
double ChannelRes;
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
double ChannelRes1K = 1 + ADG1604_OnRes;     //ͨ������ֵ(K)
double ChannelRes3K = 3 + ADG1604_OnRes;     //ͨ������ֵ(K)
double ChannelRes10K = 10 + ADG1604_OnRes;   //ͨ������ֵ(K)
double ChannelRes100K = 100 + ADG1604_OnRes; //ͨ������ֵ(K)

void Get_CondTemper(void);

int main(void)
{
    uint16_t NTimes = 100;
    delay_init();
    NVIC_Configuration(); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

    RS485_LowLevel_Init();

    AD9837_LowLevel_Init();
    AD9837_WaveSet_HZSIN(FCLK);
    ADG1604_LowLevel_Init();
    ADG1604_Channel_100K(); //100K����ͨ��

    Adc_Init();
    AD_Cond = Get_Adc_Average(8, NTimes);
    while (1)
    {
        ADG1604_Channel_100K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond <= 2000) //����100Kͨ��,10us����
        {
            NTimes = 150;
            AD_Sin = 266;
            ChannelRes = ChannelRes100K;
            //  WireRes = 0; //���Ե��ߵ���
            Get_CondTemper();
            printf("ADG1604_Channel_100K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_10K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 390 && AD_Cond <= 2000) //����10Kͨ��,100us����
        {                                         //AD_Cond >= AD_Sin1Khz + (2000-AD_Sin1Khz)/10 - ��������
            NTimes = 150;
            AD_Sin = 266;
            ChannelRes = ChannelRes10K;
            //  WireRes = 0; //���Ե��ߵ���
            Get_CondTemper();
            printf("ADG1604_Channel_10K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_3K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 715 && AD_Cond <= 2000) //����3Kͨ��,333.33us����
        {                                         //AD_Cond >= AD_Sin1Khz + ((2000-AD_Sin1Khz)/10)*3 - ��������
            NTimes = 150;
            AD_Sin = 266;
            ChannelRes = ChannelRes3K;
            //  WireRes = 2; //2�����ߵ���
            Get_CondTemper();
            printf("ADG1604_Channel_3K()\n\n");
            AD_Cond = Get_Adc_Average(8, NTimes);
        }

        ADG1604_Channel_1K();
        AD9837_WaveSet_HZSIN(FCLK);
        AD_Cond = Get_Adc_Average(8, NTimes);
        while (AD_Cond >= 834) //����1Kͨ��,1000us����
        {                      //AD_Cond >= AD_Sin1Khz + (2000-AD_Sin1Khz)/3 - ��������
            NTimes = 150;
            AD_Sin = 266;
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
    Voltage = (3.3 / 4095) * (AD_Cond - AD_Sin) * 1000; //��ѹ(mv)
    printf("AD_Cond = %f\r\n", AD_Cond);

    Current = Voltage / (ChannelRes * 1000); //����(mv/��)
    printf("Current = %f\r\n", Current);

    Resistance = (((3.3 / 4095) * AD_Sin * 1000) * 1000 / Current) - WireRes * 1000; //����(m��)
    printf("Resistance = %f\r\n", Resistance);

    CondNoTemper = (1000000000 / (((3.3 / 4095) * AD_Sin * 1000) * 1000 / Current)) * K; //δ�²�ǰ�ĵ絼��
    printf("CondNoTemper = %f\r\n", CondNoTemper);

    CondTemper = CondNoTemper * (1 + a * (25 - Temper)); //�²���ĵ絼��
    printf("Temper = %f\r\n", Temper);
    printf("CondTemper = %f\r\n", CondTemper);

    //  printf("\r\n");
}
