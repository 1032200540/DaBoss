#include "buzzer.h"

/*
*****************************************************************************
* Buzzer - 蜂鸣器接口初始化
* DESCRIPTION: -
* 
* @Param void:
* @Return :
* ----
*****************************************************************************
*/

void Buzzer_IOinit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);            //BEEP	
}

void Buzzer_BEEP(void)
{
	Beep = 1;
	delay_ms(5);
	Beep = 0;
}
