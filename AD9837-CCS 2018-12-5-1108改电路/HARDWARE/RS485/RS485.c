#include "RS485.h"
#include "stm32100e_eval.h"

uint8_t TxBuffer1[] = "����DMAʵ��";
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define TxBufferSize1   (countof(TxBuffer1) - 1)

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RS485_RCC_Configuration(void)
{
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RS485_GPIO_CLK , ENABLE);

	/* Enable USART Clock */
	RCC_APB1PeriphClockCmd(RS485_USART_CLK, ENABLE); 

	/* DMA clock enable */
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

}

/**
  * @brief  485GPIO����
  * @param  None
  * @retval None
  */
void RS485_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure USARTy Tx as alternate function open-drain */
    GPIO_InitStructure.GPIO_Pin = RS485_USART_TX_GPIO_PIN;    //PB10 TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(RS485_USART_TX_GPIO_PORT, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin = RS485_DE_GPIO_PIN;    //PA1 485DE
    GPIO_Init(RS485_DE_GPIO_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(RS485_DE_GPIO_PORT,RS485_DE_GPIO_PIN);
}

void RS485_USART_Configuration(void)
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

  USART_InitStructure.USART_BaudRate = 128000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USART3 */
  USART_Init(USART3, &USART_InitStructure);
  
  /* Enable the USART3 */
  USART_Cmd(USART3, ENABLE);

  /* Enable USARTy Half Duplex Mode*/
//  USART_HalfDuplexCmd(USART3, ENABLE);
	
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
  DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40013804; //�����ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1; //�洢����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���䷽��,������Ŀ�ĵ�ַ
  DMA_InitStructure.DMA_BufferSize = TxBufferSize1; // ������Ŀ
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // �����ַ����ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // �洢����ַ����ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;// �������ݿ��
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // �洢�����ݿ��
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // ģʽѡ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; // ͨ�����ȼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // �洢�����洢��ģʽ
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
			
/* Enable USARTy DMA TX request */
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	
/* Enable USARTy DMA TX Channel */
  DMA_Cmd(DMA1_Channel4, ENABLE);

}

/**
  * @brief  RS485�ײ�����
  * @param  None
  * @retval None
  */
void RS485_LowLevel_Init(void)
{
	RS485_RCC_Configuration();
	RS485_GPIO_Configuration();
	RS485_USART_Configuration();
}



