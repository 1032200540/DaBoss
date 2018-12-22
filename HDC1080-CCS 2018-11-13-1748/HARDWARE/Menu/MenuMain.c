/******************************************************************************
 * MenuMain.C - 菜单主循环函数
 *
 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, 梁炎昌 written
 * --------------------
 ******************************************************************************/

#include "MenuMain.h"
#include "stm32f10x_dma.h"

u8 temp_DHT11 = 0; //DHT11温度值
u8 huimi_DHT11 = 0; //DHT11湿度值
long int temp_18B20 = 0;//18b20温度值

/*
*****************************************************************************
* MenuMainLoop - 菜单主循环
* DESCRIPTION: -
* Main函数调用该函数,本函数并不会返回
* @Para void:
* Return :
*
*****************************************************************************
*/
void MenuMainLoop(void)
{
    DispHomeScreen();	 
    while(1)
	{ 
		#if !(EXTIX_IO)
        if(CheckKey())
		{//检查菜单
            delay_ms(20);
        }
		#endif
		
        if(!KeyFuncIndex) //KeyFuncIndex为0时是待机界面
		{ //待机界面代码
			GUI_DispStringAt("temp1:",4,4);
			temp_18B20 = DS18B20_Get_Temp();
			Display_SignedDecimal(temp_18B20, 48, 4, 3, 1);	
			
			GUI_DispStringAt("huimi:",4,6);
			GUI_DispStringAt("temp2:",4,8);
			Average_DHI11_Temp_Huimi(1,&temp_DHT11,&huimi_DHT11);
			Display_Number((u16)huimi_DHT11,55,6,3);
			Display_Number((u16)temp_DHT11,55,8,3);
			
			SendDisplay();
		}
		else{}
	}
}	

/*
如何实现中断中使用LCD?
1.中断发送消息，在上面的循环当中不断检查消息，根据消息显示。比如充电器插入后，发送了消息，
那么即便是我们原本已经在了某层菜单，当我们检查到消息后，我们PUSH当前菜单，根据消息显示提
示，而后POP，回到原来菜单。但是若是我原来已经在消息编辑状态，它又是如何工作？似乎不行
2.有显示缓冲区，中断时去使用液晶不修改缓冲区，结束后重新显示缓冲
2006/08/20  依然认为应当的实现方式是1的方法，通常在有OS的环境下，可以通过消息传递，而显示
仅仅在一个任务当中
3.2006/10/16 另外的方法是窗口切换：1。在内存中有两个显存缓冲，切换缓冲到液晶。2。利用LCD内
部自带的显存，切换显示开始地址（前提是LCD缓存足够做两个显存）
*/
