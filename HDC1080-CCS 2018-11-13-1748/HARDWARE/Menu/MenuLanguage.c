/******************************************************************************
 * MenuLanguage.C - �����л�ģ��
 *
 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, ���ײ� written
 * --------------------
 ******************************************************************************/

#include "MenuLanguage.h"

/*
�����������л����棬����Ҳ��ʾ�����ͨ����ǰ�޸�Item Where
void DispMenuLanguageInit()�����У�
����������������������������������������������������������
    if(Flash == FlashMode_ManualInit)
		{//�״ν��뱾��˵�������Item where
        PUSH();
        Item = language;
        Where = Item;
    }
����������������������������������������������������������

*/
//����
//Bar�Ͳ˵�
void DispMenuLanguageInit(void)
{
//----------------------
    GUI_Clear();
//--------------------
    //�л�Bar��ʾ����
//-----------------
//  BarMenu = &MenuLanguage[language];
	  BarMenu = (struct Menu *)&MenuLanguage[language];
    ItemNum = (*BarMenu).TextNum;
    DispItem = (*BarMenu).Text;

    //�û��ĳ�ʼ���������������
    //��ʾ���˵�����

    //��ʾ������ʾ          2-->OK
//    GUI_DispStringAt(Tip[language].Text+2*(Tip[language].TextLen),Enter_PosX,Enter_PosY);
    GUI_DispStringAtBar(*(Tip[language].Text+2),0,Enter_PosY,126,GUI_TA_HCENTER);
    if(Refresh == FlashMode_ManualInit)
		{//�״ν��뱾��˵�������Item where
        PUSH();
        Item = language;
        Where = Item;
    }
    //������ʼ������
    BarMenuInit();
}
/*
************************************************************
*   FIXME!
*   �������������л���
*   ���������һ������˼������:
*   ���ǵĲ˵���������Ǳ��ݹ�ȥ�ĸ��˵���Text����Ϣ��,��˼����Ǹ���������,
*   ����������Ϣ��Ȼû�б�����,����˵,�������л����Ժ�,��ʾ�ĸ���������û�б�
*   ��������:
*   ͨ�������л��ĵط���һ��·������,��˸������Ժ���ȷ�޸ı������Ϣ...
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






