 #include "AnalogSwitch.h"

void AnalogSwitch_LowLevel_Init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = SW_1S_GPIO_Pin;    //PA11  SW_1S
    GPIO_InitStructure.GPIO_Speed = SW_1S_GPIO_Speed;
    GPIO_InitStructure.GPIO_Mode = SW_1S_GPIO_Mode;
    GPIO_Init(SW_1S_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = SW_2S_GPIO_Pin;    //PA12  SW_2S 
    GPIO_Init(SW_2S_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = SW_3S_GPIO_Pin;    //PA10  SW_3S
    GPIO_Init(SW_3S_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = SW_4S_GPIO_Pin;    //PA9  SW_4S
    GPIO_Init(SW_4S_GPIO_PORT, &GPIO_InitStructure);
}



void AnalogSwitch_channel_0(void)
{
    SW_3S_HIGH();
    SW_4S_HIGH();
    SW_2S_LOW();
}

void AnalogSwitch_channel_1(void)
{
    SW_3S_HIGH();
    SW_4S_HIGH();
    SW_2S_HIGH();
}

void AnalogSwitch_channel_2(void)
{
    SW_3S_HIGH();
    SW_4S_LOW();
    SW_2S_LOW();
}

void AnalogSwitch_channel_3(void)
{
    SW_3S_HIGH();
    SW_4S_LOW();
    SW_2S_HIGH();
}

void AnalogSwitch_channel_4(void)
{
    SW_3S_LOW();
    SW_4S_LOW();
    SW_2S_LOW();
}






