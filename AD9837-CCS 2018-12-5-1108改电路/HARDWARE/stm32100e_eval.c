#include "stm32100e_eval.h"
#include "stm32f10x_spi.h"


/**
  * @brief  
  * @param  None
  * @retval None
  */
void AD9837_LowLevel_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< AD9837_SPI_CS_GPIO, AD9837_SPI_MOSI_GPIO, AD9837_SPI_MISO_GPIO and AD9837_SPI_SCK_GPIO Periph clock enable */
    RCC_APB2PeriphClockCmd(AD9837_CS_GPIO_CLK |RCC_APB2Periph_AFIO | AD9837_SPI_MOSI_GPIO_CLK | AD9837_SPI_SCK_GPIO_CLK, ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);   //禁用JTAG模式，将PA15(AD9837_CS_PIN )复用为普通IO口
 
    /*!< Configure AD9837_SPI pins: SCK */
    GPIO_InitStructure.GPIO_Pin = AD9837_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(AD9837_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(AD9837_SPI_SCK_GPIO_PORT ,AD9837_SPI_SCK_PIN);

    /*!< Configure AD9837_SPI pins: MOSI */
    GPIO_InitStructure.GPIO_Pin = AD9837_SPI_MOSI_PIN;
    GPIO_Init(AD9837_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(AD9837_SPI_MOSI_GPIO_PORT ,AD9837_SPI_MOSI_PIN);

    /*!< Configure AD9837_CS_PIN pin: AD9837 Card CS pin */
    GPIO_InitStructure.GPIO_Pin = AD9837_CS_PIN;
    GPIO_Init(AD9837_CS_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(AD9837_CS_GPIO_PORT,AD9837_SPI_SCK_PIN);
}

/**
  * @brief  
  * @param  None
  * @retval None
  */

void ADG1604_LowLevel_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

	/**/
	RCC_APB2PeriphClockCmd(ADG1604_A0_GPIO_CLK|ADG1604_A1_GPIO_CLK|ADG1604_A2_GPIO_CLK|ADG1604_EN_GPIO_CLK, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);   //禁用JTAG模式，将PA15(AD9837_CS_PIN )复用为普通IO口

	/*A0 */
	GPIO_InitStructure.GPIO_Pin = ADG1604_A0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(ADG1604_A0_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ADG1604_A0_GPIO_PORT ,ADG1604_A0_GPIO_PIN);

	/*A1*/
	GPIO_InitStructure.GPIO_Pin = ADG1604_A1_GPIO_PIN;
	GPIO_Init(ADG1604_A1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ADG1604_A1_GPIO_PORT ,ADG1604_A1_GPIO_PIN);

	/*A2*/
	GPIO_InitStructure.GPIO_Pin = ADG1604_A2_GPIO_PIN;
	GPIO_Init(ADG1604_A2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ADG1604_A2_GPIO_PORT,ADG1604_A2_GPIO_PIN);

	/*EN*/
	GPIO_InitStructure.GPIO_Pin = ADG1604_EN_GPIO_PIN;
	GPIO_Init(ADG1604_EN_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ADG1604_EN_GPIO_PORT,ADG1604_EN_GPIO_PIN);
}


