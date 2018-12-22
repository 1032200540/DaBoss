/******************************************************************************
 * MenuFSM.C - 菜单框架和FSM(Finite State Machine)代码
 *

 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, 梁炎昌 written
 * --------------------
 ******************************************************************************/

#include "MenuFSM.h"


//FIXME!
//改进想法:如何在菜单中可以接管其它有效按键,这里程序仅仅接管了方向按键,若能根据1--9这些数字按键跳转也是不错
//额外的问题是如何在应用程序中得到按键而却不需要在应用程序中做键盘检查循环(抢占CPU时间了,会使得原有可以在背景运行的程序无法执行)
/*
*   A>改进FSM编号的机制,使得维护更简单,能否自动编号?这样会使得添加FSM表容易
*   B>
*
*
*/
//-----------------------------------
/*//MenuTop.C
void DispHomeScreen(void);
void DispHomeScreenEnter(void);
void DispHomeScreenBack(void);
void DispHomeScreenUp(void);
void DispHomeScreenDown(void);

void DispIcoMenuInit(void);
void DispIcoMenuEnter(void);
void DispIcoMenuBack(void);
void DispIcoMenuUp(void);
void DispIcoMenuDown(void);

//MenuFunc.C
void DispMenuFuncInit(void);
void DispMenuFuncEnter(void);
void DispMenuFuncBack(void);
void DispMenuFuncUp(void);
void DispMenuFuncDown(void);
//MenuPara.C
void DispMenuParaInit(void);
void DispMenuParaEnter(void);
void DispMenuParaBack(void);
void DispMenuParaUp(void);
void DispMenuParaDown(void);
//MenuLanguage.C
void DispMenuLanguageInit(void);
void DispMenuLanguageEnter(void);
void DispMenuLanguageBack(void);
void DispMenuLanguageUp(void);
void DispMenuLanguageDown(void);

//MenuMeasure.C
void DispMenuMeasureInit(void);
void DispMenuMeasureEnter(void);
void DispMenuMeasureBack(void);
void DispMenuMeasureUp(void);
void DispMenuMeasureDown(void);

#ifdef DynamicBar
//MenuFunc.C
void DispMenuDataInit(void);
void DispMenuDataEnter(void);
void DispMenuDataBack(void);
void DispMenuDataUp(void);
void DispMenuDataDown(void);
#endif
//----------------------------------- */


void (*KeyFuncPtr)(); //按键功能指针

typedef struct{
        U8 KeyStateIndex; //当前状态索引号
        U8 KeyEnterState; //按下"Enter"键时转向的状态索引号
        U8 KeyBackState; //按下"Back"键时转向的状态索引号
        U8 KeyUpState;  //按下"UP"键时转向的状态索引号
        U8 KeyDownState;  //按下"Down"键时转向的状态索引号
        void (*CurrentOperate)(); //当前状态应该执行的功能操作
} KeyFunctionIndexTableStruct;   //Key function index table
//如下是菜单的关键代码
//不清楚具体含义 不能改动
//因为跟编译器相关
//如下的函数的名称也不可以轻易修改
/*
********************************************************************************
   FSM菜单实现机制说明:
A.一些约定:只有4个按键来做菜单周转,这四个按键Enter/Back/Up/Down 对应功能是:确认/回退/向上/向下
B.每一层的bar型菜单需要大概5个状态(也就是5个函数)来实现,分别是MenuInit/MenuEnter/MenuBack/MenuUp/MenuDown
对应的功能解释:
MenuInit : 初始化菜单/重新初始化菜单,在进入一个子Bar菜单时,该函数把Bar显示指针根据语言指向子Bar的资源数组,
获得需要的参数:该子菜单多少个Bar项(ItemNum)/每个Bar项的字符长度(Size)/指向Bar显示内容的指针(DispItem).
而后,调用函数BarMenuInit,该函数初始化全部Bar显示--这就是初始化菜单.
若是是从子菜单返回时,那么在返回前,Pop函数被调用,各种菜单参数被还原,在进入本函数后,本函数根据得到参数显示Bar项
初始化菜单/重新初始化菜单的不同点在于:
初始化时      高亮显示的位置是在顶部,对应选中的Item也是在顶部
重新初始化时  由于用户通过按键向上/向下来选择Bar项,而后通过按键确认来进入子菜单,为了在退出子菜单时能得到跟进入
前一致的显示内容,因此需要备份一些相关数据:高亮的位置/选中的Item/当前FSM的Index号  在退出子菜单时Pop还原这些数据
本函数根据这些还原数据恢复显示.

MenuEnter   : 根据Bar显示内容执行对应动作函数/或者周转到某层子菜单
MenuBack : 返回上层菜单 通常是简单调用Pop函数
MenuUp : 移至上一个Bar项 通常是调用BarMenuUp函数--该函数维护Bar的显示后FSM状态返回MenunInit,但由于没有打开Flash/Reflash项,因此没有执行MenuInit函数
MenuDown: 移至下一个Bar项 通常是调用BarMenuDown函数--该函数维护Bar的显示后FSM状态返回MenunInit,但由于没有打开Flash/Reflash项,因此没有执行MenuInit函数


********************************************************************************
*/
const KeyFunctionIndexTableStruct KeyTable[]={
//       |-----------> Index
//       |  Enter
//       |  |  Back
//       |  |  |  Up
//       |  |  |  |  Down   --->功能函数
//       |  |  |  |  |       |
       { 0, 1, 2, 3, 4,(*DispHomeScreen)},// 待机画面
       { 1, 0, 0, 0, 0,(*DispHomeScreenEnter)},
       { 2, 0, 0, 0, 0,(*DispHomeScreenBack)},
       { 3, 0, 0, 0, 0,(*DispHomeScreenUp)},
       { 4, 0, 0, 0, 0,(*DispHomeScreenDown)},

       { 5, 6, 7, 8, 9,(*DispIcoMenuInit)}, //图标层菜单
       { 6, 0, 0, 0, 0,(*DispIcoMenuEnter)},   //
       { 7, 0, 0, 0, 0,(*DispIcoMenuBack)}, //
       { 8, 0, 0, 0, 0,(*DispIcoMenuUp)}, //
       { 9, 0, 0, 0, 0,(*DispIcoMenuDown)},//

       {10,11,12,13,14,(*DispMenuFuncInit)}, //"功能"
       {11, 0, 0, 0, 0,(*DispMenuFuncEnter)},   //
       {12, 0, 0, 0, 0,(*DispMenuFuncBack)}, //
       {13, 0, 0, 0, 0,(*DispMenuFuncUp)}, //
       {14, 0, 0, 0, 0,(*DispMenuFuncDown)},//

       {15,16,17,18,19,(*DispMenuParaInit)}, //"参数"
       {16, 0, 0, 0, 0,(*DispMenuParaEnter)},   //
       {17, 0, 0, 0, 0,(*DispMenuParaBack)}, //
       {18, 0, 0, 0, 0,(*DispMenuParaUp)}, //
       {19, 0, 0, 0, 0,(*DispMenuParaDown)},//

       {20,21,22,23,24,(*DispMenuLanguageInit)}, //"语言"
       {21, 0, 0, 0, 0,(*DispMenuLanguageEnter)},   //
       {22, 0, 0, 0, 0,(*DispMenuLanguageBack)}, //
       {23, 0, 0, 0, 0,(*DispMenuLanguageUp)}, //
       {24, 0, 0, 0, 0,(*DispMenuLanguageDown)},//


       {25,26,27,28,29,(*DispMenuMeasureInit)}, //"测量"
       {26, 0, 0, 0, 0,(*DispMenuMeasureEnter)},   //
       {27, 0, 0, 0, 0,(*DispMenuMeasureBack)}, //
       {28, 0, 0, 0, 0,(*DispMenuMeasureUp)}, //
       {29, 0, 0, 0, 0,(*DispMenuMeasureDown)},//
#ifdef DynamicBar
       {30,31,32,33,34,(*DispMenuDataInit)}, //"Data"
       {31, 0, 0, 0, 0,(*DispMenuDataEnter)},   //
       {32, 0, 0, 0, 0,(*DispMenuDataBack)}, //
       {33, 0, 0, 0, 0,(*DispMenuDataUp)}, //
       {34, 0, 0, 0, 0,(*DispMenuDataDown)},//
#endif

}; 

