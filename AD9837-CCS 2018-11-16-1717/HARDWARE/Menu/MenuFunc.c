/******************************************************************************
 * MenuFunc.C - "����"�˵� ���̬���ɴ���
 *
 *
 * DESCRIPTION: -
 *
 * modification history
 * --------------------
 * 01a, 04/sep/2007, ���ײ� written
 * --------------------
 ******************************************************************************/

#include "MenuFunc.h"

//����
//Bar�Ͳ˵�
void DispMenuFuncInit(void)
{
//--------------------
    GUI_Clear();
//--------------------
//  BarMenu = &MenuFunc[language];
	BarMenu = (struct Menu *)&MenuFunc[language];
    ItemNum = (*BarMenu).TextNum;
    DispItem = (*BarMenu).Text;

    //��ʾ������Ӧ��������ʾ,1-->"����"
    GUI_DispStringAtBar(*(Tip[language].Text+1),0,Enter_PosY,126,GUI_TA_HCENTER);

    //�û�����ĳ�ʼ���������������
    BarMenuInit();//���ù�����ʼ���Ĵ���
}

void DispMenuFuncEnter(void)
{

    switch(Item){
        case 0:{
#ifdef  DynamicBar
            Jump2Menu(MenuDataIndex,FlashMode_AutoInit);
#else
            Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
#endif                        

            break;
        }
        case 1:{
            Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
            break;
        }
        default:{
            Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
            break;
        }
    }

}
void DispMenuFuncBack(void)
{
    POP();
}

void DispMenuFuncUp(void)
{
    BarMenuUp();
}
void DispMenuFuncDown(void)
{
    BarMenuDown();
}





#ifdef DynamicBar


//------------------------------------------------
#define DataItemSize 8
U8 DataItem[DispMax][DataItemSize]=
{
	{"DataX  "},
	{"DataX  "},
	{"DataX  "},
};


U8 *constDataItem_p[]=
{
	DataItem[0],
	DataItem[1],
	DataItem[2]
};


U8 DynamicItem;
U8 MaxDynamicItem = 0;

