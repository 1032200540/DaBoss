
#ifndef __STM32100E_EVAL_H
#define __STM32100E_EVAL_H


//AD9837 SPI Interface pins
  
#define AD9837_SPI                       SPI1
#define AD9837_SPI_CLK                   RCC_APB2Periph_SPI1

#define AD9837_SPI_SCK_PIN               GPIO_Pin_3                  /* PB.03 */
#define AD9837_SPI_SCK_GPIO_PORT         GPIOB                       /* GPIOB */
#define AD9837_SPI_SCK_GPIO_CLK          RCC_APB2Periph_GPIOB

#define AD9837_SPI_MOSI_PIN              GPIO_Pin_5                  /* PB.05 */
#define AD9837_SPI_MOSI_GPIO_PORT        GPIOB                       /* GPIOB */
#define AD9837_SPI_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOB

#define AD9837_CS_PIN                    GPIO_Pin_15                 /* PA.15 */
#define AD9837_CS_GPIO_PORT              GPIOA                       /* GPIOA */
#define AD9837_CS_GPIO_CLK               RCC_APB2Periph_GPIOA

void AD9837_LowLevel_Init(void); 


//RS485 USART Interface pins
#define RS485_GPIO_CLK                   RCC_APB2Periph_GPIOB      
#define RS485_USART_CLK                  RCC_APB1Periph_USART3    
#define RS485_USART_TX_GPIO_PORT         GPIOB                   //PB10 TX
#define RS485_USART_TX_GPIO_PIN          GPIO_Pin_10 

#define RS485_DE_CLK                     RCC_APB2Periph_GPIOA 
#define RS485_DE_GPIO_PORT               GPIOA                 //PA1 485DE
#define RS485_DE_GPIO_PIN                GPIO_Pin_1 


//ADG1604 
/*A0 PA6*/
#define ADG1604_A0_GPIO_CLK              RCC_APB2Periph_GPIOA 
#define ADG1604_A0_GPIO_PIN              GPIO_Pin_6 
#define ADG1604_A0_GPIO_PORT             GPIOA
/*A1 PA5*/
#define ADG1604_A1_GPIO_CLK              RCC_APB2Periph_GPIOA 
#define ADG1604_A1_GPIO_PIN              GPIO_Pin_5 
#define ADG1604_A1_GPIO_PORT             GPIOA
/*A2 PA4*/
#define ADG1604_A2_GPIO_CLK              RCC_APB2Periph_GPIOA 
#define ADG1604_A2_GPIO_PIN              GPIO_Pin_4 
#define ADG1604_A2_GPIO_PORT             GPIOA
/*EN PA2*/
#define ADG1604_EN_GPIO_CLK              RCC_APB2Periph_GPIOA 
#define ADG1604_EN_GPIO_PIN              GPIO_Pin_2 
#define ADG1604_EN_GPIO_PORT             GPIOA

void ADG1604_LowLevel_Init(void); 


#endif      /**  stm32100e_eval.h   **/

  
