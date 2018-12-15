/**
  ******************************************************************************
  * @file    FSMC/SRAM/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#ifdef STM32F10X_HD_VL /* High-density Value line devices */
#include "stm32100e_eval_fsmc_sram.h"
#else /* High- and XL-denisty devices */
#include "stm3210e_eval_fsmc_sram.h"
#endif

#include "stm32_eval.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup FSMC_SRAM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE 0x400
#define WRITE_READ_ADDR 0x8000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t TxBuffer[BUFFER_SIZE];
uint16_t RxBuffer[BUFFER_SIZE];
uint32_t WriteReadStatus = 0, Index = 0;

/* Private function prototypes -----------------------------------------------*/
void Fill_Buffer(uint16_t *pBuffer, uint16_t BufferLenght, uint32_t Offset);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< 在此阶段，已经配置了微控制器时钟设置，这是通过SystemInit（）函数完成的，
  该函数在从启动文件（startup_stm32f10x_xx.s）调用之前分支到应用程序main。
  要重新配置SystemInit（）函数的默认设置，请参阅 system_stm32f10x.c文件
     */

  /* 初始化安装在STM3210X-EVAL板上的Leds */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);

  /* 写入/读取FSMC SRAM存储器  *************************************/
  /* 启用FSMC时钟 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  /* 配置FSMC Bank1 NOR / SRAM3 */
  SRAM_Init();

  /* 将数据写入FSMC SRAM存储器 */
  /* Fill the buffer to send */
  Fill_Buffer(TxBuffer, BUFFER_SIZE, 0x3212);
  SRAM_WriteBuffer(TxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);

  /* 从FSMC SRAM存储器读取数据 */
  SRAM_ReadBuffer(RxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);

  /* 回读SRAM存储器并检查内容的正确性 */
  for (Index = 0x00; (Index < BUFFER_SIZE) && (WriteReadStatus == 0); Index++)
  {
    if (RxBuffer[Index] != TxBuffer[Index])
    {
      WriteReadStatus = Index + 1;
    }
  }

  if (WriteReadStatus == 0)
  {
    /* OK */
    /* Turn on LED1 */
    STM_EVAL_LEDOn(LED1);
  }
  else
  {
    /* KO */
    /* Turn on LED2 */
    STM_EVAL_LEDOn(LED2);
  }

  while (1)
  {
  }
}

/**
  * @brief  Fill the global buffer
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferSize: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  */
void Fill_Buffer(uint16_t *pBuffer, uint16_t BufferLenght, uint32_t Offset)
{
  uint16_t IndexTmp = 0;

  /* Put in global buffer same values */
  for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++)
  {
    pBuffer[IndexTmp] = IndexTmp + Offset;
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  报告源文件的名称以及发生assert_param错误的源行号。
  * @param  file: 指向源文件名的指针
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
