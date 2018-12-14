/******************************************************************************
 * MenuPara.C - "����"�˵�  �˵�����ʹ��ģ��
 *
 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, ���ײ� written
 * --------------------
 ******************************************************************************/

#include "MenuPara.h"

//����
void DispMenuParaInit()
{
//----------------------
    GUI_Clear();
//--------------------
    //�л�Bar��ʾ����
//---------------------
//  BarMenu = &MenuPara[language];
	BarMenu = (struct Menu *)&MenuPara[language];
    ItemNum = (*BarMenu).TextNum;
    DispItem = (*BarMenu).Text;

    //�û��ĳ�ʼ���������������
    //��ʾ������Ӧ��������ʾ,1-->"����"
    GUI_DispStringAtBar(*(Tip[language].Text+1),0,Enter_PosY,126,GUI_TA_HCENTER);
    //������ʼ������
    BarMenuInit();
}

/*
*****************************************************************************
�˵�ʹ������
0.Jump2Menu + FlashMode_AutoInit/FlashMode_ManualInit
  ��ת������˵�,FlashMode_AutoInit-->��BarMenuInit������ִ��PUSH;
  FlashMode_ManualInit-->�Ӳ˵���Init������PUSH,������:DispMenuLanguageInit
1.PUSH + POP
  ִ��һЩ����,��ʹ��LCD��,�ص�ԭ�н���,�ص�ԭ�н���--��������λ�ö��ָ�
2.Jump2Menu(SelfMenuIndex,FlashMode_ReFlash);
  ִ��һЩ����,��ʹ��LCD��,ִ�����ϵ���,�ص�ԭ�н���--��������λ�ö��ָ�
3.POP
  ִ��һЩ����,��ʹ��LCD��,�ص��ϲ�˵�,�ָ��ϲ����
4.Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
  ִ��һ�����ܺ�,����ռ��LCD�Ļ�,ֱ�ӽ��治��

*****************************************************************************
*/
void DispMenuParaEnter()
{
    switch(Item){
        case 0:{//Jump2Menu
            GUI_Clear();
            GUI_DispStringAt("Do Something \nthen Back to \nTop Menu!",0,0);
            delay_ms(10);
            Jump2Menu(MenuTopIndex,FlashMode_AutoInit);
            break;
        }
        case 1:{//PUSH  -->POP
            PUSH();
            GUI_Clear();
            GUI_DispStringAt("Do Something \nthen Back to \nThis Menu!",0,0);
            delay_ms(10);
            POP();
            break;
        }
        case 2:{//BackRefresh = 1
            GUI_Clear();
            GUI_DispStringAt("Do Something \nthen Back to \nThis Menu!",0,0);
            delay_ms(10);
            Jump2Menu(SelfMenuIndex,FlashMode_ReFlash);
            break;
        }
        case 3:{//POP
            GUI_Clear();
            GUI_DispStringAt("Do Something \nthen Back to \nFather Menu!",0,0);
            delay_ms(10);
            POP();
            break;
        }
        case 4:{//No BackRefresh
            //No Action Here!
            //Or The Action no need the LCD Disp
            Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
            break;
        }
        default:{
            Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
            return;
        }
    }
}
void DispMenuParaBack()
{
    POP();
}

void DispMenuParaUp()
{
    BarMenuUp();
}
void DispMenuParaDown()
{
    BarMenuDown();
}




