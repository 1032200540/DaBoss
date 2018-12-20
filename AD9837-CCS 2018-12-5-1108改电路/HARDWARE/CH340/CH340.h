#ifndef __RS485_H
#define __RS485_H 

#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"



void RS485_RCC_Configuration(void);
void RS485_GPIO_Configuration(void);
void RS485_USART_Configuration(void);
void DMA_Configuration(void);
void RS485_LowLevel_Init(void); 


#endif















