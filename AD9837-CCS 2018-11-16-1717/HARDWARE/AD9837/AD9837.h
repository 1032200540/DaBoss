#ifndef _AD9837_H_
#define _AD9837_H_

#include "stm32f10x_gpio.h"

#define AD9837_CS_HIGH() GPIO_SetBits(AD9837_CS_GPIO_PORT, AD9837_CS_PIN)
#define AD9837_CS_LOW() GPIO_ResetBits(AD9837_CS_GPIO_PORT, AD9837_CS_PIN)
#define AD9837_MOSI_HIGH() GPIO_SetBits(AD9837_SPI_MOSI_GPIO_PORT, AD9837_SPI_MOSI_PIN)
#define AD9837_MOSI_LOW() GPIO_ResetBits(AD9837_SPI_MOSI_GPIO_PORT, AD9837_SPI_MOSI_PIN)
#define AD9837_SCK_HIGH() GPIO_SetBits(AD9837_SPI_SCK_GPIO_PORT, AD9837_SPI_SCK_PIN)
#define AD9837_SCK_LOW() GPIO_ResetBits(AD9837_SPI_SCK_GPIO_PORT, AD9837_SPI_SCK_PIN)

void AD9837_SPI_Init(void);
void AD9837_Write(unsigned short val);
void AD9837_WaveSet_1KSIN(void);
void AD9837_WaveSet_500HZSIN(void);

#endif // _AD9837_H
