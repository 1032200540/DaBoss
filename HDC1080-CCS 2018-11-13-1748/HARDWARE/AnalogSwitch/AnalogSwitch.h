#ifndef __ANALOGSWITCH_H
#define __ANALOGSWITCH_H	

#include "stm32f10x_rcc.h"

#define SW_1S_GPIO_CLK   RCC_APB2Periph_GPIOA
#define SW_2S_GPIO_CLK   RCC_APB2Periph_GPIOA
#define SW_3S_GPIO_CLK   RCC_APB2Periph_GPIOA
#define SW_4S_GPIO_CLK   RCC_APB2Periph_GPIOA

#define SW_1S_GPIO_Speed   GPIO_Speed_50MHz
#define SW_2S_GPIO_Speed   GPIO_Speed_50MHz
#define SW_3S_GPIO_Speed   GPIO_Speed_50MHz
#define SW_4S_GPIO_Speed   GPIO_Speed_50MHz

#define SW_1S_GPIO_Mode   GPIO_Mode_Out_OD
#define SW_2S_GPIO_Mode   GPIO_Mode_Out_OD
#define SW_3S_GPIO_Mode   GPIO_Mode_Out_OD
#define SW_4S_GPIO_Mode   GPIO_Mode_Out_OD

#define SW_1S_GPIO_PORT    GPIOA
#define SW_2S_GPIO_PORT    GPIOA
#define SW_3S_GPIO_PORT    GPIOA
#define SW_4S_GPIO_PORT    GPIOA

#define SW_1S_GPIO_Pin   GPIO_Pin_11  //PA11  SW_1S
#define SW_2S_GPIO_Pin   GPIO_Pin_12  //PA12  SW_2S
#define SW_3S_GPIO_Pin   GPIO_Pin_10  //PA10  SW_3S
#define SW_4S_GPIO_Pin   GPIO_Pin_9  //PA9  SW_4S

#define SW_1S_HIGH()  GPIO_SetBits(SW_1S_GPIO_PORT,SW_1S_GPIO_Pin) 
#define SW_1S_LOW()  GPIO_ResetBits(SW_1S_GPIO_PORT,SW_1S_GPIO_Pin)

#define SW_2S_HIGH()  GPIO_SetBits(SW_2S_GPIO_PORT,SW_2S_GPIO_Pin) 
#define SW_2S_LOW()  GPIO_ResetBits(SW_2S_GPIO_PORT,SW_2S_GPIO_Pin)

#define SW_3S_HIGH()  GPIO_SetBits(SW_3S_GPIO_PORT,SW_3S_GPIO_Pin) 
#define SW_3S_LOW()  GPIO_ResetBits(SW_3S_GPIO_PORT,SW_3S_GPIO_Pin)

#define SW_4S_HIGH()  GPIO_SetBits(SW_4S_GPIO_PORT,SW_4S_GPIO_Pin) 
#define SW_4S_LOW()  GPIO_ResetBits(SW_4S_GPIO_PORT,SW_4S_GPIO_Pin)

void AnalogSwitch_LowLevel_Init(void); 
void AnalogSwitch_channel_0(void);
void AnalogSwitch_channel_1(void);
void AnalogSwitch_channel_2(void);
void AnalogSwitch_channel_3(void);
void AnalogSwitch_channel_4(void);
 
#endif  /*   #include "AnalogSwitch.h"  */


