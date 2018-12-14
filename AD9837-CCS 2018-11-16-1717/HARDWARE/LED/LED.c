 #include "LED.h"

void IR_LED_LowLevel_Init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(IR_LED_GPIO_CLK, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = IR_LED_Pin;    //PA8 
    GPIO_InitStructure.GPIO_Speed = IR_LED_GPIO_Speed;
    GPIO_InitStructure.GPIO_Mode = IR_LED_GPIO_Mode;
    GPIO_Init(IR_LED_PORT, &GPIO_InitStructure);
    
    IR_LED_HIGH();
}

void Motor_LED_LowLevel_Init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(Motor_LED_GPIO_CLK, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = Motor_LED_Pin;    //PA7
    GPIO_InitStructure.GPIO_Speed = Motor_LED_GPIO_Speed;
    GPIO_InitStructure.GPIO_Mode = Motor_LED_GPIO_Mode;
    GPIO_Init(Motor_LED_PORT, &GPIO_InitStructure);
    
    Motor_LED_LOW();
}