/*
ʵ�ֶ�̬������ʾ����򵥵ķ�ʽ�趨һ����С�Ļ��壬����������ݣ��������ѿ�����ʾ���������ˡ������������ά����˵����Ϊ�򵥵�
2006/08/27
����������޻�����ʵ�ֶ�̬���ݵ��������ʾ��
�����������Һ��������ʾ��������Ŀ��Ȼ������/��Խ���ˣ���ˢ�»��壿
��������Ҫ��������д����BarMenuUp�Ⱥ�����ά����ʾ
*/
/*
����ʹ��һ��������LCD��ʾ������Ŀһ�µĻ����������嶯̬���ɵ�����
��ʵ��������ĿMaxDynamicItem<=DispMaxʱ ����BarMenuUp BarMenuDown��������
����MaxDynamicItem>DispMaxʱ��������ItemNum = DispMax����ԭ���Ĵ����У�����ζ��LCD�ո�����ʾ���е���
����һ�����˶����Ϸ�ʱ�ͷ��Եײ������˵ײ��·�ʱ�ͷ��Զ��� ������ʵ�ϵ������Ŀ����ItemNum!����MaxDynamicItem
������������Ϊ�Ƕ����Ϸ�ʱ���޸ĵײ�����Ϊ�µ�������ݣ���Ļ����ˢ��(�ײ��·�����)
��������ItemNum = DispMax �������·�����Ϊ�� ItemNum > DispMaxʱ����Ϊһ�£�����λ�ö�̬�޸���ʾ����
*/
void DispMenuDataInit(void)
{
    U8 Menu_j;          //��������
    U8 *ChangeDispItem; //����ʾ����ָ��
//----------------------
    GUI_Clear();
//--------------------
    GUI_Delay(100);
//    do{
//        MaxDynamicItem = InputNum(4,4,9);//Ҫ������һ����̬�˵���ֵ,���Ǹ������ֵ���ɲ˵�
        MaxDynamicItem = 8;
//        if(MaxDynamicItem == 0xFF){//�˳�
//            Jump2Menu(SelfMenuIndex,FlashMode_AutoInit);
// //           BackRefresh = true;
//            return;
//        }
//    }while(MaxDynamicItem ==0x00);//����0����Ч

//    GUI_Clear();
    DynamicItem = 0;

    if(MaxDynamicItem >DispMax){//��Ҫ��ʾ��������Һ��������ʾ�Ķ�
        ItemNum = DispMax;
        //08/29
        BarDataMode = DynamicData;//֪ͨBarMenuUp��BarMenuDown�������ڵ������Ƕ�̬����
        //��ItemNum == DispMaxʱ��Ĭ�ϵ���ʾ��ʽ�ǵ�ͷ��ֱ������β����(��β����ֱ������ͷ����)
        //���Ǽ�Ȼ���Ƕ�̬���ݵĻ�������ʵ���ϵ�����MaxDynamicItem������DispMax��Ӧ��������ʾ�ģ�ͨ������BarDataMode�����־
        //֪ͨBarMenuUp��BarMenuDown
    } else {
        ItemNum = MaxDynamicItem;
    }


    for(Menu_j = 0;Menu_j < ItemNum; Menu_j++){//��ʼ����̬����
       ChangeDispItem = (U8 *)&DataItem[Menu_j];
        *(ChangeDispItem + 4) = Menu_j+'0';
//        *(DataItem_p[Menu_j]+4)       = Menu_j+'0';
    }


    DispItem = (U8 **)DataItem_p;


    //��ʾ������Ӧ��������ʾ,2-->"OK"
    GUI_DispStringAtBar(*(Tip[language].Text+1),0,Enter_PosY,126,GUI_TA_HCENTER);
    BarMenuInit();
    Bar(DynamicItem,MaxDynamicItem,MenuBarPosX,MenuBarNumPosX);                  //ά��������
}

void DispMenuDataEnter(void)
{
    //û�ж�����ͣ���ڱ���˵�
    Jump2Menu(SelfMenuIndex,FlashMode_NoAction);
}
void DispMenuDataBack(void)
{
    //08/29
    BarDataMode = FixedData;
    POP();
}

void DispMenuDataUp(void)
{
    U8 *ChangeDispItem; //����ʾ����ָ��
    U8 ItemBackup;
    if(DynamicItem == 0){//
        DynamicItem = MaxDynamicItem-1;
    } else {
        DynamicItem--;
    }

    if(Where == 0){//�������ƣ���Ҫ�޸�����
        if (Item == 0) {//���Item
            ItemBackup = ItemNum-1;
        } else {
            ItemBackup = Item-1;
        }
        ChangeDispItem = (U8*)&DataItem[ItemBackup];
        *(ChangeDispItem + 4) = DynamicItem+'0';
    }
    BarMenuUp();//

    Bar(DynamicItem,MaxDynamicItem,MenuBarPosX,MenuBarNumPosX);                  //ά��������
}
void DispMenuDataDown(void)
{
    U8 *ChangeDispItem; //����ʾ����ָ��
    U8 ItemBackup;
    if(DynamicItem == MaxDynamicItem-1){//ά��ʵ�ʵ�Itemֵ
        DynamicItem = 0;
    } else {
        DynamicItem++;
    }

    if(Where == (DispMin-1)){//�ײ����ƣ���Ҫ�޸�����
        if (Item == (ItemNum-1)) {//���Item
            ItemBackup = 0;
        } else {
            ItemBackup = Item + 1;
        }
        ChangeDispItem = (U8*)&DataItem[ItemBackup];//����޸�λ��
        *(ChangeDispItem + 4) = DynamicItem+'0';
    }
    BarMenuDown();
    Bar(DynamicItem,MaxDynamicItem,MenuBarPosX,MenuBarNumPosX);                  //ά��������
}
#endif

