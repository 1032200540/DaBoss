#include "CH340.h"

uint8_t TxBuffer1[] = "串口DMA实验";
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define TxBufferSize1   (countof(TxBuffer1) - 1)

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void CH340_RCC_Configuration(void)
{
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Enable USARTy Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

	/* DMA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void CH340_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Configure USARTy Tx as alternate function open-drain */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    //PA9 TX
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
}

void CH340_USART_Configuration(void)
{
	
  /* USART1 as follow:
        - BaudRate = 128000 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */

  USART_InitTypeDef USART_InitStructure;

  USART_InitStructure.USART_BaudRate = 256000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
  
  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);

  /* Enable USARTy Half Duplex Mode*/
  USART_HalfDuplexCmd(USART1, ENABLE);
	
}

/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40013804; //外设地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1; //存储器地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //传输方向,外设是目的地址
  DMA_InitStructure.DMA_BufferSize = TxBufferSize1; // 传输数目
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址增量模式
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // 存储器地址增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;// 外设数据宽度
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 存储器数据宽度
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // 模式选择
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; // 通道优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // 存储器到存储器模式
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
			
/* Enable USARTy DMA TX request */
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	
/* Enable USARTy DMA TX Channel */
  DMA_Cmd(DMA1_Channel4, ENABLE);

}

/**
  * @brief  CH340底层配置
  * @param  None
  * @retval None
  */
void CH340_LowLevel_Init(void)
{
	CH340_RCC_Configuration();
	CH340_GPIO_Configuration();
	CH340_USART_Configuration();
}