/*
*****************************************************************************
* CheckKey - 菜单键盘扫描函数
* DESCRIPTION: -
* 有有效按键则执行对应的功能函数
* 同时,若刷新标志有效,也执行相应的功能函数
* @Para void:
* Return :
*
*****************************************************************************
*/
U8 CheckKey(void)
{
    u8 IsKey;
    u8 Key;
    IsKey = 1;
    Key = KeyScan();
    switch(Key)
	{
        case Key_Enter:
		{ //Enter键,进入子菜单,找出新的菜单状态编号
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyEnterState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//执行当前按键的操作
            break;
        }
        case Key_Back:
		{ //Back键,找出新的菜单状态编号
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyBackState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//执行当前按键的操作
            break;
        }
        case Key_Up:
		{ //Up键,找出新的菜单状态编号
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyUpState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//执行当前按键的操作
            break;
        }
        case Key_Down:
		{ //Down键,找出新的菜单状态编号
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyDownState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//执行当前按键的操作
            break;
        }
//---------------------------------------------------------------------------
#ifdef DigiKeyLink
/*
2006/09/08
数字键做快捷方式输入
1.判别数字键值是否小于ItemNum-1 否则是无效快捷方式
2.有效快捷方式下，把键值给Item，调用Key_Up的处理代码
3.需要添加超时处理，超时了就不能使用？（需要么？不需要么？）
*/
        case Key_1:
        case Key_2:
        case Key_3:
        case Key_4:
        case Key_5:
        case Key_6:
        case Key_7:
        case Key_8:
        case Key_9:
            Key = chang_code(Key);
            if((Key - '1') <= ItemNum-1)
			{
                Item = Key - '1';
                if(ItemNum <= DispMax)
				{//如果需要显示的项比可以显示的项少，那么修正Where 否则默认Where为0
                    Where = Item;
                }
				else
				{
                    Where = 0;
                }
                //-------------------------------------------------
                KeyFuncIndex=KeyTable[KeyFuncIndex].KeyEnterState;
                KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
                (*KeyFuncPtr)();//执行当前按键的操作
                //-------------------------------------------------
            }
			else 
			{
                IsKey = 0;
            }
            break;
#endif
//---------------------------------------------------------------------------
        default: //按键错误的处理
            IsKey = 0;
            break;
    }

    if(Refresh)
	{//两个当中有任意一个不为零，那么执行一次，我们应该不会出现Flash和Refresh都是1的情况
        KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
        (*KeyFuncPtr)();//执行当前按键的操作
        Refresh = 0;
       // BackRefresh = 0;
     }

    return IsKey;
}

