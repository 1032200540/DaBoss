#include "CPU.H"
#include "KeyScan.h"
#include "delay.h"
#include "buzzer.h"
#include "Menu.h"


/*
*****************************************************************************
* KeyScan - 按键接口初始化
* DESCRIPTION: -
* 
* @Param void:
* @Return :
* ----
*****************************************************************************
*/
void KEY_IOinit(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_Init(GPIOF, &GPIO_InitStructure);             // Key3 GPIOF.11
		 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		   // Key2 GPIOF.12
	GPIO_Init(GPIOF, &GPIO_InitStructure);	 		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		   // Key1 GPIOF.13
	GPIO_Init(GPIOF, &GPIO_InitStructure);	 			    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;		   // Key0 GPIOF.14
	GPIO_Init(GPIOF, &GPIO_InitStructure);	 
	
	#if EXTIX_IO   //如使用IO中断扫描
	EXTIX_IO_Init();
	#endif
}


#if EXTIX_IO   //如使用IO中断扫描

void EXTIX_IO_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

  //GPIOF.11 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource11);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;	//KEY3
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOF.12	  中断线以及中断初始化配置 下降沿触发 //KEY2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource12);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOF.13	  中断线以及中断初始化配置  下降沿触发	//KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource13);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  //GPIOF.14  中断线以及中断初始化配置  下降沿触发 Key0
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource14); 

 	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//使能按键外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

}

//外部中断0服务程序 
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//消抖
	CheckKey();
	EXTI_ClearITPendingBit(EXTI_Line14); //清除LINE14上的中断标志位	
	EXTI_ClearITPendingBit(EXTI_Line13); //清除LINE13上的中断标志位	
	EXTI_ClearITPendingBit(EXTI_Line12); //清除LINE12上的中断标志位
	EXTI_ClearITPendingBit(EXTI_Line11); //清除LINE11上的中断标志位
}

#endif


/*
*****************************************************************************
* KeyScan - 键盘扫描函数
* DESCRIPTION: -
* 判4个按键那个有按下
* @Param void:
* @Return :有按键 返回键值 无按键 返回false 因此键值定义不能为false
* ----
*****************************************************************************
*/
u8 KeyScan(void)
{
	if((Key0==0)||(Key1==0)||(Key2==0)||(Key3==0))
	{
		delay_ms(30);
		if((Key0==0)||(Key1==0)||(Key2==0)||(Key3==0))
		{
			delay_ms(30);
			if((Key0==0)&&(Key1==1)&&(Key2==1)&&(Key3==1))
			{	   //Key0  GPIOF.14 
				Buzzer_BEEP(); 
				return Key_Enter;
			}
			else if((Key0==1)&&(Key1==0)&&(Key2==1)&&(Key3==1))
			{//Key1 GPIOF.13
				Buzzer_BEEP();				
				return Key_Down;
			}
			else if((Key0==1)&&(Key1==1)&&(Key2==0)&&(Key3==1))
			{//Key2 GPIOF.12
				Buzzer_BEEP();				
				return Key_Up;
			}
			else if((Key0==1)&&(Key1==1)&&(Key2==1)&&(Key3==0))
			{//Key3 GPIOF.11
				Buzzer_BEEP();			
				return Key_Back;
			}
			else return false;
		}
		else return false; //no key press
	}
	else return false;
}



#if 0
/*
*****************************************************************************
* WaitKey - 死等一个有效按键输入
* DESCRIPTION: -
*
* @Param void:
* @Return : 按键键值
* ----
*****************************************************************************
*/
U8 WaitKey(void)
{

while(1)
{
    switch(KeyScan())
	{
        case Key_Up:
		{
			return Key_Up;
            break;
        }
        case Key_Back:
		{
            return Key_Back;
            break;
        }
        case Key_Up:
		{
            return Key_Up;
            break;
        }
        case Key_Down:
		{
            return Key_Down;
            break;
        }
        default:
            break;
    }
}

}
#endif
