/******************************************************************************
 * MenuFSM.C - �˵���ܺ�FSM(Finite State Machine)����
 *

 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, ���ײ� written
 * --------------------
 ******************************************************************************/

#include "MenuFSM.h"


//FIXME!
//�Ľ��뷨:����ڲ˵��п��Խӹ�������Ч����,�����������ӹ��˷��򰴼�,���ܸ���1--9��Щ���ְ�����תҲ�ǲ���
//����������������Ӧ�ó����еõ�������ȴ����Ҫ��Ӧ�ó����������̼��ѭ��(��ռCPUʱ����,��ʹ��ԭ�п����ڱ������еĳ����޷�ִ��)
/*
*   A>�Ľ�FSM��ŵĻ���,ʹ��ά������,�ܷ��Զ����?������ʹ�����FSM������
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


void (*KeyFuncPtr)(); //��������ָ��

typedef struct{
        U8 KeyStateIndex; //��ǰ״̬������
        U8 KeyEnterState; //����"Enter"��ʱת���״̬������
        U8 KeyBackState; //����"Back"��ʱת���״̬������
        U8 KeyUpState;  //����"UP"��ʱת���״̬������
        U8 KeyDownState;  //����"Down"��ʱת���״̬������
        void (*CurrentOperate)(); //��ǰ״̬Ӧ��ִ�еĹ��ܲ���
} KeyFunctionIndexTableStruct;   //Key function index table
//�����ǲ˵��Ĺؼ�����
//��������庬�� ���ܸĶ�
//��Ϊ�����������
//���µĺ���������Ҳ�����������޸�
/*
********************************************************************************
   FSM�˵�ʵ�ֻ���˵��:
A.һЩԼ��:ֻ��4�����������˵���ת,���ĸ�����Enter/Back/Up/Down ��Ӧ������:ȷ��/����/����/����
B.ÿһ���bar�Ͳ˵���Ҫ���5��״̬(Ҳ����5������)��ʵ��,�ֱ���MenuInit/MenuEnter/MenuBack/MenuUp/MenuDown
��Ӧ�Ĺ��ܽ���:
MenuInit : ��ʼ���˵�/���³�ʼ���˵�,�ڽ���һ����Bar�˵�ʱ,�ú�����Bar��ʾָ���������ָ����Bar����Դ����,
�����Ҫ�Ĳ���:���Ӳ˵����ٸ�Bar��(ItemNum)/ÿ��Bar����ַ�����(Size)/ָ��Bar��ʾ���ݵ�ָ��(DispItem).
����,���ú���BarMenuInit,�ú�����ʼ��ȫ��Bar��ʾ--����ǳ�ʼ���˵�.
�����Ǵ��Ӳ˵�����ʱ,��ô�ڷ���ǰ,Pop����������,���ֲ˵���������ԭ,�ڽ��뱾������,���������ݵõ�������ʾBar��
��ʼ���˵�/���³�ʼ���˵��Ĳ�ͬ������:
��ʼ��ʱ      ������ʾ��λ�����ڶ���,��Ӧѡ�е�ItemҲ���ڶ���
���³�ʼ��ʱ  �����û�ͨ����������/������ѡ��Bar��,����ͨ������ȷ���������Ӳ˵�,Ϊ�����˳��Ӳ˵�ʱ�ܵõ�������
ǰһ�µ���ʾ����,�����Ҫ����һЩ�������:������λ��/ѡ�е�Item/��ǰFSM��Index��  ���˳��Ӳ˵�ʱPop��ԭ��Щ����
������������Щ��ԭ���ݻָ���ʾ.

MenuEnter   : ����Bar��ʾ����ִ�ж�Ӧ��������/������ת��ĳ���Ӳ˵�
MenuBack : �����ϲ�˵� ͨ���Ǽ򵥵���Pop����
MenuUp : ������һ��Bar�� ͨ���ǵ���BarMenuUp����--�ú���ά��Bar����ʾ��FSM״̬����MenunInit,������û�д�Flash/Reflash��,���û��ִ��MenuInit����
MenuDown: ������һ��Bar�� ͨ���ǵ���BarMenuDown����--�ú���ά��Bar����ʾ��FSM״̬����MenunInit,������û�д�Flash/Reflash��,���û��ִ��MenuInit����


********************************************************************************
*/
const KeyFunctionIndexTableStruct KeyTable[]={
//       |-----------> Index
//       |  Enter
//       |  |  Back
//       |  |  |  Up
//       |  |  |  |  Down   --->���ܺ���
//       |  |  |  |  |       |
       { 0, 1, 2, 3, 4,(*DispHomeScreen)},// ��������
       { 1, 0, 0, 0, 0,(*DispHomeScreenEnter)},
       { 2, 0, 0, 0, 0,(*DispHomeScreenBack)},
       { 3, 0, 0, 0, 0,(*DispHomeScreenUp)},
       { 4, 0, 0, 0, 0,(*DispHomeScreenDown)},

       { 5, 6, 7, 8, 9,(*DispIcoMenuInit)}, //ͼ���˵�
       { 6, 0, 0, 0, 0,(*DispIcoMenuEnter)},   //
       { 7, 0, 0, 0, 0,(*DispIcoMenuBack)}, //
       { 8, 0, 0, 0, 0,(*DispIcoMenuUp)}, //
       { 9, 0, 0, 0, 0,(*DispIcoMenuDown)},//

       {10,11,12,13,14,(*DispMenuFuncInit)}, //"����"
       {11, 0, 0, 0, 0,(*DispMenuFuncEnter)},   //
       {12, 0, 0, 0, 0,(*DispMenuFuncBack)}, //
       {13, 0, 0, 0, 0,(*DispMenuFuncUp)}, //
       {14, 0, 0, 0, 0,(*DispMenuFuncDown)},//

       {15,16,17,18,19,(*DispMenuParaInit)}, //"����"
       {16, 0, 0, 0, 0,(*DispMenuParaEnter)},   //
       {17, 0, 0, 0, 0,(*DispMenuParaBack)}, //
       {18, 0, 0, 0, 0,(*DispMenuParaUp)}, //
       {19, 0, 0, 0, 0,(*DispMenuParaDown)},//

       {20,21,22,23,24,(*DispMenuLanguageInit)}, //"����"
       {21, 0, 0, 0, 0,(*DispMenuLanguageEnter)},   //
       {22, 0, 0, 0, 0,(*DispMenuLanguageBack)}, //
       {23, 0, 0, 0, 0,(*DispMenuLanguageUp)}, //
       {24, 0, 0, 0, 0,(*DispMenuLanguageDown)},//


       {25,26,27,28,29,(*DispMenuMeasureInit)}, //"����"
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
* CheckKey - �˵�����ɨ�躯��
* DESCRIPTION: -
* ����Ч������ִ�ж�Ӧ�Ĺ��ܺ���
* ͬʱ,��ˢ�±�־��Ч,Ҳִ����Ӧ�Ĺ��ܺ���
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
		{ //Enter��,�����Ӳ˵�,�ҳ��µĲ˵�״̬���
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyEnterState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//ִ�е�ǰ�����Ĳ���
            break;
        }
        case Key_Back:
		{ //Back��,�ҳ��µĲ˵�״̬���
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyBackState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//ִ�е�ǰ�����Ĳ���
            break;
        }
        case Key_Up:
		{ //Up��,�ҳ��µĲ˵�״̬���
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyUpState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//ִ�е�ǰ�����Ĳ���
            break;
        }
        case Key_Down:
		{ //Down��,�ҳ��µĲ˵�״̬���
            KeyFuncIndex=KeyTable[KeyFuncIndex].KeyDownState;
            KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
            (*KeyFuncPtr)();//ִ�е�ǰ�����Ĳ���
            break;
        }
//---------------------------------------------------------------------------
#ifdef DigiKeyLink
/*
2006/09/08
���ּ�����ݷ�ʽ����
1.�б����ּ�ֵ�Ƿ�С��ItemNum-1 ��������Ч��ݷ�ʽ
2.��Ч��ݷ�ʽ�£��Ѽ�ֵ��Item������Key_Up�Ĵ������
3.��Ҫ��ӳ�ʱ������ʱ�˾Ͳ���ʹ�ã�����Ҫô������Ҫô����
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
				{//�����Ҫ��ʾ����ȿ�����ʾ�����٣���ô����Where ����Ĭ��WhereΪ0
                    Where = Item;
                }
				else
				{
                    Where = 0;
                }
                //-------------------------------------------------
                KeyFuncIndex=KeyTable[KeyFuncIndex].KeyEnterState;
                KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
                (*KeyFuncPtr)();//ִ�е�ǰ�����Ĳ���
                //-------------------------------------------------
            }
			else 
			{
                IsKey = 0;
            }
            break;
#endif
//---------------------------------------------------------------------------
        default: //��������Ĵ���
            IsKey = 0;
            break;
    }

    if(Refresh)
	{//��������������һ����Ϊ�㣬��ôִ��һ�Σ�����Ӧ�ò������Flash��Refresh����1�����
        KeyFuncPtr=KeyTable[KeyFuncIndex].CurrentOperate;
        (*KeyFuncPtr)();//ִ�е�ǰ�����Ĳ���
        Refresh = 0;
       // BackRefresh = 0;
     }

    return IsKey;
}

