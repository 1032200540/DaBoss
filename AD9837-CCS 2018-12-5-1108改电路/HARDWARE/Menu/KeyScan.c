#include "CPU.H"
#include "KeyScan.h"
#include "delay.h"
#include "buzzer.h"
#include "Menu.h"


/*
*****************************************************************************
* KeyScan - �����ӿڳ�ʼ��
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
	
	#if EXTIX_IO   //��ʹ��IO�ж�ɨ��
	EXTIX_IO_Init();
	#endif
}


#if EXTIX_IO   //��ʹ��IO�ж�ɨ��

void EXTIX_IO_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

  //GPIOF.11 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource11);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;	//KEY3
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOF.12	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource12);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOF.13	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource13);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  //GPIOF.14  �ж����Լ��жϳ�ʼ������  �½��ش��� Key0
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource14); 

 	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//ʹ�ܰ����ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

}

//�ⲿ�ж�0������� 
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//����
	CheckKey();
	EXTI_ClearITPendingBit(EXTI_Line14); //���LINE14�ϵ��жϱ�־λ	
	EXTI_ClearITPendingBit(EXTI_Line13); //���LINE13�ϵ��жϱ�־λ	
	EXTI_ClearITPendingBit(EXTI_Line12); //���LINE12�ϵ��жϱ�־λ
	EXTI_ClearITPendingBit(EXTI_Line11); //���LINE11�ϵ��жϱ�־λ
}

#endif


/*
*****************************************************************************
* KeyScan - ����ɨ�躯��
* DESCRIPTION: -
* ��4�������Ǹ��а���
* @Param void:
* @Return :�а��� ���ؼ�ֵ �ް��� ����false ��˼�ֵ���岻��Ϊfalse
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
* WaitKey - ����һ����Ч��������
* DESCRIPTION: -
*
* @Param void:
* @Return : ������ֵ
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
