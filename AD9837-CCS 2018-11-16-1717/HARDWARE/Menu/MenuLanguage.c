/******************************************************************************
 * MenuLanguage.C - 语言切换模版
 *
 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, 梁炎昌 written
 * --------------------
 ******************************************************************************/

#include "MenuLanguage.h"

/*
这里是语言切换界面，这里也演示了如何通过提前修改Item Where
void DispMenuLanguageInit()函数中：
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
    if(Flash == FlashMode_ManualInit)
		{//首次进入本层菜单，调整Item where
        PUSH();
        Item = language;
        Where = Item;
    }
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

*/
//语言
//Bar型菜单
void DispMenuLanguageInit(void)
{
//----------------------
    GUI_Clear();
//--------------------
    //切换Bar显示内容
//-----------------
//  BarMenu = &MenuLanguage[language];
	  BarMenu = (struct Menu *)&MenuLanguage[language];
    ItemNum = (*BarMenu).TextNum;
    DispItem = (*BarMenu).Text;

    //用户的初始化代码请放在这里
    //显示父菜单名字

    //显示按键提示          2-->OK
//    GUI_DispStringAt(Tip[language].Text+2*(Tip[language].TextLen),Enter_PosX,Enter_PosY);
    GUI_DispStringAtBar(*(Tip[language].Text+2),0,Enter_PosY,126,GUI_TA_HCENTER);
    if(Refresh == FlashMode_ManualInit)
		{//首次进入本层菜单，调整Item where
        PUSH();
        Item = language;
        Where = Item;
    }
    //公共初始化部分
    BarMenuInit();
}
/*
************************************************************
*   FIXME!
*   这里是做语言切换的
*   但是这会有一个有意思的问题:
*   我们的菜单保存机制是备份过去的父菜单的Text等信息的,因此即便是更换了语言,
*   这个保存的信息依然没有被更换,就是说,在这里切换语言后,显示的父索引还是没有变
*   改正方法:
*   通常语言切换的地方就一个路径而已,因此更换语言后正确修改保存的信息...
************************************************************
*/
void DispMenuLanguageEnter(void)
{
//-----------
    PUSH();//
//-------------------
    GUI_Clear();
    if(Item==0)
	{
        language = CN;
        delay_ms(1);
    }
	else if(Item==1)
	{
        language = EN;
        delay_ms(1);
    }
    GUI_Clear();
//-------------------
    POP();
//-------------------

}

void DispMenuLanguageBack(void)
{
    POP();
}

void DispMenuLanguageUp(void)
{
    BarMenuUp();
}

void DispMenuLanguageDown(void)
{
    BarMenuDown();
}






