#ifndef __LED_H
#define __LED_H	

#include "stm32f10x_rcc.h"
//红外LED
#define IR_LED_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IR_LED_GPIO_Speed    GPIO_Speed_50MHz
#define IR_LED_GPIO_Mode     GPIO_Mode_Out_OD
#define IR_LED_PORT      GPIOA
#define IR_LED_Pin    GPIO_Pin_8  //PA8

#define IR_LED_HIGH()  GPIO_SetBits(IR_LED_PORT,IR_LED_Pin) 
#define IR_LED_LOW()  GPIO_ResetBits(IR_LED_PORT,IR_LED_Pin)

// 电机定位LED
#define Motor_LED_GPIO_CLK   RCC_APB2Periph_GPIOA
#define Motor_LED_GPIO_Speed    GPIO_Speed_50MHz
#define Motor_LED_GPIO_Mode    GPIO_Mode_Out_PP
#define Motor_LED_PORT     GPIOA
#define Motor_LED_Pin      GPIO_Pin_7  //PA7

#define Motor_LED_HIGH()  GPIO_SetBits(Motor_LED_PORT,Motor_LED_Pin) 
#define Motor_LED_LOW()  GPIO_ResetBits(Motor_LED_PORT,Motor_LED_Pin)

void IR_LED_LowLevel_Init(void); 
void Motor_LED_LowLevel_Init(void); 

#endif /*  #include "LED.h"*/
